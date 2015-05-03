#include "FSCAN.h"
#include <vector>
#include <climits>
#include <cstdlib>

using namespace std;

FSCANScheduler::FSCANScheduler() {
	buffer_list = &list_two;
    request_list = &list_one;
	ltr = true;
}

Event FSCANScheduler::get_next_io() {
    Event lnear, rnear, ret;
	int index_found = -1;
	int minLeftDistance = INT_MAX, minRightDistance = INT_MAX, leftLoc = -1, rightLoc = -1;
	int track_distance;
	bool skip = false, lfound = false, rfound = false;
	
	if(request_list->size() == 0){
        vector<Event>* temp = request_list;
        request_list = buffer_list;
        buffer_list = temp;
        ltr = true;
      }
	
	for(unsigned int i=0; i < request_list->size(); i++){
		track_distance = abs(request_list->at(i).location - current_location);
		if(track_distance == 0){
		  skip = true;
		  index_found = i;
		  ret = request_list->at(i);
		  break;
		}
		
		if(request_list->at(i).location < current_location){
		  if(track_distance < minLeftDistance){
			lnear = request_list->at(i);
			leftLoc = i;
			lfound = true;
			minLeftDistance = track_distance;
		  }
		} else {
			if(track_distance < minRightDistance){
				rnear = request_list->at(i);
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

	request_list->erase(request_list->begin() + index_found);
	return ret;	
}

void FSCANScheduler::putEvent(Event e)  {
	 
     int loc = buffer_list->size();
      for(unsigned int i = 0; i < buffer_list->size(); i++) {
		if(e.location < buffer_list->at(i).location) {
			loc = i;
			break;
		}
      }
      buffer_list->insert(buffer_list->begin() + loc, e);
 }

bool FSCANScheduler::queueEmpty() {
     return (list_one.empty() && list_two.empty());
}

