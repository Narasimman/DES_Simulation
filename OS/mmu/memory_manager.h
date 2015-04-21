#ifndef __MM_INCLUDED__
#define __MM_INCLUDED__

#include <vector>
#include <iostream>
#include <string>
#include <cstring>

#include "PTE.h"
#include "bit_operations.h"
#include "PR_algorithm_base.h"

using namespace std;

class MMU {
	private:
		unsigned int num_frames, counter, unmap_counter, map_counter, in_counter, out_counter, zero_counter;
		bool O,P,F,S;
		BitOP *bitop;
		PR_Algorithm *pr_algo;
		
		vector<unsigned int> frames;
		vector<PTE> pages;
		vector<unsigned int> ftop; 
		
	public:
		MMU();
		MMU(int, PR_Algorithm*);
		void setOptions(char*);
		void mapPagesToFrames(int&, int&);
};

#endif
