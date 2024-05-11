/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.h
 * @author Jeremiah Shue
 * @brief header file for the buffer class
 * @version 0.1
 */

#ifndef ASSIGN4_BUFFER_H
#define ASSIGN4_BUFFER_H

// Define the data type of the buffer items
#include <pthread.h>
#include <vector>

typedef int buffer_item;

/**
 * @brief The bounded buffer class. The number of items in the buffer cannot
 * exceed the size of the buffer.
 */
class Buffer {
private:
  std::vector<buffer_item> vec;
  int size;
  pthread_mutex_t lock;
  pthread_cond_t new_data_cond, new_space_cond;
public:
  
  /**
   * @brief Construct a new Buffer object
   * @param size the size of the buffer
   */
  Buffer(int size = 5);

  /**
   * @brief Destroy the Buffer object
   */
  ~Buffer();

  /**
   * @brief Insert an item into the buffer.
   * This will block until it can acquire the mutex.
   * @param item the item to insert
   * @return true if successful
   * @return false if buffer is full.
   */
  bool insert_item(buffer_item item);

  /**
   * @brief Remove an item from the buffer
   * This will block until it can acquire the mutex.
   * @param item the item to remove
   * @return true if successful
   * @return false if buffer is empty
   */
  bool remove_item(buffer_item *item);

  /**
   * @brief Get the size of the buffer
   * @return the size of the buffer
   */
  int get_size();

  /**
   * @brief Get the number of items in the buffer
   * @return the number of items in the buffer
   */
  int get_count();

  /**
   * @brief Chceck if the buffer is empty
   * @return true if the buffer is empty, else false
   */
  bool is_empty();
  /**
   * @brief Check if the buffer is full
   * @return true if the buffer is full, else false
   */
  bool is_full();

  /**
   * @brief Print the buffer
   */
  void print_buffer();
};
#endif // ASSIGN4_BUFFER_H
