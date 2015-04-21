#ifndef __CLOCKVIRTUAL_H__
#define __CLOCKVIRTUAL_H__

#include "PR_algorithm_base.h"

class ClockVirtual : public PR_Algorithm {
	private:
		int clockhand;
	public:
		
		ClockVirtual();
	
		int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&);

};

#endif
