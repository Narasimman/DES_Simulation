#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "event.h"
#include <vector>
using namespace std;

class Scheduler {
    protected:
		//Queue
		vector<Event> ioQueue;
		// current displacement of the track head
		int current_location;
		
		bool ltr;
 
    public:

        void setReadyQueue(vector<Event>&);
        vector<Event> getReadyQueue();

		void setCurrentLocation(int);
		int getCurrentLocation();
		
		// getters and setters
        Event getEvent();
        virtual void putEvent(Event) = 0;

        virtual bool queueEmpty() = 0;
		
        // returns the next io available in the ready queue
        virtual Event get_next_io() = 0;

};


#endif

