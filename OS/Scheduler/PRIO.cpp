#include "PRIO.h"
#include <vector>
#include <iostream>
using namespace std;

PRIOScheduler::PRIOScheduler() {}
PRIOScheduler::PRIOScheduler(int t) {
    type = t;
}

Process PRIOScheduler::get_next_process() {
    Process p;
    bool empty = true;
    for(int i = 3; i > -1; i--) {
        if(activeQueue[i].size() > 0) { empty  = false; break; }
    }
    if(empty) {
        swap(activeQueue, expiredQueue);
    }
    for(int i = 3; i > -1; i--) {
        if(activeQueue[i].size() > 0) {
            p = activeQueue[i].front();
            activeQueue[i].erase(activeQueue[i].begin());
            break;
        }
    }
    return p;
}

void swap(vector<Process> &a, vector<Process> &e){
    vector<Process> temp = a;
    a = e;
    e = temp;
}

void PRIOScheduler::add_process(Process &p) {
    if(p.getDynPrio() == -1) {
        expiredQueue[p.getPriority()].push_back(p);
    } else {
        activeQueue[p.getDynPrio()].push_back(p);
    }
}

