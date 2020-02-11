#1.下载命令
git clone https://github.com/google/googletest

#2.编译安装
> cd googletest
> mkdir release
> cd release
> cmake ..
> make -j8
> make install

#3.编译gtest例子

bld11 abs.cpp -lgtest -lpthread

```cpp
#include <iostream>
using namespace std;
#include <gtest/gtest.h>

int Abs(int x)
{
     return x > 0 ? x : -x;
}

TEST(IsAbsTest,HandlerTrueReturn)
{
    ASSERT_TRUE(Abs(1) == 1) << "Abs(1)=1";  
    ASSERT_TRUE(Abs(-1) == 1) << "Abs(-1)=1";
    ASSERT_FALSE(Abs(-2) == -2);  
    ASSERT_EQ(Abs(1),Abs(-1));
    ASSERT_NE(Abs(-1),0);
    ASSERT_LT(Abs(-1),2);
    ASSERT_GT(Abs(-1),0);
    ASSERT_LE(Abs(-1),2);
    ASSERT_GE(Abs(-1),0);
}

int main(int argc, char*argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}

```