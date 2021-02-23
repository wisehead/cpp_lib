/*******************************************************************************
 *      File Name: test.c                                               
 *         Author: Hui Chen. (c) 2020                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2020/02/13-19:58                                    
 *	Modified Time: 2020/02/13-19:58                                    
 *******************************************************************************/
#include <stdio.h>

void test(int count)
{
    if (count == -1)
        printf ("获取到值为2,%d为-1,测试通道二已通过",count);
    else
        printf ("滴滴滴，测试通道一已通过");
}
