/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/04-17:15:27                              
 *  modified time: 2020/08/04-17:15:27                              
 *******************************************************************************/
#include <iostream>
#include "include/eteran/cpp-utilities/bitwise.h"
int main() {
    int x = 5;
    int y = bitwise::rotate_right(x, 15);
    int z = bitwise::rotate_left(x, 20);
    std::cout<<"x:"<<x<<std::endl;
    std::cout<<"y:"<<y<<"    z:"<<z<<std::endl;
}
