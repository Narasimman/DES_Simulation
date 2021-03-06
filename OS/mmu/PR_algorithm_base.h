#ifndef __PR_ALGORITHM_INCLUDED__
#define __PR_ALGORITHM_INCLUDED__

#include <vector>

#include "PTE.h"
#include "RandomNumber.h"
#include "bit_operations.h"

using namespace std;

class PR_Algorithm {
	public:
		RandomNumber rnd;
		BitOP *bitop;
		void initializeRandom(RandomNumber&);
		virtual void updateCounter(vector<unsigned int>&, int);
		virtual int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&) = 0;
};

#endif
