#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "event.h"
#include <vector>
using namespace std;

class Processor {
    private:
        vector<Event> eventQueue;
    public:
        // getters and setters
        Event getEvent();
        void putEvent(Event);

        bool queueEmpty();
        Processor();

};

#endif

