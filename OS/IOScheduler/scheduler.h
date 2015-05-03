#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "event.h"
#include <vector>
using namespace std;

class Scheduler {
    protected:
		//Queue
		vector<Event> ioQueue;
 
    public:

        void setReadyQueue(vector<Event>&);
        vector<Event> getReadyQueue();

		// getters and setters
        Event getEvent();
        void putEvent(Event);

        bool queueEmpty();
		
        // returns the next io available in the ready queue
        virtual Event get_next_io() = 0;

};


#endif

