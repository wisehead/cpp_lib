/*******************************************************************************
 *      file name: compare.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-11:09:26                              
 *  modified time: 2020/08/19-11:09:26                              
 *******************************************************************************/
//compare.h
#include <string.h>
template <class T>
 class compare
 {
  public:
  bool equal(T t1, T t2)
  {
       return t1 == t2;
  }
};
   

template<>class compare<char *>  
{
public:
    bool equal(char* t1, char* t2)
    {
        return strcmp(t1, t2) == 0;
    }
};
