/*******************************************************************************
 *      File Name: main.c                                               
 *         Author: Hui Chen. (c) 2020                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2020/02/13-19:58                                    
 *	Modified Time: 2020/02/13-19:58                                    
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
