#include "OutputFormatTypes.h"
#include "OutputFormatText.h"

void OutputFormatText::addPoint(OutputFeaturePoint newPoint) {
	// if (!this->outputFile) {
	// 	fprintf(stderr, "No output file is open for writing.");
	// 	return;
	// }
	
	// fprintf(this->outputFile, "POINT at (%f,%f)\n", newPoint.get_X(), newPoint.get_Y());
}

void OutputFormatText::addLine(OutputFeatureLine newLine) {
	// if (!this->outputFile) {
	// 	fprintf(stderr, "No output file is open for writing.");
	// 	return;
	// }

	// fprintf(this->outputFile, "LINE from (%f,%f) to (%f,%f)\n", newLine.get_X1(), newLine.get_Y1(), newLine.get_X2(), newLine.get_Y2());
}

void OutputFormatText::addPolyLine(std::vector<OutputFeaturePoint *> newPoints) {
	// if (!this->outputFile) {
	// 	fprintf(stderr, "No output file is open for writing.");
	// 	return;
	// }

	// fprintf(this->outputFile, "Polyline with Points:");
	// for (int i = 0; i < newPoints.size(); i++) {
	// 	fprintf(this->outputFile, " (%f,%f)", newPoints[i]->get_X(), newPoints[i]->get_Y());
	// }
	// fprintf(this->outputFile, "\n");
}

void OutputFormatText::addPolygon(std::vector<OutputFeaturePoint *> newPoints) {
	// if (!this->outputFile) {
	// 	fprintf(stderr, "No output file is open for writing.");
	// 	return;
	// }
	
	// fprintf(this->outputFile, "Polygon with Points:");
	
	// for (int i = 0; i < newPoints.size(); i++) {
	// 	fprintf(this->outputFile, " (%f,%f)", newPoints[i]->get_X(), newPoints[i]->get_Y());
	// }
	// fprintf(this->outputFile, "\n");
}

void OutputFormatText::addText(OutputFeaturePoint location, const char * text) {
	if (!this->outputFile) {
		fprintf(stderr, "No output file is open for writing.");
		return;
	}

	fprintf(this->outputFile, "%s\n", text);
}

OutputFormatText::OutputFormatText(const char * filename) {
	this->outputFile = fopen(filename, "w");
}

void OutputFormatText::finalizeOutput() {
	if (this->outputFile) fclose(this->outputFile);
}
