#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class SJFScheduler : public Scheduler {
    public:
        SJFScheduler();
        SJFScheduler(int);

        Process get_next_process();
        void add_process(Process);
};


#endif

