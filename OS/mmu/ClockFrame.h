#ifndef __CLOCKFRAME_H__
#define __CLOCKFRAME_H__

#include "PR_algorithm_base.h"

class ClockFrame : public PR_Algorithm {
	private:
		int clockhand;
	public:
		
		ClockFrame();
	
		int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&);

};

#endif
