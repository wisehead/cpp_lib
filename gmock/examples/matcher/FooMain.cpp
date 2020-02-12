/*******************************************************************************
 *      file name: FooMain.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-10:18:03                              
 *  modified time: 2020/02/12-10:18:03                              
 *******************************************************************************/
#include <cstdlib>
#include <gmock/gmock.h>
#include <iostream>
#include <string>
 
#include "MockFoo.h"
 
using namespace seamless;
using namespace std;
 
using ::testing::Assign;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Return;
 
int main(int argc, char** argv) {
        ::testing::InitGoogleMock(&argc, argv);
 
        string value = "Hello World!";
        MockFoo mockFoo;
 
        EXPECT_CALL(mockFoo, setValue(testing::_));
        mockFoo.setValue(value);
 
        // 这里我故意犯错
        EXPECT_CALL(mockFoo, setDoubleValues(Eq(1), Ge(1)));
        mockFoo.setDoubleValues(1, 0);
 
        return EXIT_SUCCESS;
}