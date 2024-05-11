/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Jeremiah Shue
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"
#include "replacement.h"

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{}

FIFOReplacement::~FIFOReplacement() {}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    page_table[page_num].valid = true;
    frames.push(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    auto victim = frames.front();
    page_table[victim].valid=false;
    frames.pop();
    load_page(page_num);
    return victim;
}