#ifndef EVENT_H
#define EVENT_H

using namespace std;

class Event {
    public:
        // timestamp of the next execution of the event
        int timestamp;
        // id
        int id;
		// location
        int location;
		
		int getLocation();

        Event();
        Event(int, int, int);
};

#endif

