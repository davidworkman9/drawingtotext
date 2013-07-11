#include "InputFormatDXF.h"

InputFormatDXF::InputFormatDXF(const char * inputFilename) {
	// Get the insertions / blocks - so that we know what offsets to use as we encounter these blocks:
	DL_Dxf * fetchInsertions = new DL_Dxf();
	this->insertionReceiver = new GetInsertions();
	if (!fetchInsertions->in(inputFilename, this->insertionReceiver)) {
		fprintf(stderr, "Could not retrieve insertion blocks from input file.\n");
		delete fetchInsertions;
		exit(1);
	}
	delete fetchInsertions;
	fetchInsertions = NULL;

	this->filename = new char[strlen(inputFilename)];
	strcpy(this->filename, inputFilename);

	this->currentBlockX = 0;
	this->currentBlockY = 0;
}

void InputFormatDXF::finishPendingPolyline() {
	if (this->pendingPolyline.empty()) return;

	this->output->addPolyLine(this->pendingPolyline);
	for (int i = 0; i < this->pendingPolyline.size(); i++) delete this->pendingPolyline[i];
	this->pendingPolyline.clear();
}

void InputFormatDXF::readFeaturesInto(OutputFormat * outputHandler) {
	// Pull in actual data now...
	this->output = outputHandler;
	DL_Dxf * getData = new DL_Dxf();
	if (!getData->in(this->filename, this)) {
		fprintf(stderr, "Could not retrieve data from input file.\n");
		delete getData;
		exit(1);
	}	

	// Clean up any hanging polylines:
	this->finishPendingPolyline();

	if (this->filename) {
		delete this->filename;
		this->filename = NULL;
	}
	
	if (this->insertionReceiver) {
		delete this->insertionReceiver;
		this->insertionReceiver = NULL;
	}
	
	// Don't delete output format - caller can do that
	this->output = NULL;

	delete getData;
}

void InputFormatDXF::addPoint(const DL_PointData& data) {
	OutputFeaturePoint * newPoint = new OutputFeaturePoint(data.x + this->currentBlockX, data.y + this->currentBlockY, data.z);
	this->output->addPoint(*newPoint);
	delete newPoint;
}

void InputFormatDXF::addLine(const DL_LineData& data) {
	OutputFeatureLine * newLine = new OutputFeatureLine(data.x1 + this->currentBlockX, data.y1 + this->currentBlockY, data.z1, data.x2 + this->currentBlockX, data.y2 + this->currentBlockY, data.z2);
	this->output->addLine(*newLine);
	delete newLine;
}

void InputFormatDXF::addArc(const DL_ArcData& data) {
	double pi = 3.1415926535897932384626433832795;
	int fromAngle = (int) data.angle1 + 1;
	int toAngle = (int) data.angle2 + 1;
	
	// Approximate the arc with 500 points
	const int approximationCount = 500;
	std::vector<OutputFeaturePoint *> points;
	register int i = 0;
	register double radianMeasure;
	register double deg2radFactor = (pi / 180);
	for (i = fromAngle; ; i++) {
		if (i > 360) i = 0;
		if (points.size() > approximationCount) break;

		radianMeasure = i * deg2radFactor;
		points.push_back(new OutputFeaturePoint(data.radius * cos(radianMeasure) + data.cx + this->currentBlockX, data.radius * sin(radianMeasure) + data.cy + this->currentBlockY, data.cz));
	}

	this->output->addPolyLine(points);

	for (i = 0; i < approximationCount; i++) delete points[i];
}

void InputFormatDXF::addCircle(const DL_CircleData& data) {
	// Approximate the circle with 360 line segments connecting points along that circle
	register double pi = 3.1415926535897932384626433832795;
	register double increment = ((2 * pi ) / 360);
	register double i = 0;

	std::vector<OutputFeaturePoint *> points;
	for (; i <= 2 * pi; i += increment) {
		points.push_back(new OutputFeaturePoint(data.radius * cos(i) + data.cx + this->currentBlockX, data.radius * sin(i) + data.cy + this->currentBlockY, data.cz));
	}

	this->output->addPolyLine(points);

	for (int q = 0; q < 360; q++) delete points[q];
}

void InputFormatDXF::addPolyline(const DL_PolylineData& data) {
	// Just clear out any old one to make way:
	this->finishPendingPolyline();
}

void InputFormatDXF::addVertex(const DL_VertexData& data) {
	OutputFeaturePoint * pt = new OutputFeaturePoint(data.x + this->currentBlockX, data.y + this->currentBlockY, data.z);
	this->pendingPolyline.push_back(pt);
	// Do not delete - pendingPolyline vector holds reference
}

void InputFormatDXF::addBlock(const DL_BlockData& data) {
	if (data.name.compare("ADCADD_ZZ") == 0) return; // Ignore this particular block - meaningless

	for (int i = 0; i < this->insertionReceiver->countInserts; i++) {
		if (strcmp(this->insertionReceiver->Names[i].c_str(), data.name.c_str()) == 0) {
			this->currentBlockX = this->insertionReceiver->XVals[i];
			this->currentBlockY = this->insertionReceiver->YVals[i];
		}
	}
}

std::string replaceAll( std::string const& original, std::string const& before, std::string const& after ) {
    std::string retval;
    std::string::const_iterator end     = original.end();
    std::string::const_iterator current = original.begin();
    std::string::const_iterator next    = std::search( current, end, before.begin(), before.end() );
    while ( next != end ) {
        retval.append( current, next );
        retval.append( after );
        current = next + before.size();
        next = std::search( current, end, before.begin(), before.end() );
    }
    retval.append( current, next );
    return retval;
}

void InputFormatDXF::addMTextChunk(const char * text) {
	OutputFeaturePoint * newPoint = new OutputFeaturePoint();
	std::string textstr = replaceAll(std::string(text), "\\P", " ");
	this->output->addText(*newPoint, textstr.c_str());
	delete newPoint;
}

void InputFormatDXF::addMText(const DL_MTextData& data) {
	OutputFeaturePoint * newPoint = new OutputFeaturePoint();
	std::string text = replaceAll(data.text, "\\P", " ");
	this->output->addText(*newPoint, text.c_str());
	delete newPoint;
}

void InputFormatDXF::addText(const DL_TextData& data) {
	OutputFeaturePoint * newPoint = new OutputFeaturePoint();
	this->output->addText(*newPoint, data.text.c_str());
	delete newPoint;
}

void InputFormatDXF::endBlock() {
	this->finishPendingPolyline();
	this->currentBlockX = 0;
	this->currentBlockY = 0;
}

void InputFormatDXF::endEntity() {
	this->finishPendingPolyline();
}
