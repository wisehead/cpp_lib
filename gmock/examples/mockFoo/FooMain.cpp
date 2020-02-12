/*******************************************************************************
 *      file name: FooMain.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-10:18:03                              
 *  modified time: 2020/02/12-10:18:03                              
 *******************************************************************************/
#include <cstdlib>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
 
#include "FooMock.h"
 
using namespace seamless;
using namespace std;
 
using ::testing::Return;
 
int main(int argc, char** argv) {
        ::testing::InitGoogleMock(&argc, argv);
 
        string value = "Hello World!";
        MockFoo mockFoo;
        EXPECT_CALL(mockFoo, getArbitraryString()).Times(1).
                WillOnce(Return(value));
        string returnValue = mockFoo.getArbitraryString();
        cout << "Returned Value: " << returnValue << endl;
 
        return EXIT_SUCCESS;
}
