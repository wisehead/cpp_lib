/*******************************************************************************
 *      file name: main.cpp                                               
 *         author: Hui Chen. (c) 2018                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2018/12/18-14:50:56                              
 *  modified time: 2018/12/18-14:50:56                              
 *******************************************************************************/
#include <functional>
#include <iostream>
#include "Test.h"
//示例代码1.0 http://www.cnblogs.com/feng-sc/p/5710724.html
int add(int a,int b)
{
    std::cout << "add" << std::endl;
    return a + b;
}

class TestAdd
{
public:
    int Add(int a,int b)
    {
        std::cout << "TestAdd::Add" << std::endl;
        return a + b;
    }
};

int main()
{
    Test test;
    test.Add(add, 1, 2);

    TestAdd testAdd;
    test.Add(std::bind(&TestAdd::Add, testAdd, std::placeholders::_1, std::placeholders::_2), 1, 2);
    return 0;
}
