/*******************************************************************************
 *      file name: MockIAPIProviderInterface.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-15:05:26                              
 *  modified time: 2020/02/12-15:05:26                              
 *******************************************************************************/
#ifndef MOCKIAPIPROVIDERINTERFACE_H_
#define MOCKIAPIPROVIDERINTERFACE_H_
 
#include <gmock/gmock.h>
 
#include "IAPIProviderInterface.h"
#include "IParameterInterface.h"
 
namespace seamless {
 
class MockIAPIProviderInterface: public IAPIProviderInterface{
public:
        MOCK_METHOD0(getParameterInterface, IParameterInterface*());
};
 
}  // namespace seamless
 
#endif // MOCKIAPIPROVIDERINTERFACE_H_
