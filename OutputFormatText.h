#ifndef OUTPUTFORMATTEXT_H
#define OUTPUTFORMATTEXT_H

#include "OutputFormatTypes.h"
#include "OutputFormat.h"
#include <stdio.h>

class OutputFormatText: public OutputFormat {
	public:
		void addPoint(OutputFeaturePoint newPoint);
		void addLine(OutputFeatureLine newLine);
		void addPolyLine(std::vector<OutputFeaturePoint *> newPoints);
		void addPolygon(std::vector<OutputFeaturePoint *> newPoints);

		void addText(OutputFeaturePoint location, const char * text);

		OutputFormatText (const char * filename);
		void finalizeOutput();
	private:
		FILE * outputFile;
};

#endif
