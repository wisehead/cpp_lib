/*******************************************************************************
 *      file name: statck.h                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/08/19-10:47:25                              
 *  modified time: 2020/08/19-10:47:25                              
 *******************************************************************************/
//statck.h
template <class T,int maxsize = 100> class Stack {
    public:
        Stack();
        ~Stack();
        void push(T t);
        T pop();
        bool isEmpty();
    private:
        T *m_pT;        
        int m_maxSize;
        int m_size;
};
#include "stack.cpp"
