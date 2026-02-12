#include <iostream>
#include <vector>
#include <queue>
#include "Process.h"

struct PriorityComparator {
    bool operator()(Process* a, Process* b) const {
        // FCFS for same priority processes
        if (a->getPriority() == b->getPriority()) {
            return a->getArrivalTime() > b->getArrivalTime(); 
        }
        // Lower value = higher priority
        return a->getPriority() > b->getPriority();
    }
};

void queueNewArrivals(const std::vector<Process>& allProcesses,
                    std::priority_queue<Process*, std::vector<Process*>, PriorityComparator>& readyQueue,
                    size_t& index,
                    int cpuCycle)
{
    while (index < allProcesses.size() && allProcesses[index].getArrivalTime() <= cpuCycle) {
        readyQueue.push(const_cast<Process*>(&allProcesses[index]));
        index++;
    }
}

int main() {
    // Predefined processes that are scheduled to run
    std::vector<Process> allProcesses = {
        // burst, arrival, priority
        Process(5, 0, 2),
        Process(4, 1, 1),
        Process(6, 3, 3),
        Process(1, 4, 2)
    };

    std::priority_queue<Process*, std::vector<Process*>, PriorityComparator> readyQueue;
    size_t index = 0;
    int cpuCycle = 0;

    while (index < allProcesses.size() || !readyQueue.empty()) {
        // Add new arrivals at current CPU cycle
        queueNewArrivals(allProcesses, readyQueue, index, cpuCycle);

        if (!readyQueue.empty()) {
            Process* p = readyQueue.top();
            readyQueue.pop();

            // Run same process until complete
            int burst = p->getBurstTime();
            for (int i = 0; i < burst; i++) {
                cpuCycle++;
                p->setBurstTime(p->getBurstTime() - 1);
                std::cout << p->getPid() << " ";
                
                // Check for arrivals every cycle
                queueNewArrivals(allProcesses, readyQueue, index, cpuCycle);
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
