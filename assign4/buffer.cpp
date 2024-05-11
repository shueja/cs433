/**

* Assignment 4: Producer Consumer Problem

 * @file buffer.cpp

 * @author Jeremiah Shue

 * @brief Implementation file for the buffer class

 * @version 0.1

 */



#include "buffer.h"

#include <iostream>

#include <pthread.h>

#include <vector>



    /**

     * @brief Construct a new Buffer object

     * @param size the size of the buffer

     */

    Buffer::Buffer(int size) {

        this->size=size;

        vec.reserve(size);

        pthread_mutex_init(&lock, NULL);

        pthread_cond_init(&new_data_cond, NULL);

        pthread_cond_init(&new_space_cond, NULL);

    }



    /**

     * @brief Destroy the Buffer object

     */

    Buffer::~Buffer(){}



    /**

     * @brief Insert an item into the buffer

     * @param item the item to insert

     * @return true if successful

     * @return false if not successful

     */

    bool Buffer::insert_item(buffer_item item) {

        

        if (is_full()) {

            

            return false;

        }

        pthread_mutex_lock(&lock);

        while (is_full()) {

            pthread_cond_wait(&new_space_cond, &lock);

        }

        vec.push_back(item);

        pthread_mutex_unlock(&lock);

        pthread_cond_signal(&new_data_cond);

        return true;

    }



    /**

     * @brief Remove an item from the buffer

     * @param item the item to remove

     * @return true if successful

     * @return false if not successful

     */

    bool Buffer::remove_item(buffer_item *item){

        if (is_empty()){return false;}

        pthread_mutex_lock(&lock);

        while (is_empty()) {

            pthread_cond_wait(&new_space_cond, &lock);

        }

        *item = vec.front();

        vec.erase(vec.begin());

        pthread_mutex_unlock(&lock);

        pthread_cond_signal(&new_space_cond);

        return true;

    }



    /**

     * @brief Get the size of the buffer

     * @return the size of the buffer

     */

    int Buffer::get_size() {

        return size;

    }



    /**

     * @brief Get the number of items in the buffer

     * @return the number of items in the buffer

     */

    int Buffer::get_count(){

        return vec.size();

    }



    /**

     * @brief Chceck if the buffer is empty

     * @return true if the buffer is empty, else false

     */

    bool Buffer::is_empty(){

        return get_count() == 0;

    }

    /**

     * @brief Check if the buffer is full

     * @return true if the buffer is full, else false

     */

    bool Buffer::is_full() {

        return get_count()==size;

    }



    /**

     * @brief Print the buffer

     */

    void Buffer::print_buffer() {

        std::cout << "Buffer: [";

        for (auto item: vec) {

            std::cout<<" " << item;

            

        }

        std::cout<<"]"<<std::endl;

    }
