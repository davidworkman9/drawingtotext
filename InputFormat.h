#ifndef INPUTFORMAT_H
#define INPUTFORMAT_H

#include "OutputFormat.h"

class InputFormat {
	public:
		InputFormat() {};
		~InputFormat() {};
		virtual void readFeaturesInto(OutputFormat * outputHandler) = 0; 
};

#endif
