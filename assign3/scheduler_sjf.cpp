/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Jeremiah Shue
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_sjf.h"
#include <algorithm>
#include <vector>

SchedulerSJF::SchedulerSJF() {
}


SchedulerSJF::~SchedulerSJF() {}

void SchedulerSJF::init(std::vector<PCB>& process_list) {
    this->process_list = process_list;
}

void SchedulerSJF::print_results() {
    Scheduler::print_results(process_list);
}

void SchedulerSJF::simulate() {
    
    int timestep = 0;
    
    auto list = vector<PCB>(process_list);
    sort(process_list.begin(), process_list.end(), [](PCB pcb1, PCB pcb2){return pcb1.burst_time < pcb2.burst_time;});

    for (auto pit = process_list.begin(); pit < process_list.end(); pit++) {
        printf("Running process %s for %d time units\n", pit->name.c_str(), pit->burst_time);
        pit->end_time = timestep + pit->burst_time;
        timestep += pit->burst_time;
    }
    sort(process_list.begin(), process_list.end(), [](PCB pcb1, PCB pcb2){return pcb1.id < pcb2.id;});
}
