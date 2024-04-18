/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Jeremiah Shue
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */


#include "scheduler_fcfs.h"
#include <vector>

SchedulerFCFS::SchedulerFCFS() {
}


SchedulerFCFS::~SchedulerFCFS() {}

void SchedulerFCFS::init(std::vector<PCB>& process_list) {
    this->process_list = process_list;
}

void SchedulerFCFS::print_results() {
    Scheduler::print_results(process_list);
}

void SchedulerFCFS::simulate() {
    
    int timestep = 0;
    // Go through in order, increment timestep, and populate each process's end time
    for (auto pit = process_list.begin(); pit < process_list.end(); pit++) {
        printf("Running process %s for %d time units\n", pit->name.c_str(), pit->burst_time);
        pit->end_time = timestep + pit->burst_time;
        timestep += pit->burst_time;
    }
}
