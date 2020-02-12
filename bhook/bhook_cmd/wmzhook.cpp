/*******************************************************************************
 *      File Name: wmzhook.cpp                                               
 *         Author: Hui Chen. (c) 2020                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2020/02/12-20:22                                    
 *	Modified Time: 2020/02/12-20:22                                    
 *******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "bhook.h"
using namespace std;
 
int my_func()
{
    printf("this is my hook func and will return -1!\n");
    return -1;
}
 
void __attribute__ ((constructor)) hook_init(void)
{
    attach_func_lib("func", (void *)my_func);
}
