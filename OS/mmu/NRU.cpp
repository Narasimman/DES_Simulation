#include "NRU.h"
#include "memory_manager.h"

using namespace std;
NRU::NRU() {
	counter = 0;
}

int NRU::getFrame(vector<PTE> &pte, vector<unsigned int> &frames, vector<unsigned int> &ftop) {

	unsigned int framenumber = -1, m ,r;
	vector<PTE> *categories = new vector<PTE>[4];
		
	for(unsigned int i = 0; i < pte.size(); i++) {
		PTE& page = pte[i];
		
		if(bitop->GET_PRESENT(page) == 1) {
			r = bitop->GET_REFERENCED(page);
			m = bitop->GET_MODIFIED(page);
			
			if(m == 0 && r == 0) {
				categories[0].push_back(page);
			} else if(m == 1 && r == 0) {
				categories[1].push_back(page);
			} else if(m == 0 && r == 1) {
				categories[2].push_back(page);
			} else if(m == 1 && r == 1) {
				categories[3].push_back(page);
			}		
		}
	}
		
	for(int i = 0; i <= 3; i++) {			
		if(categories[i].size() > 0) {
			framenumber = categories[i][rnd.getRandomNumber() % categories[i].size()].framenumber;
			break;
		}
	}
	
	counter++;	
	if(counter == 10) {
		for(unsigned int i = 0; i < pte.size(); i++) {
			PTE& page = pte[i];
			if(bitop->GET_PRESENT(page) == 1) {
				bitop->UNSET_REFERENCED(page);
			}
		}
		counter = 0;
	}
	
	
	return framenumber;
}