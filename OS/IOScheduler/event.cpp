#include "event.h"

// Constructor
Event::Event() {

}

Event::Event(int t, int eid, int loc){
    timestamp = t;
    id = eid;
    location = loc;
}

int Event::getLocation() {
	return location;
}