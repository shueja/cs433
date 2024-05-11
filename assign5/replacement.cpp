/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Jeremiah Shue
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */

#include <iostream>
#include "replacement.h"



// Constructor
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages), max_frames(num_frames)
{
}

// Destructor
Replacement::~Replacement()
{
    // TOOD: Add your code here
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    references++;
    auto page = getPageEntry(page_num);
    if (page.valid) {
        touch_page(page_num);
    } else {
        faults++;
        if (frames_in_mem() < max_frames) {
            load_page(page_num);
        } else {
            replacements++;
            replace_page(page_num);
        }
        return true;
    }
    return false;
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
		std::cout << "Number of references: \t\t" <<references << std::endl;
		std::cout << "Number of page faults: \t\t" << faults<< std::endl;
		std::cout << "Number of page replacements: \t"  << replacements<< std::endl;
}
