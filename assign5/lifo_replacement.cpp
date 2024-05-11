/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Jeremiah Shue
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */


#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{}


LIFOReplacement::~LIFOReplacement() {
    
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    page_table[page_num].valid = true;
    frames.push_back(page_num);
    
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    //DIFFERENT from FIFO: we erase the end of the vector (the side that we insert)
    auto victim = frames.back();
    page_table[victim].valid=false;
    frames.pop_back();
    load_page(page_num);
    return victim;
}