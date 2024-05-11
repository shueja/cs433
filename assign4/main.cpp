/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Jeremiah Shue
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
#include <iostream>
#include "buffer.h"
#include <pthread.h>
#include <string>
#include <unistd.h>

using namespace std;

// global buffer object
Buffer buffer;

// Producer thread function
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
    }
}

// Consumer thread function
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        exit(1);
    }
    const int main_sleep = stoi(argv[1]);
    const int prod_threads = stoi(argv[2]);
    const int cons_threads = stoi(argv[3]);
    buffer = Buffer(5);
    for (int i = 1; i <= prod_threads; i++) {
        pthread_t thread;
        pthread_create(&thread, NULL, producer, &i);
    }
    for (int i = 1; i <= cons_threads; i++) {
        pthread_t thread;
        pthread_create(&thread, NULL, consumer, &i);
    }
    usleep(main_sleep * 1e6);
}
