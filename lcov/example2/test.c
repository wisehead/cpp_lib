/*******************************************************************************
 *      file name: test.c                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/13-19:41:21                              
 *  modified time: 2020/02/13-19:41:21                              
 *******************************************************************************/
#include <stdio.h>

void test(int count)
{
    if (count == -1)
        printf ("获取到值为2,%d为-1,测试通道二已通过",count);
    else
        printf ("滴滴滴，测试通道一已通过");
}
