/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Jeremiah Shue
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */


#include "pagetable.h"
PageTable::PageTable(int num_pages) {
    PageEntry defaultEntry;
    pages.resize(num_pages, defaultEntry);
    for (int i = 0; i < num_pages; i++) {
        pages.at(i).frame_num = i;
    }
}
PageTable::~PageTable() {
    
}