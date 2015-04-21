#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "PR_algorithm_base.h"
#include "RandomNumber.h"

class Random : public PR_Algorithm {
	public:
		Random();
		int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&);

};

#endif
