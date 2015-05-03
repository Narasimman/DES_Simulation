#ifndef SSTF_SCHEDULER_H
#define SSTF_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class SSTFScheduler : public Scheduler {
    public:
        SSTFScheduler();
        void putEvent(Event);
        Event get_next_io();       
         bool queueEmpty();
};

#endif

