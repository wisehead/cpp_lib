/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/04-16:27:06                              
 *  modified time: 2020/08/04-16:27:06                              
 *******************************************************************************/
#include <iostream>
#include "include/eteran/cpp-utilities/bitset.h"
int main() {
    std::bitset<32> bs;
    bs[4]  = true;
    bs[10] = true;
    int bit_l = bitset::find_first(bs); // returns 4
    int bit_h = bitset::find_last(bs); // returns 10
    std::cout<<"bit_l:"<<bit_l<<"    bit_h:"<<bit_h<<std::endl;
}
