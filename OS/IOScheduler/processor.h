#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "event.h"
#include "scheduler.h"
#include <vector>
using namespace std;

class Processor {
    private:
		Scheduler *sched;
		vector<Event> eventQueue;
    
    public:
        // getters and setters
        Event getEvent();
        void putEvent(Event);

        bool queueEmpty();
    
		void handler();
        Processor();
		Processor(Scheduler*);

};

#endif

