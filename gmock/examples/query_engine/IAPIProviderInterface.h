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
 
#include "IParameterInterface.h"
#include "VariantField.h"
 
namespace seamless {
 
class IAPIProviderInterface {
public:
        IAPIProviderInterface() {}
        virtual ~IAPIProviderInterface() {}
 
public:
        virtual IParameterInterface* getParameterInterface() = 0;
};
 
}
 
#endif // IAPIPROVIDERINTERFACE_H_
