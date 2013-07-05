#include "InputFormatDXF.h"
#include "InputFormatDWG.h"
#include "OutputFormatText.h"
#include "OutputFormatConsole.h"
#include <sys/stat.h>
#include <stdio.h>

void usage(char * me) {
	printf("Usage: %s inputfile outputfile\n", me);
	printf("Input formats supported:\n");
	printf("\tAutoCAD DXF (*.dxf)\n");
	printf("\tAutoCAD DWG (*.dwg)\n");
	printf("Output formats supported:\n");
	printf("\tText (*.txt)\n");
	printf("\tConsole output (don't specify second parameter)\n");
	printf("\nInput format and output format are determined automatically by file extension.\n");
}

int main(int argc, char * argv[]) {
	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}

	OutputFormat * output = NULL;	
	InputFormat * input = NULL;
	struct stat fileExists;

	// Set up output format first...

	std::string outFile = argc < 3 ? "" : argv[2];
	if (outFile != "" && outFile.rfind('.') == std::string::npos) {
		printf("I couldn't make sense of your output filename's extension: %s. Please use filename.shp, filename.kml, or filename.txt.\n", argv[2]);
		return 1;
	}

	if (outFile.substr(outFile.rfind('.')+1) == "txt") {
		printf("Setting up output file %s...\n", argv[2]);
		output = new OutputFormatText(argv[2]);
	} else if(outFile == "") {
		output = new OutputFormatConsole();
	}

	// Next grab the input file
	std::string inFile = argv[1];
	if (inFile.rfind('.') == std::string::npos) {
		printf("I couldn't make sense of your input filename's extension: %s. Please use filename.dxf or filename.dwg.\n", argv[1]);
		delete output;
		return 1;
	}
	if (stat(argv[1], &fileExists) != 0) {
		printf("The specified input file does not exist or is not accessible: %s\n", argv[1]);
		return 1;
	}

	if (inFile.substr(inFile.rfind('.')+1) == "dxf") {
		input = new InputFormatDXF(argv[1]);
		if(outFile != "")
			printf("Setting up input file %s...\n", argv[1]);
	} else if (inFile.substr(inFile.rfind('.')+1) == "dwg") {
		input = new InputFormatDWG(argv[1]);
		if(outFile != "")
			printf("Setting up input file %s...\n", argv[1]);
	}

	if (!input) {
		printf("The input file was not recognized or could not be opened.\n");
		return 1;
	}
	if (!output) {
		printf("The output file was not recognized or could not be opened.\n");
		return 1;
	}
	if(outFile != "")
		printf("Converting file...\n");
	input->readFeaturesInto(output);
	output->finalizeOutput();
	if(outFile != "")
		printf("Done!\n");

	delete input;
	delete output;
	return 0;
}
