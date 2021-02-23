/*******************************************************************************
 *      file name: Rank.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/02/12-14:48:03                              
 *  modified time: 2020/02/12-14:48:03                              
 *******************************************************************************/
#ifndef RANK_H_
#define RANK_H_
 
#include "IAPIProviderInterface.h"
 
namespace seamless {
 
class Rank {
public:
        virtual ~Rank() {}
 
public:
        void processQuery(IAPIProviderInterface* iAPIProvider);
};
 
}  // namespace seamless
 
#endif // RANK_H_
