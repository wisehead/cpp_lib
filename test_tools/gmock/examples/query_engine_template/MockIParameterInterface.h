/*******************************************************************************
 *      file name: MockIParameterInterface.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-15:00:39                              
 *  modified time: 2020/02/12-15:00:39                              
 *******************************************************************************/
#ifndef MOCKIPARAMETERINTERFACE_H_
#define MOCKIPARAMETERINTERFACE_H_
 
#include <boost/cstdint.hpp>
#include <gmock/gmock.h>
 
#include "IParameterInterface.h"
#include "VariantField.h"
 
namespace seamless {
 
class MockIParameterInterface: public IParameterInterface {
public:
        MOCK_METHOD2(getParameter, int32_t(const char* name,  VariantField*& value));
};
 
}  // namespace seamless
 
#endif // MOCKIPARAMETERINTERFACE_H_
