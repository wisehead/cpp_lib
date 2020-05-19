/*******************************************************************************
 *      file name: thread.c                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/05/19-18:38:25                              
 *  modified time: 2020/05/19-18:38:25                              
 *******************************************************************************/
#include<stdio.h>
#include<pthread.h>
#include<string.h>
pthread_key_t p_key;
 
void func1()
{
        int *tmp = (int*)pthread_getspecific(p_key);//同一线程内的各个函数间共享数据。
        printf("%d is runing in %s\n",*tmp,__func__);
 
}
void *thread_func(void *args)
{
 
        pthread_setspecific(p_key,args);
 
        int *tmp = (int*)pthread_getspecific(p_key);//获得线程的私有空间
        printf("%d is runing in %s\n",*tmp,__func__);
 
        *tmp = (*tmp)*100;//修改私有变量的值
 
        func1();
 
        return (void*)0;
}
int main()
{
        pthread_t pa, pb;
        int a=1;
        int b=2;
        pthread_key_create(&p_key,NULL);
        pthread_create(&pa, NULL,thread_func,&a);
        pthread_create(&pb, NULL,thread_func,&b);
        pthread_join(pa, NULL);
        pthread_join(pb, NULL);
        return 0;
}

