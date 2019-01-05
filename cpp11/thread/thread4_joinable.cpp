/*******************************************************************************
 *      file name: thread4_joinable.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/05-12:27:51                              
 *  modified time: 2019/01/05-12:27:51                              
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
  std::thread t;
  std::cout << "before starting, joinable: " << t.joinable() << '\n';

  t = std::thread(foo);
  std::cout << "after starting, joinable: " << t.joinable() << '\n';

  t.join();
}
