/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author Jeremiah Shue
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */
#pragma once

#include "pcb.h"

typedef PCB* T;
/**
 * @brief A queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * This priority queue is implemented using a max-heap.
 */
class ReadyQueue {
private:

    T *heaparray; // pointer to the array holding the heap
    int capacity;   // the capacity of the heap
    int count;      // how many elements are in the heap

    /**
     * @brief Copy constructor
     * @param other the queue to be copied
     */
    ReadyQueue(const ReadyQueue &other);

    /**
     * @brief Assignment operator
     * @param other the queue to be copied
     * @return ReadyQueue& a reference to the queue
     */
    ReadyQueue &operator=(const ReadyQueue &other);

    void resizeArray();
    /**
     * @brief reorganizes the heap to maintain the heap property,
     *        by using the percolateDown and/or percolateUp functions.
     *
     */
    void heapify();

    /**
     * @brief removes the maximum element from the heap, maintaining the heap property.
     * @return int the maximum element. return -1 if heap is empty
     */
    T removeMax();

    // /*
    //  * @brief converts the heap into a string
    //  */
    // string toString();

    // @brief Prints the heap
    void printHeap();

    /**
     * @brief Inserts a new element into the heap. It maintains the heap property.
     * @param value the value to be inserted
     */
    void insert(T value);

    /**
     * @brief Change the key of the element at position i to the new value.
     *        It should percolate up or down to maintain the heap property after the change.
     * @param i the position of the element to be decreased
     * @param value the new value
     */
    void changeKey(int i, T new_val);

    // Helper functions.
    /**
     * @brief Returns the left child of the node at index
     */
    int leftChild(int index)
    {
        return 2 * index + 1;
    }
    /**
     * @brief Returns the right child of the node at index
     */
    int rightChild(int index)
    {
        return 2 * index + 2;
    };

    /**
     * @brief Returns the index of the parent of the child located at index
     */
    int parent(int index)
    {
        if (index <= 0 || index >= count)
            return -1;
        return (index - 1) / 2;
    }

    /**
     * @brief Percolates down the node at index to maintain the heap property
     *
     * @param index
     */
    // void percolateDown(Heap *h, int index);
    void percolateDown(int index);
    void percolateDownSubheap(int index, int size);

    // void percolateDownBinary(Heap* h, int index);
    /**
     * @brief Percolates up the node at index to maintain the heap property
     *
     * @param index
     */
    // void percolateUp(Heap *h, int index);
    void percolateUp(int index);

    /**
     * @brief swaps the values of the two nodes at index1 and index2
     *
     * @param index1
     * @param index2
     */
    void swap(int index1, int index2);

    /**
     * @brief returns the max value in the heap
     *
     * @return int return -1 if the heap is empty, otherwise return the max value in the heap
     */
    T getMax() const;

    // TODO: add your private member variables here
    // choose a data structure for the ReadyQueue. No STL class is allowed.

public:
    /**
     * @brief Construct a new ReadyQueue object
     *
     */
    ReadyQueue();

    /**
     * @brief Destructor
     */
    ~ReadyQueue();

	// You may add additional member functions, but don't change the definitions of the following four member functions.

    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
	void addPCB(PCB* pcbPtr);

    /**
     * @brief Remove and return the PCB with the highest priority from the queue
     *
     * @return PCB*: the pointer to the PCB with the highest priority
     */
	PCB* removePCB();

    /**
     * @brief Returns the number of elements in the queue.
     *
     * @return int: the number of PCBs in the queue
     */
    int size() { return count; }

     /**
      * @brief Display the PCBs in the queue.
      */
	void displayAll();

};