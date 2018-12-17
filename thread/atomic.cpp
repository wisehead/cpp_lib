/*******************************************************************************
 *      file name: atomic.cpp                                               
 *         author: Hui Chen. (c) 2018                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2018/12/17-15:19:50                              
 *  modified time: 2018/12/17-15:19:50                              
 *******************************************************************************/
#include <iostream>
#include <thread>
#include <atomic>
#include <stdio.h>
#include <list>
//std::atomic_bool bIsReady = false;
std::atomic_bool bIsReady(false);
//std::atomic_int iCount = 100;
std::atomic_int iCount(100);
void threadfun1()
{
    if (!bIsReady) {
        std::this_thread::yield();
    }
    while (iCount > 0)
    {
        printf("iCount:%d\r\n", iCount--);
    }
}

int main()
{
    std::atomic_bool b;
    std::list<std::thread> lstThread;
    for (int i = 0; i < 10; ++i)
    {
        lstThread.push_back(std::thread(threadfun1));
    }
    for (auto& th : lstThread)
    {
        th.join();
    }
}
