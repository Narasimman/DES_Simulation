#include "AgingVirtual.h"
#include "memory_manager.h"
#include <climits>
#include <iostream>

using namespace std;
AgingVirtual::AgingVirtual() {
	counter = vector<unsigned int>();
}

int AgingVirtual::getFrame(vector<PTE> &pte, vector<unsigned int> &frames, vector<unsigned int> &ftop) {
	
	int framenumber = -1;
	if (counter.size() == 0) {
        counter = vector<unsigned int>(64, 0);
    }
	
	for (unsigned int i = 0; i < pte.size(); ++i) {
		
		unsigned int& cValue = counter[i];
		
		cValue = (cValue >> 1) | (bitop->GET_REFERENCED(pte[i]) << 31);
		counter[i] = cValue;
		if (bitop->GET_PRESENT(pte[i]) == 1) {
			bitop->UNSET_REFERENCED(pte[i]);	
		}		
        
	}
	
	unsigned int min = 0xffffffff, tmp, min_index;
	for(unsigned int i = 0; i < pte.size(); i++){
		tmp = counter[i];

		if(bitop->GET_PRESENT(pte[i]) == 1) {
			if(tmp <  min){
			  min = tmp;
			  min_index = i;
			}
		}
	}
	framenumber = pte[min_index].framenumber;
	counter[min_index] = 0;

	return framenumber;
}
