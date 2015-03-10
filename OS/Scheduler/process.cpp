#include "process.h"

using namespace std;

Process::Process() {

}

Process::Process(int id, int a, int t, int c, int i) {
    pid = id;
    arrivalTime = a;
    remainingCPU = totalCPUTime = t;
    maxCPUBurstTime = c;
    maxIOBurstTime = i;

    state = finishingTime = remainingBurst = remainingIO = prevStateTime = turnaroundTime = iOTime = cpuWaitingTime = 0;
}

int Process::getPid() {
    return pid;
}

void Process::setPid(int id) {
    pid = id;
}
int Process::getArrivalTime(){
    return arrivalTime;
}
void Process::setArrivalTime(int t) {
    arrivalTime = t;
}
int Process::getTotalCPUTime() {
    return totalCPUTime;
}
void Process::setTotalCPUTime(int t){
    totalCPUTime = t;
}
int Process::getMaxCPUBurstTime() {
    return maxCPUBurstTime;
}
void Process::setMaxCPUBurstTime(int t) {
    maxCPUBurstTime = t;
}
int Process::getMaxIOBurstTime() {
    return maxIOBurstTime;
}
void Process::setMaxIOBurstTime(int t) {
    maxIOBurstTime = t;
}
int Process::getPriority() {
    return priority;
}
void Process::setPriority(int p) {
    priority = p;
}
int Process::getDynPrio(){
    return dynPrio;
}
void Process::setDynPrio(int p) {
    dynPrio = p;
}
int Process::getState() {
    return state;
}
void Process::setState(int s) {
    state = s;
}
int Process::getRemainingCPU() {
    return remainingCPU;
}
void Process::setRemainingCPU(int t) {
    remainingCPU = t;
}
int Process::getIOBurst() {
    return remainingIO;
}
void Process::setIOBurst(int t) {
    remainingIO = t;
}
int Process::getRemainingBurst() {
    return remainingBurst;
}
void Process::setRemainingBurst(int b) {
    remainingBurst = b;    
}
int Process::getPrevStateTime() {
    return prevStateTime;
}
void Process::setPrevStateTime(int t) {
    prevStateTime = t;
}
int Process::getLastReady() {
    return lastReady;
}
void Process::setLastReady(int t) {
    lastReady = t;
}
int Process::getFinishingTime() {
    return finishingTime;
}
void Process::setFinishingTime(int t) {
    finishingTime = t;
}
int Process::getTurnaroundTime() {
    turnaroundTime = finishingTime - arrivalTime;
    return turnaroundTime;
}
void Process::setTurnaroundTime(int t) {
    turnaroundTime = t;
}
int Process::getIOTime() {
    return iOTime;
}
void Process::setIOTime(int t) {
    iOTime = t;
}
int Process::getCpuWaitingTime() {
    return cpuWaitingTime;
}
void Process::setCpuWaitingTime(int t) {
    cpuWaitingTime = t;
}

