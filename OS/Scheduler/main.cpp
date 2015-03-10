#include <vector>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>
#include <algorithm>

#include "process.h"
#include "event.h"
#include "scheduler.h"
#include "processor.h"
#include "FCFS.h"
#include "LCFS.h"
#include "RR.h"
#include "SJF.h"
#include "PRIO.h"

using namespace std;

// random file
FILE* rFile;
// procees file
FILE* pFile;

Processor processor;
Scheduler* scheduler;

vector<Process> proc;
int cpucycles;
bool verbose = false;
const string states[6] = {
    "CREATED -> READY",
    "READY -> RUNNG",
    "RUNNG -> BLOCK",
    "BLOCK -> READY",
    "RUNNG -> READY",
    "Done"
};

// structure to record the time segment of IO waitig 
typedef struct IOWAIT {
   int beg;
   int end;
} IOWait;
std::vector<IOWait>  ioWait;


bool cmp(IOWait a, IOWait b) {
   return a.beg == b.beg ? a.end < b.end : a.beg < b.beg;
}

void printsummary() {
    cout << scheduler->getType();

    if(scheduler->getQuantum() < 9999) {
        cout << " " << scheduler->getQuantum();
    }
    cout << endl;

    for(unsigned int i = 0; i < proc.size(); i++) {
        cout << setfill('0') << setw(4) << i << ": "; // Counter
        cout << setfill(' ') << setw(4) << proc[i].getArrivalTime();
        cout << " " << setfill(' ') << setw(4) << proc[i].getTotalCPUTime();
        cout << " " << setfill(' ') << setw(4) << proc[i].getMaxCPUBurstTime();
        cout << " " << setfill(' ') << setw(4) << proc[i].getMaxIOBurstTime();
        cout << " " << proc[i].getPriority();
        cout << " | ";
        cout << setfill(' ') << setw(5) << proc[i].getFinishingTime() << " ";
        cout << setfill(' ') << setw(5) << proc[i].getTurnaroundTime() << " ";    
        cout << setfill(' ') << setw(5) << proc[i].getIOTime() << " ";
        cout << setfill(' ') << setw(5) << proc[i].getCpuWaitingTime();
        cout << endl;
    }
}

void printfinalsummary() {
    int    maxfintime = cpucycles;
    
    double cpu_util = 0.0;
    double io_util  = 0.0;
    double avg_turnaround = 0.0;
    double avg_waittime = 0.0;

    std::sort(ioWait.begin(), ioWait.end(), cmp);
    int end;
    for (unsigned int i = 0; i < ioWait.size(); ++i) {
        if (i == 0 || end <= ioWait[i].beg) {
            io_util += ioWait[i].end - ioWait[i].beg;
            end = ioWait[i].end;
        } else if (end < ioWait[i].end) {
            io_util += ioWait[i].end - end;
            end = ioWait[i].end;
        }
    }


    for(unsigned int i = 0;i < proc.size(); i++) {
        cpu_util += proc[i].getTotalCPUTime();
        avg_turnaround += proc[i].getTurnaroundTime();
        avg_waittime += proc[i].getCpuWaitingTime();       
    }

    cpu_util = (cpu_util/cpucycles) * 100.0;
    io_util = (io_util/cpucycles) * 100.0;
    avg_turnaround = avg_turnaround / (double) proc.size();
    avg_waittime = avg_waittime/ (double) proc.size();

    double throughput = (double)proc.size() / ((double)maxfintime / 100.0);
    printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n",
        maxfintime,
        cpu_util,
        io_util,
        avg_turnaround,
        avg_waittime, 
        throughput);
}

void printstatus(Event e, Process p) {
    if(verbose) {
        cout << cpucycles << " " << p.getPid() << " " << p.getPrevStateTime() << ": " << states[e.transition].c_str();
        if(e.transition == 4) cout << " ";
        if(e.transition == 1 || e.transition == 4) cout << " cb=" << p.getRemainingBurst();
        if(e.transition == 2) cout << "  ib=" << p.getIOBurst();
        if(e.transition == 1 || e.transition == 2 || e.transition == 4) cout << " rem=" << p.getRemainingCPU();
        if(e.transition == 1 || e.transition == 4 ) cout << " prio=" << p.getDynPrio();
        cout << endl;
    }
}

int getRandomNumber() {
    char buf[80];
    int rand;

    fgets(buf, 80, rFile);
    // if reaches the end, wrap around
    if (feof(rFile)) {
        fseek(rFile, 0, SEEK_SET);
        fgets(buf, 80, rFile);
        fgets(buf, 80, rFile);
    }
    sscanf(buf, "%d", &rand);
    return rand;
}

vector<Process> getProcesses() {
    vector<Process> p;
    Process pr;
    char buf[80];
    int id = 0;
    int prio;

    while (fgets(buf, 80, pFile) != NULL) {
        int a, t, c, i;
        sscanf(buf, "%d%d%d%d", &a, &t, &c, &i);
        pr = Process(id++, a, t, c, i);
        prio = 1 + (getRandomNumber() % 4);
        pr.setPriority(prio);
        pr.setDynPrio(prio);
        p.push_back(pr);
    }
    return p;
}


void simulate() {

    // dummy initial event
    Event  curEvent(0, -1, 0);
    int id   = curEvent.pid;
    int ioburst   = 0;
    int cpuburst  = 0;
    int nextAvailable = 0;
    cpucycles = 0;
    int rand;
    int quantum = scheduler->getQuantum(); 
    while(!processor.queueEmpty()) {

        curEvent = processor.getEvent();

        if(curEvent.pid < 0) break;

        id = curEvent.pid;
        cpucycles = cpucycles > curEvent.timestamp ? cpucycles : curEvent.timestamp;

        // Created -> Ready : So, it is ready for running
        if(curEvent.transition == 0) {
            printstatus(curEvent, proc[id]);
            Event e(proc[id].getArrivalTime(), id, 1);
            e.inReady = cpucycles;
            processor.putEvent(e);
            proc[id].setDynPrio(proc[id].getDynPrio() - 1);
            proc[id].setLastReady(curEvent.timestamp);
            scheduler->add_process(proc[id]);
        }
        // Ready -> Running
        else if(curEvent.transition == 1) {

            //This is to update the time stamp to the next available slot in the CPU
            if (curEvent.timestamp < nextAvailable) {
                if(proc[id].getLastReady() < 0 ) {
                    proc[id].setLastReady(curEvent.timestamp);
                }
                curEvent.timestamp = nextAvailable;
                processor.putEvent(curEvent);                
                continue;
            }
            Process pr = scheduler->get_next_process();
            id = pr.getPid();
            proc[id].setPrevStateTime(curEvent.timestamp - proc[id].getLastReady());

            // First calculate the CPU Wait time
            proc[id].setCpuWaitingTime(proc[id].getCpuWaitingTime() + (curEvent.timestamp - proc[id].getLastReady()));
            //  GET random number only when remaining cpu is zero
            if(proc[id].getRemainingBurst() == 0) {
                rand = 1 + (getRandomNumber() % proc[id].getMaxCPUBurstTime());
                if(rand > proc[id].getRemainingCPU()) {
                     proc[id].setRemainingBurst(proc[id].getRemainingCPU());
                } else {
                    proc[id].setRemainingBurst(rand);
                }
            }
            cpuburst = proc[id].getRemainingBurst();
            // Quantum is lesser than remaining CPU Butst(RR)
            if(quantum <= proc[id].getRemainingBurst()) {
                // We have to pre-empt in this case
                if(quantum < cpuburst) {
                    printstatus(curEvent, proc[id]);
                    Event e(cpucycles + quantum, id, 4);
                    processor.putEvent(e);
                    proc[id].setRemainingBurst(cpuburst - quantum);
                    proc[id].setPrevStateTime(quantum);
                    proc[id].setRemainingCPU(proc[id].getRemainingCPU() - quantum);
                    nextAvailable = cpucycles + quantum;        
                    
                } else {
                    // Going into IO blocked mode
                    // Generate CPU burst from the random file
                    printstatus(curEvent, proc[id]);
                    Event e(cpucycles + cpuburst, id, (cpuburst == proc[id].getRemainingCPU())?5:2);
                    processor.putEvent(e);
                    proc[id].setRemainingBurst(0);
                    proc[id].setRemainingCPU(proc[id].getRemainingCPU() - cpuburst);
                    proc[id].setPrevStateTime(cpuburst);
                    proc[id].setDynPrio(proc[id].getPriority());
                    nextAvailable = cpucycles + cpuburst;
                                       
                }
            } 
            // Quantum is greater than remaining CPU (for cases NOT RR/PRIO)
            else {

                if (proc[id].getRemainingCPU() <= cpuburst) {
                    // Process is done running on the maxCPU burst
                    printstatus(curEvent, proc[id]);
                    Event e(cpucycles + proc[id].getRemainingCPU(), id, 5);
                    processor.putEvent(e);
                    proc[id].setRemainingBurst(0);
                    nextAvailable = cpucycles + proc[id].getRemainingCPU();
                    proc[id].setPrevStateTime(proc[id].getRemainingCPU());
                    proc[id].setRemainingCPU(0);
                }
                else {
                    // Going into IO blocked mode
                    // Generate CPU burst from the random file
                    printstatus(curEvent, proc[id]);
                    Event e(cpucycles + cpuburst, id, 2);
                    processor.putEvent(e);
                    proc[id].setRemainingBurst(0);
                    proc[id].setRemainingCPU(proc[id].getRemainingCPU() - cpuburst);
                    proc[id].setPrevStateTime(cpuburst);
                    proc[id].setDynPrio(proc[id].getPriority());
                    nextAvailable = cpucycles + cpuburst;
                }
            }
            proc[id].setLastReady(-1);
        }
        // Running -> Blocked
        else if(curEvent.transition == 2) {

            // Generate IO Burst from the random file
            ioburst = 1 + getRandomNumber() % proc[id].getMaxIOBurstTime();
            proc[id].setIOBurst(ioburst);
            printstatus(curEvent, proc[id]);

            Event e(cpucycles + ioburst, id, 3);
            proc[id].setIOTime(proc[id].getIOTime() + ioburst);
            IOWait io;
            io.beg = cpucycles;
            io.end = cpucycles + ioburst;
            ioWait.push_back(io);
            proc[id].setPrevStateTime(ioburst);
            proc[id].setDynPrio(proc[id].getPriority());
            processor.putEvent(e);

        }
        // Blocked -> Ready
        else if(curEvent.transition == 3) {
            printstatus(curEvent, proc[id]);
            Event e(cpucycles, id, 1);
            e.inReady = cpucycles; // To calculate CPU Wait Time
            processor.putEvent(e);
            proc[id].setLastReady(curEvent.timestamp);
            proc[id].setDynPrio(proc[id].getDynPrio() - 1);
            scheduler->add_process(proc[id]);
        }
        // Running -> Ready (Pre-emption) ##TODO
        else if(curEvent.transition == 4) {
            printstatus(curEvent, proc[id]);
            Event e(cpucycles, id, 1);
            e.inReady = cpucycles;
            processor.putEvent(e);
            proc[id].setLastReady(curEvent.timestamp);
            // Dynamic priority is reset in add_process except PRIO
            if(proc[id].getDynPrio() > 0)
               proc[id].setDynPrio(proc[id].getDynPrio() - 1);
            else
               proc[id].setDynPrio(proc[id].getPriority() - 1);
            scheduler->add_process(proc[id]);
        }
        //done
        else if(curEvent.transition == 5) {
            printstatus(curEvent, proc[id]);
            proc[id].setPrevStateTime(0);
            proc[id].setFinishingTime(cpucycles);
        }

    }
}

int main(int argc, char *argv[]) {
    pFile = fopen(argv[1], "r");
    rFile = fopen(argv[2], "r");
    
    int c, quantum;
    while ((c = getopt (argc, argv, "vs:")) != -1) {
            if(c == 's') {
                if(optarg[0] == 'R' || optarg[0] == 'P') {
                    sscanf(optarg + 1, "%d", &quantum);
                } else {
                    quantum = 9999;    
                }
                switch(optarg[0]) {
                    case 'F':
                        scheduler = new FCFSScheduler(quantum);
                        break;
                    case 'L': 
                        scheduler = new LCFSScheduler(quantum);
                        break;
                    case 'S':
                        scheduler = new SJFScheduler(quantum);
                        break;
                    case 'R':
                        scheduler = new RRScheduler(quantum);
                        break;
                    case 'P':
                        scheduler = new PRIOScheduler(quantum);
                        break;
                    default:
                        abort();    
                }                
            } else if(c == 'v') {
                verbose = true;    
            }       
    }

    if(argc - optind != 2){
        cout << "inputfile and randfile are required.\nInput the required inputs in the format specified. [-v] [-s<schedspec>] inputfile randfile\n";
        exit(99);
    }

    pFile = fopen(argv[optind], "r");
    rFile = fopen(argv[optind + 1], "r");
    
    char buf[80];
    fgets(buf, 80, rFile);

    proc = getProcesses();

    for (unsigned int i = 0; i < proc.size(); ++i) {
        processor.putEvent(Event(proc[i].getArrivalTime(), proc[i].getPid(), 0));
    }

    simulate();

    printsummary();
    printfinalsummary();

    fclose(rFile);
    fclose(pFile);
    return 0;
}

