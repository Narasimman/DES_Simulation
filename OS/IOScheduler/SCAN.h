#ifndef SCAN_SCHEDULER_H
#define SCAN_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class SCANScheduler : public Scheduler {
    public:
        SCANScheduler();
		void putEvent(Event);
        Event get_next_io();        
         bool queueEmpty();
};

#endif

