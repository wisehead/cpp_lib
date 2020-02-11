/*******************************************************************************
 *      file name: environment.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/11-16:02:31                              
 *  modified time: 2020/02/11-16:02:31                              
 *******************************************************************************/
#include <iostream>
#include <gtest/gtest.h>
using namespace std;

class GlobalTest: public testing::Environment
{
public:
	virtual void SetUp()
	{
		cout<<"SetUp()"<<endl;
	}

	virtual void TearDown()
	{
		cout<<"TearDownp()"<<endl;
	}
};

int main(int argc, char*argv[])
{
    testing::InitGoogleTest(&argc, argv);
	testing::Environment* env = new GlobalTest();
	testing::AddGlobalTestEnvironment(env);
    return RUN_ALL_TESTS();
}

