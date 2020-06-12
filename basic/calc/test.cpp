/*******************************************************************************
 *      file name: test.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/06/12-16:14:54                              
 *  modified time: 2020/06/12-16:14:54                              
 *******************************************************************************/
#include <iostream>
using namespace std;

int main()
{
	int a = (~0U << 1);
	printf("a is %x.\n", a);
	unsigned int ua = (~0U << 1);
	printf("ua is %x.\n", ua);
	int turn_a = ~(~0U << 1);
	printf("turn_a is %x.\n", turn_a);
	unsigned int turn_ua = ~(~0U << 1);
	printf("turn_ua is %x.\n", turn_ua);

	unsigned int c =  (~(~0U << 1)) << (0 + 1 + 4 + 1 + 4 + 1 + 1 + 1);
	printf("FSP_FLAGS_MASK_ENCRYPTION:	c: (~(~0U << 1)) << (0 + 1 + 4 + 1 + 4 + 1 + 1 + 1)---- is :%x.\n", c);

	unsigned int d = ~((~(~0U << 1)) << (0 + 1 + 4 + 1 + 4 + 1 + 1 + 1));
	printf("~(FSP_FLAGS_MASK_ENCRYPTION):	d: ~((~(~0U << 1)) << (0 + 1 + 4 + 1 + 4 + 1 + 1 + 1))---- is :%x.\n", d);
}
