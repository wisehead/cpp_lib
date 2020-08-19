/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-10:48:42                              
 *  modified time: 2020/08/19-10:48:42                              
 *******************************************************************************/
//main.cpp
#include <stdio.h>
#include "stack.h"
int main() {
    int maxsize = 1024;
    Stack<int,1024> intStack;
    for (int i = 0; i < maxsize; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        printf("num:%d\n", intStack.pop());
    }
    return 0;
}
