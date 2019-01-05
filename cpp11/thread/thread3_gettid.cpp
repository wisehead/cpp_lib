/*******************************************************************************
 *      file name: thread3_gettid.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/04-18:43:41                              
 *  modified time: 2019/01/04-18:43:41                              
 *******************************************************************************/
#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
  std::thread t1(foo);
  std::thread::id t1_id = t1.get_id();

  std::thread t2(foo);
  std::thread::id t2_id = t2.get_id();

  std::cout << "t1's id: " << t1_id << '\n';
  std::cout << "t2's id: " << t2_id << '\n';

  t1.join();
  t2.join();
}
