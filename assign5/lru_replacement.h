/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.h
 * @author Jeremiah Shue
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */


#pragma once

// Remember to add comments to your code

#include "replacement.h"
#include <list>
#include <unordered_map>

/**
 * @brief A class to simulate the least recently used (LRU) page replacement algorithm.
 */
class LRUReplacement : public Replacement
{
private:
    std::list<int> usage_list; 
  
    // store references of key in cache 
    std::unordered_map<int, std::list<int>::iterator> map; 

public:
	/**
	 * @brief Constructor
	 * @param num_pages 
	 * @param num_frames 
	 */
	LRUReplacement(int num_pages, int num_frames);
	
    /**
    * @brief Destructor
    */
    virtual ~LRUReplacement();

    /**
     * @brief Accesss a page alreay in physical memory
     * It may be overridden in a subclass 
     * @param page_num The logical page number.
     */
    virtual void touch_page(int page_num);

    /**
     * @brief Access an invalid page, but free frames are available.
     * Assign the page to an available  frame, not replacement needed
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Access an invalid page, and there is no free frame.
     * Replace the page with the page that has been in memory the longest.
     * @param page_num The logical page number.
     * @return Selected victim page #
     */
    virtual int replace_page(int page_num);
    void update_map(int page_num);
    int frames_in_mem() override;
};