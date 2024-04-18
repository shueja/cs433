/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Jeremiah Shue
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */


#include "scheduler_rr.h"

#include <queue>
#include <vector>

SchedulerRR::SchedulerRR(int time_quantum) : time_quantum(time_quantum) {
}


SchedulerRR::~SchedulerRR() {}

void SchedulerRR::init(std::vector<PCB>& process_list) {
    this->process_list = process_list;
}

void SchedulerRR::print_results() {
    Scheduler::print_results(process_list);
}

void SchedulerRR::simulate() {
    
    int timestep = 0;
    
    auto list = vector<PCB>(process_list);
    auto readyQueue= queue<PCB*>();
    for (auto pit = process_list.begin(); pit < process_list.end(); pit++) {
        readyQueue.emplace(&*pit);
    }
    while (!readyQueue.empty()) {
        PCB* next = readyQueue.front();
        readyQueue.pop();
        auto time = 0;
        auto isInterrupted = next->remaining_burst_time > time_quantum;
        if (isInterrupted) {
            time = time_quantum;
        } else {
            time = next->remaining_burst_time;
        }
        printf("Running process %s for %d time units\n", next->name.c_str(), time);
        timestep += time;
        next->remaining_burst_time -= time;
        if (isInterrupted) {
            readyQueue.push(next);
        } else {
            next->end_time = timestep;
        }
        
    }
}
