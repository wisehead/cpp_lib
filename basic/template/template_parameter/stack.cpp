/*******************************************************************************
 *      file name: stack.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-10:48:16                              
 *  modified time: 2020/08/19-10:48:16                              
 *******************************************************************************/
//stack.cpp
//#include "stack.h"
template <class T,int maxsize> Stack<T, maxsize>::Stack(){
   m_maxSize = maxsize;      
   m_size = 0;
   m_pT = new T[m_maxSize];
}
template <class T,int maxsize>  Stack<T, maxsize>::~Stack() {
   delete [] m_pT ;
}
        
template <class T,int maxsize> void Stack<T, maxsize>::push(T t) {
    m_size++;
    m_pT[m_size - 1] = t;
    
}
template <class T,int maxsize> T Stack<T, maxsize>::pop() {
    T t = m_pT[m_size - 1];
    m_size--;
    return t;
}
template <class T,int maxsize> bool Stack<T, maxsize>::isEmpty() {
    return m_size == 0;
}
