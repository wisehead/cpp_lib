/*******************************************************************************
 *      file name: clog.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/04-14:20:20                              
 *  modified time: 2019/01/04-14:20:20                              
 *******************************************************************************/
#include <iostream>
 
using namespace std;
 
int main( )
{
   char str[] = "Unable to read....";
 
   clog << "Error message : " << str << endl;
}
