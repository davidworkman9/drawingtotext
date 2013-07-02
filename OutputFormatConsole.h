#ifndef OUTPUTFORMATCONSOLE_H
#define OUTPUTFORMATCONSOLE_H

#include "OutputFormatTypes.h"
#include "OutputFormat.h"
#include <stdio.h>
#include <iostream>

class OutputFormatConsole: public OutputFormat {
	public:
		void addPoint(OutputFeaturePoint newPoint);
		void addLine(OutputFeatureLine newLine);
		void addPolyLine(std::vector<OutputFeaturePoint *> newPoints);
		void addPolygon(std::vector<OutputFeaturePoint *> newPoints);

		void addText(OutputFeaturePoint location, const char * text);

		OutputFormatConsole ();
		void finalizeOutput();
	// private:
//		FILE * outputFile;
};

#endif