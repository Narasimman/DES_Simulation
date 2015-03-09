#include "scheduler.h"

using namespace std;

const string scheduler_types[5] = {
    "FCFS",
    "LCFS",
    "SJF",
    "RR",
    "PRIO"
};

void Scheduler::setType(int t) {
    type = t;
}

string Scheduler::getType() {
    return scheduler_types[type];
}

void Scheduler::setReadyQueue(vector<Process> q) {
    readyQueue = q;
}

vector<Process> Scheduler::getReadyQueue() {
    return readyQueue;
}

void Scheduler::setQuantum(int q) {
    quantum = q;    
}

int Scheduler::getQuantum(){
    return quantum;    
}

