#ifndef __MM_INCLUDED__
#define __MM_INCLUDED__

#include <vector>
#include <iostream>
#include <string>
#include <cstring>

#include "PTE.h"
#include "bit_operations.h"

using namespace std;

class VMM {
	private:
		int num_frames;
		bool O,P,F,S;
		BitOP *bitop;
		
		vector<unsigned int> frames;
		vector<PTE> pages;
		vector<unsigned int> ftop; 
		
	public:
		VMM();
		VMM(int);
		void setOptions(char*);
		void mapPagesToFrames(int&, int&);
};

#endif
