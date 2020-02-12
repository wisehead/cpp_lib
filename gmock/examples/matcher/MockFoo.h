/*******************************************************************************
 *      file name: FooMock.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-10:17:03                              
 *  modified time: 2020/02/12-10:17:03                              
 *******************************************************************************/
#ifndef MOCKFOO_H_
#define MOCKFOO_H_
 
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include "FooInterface.h"
 
namespace seamless {
 
class MockFoo: public FooInterface {
public:
        MOCK_METHOD0(getArbitraryString, std::string());
        MOCK_METHOD1(setValue, void(std::string& value));
        MOCK_METHOD2(setDoubleValues, void(int x, int y));
};
 
}  // namespace seamless
 
#endif // MOCKFOO_H_
