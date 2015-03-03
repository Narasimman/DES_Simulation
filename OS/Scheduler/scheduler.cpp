#include "scheduler.h"

using namespace std;

void Scheduler::setType(int t) {
    type = t;
}

int Scheduler::getType() {
    return type;
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

