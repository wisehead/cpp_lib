/*******************************************************************************
 *      file name: VariantField.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-14:46:05                              
 *  modified time: 2020/02/12-14:46:05                              
 *******************************************************************************/
#ifndef VARIANTFIELD_H_
#define VARIANTFIELD_H_
 
#include <boost/cstdint.hpp>
 
namespace seamless {
 
union VariantField
{
    const char * strVal;
    int32_t intVal;
};
 
}  // namespace mlr_isearch_api
 
#endif // VARIANTFIELD_H_
