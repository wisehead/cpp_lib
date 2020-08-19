/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-11:09:45                              
 *  modified time: 2020/08/19-11:09:45                              
 *******************************************************************************/
#include <iostream>
#include "compare.h"
int main()
{
	using namespace std;
	char str1[] = "Hello";
	char str2[] = "Hello";
	compare<int> c1;
	compare<char *> c2;   
	cout << c1.equal(1, 1) << endl;        //比较两个int类型的参数
	cout << c2.equal(str1, str2) << endl;   //比较两个char *类型的参数
	return 0;
}
