#ifndef __AGINGVIRTUAL_H__
#define __AGINGVIRTUAL_H__

#include "PR_algorithm_base.h"

class AgingVirtual : public PR_Algorithm {
	private:
		vector<unsigned int> counter;
	public:
		
		AgingVirtual();
	
		int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&);

};

#endif
