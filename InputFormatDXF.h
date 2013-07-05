#ifndef INPUTFORMATDXF_H
#define INPUTFORMATDXF_H

#include "InputFormat.h"
#include "OutputFormat.h"
#include "GetInsertions.h"
#include "dxflib/src/dl_dxf.h"
#include "dxflib/src/dl_creationadapter.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

class InputFormatDXF: public InputFormat, public DL_CreationAdapter {
	public:
		// Our functions:
		InputFormatDXF(const char * inputFilename);
		void readFeaturesInto(OutputFormat * outputHandler);

		// Functions required for DL_CreationAdapter:
		void addPoint(const DL_PointData& data);
		void addLine(const DL_LineData& data);
		void addArc(const DL_ArcData& data);
		void addCircle(const DL_CircleData& data);
		void addPolyline(const DL_PolylineData& data);
		void addVertex(const DL_VertexData& data);
		void addBlock(const DL_BlockData& data);
		void addText(const DL_TextData& data);
		void addMText (const DL_MTextData& data);
		void endBlock();
		void endEntity();

	private:
		char * filename;	
		GetInsertions * insertionReceiver;
		OutputFormat * output;
		double currentBlockX;
		double currentBlockY;
		std::vector<OutputFeaturePoint *> pendingPolyline;

		void finishPendingPolyline();
};

#endif
