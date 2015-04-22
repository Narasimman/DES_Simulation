#include "LRU.h"
#include "memory_manager.h"
#include <climits>

using namespace std;
LRU::LRU() {
	
}

void LRU::updateCounter(vector<unsigned int> &frames, int fnumber) {
	for (unsigned int i = 0; i < frames.size(); ++i) {
        if (frames[i] == fnumber) {
            frames.erase(frames.begin() + i);
            break;
        }
    }
	 
    frames.push_back(fnumber);
	
}

int LRU::getFrame(vector<PTE> &pte, vector<unsigned int> &frames, vector<unsigned int> &ftop) {
	unsigned int framenumber = frames.front();
    frames.erase(frames.begin());
    frames.push_back(framenumber);
    return framenumber;
}