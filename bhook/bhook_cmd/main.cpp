/*******************************************************************************
 *      File Name: main.cpp                                               
 *         Author: Hui Chen. (c) 2020                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2020/02/12-20:22                                    
 *	Modified Time: 2020/02/12-20:22                                    
 *******************************************************************************/
#include <iostream>
#include <iostream>
#include <stdio.h>
using namespace std;
 
int func() {
    printf("this is func\n");
    return 0;
}
 
int main() {
    int ret = func();
    if(ret == 0) {
        printf("Everything is OK!\n");
    } else {
        printf("Oh, no! Impossible!\n");
    }  
    return 0;
}
