#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <vector>
using namespace std;

class Scheduler {
    protected:
        // Type of the Scheduler
        int type;

        // Ready Queue
        vector<Process> readyQueue;

        //Quantum
        int quantum;

 
    public:

        // getters and setters
        void setType(int);
        string getType();

        void setReadyQueue(vector<Process>);
        vector<Process> getReadyQueue();

        int getQuantum();
        void setQuantum(int);

        // returns the next process available in the ready queue
        virtual Process get_next_process() = 0;

        // Adds the given process to the ready queue based on the scheduler type.
        virtual void add_process(Process) = 0;

};


#endif

