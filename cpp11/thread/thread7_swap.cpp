/*******************************************************************************
 *      file name: thread7_swap.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/05-12:42:06                              
 *  modified time: 2019/01/05-12:42:06                              
 *******************************************************************************/
#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
  std::cout << "start foo() "<< std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "end foo() "<< std::endl;
}

void bar()
{
  std::cout << "start bar() "<< std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "end bar() "<< std::endl;
}

int main()
{
  std::thread t1(foo);
  std::thread t2(bar);

  std::cout << "thread 1 id: " << t1.get_id() << std::endl;
  std::cout << "thread 2 id: " << t2.get_id() << std::endl;

  std::swap(t1, t2);

  std::cout << "after std::swap(t1, t2):" << std::endl;
  std::cout << "thread 1 id: " << t1.get_id() << std::endl;
  std::cout << "thread 2 id: " << t2.get_id() << std::endl;

  t1.swap(t2);

  std::cout << "after t1.swap(t2):" << std::endl;
  std::cout << "thread 1 id: " << t1.get_id() << std::endl;
  std::cout << "thread 2 id: " << t2.get_id() << std::endl;

  t1.join();
  t2.join();
}
