/*******************************************************************************
 *      file name: FooInterface.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-10:16:31                              
 *  modified time: 2020/02/12-10:16:31                              
 *******************************************************************************/
#ifndef FOOINTERFACE_H_
#define FOOINTERFACE_H_
 
#include <string>
 
namespace seamless {
 
class FooInterface {
public:
        virtual ~FooInterface() {}
 
public:
        virtual std::string getArbitraryString() = 0;
};
 
}  // namespace seamless
 
#endif // FOOINTERFACE_H_
