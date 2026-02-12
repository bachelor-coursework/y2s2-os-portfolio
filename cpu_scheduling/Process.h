#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    static int rollingPid;
    int const pid;
    int const arrivalTime;
    int const burstTime;
    int burstTimeRemaining;
    int priority = 0;

    // only settable within class
    int startingTime = -1;
    int endTime = -1;
    int turnaroundTime = -1;
    int waitingTime = -1;

public:
    Process(int burstTime, int arrivalTime);
    Process(int burstTime, int arrivalTime, int priority);

    // getters
    int getPid() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getBurstTimeRemaining() const;
    int getPriority() const;
    int getStartingTime() const;
    int getEndTime() const;
    int getTurnaroundTime() const;
    int getWaitingTime() const;

    // setters
    void setBurstTimeRemaining(int burst);
    void setPriority(int value);

    static void printStatsHeader();
    void printStats() const;
    static void printProcessListStats(const std::vector<Process>& processes);

    void executeSingleBurst(int currentCPUCycle);
};

#endif
