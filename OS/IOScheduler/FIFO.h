#ifndef FIFO_SCHEDULER_H
#define FIFO_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class FIFOScheduler : public Scheduler {
    public:
        FIFOScheduler();

        Event get_next_io();        
};

#endif

