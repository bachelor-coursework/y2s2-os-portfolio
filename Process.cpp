#include <iomanip>
#include <iostream>
#include <vector>
#include "Process.h"

// define static member
int Process::rollingPid = 1;

Process::Process(int burstTime, int arrivalTime)
    : pid(rollingPid++),
      arrivalTime((arrivalTime >= 0) ? arrivalTime : 0),
      burstTime((burstTime >= 0) ? burstTime : 0),
      burstTimeRemaining((burstTime >= 0) ? burstTime : 0)
{}

Process::Process(int burstTime, int arrivalTime, int priority)
    : pid(rollingPid++),
      arrivalTime((arrivalTime >= 0) ? arrivalTime : 0),
      burstTime((burstTime >= 0) ? burstTime : 0),
      burstTimeRemaining((burstTime >= 0) ? burstTime : 0),
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

int Process::getBurstTimeRemaining() const {
    return burstTimeRemaining;
}

int Process::getPriority() const {
    return priority;
}

int Process::getStartingTime() const {
    return startingTime;
}

int Process::getEndTime() const {
    return endTime;
}

int Process::getTurnaroundTime() const {
    return turnaroundTime;
}

int Process::getWaitingTime() const {
    return waitingTime;
}

void Process::setBurstTimeRemaining(int burst) {
    burstTimeRemaining = (burst >= 0) ? burst : 0;
}

void Process::setPriority(int value) {
    priority = value;
}

void Process::printStatsHeader() {
    std::cout << std::setw(5) << "PID"
              << std::setw(10) << "Arrival"
              << std::setw(8) << "Burst"
              << std::setw(10) << "Start"
              << std::setw(8) << "End"
              << std::setw(8) << "TAT"
              << std::setw(8) << "WT"
              << std::endl;
}

void Process::printStats() const {
    std::cout << std::setw(5) << getPid()
                << std::setw(10) << getArrivalTime()
                << std::setw(8) << getBurstTime()
                << std::setw(10) << getStartingTime()
                << std::setw(8) << getEndTime()
                << std::setw(8) << getTurnaroundTime()
                << std::setw(8) << getWaitingTime() 
                << std::endl;
}

void Process::printProcessListStats(const std::vector<Process>& processes) {
    std::cout << "\n\nProcess stats:\n";
    printStatsHeader();

    double totalTT = 0;
    double totalWT = 0;

    for (const auto& p : processes) {
        totalTT += p.getTurnaroundTime();
        totalWT += p.getWaitingTime();
        p.printStats();
    }

    std::cout << "\nAverage Turnaround Time: " << (totalTT / processes.size()) << "\n";
    std::cout << "Average Waiting Time: " << (totalWT / processes.size()) << "\n";
}

void Process::executeSingleBurst(int currentCPUCycle) {
    if (startingTime == -1) startingTime = currentCPUCycle;

    if (burstTimeRemaining > 0) burstTimeRemaining--;

    if (burstTimeRemaining == 0 && endTime == -1) {
        endTime = currentCPUCycle + 1; // process finishes at the end of this cycle
        turnaroundTime = endTime - arrivalTime;
        waitingTime = turnaroundTime - burstTime;
    }
};