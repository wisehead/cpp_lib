/*******************************************************************************
 *      file name: thread10_this_thread_get_pid.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/07-17:47:57                              
 *  modified time: 2019/01/07-17:47:57                              
 *******************************************************************************/
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex g_display_mutex;

void foo()
{
  std::thread::id this_id = std::this_thread::get_id();

  g_display_mutex.lock();
  std::cout << "thread " << this_id << " sleeping...\n";
  g_display_mutex.unlock();

  std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
  std::thread t1(foo);
  std::thread t2(foo);

  t1.join();
  t2.join();
}
