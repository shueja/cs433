/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Jeremiah Shue
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_RR_H
#define ASSIGN3_SCHEDULER_RR_H

#include "scheduler.h"

class SchedulerRR : public Scheduler {
private:
    int time_quantum;
    std::vector<PCB> process_list;
public:
    /**
     * @brief Construct a new SchedulerRR object
     */
    SchedulerRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerRR object
     */
    ~SchedulerRR() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;
};


#endif //ASSIGN3_SCHEDULER_RR_H
