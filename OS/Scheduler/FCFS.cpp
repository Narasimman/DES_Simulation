#include "FCFS.h"
#include <vector>

using namespace std;

FCFSScheduler::FCFSScheduler() {}
FCFSScheduler::FCFSScheduler(int t) {
    type = t;
}

Process FCFSScheduler::get_next_process() {
    Process p;
    if (!readyQueue.empty()) {
        p = readyQueue.front();
        readyQueue.erase(readyQueue.begin());
    }
    return p;
}

void FCFSScheduler::add_process(Process &p) {
    p.setDynPrio(p.getPriority() - 1);
    readyQueue.push_back(p);
}

