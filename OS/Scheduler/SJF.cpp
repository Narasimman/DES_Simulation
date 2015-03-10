#include "SJF.h"
#include <vector>

using namespace std;

SJFScheduler::SJFScheduler() {}
SJFScheduler::SJFScheduler(int t) {
    type = t;
}

Process SJFScheduler::get_next_process() {
    Process p;
    if (!readyQueue.empty()) {
        int shortest = readyQueue[0].getRemainingCPU();
        int current = 0;

        for(unsigned int i =1; i < readyQueue.size(); i++) {
            if(readyQueue[i].getRemainingCPU() < shortest) {
                shortest = readyQueue[i].getRemainingCPU();
                current  = i;
            }           
        }
        p = readyQueue[current];
        readyQueue.erase(readyQueue.begin() + current);
    }
    return p;
}

void SJFScheduler::add_process(Process &p) {
    p.setDynPrio(p.getPriority() - 1);
    readyQueue.push_back(p);
}

