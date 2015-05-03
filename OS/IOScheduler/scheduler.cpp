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
   ioQueue.push_back(e);
}

bool Scheduler::queueEmpty() {
    return ioQueue.empty();
}
