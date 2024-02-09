/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Jeremiah Shue
 * @brief This is the implementation file for the PCBTable class.
 */

#include "pcbtable.h"
#include <list>

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
    table.clear();
    for (int i = 0; i < size; i++) {
        table.push_back(new PCB(i));
    }
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
    for (auto it = table.begin(); it != table.end(); it++) {
        delete *it;
    }
    table.clear();
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    auto it = table.begin();
    for (int i = 0; i < idx; i++) {
        it++;
    }
    return *it;
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    auto it = table.begin();
    for (int i = 0; i < idx; i++) {
        it++;
    }
    table.insert(it, pcb);
}
