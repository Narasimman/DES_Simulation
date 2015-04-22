#ifndef __LRU_H__
#define __LRU_H__

#include "PR_algorithm_base.h"

class LRU : public PR_Algorithm {
	public:
		LRU();
		int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&);
		void updateCounter(vector<unsigned int>&, int);
};

#endif
