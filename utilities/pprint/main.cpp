/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/04-18:46:06                              
 *  modified time: 2020/08/04-18:46:06                              
 *******************************************************************************/
#include <iostream>
#include "include/eteran/cpp-utilities/pprint.h"
int main() {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };
    std::cout << pprint::to_string(v) << std::endl;
    std::list<std::vector<int> > v2 = { {1, 2, 3}, {4, 5, 6, 7} };
    std::cout << pprint::to_string(v2) << std::endl;
}
