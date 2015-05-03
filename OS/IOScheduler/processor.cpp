#include "processor.h"
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

Processor::Processor(Scheduler *s) {
	sched = s;
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


void Processor::handler() {
	Event e;
	bool iorunning = false;
	
	int currenttime = 0, next_available = 0, current_end = 0;
	unsigned int processed = 0, total = eventQueue.size();
	
	int turnaround_time = 0;
	while(processed < total) {
		
		if(!iorunning) {
			if(!sched->queueEmpty()) {
				e = sched->get_next_io();
				cout << setw(5) << setfill(' ') << currenttime << ":" << setw(6) << setfill(' ') << e.id << " issue " << e.location << " " << current_end << endl;				
				iorunning = true;
			} else {
				e = this->getEvent();
				sched->putEvent(e);
				currenttime = e.timestamp;
				cout << setw(5) << setfill(' ') << e.timestamp << ":" << setw(6) << setfill(' ') << e.id << " add " << e.location << endl;
			}
		} else {
			next_available = currenttime + abs(current_end - e.location);
			while(!this->queueEmpty() && eventQueue[0].timestamp <= next_available) {
				Event event = this->getEvent();
				sched->putEvent(event);
				cout << setw(5) << setfill(' ') << event.timestamp << ":" << setw(6) << setfill(' ') << event.id << " add " << event.location << endl;
				currenttime = event.timestamp;
			}
			
			current_end = e.location;
			currenttime = next_available;
			
			turnaround_time += (currenttime - e.timestamp);
			
			cout << setw(5) << setfill(' ') << currenttime << ":" << setw(6) << setfill(' ') << e.id << " finish " << (currenttime - e.timestamp) << endl;
			processed++;
			iorunning = false;
		}
	
	}

}
