#ifndef OUTPUTFORMAT_H
#define OUTPUTFORMAT_H

#include "OutputFormatTypes.h"
#include <vector>

class OutputFormat {
	public:
		OutputFormat() {};
		~OutputFormat() {};

		// Standard feature types:
		virtual void addPoint(OutputFeaturePoint newPoint) = 0;
		virtual void addLine(OutputFeatureLine newLine) = 0;
		virtual void addPolyLine(std::vector<OutputFeaturePoint *> newPoints) = 0;
		virtual void addPolygon(std::vector<OutputFeaturePoint *> newPoints) = 0;

		// For approximating text on DXF/DWG with a separate point layer with a label attribute:
		virtual void addText(OutputFeaturePoint location, const char * text) = 0;

		// Our cleanup function - destructor on derived class won't run since we cast
		// it as base class
		virtual void finalizeOutput() = 0;
};

#endif
