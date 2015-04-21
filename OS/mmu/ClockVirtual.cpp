#include "ClockVirtual.h"
#include "memory_manager.h"

using namespace std;
ClockVirtual::ClockVirtual() {
	clockhand = 0;
}

int ClockVirtual::getFrame(vector<PTE> &pte, vector<unsigned int> &frames, vector<unsigned int> &ftop) {

	unsigned int framenumber;

	while(true) {
		PTE& page = pte[clockhand];
		framenumber = page.framenumber;

		if(bitop->GET_PRESENT(page) == 1) {
			if(bitop->GET_REFERENCED(page) == 0) {
				break;
			} else {
				bitop->UNSET_REFERENCED(page);
			}
		}
		clockhand = (clockhand + 1) % (pte.size());
	}
	clockhand = (clockhand + 1) % (pte.size());
	return framenumber;
}
