#ifndef LCFS_SCHEDULER_H
#define LCFS_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class LCFSScheduler : public Scheduler {
    public:
        LCFSScheduler();
        LCFSScheduler(int);

        Process get_next_process();
        void add_process(Process&);
};


#endif

