#include "OutputFormatTypes.h"
#include "OutputFormatConsole.h"

void OutputFormatConsole::addPoint(OutputFeaturePoint newPoint) { }

void OutputFormatConsole::addLine(OutputFeatureLine newLine) { }

void OutputFormatConsole::addPolyLine(std::vector<OutputFeaturePoint *> newPoints) { }

void OutputFormatConsole::addPolygon(std::vector<OutputFeaturePoint *> newPoints) { }

void OutputFormatConsole::addText(OutputFeaturePoint location, const char * text) {
	std::cout << text << std::endl;
}

OutputFormatConsole::OutputFormatConsole() {
}

void OutputFormatConsole::finalizeOutput() {
	//if (this->outputFile) fclose(this->outputFile);
}
