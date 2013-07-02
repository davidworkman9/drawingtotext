#ifndef INSERTIONCLASS_H
#define INSERTIONCLASS_H

#include "dxflib/src/dl_creationadapter.h"

class GetInsertions: public DL_CreationAdapter {
	public:
		GetInsertions();
		~GetInsertions();

		virtual void addInsert(const DL_InsertData& data);

		string * Names;
		double * XVals;
		double * YVals;

		int countInserts;
		const static int MaxInserts = 1000000;
};

#endif
