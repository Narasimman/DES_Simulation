#include "scheduler.h"

using namespace std;

void Scheduler::setReadyQueue(vector<Event>& q) {
    ioQueue = q;
}

vector<Event> Scheduler::getReadyQueue() {
    return ioQueue;
}

// Insert an event based on the timestamp. Time stamp ordered event queue
void Scheduler::putEvent(Event e) {
   int loc = ioQueue.size();
   for (unsigned int i = 0; i < ioQueue.size(); ++i) {
       if (e.timestamp < ioQueue[i].timestamp) {
           loc = i;
           break;
       }
   }
   ioQueue.insert(ioQueue.begin() + loc, e);
}

bool Scheduler::queueEmpty() {
    return ioQueue.empty();
}
