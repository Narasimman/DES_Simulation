#ifndef __PR_ALGORITHM_INCLUDED__
#define __PR_ALGORITHM_INCLUDED__

#include <vector>

#include "PTE.h"

using namespace std;

class PR_Algorithm {
	public:
		virtual int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&) = 0;
};

#endif
