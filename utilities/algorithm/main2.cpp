/*******************************************************************************
 *      file name: main2.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/04-17:30:01                              
 *  modified time: 2020/08/04-17:30:01                              
 *******************************************************************************/
#include <iostream>
#include <stdio.h>
#include "include/eteran/cpp-utilities/algorithm.h"
template <int N>
struct Foo {
    static const int value = N * 2;
};

int main() {
    int n = Foo<algorithm::static_max(1, 2, 3, 10, 5, 6)>::value;
    printf("%d\n", n); // prints 20
}
