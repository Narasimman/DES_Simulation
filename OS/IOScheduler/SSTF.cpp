#include "SSTF.h"
#include <vector>
#include <climits>
#include <cstdlib>

using namespace std;

SSTFScheduler::SSTFScheduler() {}

Event SSTFScheduler::get_next_io() {
    Event e;
	int min = INT_MAX, min_index = -1;
	
	for(unsigned int i = 0; i < ioQueue.size(); i++) {
		int temp = abs(current_location - ioQueue[i].location);
		if( temp < min) {
			min = temp;
			min_index = i;			
		}		
	}
    e = ioQueue[min_index];
    ioQueue.erase(ioQueue.begin() + min_index);
    return e;
}
