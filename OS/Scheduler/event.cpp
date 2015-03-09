#include "event.h"

// Constructor
Event::Event() {

}

Event::Event(int t, int id, int trans){
    timestamp = t;
    pid = id;
    transition = trans;
    inReady = 0;
}

