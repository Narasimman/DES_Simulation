#include "processor.h"
#include <vector>
#include <iostream>

using namespace std;

Processor::Processor() {

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



