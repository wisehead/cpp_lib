/*******************************************************************************
 *      file name: test.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/04/13-22:02:46                              
 *  modified time: 2020/04/13-22:02:46                              
 *******************************************************************************/
extern "C" 
{ 
#include "f1.h" 
} 

extern "C" 
{ 
	extern void f1(); 
}

int main() 
{ 
	f1();
	return 0; 
} 
