/*******************************************************************************
 *      file name: IParameterInterface.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-14:46:52                              
 *  modified time: 2020/02/12-14:46:52                              
 *******************************************************************************/
#ifndef IPARAMETERINTERFACE_H_
#define IPARAMETERINTERFACE_H_
 
#include <boost/cstdint.hpp>
 
#include "VariantField.h"
 
namespace seamless {
 
class IParameterInterface {
public:
        virtual ~IParameterInterface() {};
 
public:
        virtual int32_t getParameter(const char* name,  VariantField*& value) = 0;
};
 
}  // namespace
 
#endif // IPARAMETERINTERFACE_H_
