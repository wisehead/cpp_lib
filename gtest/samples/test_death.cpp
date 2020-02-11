/*******************************************************************************
 *      file name: abs.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/11-15:43:53                              
 *  modified time: 2020/02/11-15:43:53                              
 *******************************************************************************/
#include <iostream>
using namespace std;
#include <gtest/gtest.h>

int func()
{
	int *ptr = NULL;
	*ptr = 100;
	return 0;
}

TEST(FuncDeathTest, Nullptr)
{
	ASSERT_DEATH(func(), "");
}

int main(int argc, char*argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
