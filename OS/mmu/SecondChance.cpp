#include "SecondChance.h"
#include "memory_manager.h"

using namespace std;
SecondChance::SecondChance() {}

int SecondChance::getFrame(vector<PTE> &pte, vector<unsigned int> &frames, vector<unsigned int> &ftop) {

	unsigned int pgindex, framenumber;
	

	for(unsigned int i = 0; i < frames.size(); i++){
		framenumber = frames.front();
		pgindex = ftop[framenumber];
		PTE& page = pte[pgindex];

		if(bitop->GET_REFERENCED(page) == 0) {
			break;
		} else {
			bitop->UNSET_REFERENCED(page);
		}
		frames.erase(frames.begin());
		frames.push_back(framenumber);
	}
	
	framenumber = frames.front();
	frames.erase(frames.begin());
	frames.push_back(framenumber);
	return framenumber;
}
