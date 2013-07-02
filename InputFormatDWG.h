#ifndef INPUTFORMATDWG_H
#define INPUTFORMATDWG_H

#include "InputFormat.h"
#include "OutputFormat.h"
#include <stdio.h>
#include <math.h>

extern "C" {
	#include <dwg.h>
}

class InputFormatDWG: public InputFormat {
	public:
		// Our functions:
		InputFormatDWG(const char * inputFilename);
		~InputFormatDWG();
		void readFeaturesInto(OutputFormat * outputHandler);

		// Functions required for DL_CreationAdapter:
		void dumpBlock(Dwg_Object_Ref * block);

	private:
		Dwg_Data * dwg;
		double currentBlockX;
		double currentBlockY;
		OutputFormat * output;
};

#endif
