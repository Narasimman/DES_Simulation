#ifndef __NRU_H__
#define __NRU_H__

#include "PR_algorithm_base.h"

class NRU : public PR_Algorithm {
	private:
		int counter;
	public:
		NRU();
		int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&);
};

#endif
