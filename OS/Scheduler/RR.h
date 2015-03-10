#ifndef RR_SCHEDULER_H
#define RR_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class RRScheduler : public Scheduler {
    public:
        RRScheduler();
        RRScheduler(int);

        Process get_next_process();
        void add_process(Process&);
};


#endif

