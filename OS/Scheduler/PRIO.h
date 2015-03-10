#ifndef PRIO_SCHEDULER_H
#define PRIO_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class PRIOScheduler : public Scheduler {
    private:
        vector<Process> activeQueue[4];
        vector<Process> expiredQueue[4];
        void swap(vector<Process>, vector<Process>);
    public:
        PRIOScheduler();
        PRIOScheduler(int);

        Process get_next_process();
        void add_process(Process&);
};


#endif

