/*******************************************************************************
 *      file name: main.c                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/13-19:41:01                              
 *  modified time: 2020/02/13-19:41:01                              
 *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void test(int vount);

int main(int argc, char *argv[])
{
    int i = 0;
    if(argc == 2)
        i = -1;
    else
        i = 10;

    printf("arg is %d\n",i);

    test(i);

    return EXIT_SUCCESS;
}
