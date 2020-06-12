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

	//ut_ad(!((flags ^ space->flags) & ~(FSP_FLAGS_MASK_ENCRYPTION)));
	//18432 ^ 2048 = 0x4000
	unsigned int flags = 18432; 
	unsigned int space_flags = 2048; 
	unsigned int e = flags ^ space_flags; 
	printf("(flags ^ space->flags):	e: ---- is :%x.\n", e);

	unsigned int f = ((flags ^ space_flags) & d); 
	printf("((flags ^ space->flags) & ~(FSP_FLAGS_MASK_ENCRYPTION)):	f: ---- is :%x.\n", f);

	unsigned int g = !((flags ^ space_flags) & d); 
	printf("!((flags ^ space->flags) & ~(FSP_FLAGS_MASK_ENCRYPTION)):	g: ---- is :%x.\n", g);


}
