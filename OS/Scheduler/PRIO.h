#ifndef PRIO_SCHEDULER_H
#define PRIO_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class PRIOScheduler : public Scheduler {
    private:
        vector<Process> *activeQueue;
        vector<Process> *expiredQueue;
    public:
        PRIOScheduler();
        PRIOScheduler(int);

        Process get_next_process();
        void add_process(Process&);
};


#endif

