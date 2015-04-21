#ifndef __PR_ALGORITHM_INCLUDED__
#define __PR_ALGORITHM_INCLUDED__

#include <vector>

#include "PTE.h"
#include "RandomNumber.h"

using namespace std;

class PR_Algorithm {
	public:
		RandomNumber rnd;
		void initializeRandom(RandomNumber&);
		virtual int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&) = 0;
};

#endif
