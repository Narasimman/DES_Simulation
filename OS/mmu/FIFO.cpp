#include "FIFO.h"
#include "memory_manager.h"

using namespace std;
FIFO::FIFO() {}

int FIFO::getFrame(vector<PTE> &pte, vector<unsigned int> &frames, vector<unsigned int> &ftop) {
	int framenumber = frames.front();
	frames.erase(frames.begin());
	frames.push_back(framenumber);
	return framenumber;
}
