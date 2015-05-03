#include "SCAN.h"
#include <vector>
#include <climits>
#include <cstdlib>

using namespace std;

SCANScheduler::SCANScheduler() {
	ltr = true;
}

Event SCANScheduler::get_next_io() {    
	Event lnear, rnear, ret;
	int index_found = -1;
	int minLeftDistance = INT_MAX, minRightDistance = INT_MAX, leftLoc = -1, rightLoc = -1;
	int track_distance;
	bool skip = false, lfound = false, rfound = false;
	for(unsigned int i=0; i < ioQueue.size(); i++){
		track_distance = abs(ioQueue[i].location - current_location);
		if(track_distance == 0){
		  skip = true;
		  index_found = i;
		  ret = ioQueue[i];
		  break;
		}
		
		if(ioQueue[i].location < current_location){
		  if(track_distance < minLeftDistance){
			lnear = ioQueue[i];
			leftLoc = i;
			lfound = true;
			minLeftDistance = track_distance;
		  }
		} else {
			if(track_distance < minRightDistance){
				rnear = ioQueue[i];
				rightLoc = i;
				rfound = true;
				minRightDistance = track_distance;
			}
		}
	}

	if(!skip){
		if(ltr && !rfound){
		  ret = lnear;
		  index_found = leftLoc;
		  ltr = !ltr;
		}else if(ltr && rfound){
		  ret = rnear;
		  index_found = rightLoc;
		}else if(!ltr && !lfound){
		  ret = rnear;
		  index_found = rightLoc;
		  ltr = !ltr;
		}else{
		  ret = lnear;
		  index_found = leftLoc;
		}
	}

	ioQueue.erase(ioQueue.begin() + index_found);
	return ret;	
}

void SCANScheduler::putEvent(Event e) {
   int loc = ioQueue.size();
      for(unsigned int i = 0; i < ioQueue.size(); i++) {
		if(e.location < ioQueue[i].location) {
			loc = i;
			break;
		}
      }
      ioQueue.insert(ioQueue.begin() + loc, e);
}

bool SCANScheduler::queueEmpty() {
    return ioQueue.empty();
}

