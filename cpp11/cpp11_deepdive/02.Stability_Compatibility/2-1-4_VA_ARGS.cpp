/*******************************************************************************
 *      file name: 2-1-4_VA_ARGS.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/16-21:27:34                              
 *  modified time: 2020/08/16-21:27:34                              
 *******************************************************************************/
#include <stdio.h>
#define LOG(...)   {\
    fprintf(stderr,"%s: Line %d:\t", __FILE__, __LINE__);\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr,"\n");\
}
int main() {
    int x = 3;
    // 一些代码...
    LOG("x = %d", x); // 2-1-5.cpp: Line 12:      x = 3
}
// 编译选项:g++ -std=c++11 2-1-5.cpp
