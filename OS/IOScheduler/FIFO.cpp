#include "FIFO.h"
#include <vector>

using namespace std;

FIFOScheduler::FIFOScheduler() {}

Event FIFOScheduler::get_next_io() {
    Event e;
    if (!ioQueue.empty()) {
        e = ioQueue.front();
        ioQueue.erase(ioQueue.begin());
    }
    return e;
}
