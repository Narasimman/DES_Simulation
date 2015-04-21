#include "ClockFrame.h"
#include "memory_manager.h"

using namespace std;
ClockFrame::ClockFrame() {
	clockhand = 0;
}

int ClockFrame::getFrame(vector<PTE> &pte, vector<unsigned int> &frames, vector<unsigned int> &ftop) {

	unsigned int pgindex, framenumber;

	while(true) {
		framenumber = frames[clockhand];
		pgindex = ftop[framenumber];
		PTE& page = pte[pgindex];

		if(bitop->GET_REFERENCED(page) == 0) {
			break;
		} else {
			bitop->UNSET_REFERENCED(page);
		}
		clockhand = (clockhand + 1) % (frames.size());
	}
	clockhand = (clockhand + 1) % (frames.size());
	return framenumber;
}
