#ifndef EVENT_H
#define EVENT_H

using namespace std;

class Event {
    public:
        // timestamp of the next execution of the event
        int timestamp;
        // process associated with the event
        int pid;

        int old_state;

        int new_state;

        int transition;

        Event();
        Event(int, int, int);
};

#endif

