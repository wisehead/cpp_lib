/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/04-17:29:29                              
 *  modified time: 2020/08/04-17:29:29                              
 *******************************************************************************/
#include <iostream>
#include <stdio.h>
#include "include/eteran/cpp-utilities/algorithm.h"
int main() {
    int n = algorithm::static_max(1, 2, 3, 10, 5, 6);
    printf("%d\n", n); // prints 10
    //std::cout<<"bit_l:"<<bit_l<<"    bit_h:"<<bit_h<<std::endl;
}
