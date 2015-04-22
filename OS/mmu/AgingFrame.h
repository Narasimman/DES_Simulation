#ifndef __AGINGFRAME_H__
#define __AGINGFRAME_H__

#include "PR_algorithm_base.h"

class AgingFrame : public PR_Algorithm {
	private:
		vector<unsigned int> counter;
	public:
		
		AgingFrame();
	
		int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&);

};

#endif
