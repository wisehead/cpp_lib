/*******************************************************************************
 *      file name: IAPIProviderInterface.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-14:47:16                              
 *  modified time: 2020/02/12-14:47:16                              
 *******************************************************************************/
#ifndef IAPIPROVIDERINTERFACE_H_
#define IAPIPROVIDERINTERFACE_H_
 
#include <boost/cstdint.hpp>
#include <iostream>
 
#include "IBaseInterface.h"
#include "IParameterInterface.h"
#include "VariantField.h"
 
// In order to Mock
#include <boost/shared_ptr.hpp>
#include <gmock/gmock.h>
#include "MockIParameterInterface.h"
 
namespace seamless {
 
class IAPIProviderInterface: public IBaseInterface {
public:
        IAPIProviderInterface() {}
        virtual ~IAPIProviderInterface() {}
 
public:
        virtual int32_t queryInterface(IBaseInterface*& pInterface) = 0;
 
        template<typename InterfaceType>
        InterfaceType* getInterface() {
                IBaseInterface* pInterface = NULL;
                if (queryInterface(pInterface) == 0) {
                        std::cerr << "Query Interface failed" << std::endl;
                }
 
                // In order to Mock
                if ((typeid(InterfaceType) == typeid(IParameterInterface)) ||
                        (typeid(InterfaceType) == typeid(MockIParameterInterface))) {
                        using namespace ::testing;
                        MockIParameterInterface* iParameter = new MockIParameterInterface;
                        boost::shared_ptr<VariantField> retailWholesaleValue(new VariantField);
                        retailWholesaleValue->strVal = "0";
 
                        boost::shared_ptr<VariantField> defaultValue(new VariantField);
                        defaultValue->strVal = "9";
 
                        EXPECT_CALL(*iParameter, getParameter(_, _)).Times(AtLeast(1)).
                                WillOnce(DoAll(SetArgumentPointee<1>(*retailWholesaleValue), Return(1))).
                                WillRepeatedly(DoAll(SetArgumentPointee<1>(*defaultValue), Return(1)));
                        return static_cast<InterfaceType* >(iParameter);
                }
                // end of mock
 
                return static_cast<InterfaceType* >(pInterface);
        }
};
 
}
 
#endif // IAPIPROVIDERINTERFACE_H_