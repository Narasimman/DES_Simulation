#include "processor.h"
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

Processor::Processor(Scheduler *s) {
	sched = s;
	verbose = false;
}

Event Processor::getEvent() {
    Event e(0, -1, 0);
    if (!eventQueue.empty()) {
        e = eventQueue.front();
        eventQueue.erase(eventQueue.begin());
    }
    return e;
}

// Insert an event based on the timestamp. Time stamp ordered event queue
void Processor::putEvent(Event e) {
   int loc = eventQueue.size();
   for (unsigned int i = 0; i < eventQueue.size(); ++i) {
       if (e.timestamp < eventQueue[i].timestamp) {
           loc = i;
           break;
       }
   }
   eventQueue.insert(eventQueue.begin() + loc, e);
}

bool Processor::queueEmpty() {
    return eventQueue.empty();
}

void Processor::printstatus(Event e, int type, int current, int currenttime) {
	if(verbose) {
		if(type == 1) {
			cout << currenttime << ":" << setw(6) << setfill(' ') << e.id << " issue " << e.location << " " << current << endl;
		} else if(type == 0) {
			cout << e.timestamp << ":" << setw(6) << setfill(' ') << e.id << " add " << e.location << endl;
		} else {
			cout << currenttime << ":" << setw(6) << setfill(' ') << e.id << " finish " << current << endl;
		}
	}		
}
void Processor::handler() {
	Event e;
	bool iorunning = false;
	
	int currenttime = 0, next_available = 0, current_end = 0;
	unsigned int total = eventQueue.size();
	
	int turnaround_time = 0, wait_time = 0, max_wait = 0, total_movement = 0;
	while( iorunning || !this->queueEmpty() || !sched->queueEmpty()) {
		if(!iorunning) {
			if(sched->queueEmpty()) {				
				e = this->getEvent();
				sched->putEvent(e);
				currenttime = e.timestamp;
				
				//add
				printstatus(e, 0, 0, currenttime);
			} else {				
				e = sched->get_next_io();
				
				//issue
				printstatus(e, 1, current_end, currenttime);
				total_movement += abs(current_end - e.location);
				int waiting = abs(currenttime - e.timestamp);
				wait_time += waiting;
				if(waiting > max_wait) {
					max_wait =  waiting;
				}
				iorunning = true;
			}
		} else {
			next_available = currenttime + abs(current_end - e.location);
			while(!this->queueEmpty() && eventQueue[0].timestamp <= next_available) {
				Event event = this->getEvent();
				sched->putEvent(event);
				
				//add
				printstatus(event, 0, 0, currenttime);		
				currenttime = event.timestamp;
			}
			
			current_end = e.location;
			sched->setCurrentLocation(current_end);
			currenttime = next_available;
			
			turnaround_time += (currenttime - e.timestamp);
			
			//finish
			printstatus(e, 2, (currenttime - e.timestamp), currenttime);
			iorunning = false;
		}
	
	}
	
	printf("SUM: %d %d %.2lf %.2lf %d\n", currenttime, total_movement,
            (double)turnaround_time / total, (double)wait_time / total,
            max_wait);

}
