#include "CSCAN.h"
#include <vector>
#include <climits>
#include <cstdlib>
#include <iostream>
using namespace std;

CSCANScheduler::CSCANScheduler() {}

Event CSCANScheduler::get_next_io() {
     int locToErase = 0;
      Event e;
      for(unsigned int i=0; i < ioQueue.size(); i++){
        if(ioQueue[i].location < current_location){
          continue;
        }
        locToErase = i;
        break;
      }
      e = ioQueue[locToErase];
      ioQueue.erase(ioQueue.begin() + locToErase);
      return e;
}

void CSCANScheduler::putEvent(Event e) {
   int loc = ioQueue.size();
      for(unsigned int i = 0; i < ioQueue.size(); i++) {
		if(e.location < ioQueue[i].location) {
			loc = i;
			break;
		}
      }
      ioQueue.insert(ioQueue.begin() + loc, e);
}

bool CSCANScheduler::queueEmpty() {
     return ioQueue.empty();
 }

