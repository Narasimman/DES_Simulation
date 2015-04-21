#ifndef __SECONDCHANCE_H__
#define __SECONDCHANCE_H__

#include "PR_algorithm_base.h"

class SecondChance : public PR_Algorithm {
	public:
		SecondChance();
	
		int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&);

};

#endif
