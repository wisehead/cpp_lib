---
title: 线程数据共享：pthread_getspecific和pthread_setspecific - 简书
category: default
tags: 
  - www.jianshu.com
created_at: 2020-05-19 18:41:52
original_url: https://www.jianshu.com/p/d78d93d46fc2
---

# 线程数据共享：pthread\_getspecific和pthread\_setspecific

[![](assets/1589884912-636fd69958522ff736152050c5209dc6.png)](https://www.jianshu.com/u/0d2f0ef22c40)

[EamonXia](https://www.jianshu.com/u/0d2f0ef22c40)关注

2019.03.05 10:44:12字数 274阅读 4,018

pthread\_getpecific和pthread\_setspecific提供了在同一个线程中不同函数间共享数据即线程存储的一种方法。具体用法为：  
1.调用pthread\_key\_create()来创建一个类型为pthread\_key\_t类型的变量

该函数有两个参数，第一个参数就是声明的pthread\_key\_t变量，第二个参数是一个清理函数，用来在线程释放该线程存储的时候被调用。该函数指针可以设成NULL，这样系统将调用默认的清理函数。

2.调用pthread_setspcific()

当线程中需要存储特殊值的时候调用该函数，该函数有两个参数，第一个为前面声明的pthread\_key\_t变量，第二个为void*变量，用来存储任何类型的值。

3.如果需要取出所存储的值，调用pthread_getspecific()

该函数的参数为前面提到的pthread\_key\_t变量，该函数返回void*类型的值。

```cpp
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

```

`#gcc thread.c -o test -lpthread`  
`#./test`  
运行结果：

```csharp
1 is runing in thread_func
100 is runing in func1
2 is runing in thread_func
200 is runing in func1
```

本文非原创：  
[线程数据共享：pthread\_getspecific和pthread\_setspecific](https://blog.csdn.net/arag2009/article/details/17223001)

0人点赞

[工作日记](https://www.jianshu.com/nb/31899048)

"小礼物走一走，来简书关注我"

赞赏支持还没有人赞赏，支持一下

[![  ](assets/1589884912-2162c081edc10195584f6708942fce4a.png)](https://www.jianshu.com/u/0d2f0ef22c40)

[EamonXia](https://www.jianshu.com/u/0d2f0ef22c40 "EamonXia")1、应用数学硕士，研究方向为信息安全，偏向密码学算法方向。 2、工作方向偏向Linux平台内...

总资产1 (约0.10元)共写了1.1W字获得4个赞共5个粉丝

关注

---------------------------------------------------


原网址: [访问](https://www.jianshu.com/p/d78d93d46fc2)

创建于: 2020-05-19 18:41:52

目录: default

标签: `www.jianshu.com`

