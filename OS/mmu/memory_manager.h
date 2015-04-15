#ifndef __MM_INCLUDED__
#define __MM_INCLUDED__

#include <vector>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct PTE {
	unsigned int present : 1;
	unsigned int referenced : 1;
	unsigned int modified : 1;
	unsigned int pagedout :1;
	unsigned int framenumber : 24;
};

struct FrameTable {
	PTE pte;
};

class VMM {
	private:
		int num_frames;
		bool O,P,F,S;
		
		vector<unsigned int> frames;
		vector<PTE> pages;
		vector<FrameTable> ftop; 
		
	public:
		VMM();
		VMM(int);
		void setOptions(char*);
		void mapPagesToFrames(int&, int&);
};

#endif
