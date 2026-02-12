#include <iostream>
#include <queue>
#include <vector>
#include "Process.h"

constexpr int TIME_QUANTUM = 3;

void queueNewArrivals(const std::vector<Process>& allProcesses, std::queue<Process*>& readyQueue, size_t& index, int cpuCycle) {
    while (index < allProcesses.size() && allProcesses[index].getArrivalTime() == cpuCycle) {
        readyQueue.push(const_cast<Process*>(&allProcesses[index])); // add pointer to queue
        index++;
    }
}

int main() {
    // Predefined processes that are scheduled to run
    std::vector<Process> allProcesses = {
        // burst, arrival
        Process(5, 0),
        Process(4, 1),
        Process(6, 3),
        Process(1, 4)
    };

    std::queue<Process*> readyQueue;
    int cpuCycle = 0;
    size_t index = 0;

    // Run until all processes are finished
    while (index < allProcesses.size() || !readyQueue.empty()) {
        queueNewArrivals(allProcesses, readyQueue, index, cpuCycle);

        if (!readyQueue.empty()) {
            Process* p = readyQueue.front();
            readyQueue.pop();

            int runTime = std::min(TIME_QUANTUM, p->getBurstTime());

            // Run process, and between every burst, check for new arrivals
            for (int i = 0; i < runTime; i++) {
                cpuCycle++;
                p->setBurstTime(p->getBurstTime() - 1);
                std::cout << p->getPid() << " ";

                queueNewArrivals(allProcesses, readyQueue, index, cpuCycle);
            }

            // Push back into readyQueue if process has not finished
            if (p->getBurstTime() > 0) {
                readyQueue.push(p);
            }
        } else {
            // CPU idle
            cpuCycle++;
            std::cout << "X ";
        }
    }

    std::cout << std::endl;
    return 0;
}
