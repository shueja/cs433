/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Jeremiah Shue
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */



#include "scheduler_priority.h"
/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Jeremiah Shue
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */

#include <algorithm>
#include <vector>

SchedulerPriority::SchedulerPriority() {
}


SchedulerPriority::~SchedulerPriority() {}

void SchedulerPriority::init(std::vector<PCB>& process_list) {
    this->process_list = process_list;
}

void SchedulerPriority::print_results() {
    Scheduler::print_results(process_list);
}

void SchedulerPriority::simulate() {
    
    int timestep = 0;
    // Sort existing list into priority order
    sort(process_list.begin(), process_list.end(), [](PCB pcb1, PCB pcb2){return pcb1.priority > pcb2.priority;});
    // Go through in order, increment timestep, and populate each process's end time
    for (auto pit = process_list.begin(); pit < process_list.end(); pit++) {
        printf("Running process %s for %d time units\n", pit->name.c_str(), pit->burst_time);
        pit->end_time = timestep + pit->burst_time;
        timestep += pit->burst_time;
    }
    // Sort back into original order
    sort(process_list.begin(), process_list.end(), [](PCB pcb1, PCB pcb2){return pcb1.id < pcb2.id;});
}