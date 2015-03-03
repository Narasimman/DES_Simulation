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

#include "process.h"
#include "event.h"
#include "scheduler.h"
#include "processor.h"
#include "FCFS.h"

using namespace std;

// random file
FILE* rFile;
// procees file
FILE* pFile;

Processor processor;
Scheduler* scheduler;

vector<Process> proc;
int cpucycles;
const string states[6] = {
    "CREATED -> READY",
    "READY -> RUNNG",
    "RUNNG -> BLOCK",
    "BLOCK -> READY",
    "RUNNG -> READY",
    "DONE"
};

void printstatus(Event e, Process p) {
//        printf("%d %d : %s %d %d\n", cpucycles, p.getPid(),
  //                  states[e.transition].c_str(), p.getRemainingCPU(), p.getPriority());
        cout << cpucycles << " " << p.getPid() << " : " << states[e.transition].c_str() << " ";
        if(e.transition == 1 || e.transition == 2) cout << "rem=" << p.getRemainingCPU() << " ";
        if(e.transition == 1) cout << "prio=" << p.getPriority();
        cout << endl;
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

    while (fgets(buf, 80, pFile) != NULL) {
        int a, t, c, i;
        sscanf(buf, "%d%d%d%d", &a, &t, &c, &i);
        pr = Process(id++, a, t, c, i);
        // CHECK PRIO CLACULATION
        pr.setPriority(1 + (getRandomNumber() % pr.getMaxCPUBurstTime()));
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
    int quantum = scheduler->getQuantum(); //#TODO
    while(!processor.queueEmpty()) {

        curEvent = processor.getEvent();

        if(curEvent.pid < 0) break;

        id = curEvent.pid;
        cpucycles = cpucycles > curEvent.timestamp ? cpucycles : curEvent.timestamp;

        // Created -> Ready : So, it is ready for running
        if(curEvent.transition == 0) {
            printstatus(curEvent, proc[id]);
            Event e(proc[id].getArrivalTime(), id, 1);
            processor.putEvent(e);
            scheduler->add_process(proc[id]);
        }
        // Ready -> Running
        else if(curEvent.transition == 1) {
            //This is to update the time stamp to the next available slot in the CPU
            //cout << curEvent.timestamp << " " << nextAvailable << endl;
            if (curEvent.timestamp < nextAvailable) {
                curEvent.timestamp = nextAvailable;
                processor.putEvent(curEvent);
                continue;
            }


            cpuburst = 1 + (getRandomNumber() % proc[id].getMaxCPUBurstTime());
            //cout << proc[id].getRemainingCPU() << " " << cpuburst << " ** " << endl;
            
            // Quantum is lesser than remaining CPU (RR)
            if(quantum <= proc[id].getRemainingCPU()) {
                // We have to pre-empt in this case
                if(quantum <= cpuburst) { 
                        printstatus(curEvent, proc[id]);
                        Process p = scheduler->get_next_process();
                        Event e(cpucycles + q, id, 4);
                        processor.putEvent(e);
                        proc[id].setRemainingCPU(proc[id].getRemainingCPU() - q);
                        nextAvailable = cpucycles + q;                   
                    
                } else {
                    // Going into IO blocked mode
                    // Generate CPU burst from the random file
                    printstatus(curEvent, proc[id]);
                    Process p = scheduler->get_next_process();
                    Event e(cpucycles + cpuburst, id, 2);
                    processor.putEvent(e);
                    proc[id].setRemainingCPU(proc[id].getRemainingCPU() - cpuburst);
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
                    nextAvailable = cpucycles + proc[id].getRemainingCPU();
                    proc[id].setRemainingCPU(0);
                }  
                else {
                    // Going into IO blocked mode
                    // Generate CPU burst from the random file
                    printstatus(curEvent, proc[id]);
                    Process p = scheduler->get_next_process();
                    Event e(cpucycles + cpuburst, id, 2);
                    processor.putEvent(e);
                    proc[id].setRemainingCPU(proc[id].getRemainingCPU() - cpuburst);
                    nextAvailable = cpucycles + cpuburst;
                }
            }
        }
        // Running -> Blocked
        else if(curEvent.transition == 2) {

            // Generate IO Burst from the random file
            ioburst = 1 + getRandomNumber() % proc[id].getMaxIOBurstTime();
            printstatus(curEvent, proc[id]);

            Event e(cpucycles + ioburst, id, 3);
            proc[id].setIOTime(proc[id].getIOTime() + ioburst);
            processor.putEvent(e);

        }
        // Blocked -> Ready
        else if(curEvent.transition == 3) {
            printstatus(curEvent, proc[id]);
            Event e(cpucycles, id, 1);
            processor.putEvent(e);
            scheduler->add_process(proc[id]);
        }
        // Running -> Ready (Pre-emption) ##TODO
        else if(curEvent.transition == 4) {
            printstatus(curEvent, proc[id]);
            Event e(cpucycles, id, 1);
            processor.putEvent(e);
            scheduler->add_process(proc[id]);
        }
        //done
        else if(curEvent.transition == 5) {
            printstatus(curEvent, proc[id]);
            proc[id].setFinishingTime(cpucycles);
        }

    }
}

int main(int argc, char *argv[]) {
    pFile = fopen(argv[1], "r");
    rFile = fopen(argv[2], "r");
    
    int c, s = -1;
    while ((c = getopt (argc, argv, "s:")) != -1) {
            if(c == 's') {
                if(optarg[0] == 'F') s = 0;

                switch(s) {
                    case 0:
                        scheduler = new FCFSScheduler(0);
                        break;
                    default:
                        abort();    
                }   
                
            }
        
        
    }


    // TODO
    char buf[80];
    fgets(buf, 80, rFile);

    proc = getProcesses();

    //scheduler = new FCFSScheduler(0);

    for (int i = 0; i < proc.size(); ++i) {
        processor.putEvent(Event(proc[i].getArrivalTime(), proc[i].getPid(), 0));
    }

    simulate();


    fclose(rFile);
    fclose(pFile);
    return 0;
}

