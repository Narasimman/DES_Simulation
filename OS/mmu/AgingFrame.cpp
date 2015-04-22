#include "AgingFrame.h"
#include "memory_manager.h"
#include <climits>
#include <iostream>

using namespace std;
AgingFrame::AgingFrame() {
	counter = vector<unsigned int>();
}

int AgingFrame::getFrame(vector<PTE> &pte, vector<unsigned int> &frames, vector<unsigned int> &ftop) {
	
	int pgindex = -1, framenumber = -1;
	if (counter.size() == 0) {
        counter = vector<unsigned int>(frames.size(), 0);
    }
	
	for (unsigned int i = 0; i < frames.size(); ++i) {
		framenumber = frames[i];
		pgindex = ftop[framenumber];
		
		unsigned int& cValue = counter[i];
		
		cValue = (cValue >> 1) | (bitop->GET_REFERENCED(pte[pgindex]) << 31);
		counter[i] = cValue;
        bitop->UNSET_REFERENCED(pte[pgindex]);		
        
	}
	
	unsigned int min = 0xffffffff, tmp, min_index, physical_frame;
	for(unsigned int i = 0; i < frames.size(); i++){
		physical_frame = frames[i];
		tmp = counter[i];

		if(tmp <  min){
		  min = tmp;
		  framenumber = physical_frame;
		  min_index = i;
		}
	}
	counter[min_index] = 0;

	return framenumber;
}
