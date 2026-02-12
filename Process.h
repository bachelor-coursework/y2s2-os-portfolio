#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    static int rollingPid;
    int const pid;
    int const arrivalTime;
    int burstTime;
    int priority = 0;

public:
    Process(int burstTime, int arrivalTime);
    Process(int burstTime, int arrivalTime, int priority);

    int getPid() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;

    void setBurstTime(int burst);
    void setPriority(int value);
};

#endif
