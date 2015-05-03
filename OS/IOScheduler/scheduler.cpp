#include "scheduler.h"

using namespace std;

void Scheduler::setReadyQueue(vector<Event>& q) {
    ioQueue = q;
}

vector<Event> Scheduler::getReadyQueue() {
    return ioQueue;
}

void Scheduler::setCurrentLocation(int track) {
	current_location = track;
}

int Scheduler::getCurrentLocation() {
	return current_location;
}

