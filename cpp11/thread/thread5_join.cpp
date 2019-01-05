/*******************************************************************************
 *      file name: thread5_join.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/05-12:33:04                              
 *  modified time: 2019/01/05-12:33:04                              
 *******************************************************************************/
#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
  // simulate expensive operation
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar()
{
  // simulate expensive operation
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
  std::cout << "starting first helper...\n";
  std::thread helper1(foo);

  std::cout << "starting second helper...\n";
  std::thread helper2(bar);

  std::cout << "waiting for helpers to finish..." << std::endl;
  helper1.join();
  helper2.join();

  std::cout << "done!\n";
}
