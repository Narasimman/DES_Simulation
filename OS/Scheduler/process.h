#ifndef PROCESS_H
#define PROCESS_H

#include <string>

using namespace std;

class Process {
    private:
        int pid;
		// Input Parameters
        int arrivalTime;
		int totalCPUTime;
        int maxCPUBurstTime;
        int maxIOBurstTime;
		int priority;
        int dynPrio;

		// Process State
		int state;
        // remainig time to execute
        int remainingCPU;
        // remainig IO time
        int remainingIO;
        // remaining cpu burst in case of pre emption
        int remainingBurst;
        // time of the previous state
        int lastReady;
        int prevStateTime;

		//Output parameters
		int finishingTime;
		int turnaroundTime;
		int iOTime;
		int cpuWaitingTime;

    public:
        // Constructors
        Process();
        Process(int, int, int, int, int);

        // getters and setters

        int getPid();
        void setPid(int);
        int getArrivalTime();
        void setArrivalTime(int);
        int getTotalCPUTime();
        void setTotalCPUTime(int);
        int getMaxCPUBurstTime();
        void setMaxCPUBurstTime(int);
        int getMaxIOBurstTime();
        void setMaxIOBurstTime(int);
        int getPriority();
        void setPriority(int);
        int getDynPrio();
        void setDynPrio(int);

        int getState();
        void setState(int);
        int getRemainingCPU();
        void setRemainingCPU(int);
        int getIOBurst();
        void setIOBurst(int);
        int getRemainingBurst();
        void setRemainingBurst(int);
        int getPrevStateTime();
        void setPrevStateTime(int);
        int getLastReady();
        void setLastReady(int);

        int getFinishingTime();
        void setFinishingTime(int);
        int getTurnaroundTime();
        void setTurnaroundTime(int);
        int getIOTime();
        void setIOTime(int);
        int getCpuWaitingTime();
        void setCpuWaitingTime(int);
};


#endif

