#include <iostream>
#include <queue>
#include <vector>
#include "Process.h"

constexpr int TIME_QUANTUM = 3;

void queueNewArrivals(const std::vector<Process>& allProcesses, std::queue<Process*>& readyQueue, size_t& index, int timeUnit) {
    while (index < allProcesses.size() && allProcesses[index].getArrivalTime() == timeUnit) {
        readyQueue.push(const_cast<Process*>(&allProcesses[index])); // add pointer to queue
        index++;
    }
}

int main() {
    // Predefined processes that are scheduled to run
    std::vector<Process> allProcesses = {
        // burst, arrival
        Process(5, 0),
        Process(10, 1),
        Process(1, 2),
        Process(6, 3),
        Process(1, 4),
        Process(7, 4),

    };

    std::queue<Process*> readyQueue;
    int timeUnit = 0;
    size_t index = 0;

    // Run until all processes are finished
    while (index < allProcesses.size() || !readyQueue.empty()) {
        queueNewArrivals(allProcesses, readyQueue, index, timeUnit);

        if (!readyQueue.empty()) {
            Process* p = readyQueue.front();
            readyQueue.pop();

            int runTime = std::min(TIME_QUANTUM, p->getBurstTimeRemaining());

            // Run process, and between every burst, check for new arrivals
            for (int i = 0; i < runTime; i++) {
                p->executeSingleBurst(timeUnit);
                std::cout << p->getPid() << " ";
                
                timeUnit++;

                // Check for arrivals every cycle
                queueNewArrivals(allProcesses, readyQueue, index, timeUnit);
            }

            // Push back into readyQueue if process has not finished
            if (p->getBurstTimeRemaining() > 0) {
                readyQueue.push(p);
            }
        } else {
            // CPU idle
            timeUnit++;
            std::cout << "X ";
        }
    }

    Process::printProcessListStats(allProcesses);
    return 0;
}
