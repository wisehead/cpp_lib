/*******************************************************************************
 *      file name: single_sharp.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/01/04-15:34:57                              
 *  modified time: 2019/01/04-15:34:57                              
 *******************************************************************************/
#include <iostream>
using namespace std;
 
#define MKSTR( x ) #x
 
int main ()
{
    cout << MKSTR(HELLO C++) << endl;
 
    return 0;
}
