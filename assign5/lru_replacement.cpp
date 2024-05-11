/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Jeremiah Shue
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */


#include "lru_replacement.h"
#include "replacement.h"
#include <iostream>
#include <ostream>

LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
}

LRUReplacement::~LRUReplacement()
{
    
}

void LRUReplacement::update_map(int page_num){
    usage_list.push_front(page_num);
    map[page_num]=usage_list.begin();
}
// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    Replacement::touch_page(page_num);
    usage_list.erase(map[page_num]);
    update_map(page_num);
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    page_table[page_num].valid = true;
    update_map(page_num);
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {    
    //remove last page and load in page_num;
    int last = usage_list.back();
    usage_list.pop_back();
    map.erase(last);
    page_table[last].valid = false;
    load_page(page_num);
    return last;
}

int LRUReplacement::frames_in_mem() {
    return usage_list.size();
}