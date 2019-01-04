/*******************************************************************************
 *      file name: double_sharp.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/04-15:35:59                              
 *  modified time: 2019/01/04-15:35:59                              
 *******************************************************************************/
#include <iostream>
using namespace std;
 
#define concat(a, b) a ## b
int main()
{
   int xy = 100;
   
   cout << concat(x, y)<<endl;
   return 0;
}
