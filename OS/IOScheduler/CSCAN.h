#ifndef CSCAN_SCHEDULER_H
#define CSCAN_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class CSCANScheduler : public Scheduler {
    public:
        CSCANScheduler();
		void putEvent(Event);
        Event get_next_io();       
         bool queueEmpty();
};

#endif

