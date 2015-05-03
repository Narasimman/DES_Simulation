#ifndef FSCAN_SCHEDULER_H
#define FSCAN_SCHEDULER_H

#include "scheduler.h"

using namespace std;

class FSCANScheduler : public Scheduler {
	private:
		vector<Event>* request_list;
		vector<Event>* buffer_list;

		vector<Event> list_one;
		vector<Event> list_two;

		
		bool ltr;
    public:
        FSCANScheduler();
        void putEvent(Event);
        Event get_next_io();
         bool queueEmpty();
};

#endif

