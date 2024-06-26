#include <iostream>
#include "readyqueue.h"

using namespace std;

/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
    capacity = 100;
    count = 0;
    heaparray = new T[capacity];
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    delete[] heaparray;
}

ReadyQueue::ReadyQueue(const ReadyQueue &other) {
    this->capacity = other.capacity;
    this->count = other.count;
    this->heaparray = new T[count];
    for (int i = 0; i < count; i++)
    {
        this->heaparray[i] = other.heaparray[i];
    }
}

ReadyQueue& ReadyQueue::operator=(const ReadyQueue &other) {
        if (&other == this)
    {
        return *this;
    }
    this->capacity = other.capacity;
    this->count = other.count;
    delete[] heaparray;
    this->heaparray = new T[count];
    for (int i = 0; i < count; i++)
    {
        this->heaparray[i] = other.heaparray[i];
    };
    return *this;
}
/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    pcbPtr->setState(ProcState::READY);
    insert(pcbPtr);
    // When adding a PCB to the queue, you must change its state to READY.
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    PCB* max = removeMax();
    max->setState(ProcState::RUNNING);
    return max;
    // When removing a PCB from the queue, you must change its state to RUNNING.
}


/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    printHeap();
}
// @brief gets the maximum value in the heap
// @return the highest value integer in the heap
T ReadyQueue::getMax() const
{
    if (count <= 0)
    {
        return nullptr;
    }
    else
    {
        return heaparray[0];
    }
}

/**
 * @brief   organizes the values in the heap to satisfy heap property.
 */
void ReadyQueue::heapify()
{
    // Heapify numbers array
    int i = count / 2 - 1;
    while (i >= 0)
    {
        percolateDown(i);
        i--;
    }
}

/**
 * @brief  Runs percolate down on the heap for the node stored in index.
 */
void ReadyQueue::percolateDownSubheap(int index, int size)
{

    int childIndex = 2 * index + 1;
    T value = heaparray[index];

    while (childIndex < size)
    {
        T maxValue = value;
        int maxIndex = -1;
        int i = 0;
        while (i < 2 && i + childIndex < size)
        {
            if (heaparray[i + childIndex] > maxValue)
            {
                maxValue = heaparray[i + childIndex];
                maxIndex = i + childIndex;
            }
            i++;
        }

        if (maxValue == value)
        {
            return;
        }
        else
        {
            swap(index, maxIndex);
            index = maxIndex;
            childIndex = 2 * index + 1;
        }
    }
}

void ReadyQueue::percolateDown(int index)
{
    percolateDownSubheap(index, count);
}

/**
 * @brief  Runs percolate up on the heap for the node stored in index.
 */
void ReadyQueue::percolateUp(int index)
{
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (heaparray[index] <= heaparray[parentIndex])
        {
            return;
        }
        else
        {
            swap(index, parentIndex);
            index = parentIndex;
        }
    }
}

void ReadyQueue::resizeArray()
{
    cout << "resize" << endl;
    int newCapacity = capacity * 4;
    T *newArray = new T[newCapacity];
    if (newArray)
    {
        for (int i = 0; i < capacity; i++)
        {
            newArray[i] = heaparray[i];
        }

        delete[] heaparray;
        heaparray = newArray;

        capacity = newCapacity;
    }
}
/**
 * @brief  inserts a value into the heap
 *
 */
void ReadyQueue::insert(T value)
{
    if (count == capacity)
    {
        resizeArray();
    }

    heaparray[count] = value;
    count++;
    percolateUp(count - 1);
}

/**
 * @brief  Removes the max value from the heap
 * @return the value that was removed
 */
T ReadyQueue::removeMax()
{
    T maxValue = heaparray[0];
    T replaceValue = heaparray[--count];
    if (count > 0)
    {
        heaparray[0] = replaceValue;
        percolateDown(0);
    }
    return maxValue;
}

// // @brief converts the heap into a string
// string ReadyQueue::toString()
// {
//     string s = "[ ";
//     for (int i = 0; i < count; i++)
//     {
//         s += heaparray[i]->display() + " ";
//     }
//     s += "]";
//     return s;
// }

/**
 * @brief  Prints the values in the heap
 */
void ReadyQueue::printHeap()
{
    for (int i = 0; i < count; i++)
    {
        heaparray[i]->display();
    }
    cout << endl;
}

/**
 * @brief  Prints the values in an array
 */
void printArray(T values[], int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        values[i]->display();
    }
}

/**
 * @brief  Swaps the values in the heap at index1 and index2
 */
void ReadyQueue::swap(int index1, int index2)
{
    T temp = heaparray[index1];
    heaparray[index1] = heaparray[index2];
    heaparray[index2] = temp;
}
