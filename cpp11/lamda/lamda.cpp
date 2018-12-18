/*******************************************************************************
 *      file name: lamda.cpp                                               
 *         author: Hui Chen. (c) 2018                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2018/12/18-15:02:25                              
 *  modified time: 2018/12/18-15:02:25                              
 *******************************************************************************/
#include <iostream>
//示例代码1.0 http://www.cnblogs.com/feng-sc/p/5710724.html
int main()
{
    auto add= [](int a, int b)->int{
        return a + b;
    };
    int ret = add(1,2);
    std::cout << "ret:" << ret << std::endl;
    return 0;
}
