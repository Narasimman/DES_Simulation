#include "RR.h"
#include <vector>

using namespace std;

RRScheduler::RRScheduler() {}
RRScheduler::RRScheduler(int t) {
    type = t;
}

Process RRScheduler::get_next_process() {
    Process p;
    if (!readyQueue.empty()) {
        p = readyQueue.front();
        readyQueue.erase(readyQueue.begin());
    }
    return p;
}

void RRScheduler::add_process(Process p) {
    readyQueue.push_back(p);
}

