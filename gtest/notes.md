#一、gtest系列之TEST宏

> TEST(test_case_name, test_name)
> TEST_F(test_fixture,test_name)  
> //多个测试场景需要相同数据配置的情况，用TEST_F。
> //TEST_F  test fixture，测试夹具，测试套，承担了一个注册的功能。

TEST宏的作用是创建一个简单测试，它定义了一个测试函数，在这个函数里可以使用任何C++代码并使用提供的断言来进行检查。后续文章还会提到TEST_P这个宏，在这里就先不介绍了。

#二、gtest系列之断言
##2.1 原理
gtest中断言的宏可以分为两类：一类是ASSERT宏，另一类就是EXPECT宏了。
1、ASSERT_系列：如果当前点检测失败则退出当前函数
2、EXPECT_系列：如果当前点检测失败则继续往下执行
如果你对自动输出的错误信息不满意的话，也是可以通过operator<<能够在失败的时候打印日志，将一些自定义的信息输出。
ASSERT_系列：

> bool值检查
> 1>、 ASSERT_TRUE(参数)，期待结果是true
> 2>、ASSERT_FALSE(参数)，期待结果是false
> 数值型数据检查
> 3>、ASSERT_EQ(参数1，参数2)，传入的是需要比较的两个数  equal
> 4>、ASSERT_NE(参数1，参数2)，not equal，不等于才返回true
> 5>、ASSERT_LT(参数1，参数2)，less than，小于才返回true
> 6>、ASSERT_GT(参数1，参数2)，greater than，大于才返回true
> 7>、ASSERT_LE(参数1，参数2)，less equal，小于等于才返回true
> 8>、ASSERT_GE(参数1，参数2)，greater equal，大于等于才返回true
> 字符串检查
> 9>、ASSERT_STREQ(expected_str, actual_str)，两个C风格的字符串相等才正确返回
> 10>、ASSERT_STRNE(str1, str2)，两个C风格的字符串不相等时才正确返回
> 11>、ASSERT_STRCASEEQ(expected_str, actual_str)
> 12>、ASSERT_STRCASENE(str1, str2)
> 13>、EXPECT_系列，也是具有类似的宏结构的
> 
> 

##2.2 一个例子

```cpp
#include<iostream>
using namespace std; 
#include<gtest/gtest.h>

int Abs(int x)
{
     return x > 0 ? x : -x;
}

TEST(IsAbsTest,HandlerTrueReturn)
{
    ASSERT_TRUE(Abs(1) == 1) << "Abs(1)=1";  //ASSERT_TRUE期待结果是true,operator<<输出一些自定义的信息
    ASSERT_TRUE(Abs(-1) == 1) << "Abs(-1)=1";
    ASSERT_FALSE(Abs(-2) == -2);  //期待结果是false
    ASSERT_EQ(Abs(1),Abs(-1));
    ASSERT_NE(Abs(-1),0);
    ASSERT_LT(Abs(-1),2);
    ASSERT_GT(Abs(-1),0);
    ASSERT_LE(Abs(-1),2);
    ASSERT_GE(Abs(-1),0);
}
//要加上最后这段
int main(int argc, char*argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}
```
