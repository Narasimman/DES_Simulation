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
		bool verbose;
    
    public:
        // getters and setters
        Event getEvent();
        void putEvent(Event);

        bool queueEmpty();
		
		void printstatus(Event, int, int, int);
    
		void handler();
        Processor();
		Processor(Scheduler*);

};

#endif

