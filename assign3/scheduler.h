/**
* Assignment 3: CPU Scheduler
 * @file scheduler.h
 * @author Jeremiah Shue
 * @brief This is the header file for the base Scheduler class. Specific schedulers, e.g. FCFS, SJF and RR, inherit
 *        this base class.
 * @version 0.1
 */

#pragma once

#include <vector>
#include "pcb.h"

using namespace std;
/**
 * @brief This is the base class for the scheduler.
 */
class Scheduler {
public:
    /**
     * @brief Construct a new Scheduler object
     */
    Scheduler() {}
    /**
     * @brief Destroy the Scheduler object
     */
    virtual ~Scheduler() {}
    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    virtual void init(std::vector<PCB>& process_list) = 0;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    virtual void print_results() = 0;

    void print_results(std::vector<PCB>& process_list) {
            float tot_turnaround = 0;
    float tot_wait = 0;
    for (auto pit = process_list.begin(); pit < process_list.end(); pit++) {
        printf("%s turnaround time = %d, waiting time = %d\n", pit->name.c_str(), pit->end_time, pit->end_time - pit->burst_time);
        tot_turnaround += pit->end_time;
        tot_wait += (pit->end_time - pit->burst_time);
    }
    printf ("Average waiting time: %f, Average turnaround time: %f\n", tot_wait / process_list.size(), tot_turnaround / process_list.size());
    }


    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    virtual void simulate() = 0;
};