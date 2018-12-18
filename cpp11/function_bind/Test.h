/*******************************************************************************
 *      file name: Test.h                                               
 *         author: Hui Chen. (c) 2018                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2018/12/18-14:50:37                              
 *  modified time: 2018/12/18-14:50:37                              
 *******************************************************************************/
#include <iostream>
//示例代码1.0 http://www.cnblogs.com/feng-sc/p/5710724.html
class Test
{
public:
    void Add(std::function<int(int, int)> fun, int a, int b)
    {
        int sum = fun(a, b);
        std::cout << "sum:" << sum << std::endl;
    }
};
