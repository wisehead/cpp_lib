/*******************************************************************************
 *      file name: thread12_this_thread_sleepfor.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/07-18:45:03                              
 *  modified time: 2019/01/07-18:45:03                              
 *******************************************************************************/
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
  std::cout << "Hello waiter" << std::endl;
  std::chrono::milliseconds dura( 2000 );
  std::this_thread::sleep_for( dura );
  std::cout << "Waited 2000 ms\n";
}
