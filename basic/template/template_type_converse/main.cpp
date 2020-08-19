/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-11:13:16                              
 *  modified time: 2020/08/19-11:13:16                              
 *******************************************************************************/
//main.cpp
#include <stdio.h>
#include "stack.h"
#include "shape.h"
int main() {
    Stack<Circle*> pcircleStack;
    Stack<Shape*> pshapeStack;
    pcircleStack.push(new Circle);
    pshapeStack = pcircleStack;
    return 0;
}
