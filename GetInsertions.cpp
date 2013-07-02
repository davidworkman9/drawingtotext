#include "GetInsertions.h"
#include <stdio.h>

GetInsertions::GetInsertions() {
	Names = new string[MaxInserts];
	XVals = new double[MaxInserts];
	YVals = new double[MaxInserts];

	countInserts = 0;
}

GetInsertions::~GetInsertions() {
	if (Names != NULL) { 
		delete [] Names;
		Names = NULL;
	}
	if (XVals != NULL) {
		delete [] XVals;
		XVals = NULL;
	}
	if (YVals != NULL) { 
		delete [] YVals;
		YVals = NULL;
	}
}

void GetInsertions::addInsert(const DL_InsertData& data) {
	if (countInserts < MaxInserts) {
		Names[countInserts] = data.name;
		XVals[countInserts] = data.ipx;
		YVals[countInserts] = data.ipy;
		countInserts++;
	}

	if (countInserts > MaxInserts) {
		fprintf(stderr, "Warning: Exceeded hardcoded limit of 1,000,000 'Insert' blocks. Results may be unpredictable.\n");
	}
}
