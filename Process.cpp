#include "Process.h"

// define static member
int Process::rollingPid = 1;

Process::Process(int burstTime, int arrivalTime)
    : pid(rollingPid++),
      burstTime((burstTime >= 0) ? burstTime : 0),
      arrivalTime((arrivalTime >= 0) ? arrivalTime : 0)
{}

Process::Process(int burstTime, int arrivalTime, int priority)
    : pid(rollingPid++),
      burstTime((burstTime >= 0) ? burstTime : 0),
      arrivalTime((arrivalTime >= 0) ? arrivalTime : 0),
      priority(priority)
{}

int Process::getPid() const {
    return pid;
}

int Process::getArrivalTime() const {
    return arrivalTime;
}

int Process::getBurstTime() const {
    return burstTime;
}

int Process::getPriority() const {
    return priority;
}

void Process::setBurstTime(int burst) {
    burstTime = (burst >= 0) ? burst : 0;
}

void Process::setPriority(int value) {
    priority = value;
}