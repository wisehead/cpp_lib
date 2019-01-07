/*******************************************************************************
 *      file name: thread9_hardware_concurrency.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/07-17:36:21                              
 *  modified time: 2019/01/07-17:36:21                              
 *******************************************************************************/
#include <iostream>
#include <thread>

int main() {
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported.\n";
}
