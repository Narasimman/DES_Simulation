#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class FCFSScheduler : public Scheduler {
    public:
        FCFSScheduler();
        FCFSScheduler(int);

        Process get_next_process();
        void add_process(Process&);
};


#endif

