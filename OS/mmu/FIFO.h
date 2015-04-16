#ifndef __FIFO_H__
#define __FIFO_H__

#include "PR_algorithm_base.h"

class FIFO : public PR_Algorithm {
	public:
		FIFO();
	
		int getFrame(vector<PTE>&, vector<unsigned int>&, vector<unsigned int>&);

};

#endif
