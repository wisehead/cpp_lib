# jemalloc 性能测试

2020-07-30

[c/c++](https://wenfh2020.com/category/#c/c++ "Category: c/c++")

* * *

`jemalloc` 是一个优秀的内存分配器，通过与系统默认的内存分配器进行比较：`jemalloc` 内存分配性能比系统默认的分配器快 50%。

* * *

## 1\. 安装

*   MacOS

```shell
brew install jemalloc
```

*   Centos

```
1
2yum install jemalloc
yum install jemalloc-devel
```

* * *

## 2\. 测试

### 2.1. 源码 （[github 测试源码](https://github.com/wenfh2020/c_test/blob/master/jemalloc/test_jemalloc.cpp)）

测试 10,000,000 次，随机大小的内存块分配和回收，查看它们的工作效率。

```
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <iostream>

#ifdef USE_JEMALLOC
#include <jemalloc/jemalloc.h>
#endif

#define MALLOC_CNT 10000000

long long mstime() {
    long long mst;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    mst = ((long long)tv.tv_sec) * 1000;
    mst += tv.tv_usec / 1000;
    return mst;
}

int main() {
    srand((unsigned)time(NULL));
    long long begin = mstime();
    for (int i = 0; i < MALLOC_CNT; i++) {
        int size = 1024 * 4 + rand() % 1024;
        char* p = (char*)malloc(size);
        memset(p, rand() % 128, size);
        free(p);
    }
    long long end = mstime();

    std::cout << "begin: " << begin << std::endl
              << "end: " << end << std::endl
              << "val: " << end - begin << std::endl;
    return 0;
}
```

* * *

### 2.2. 测试结果

测试时间单位：微秒，jemalloc 内存管理耗时大约是系统默认内存管理的一半 **（605 vs 1253）**。demo 只是对 大于 4 \* 1024 比较大块的内存进行测试，对于小内存的测试，`jemalloc` 表现还更加优秀。

> 有兴趣的朋友，也可以测试一下 `jemalloc` 对 C++ 的 new 和 delete 的影响。

```
1
2
3
4
5
6
7
8
9
10
11# normal mem test.
$ g++ -std='c++11' -g test_jemalloc.cpp -o tjemalloc  && ./tjemalloc
begin: 1596078974122
end: 1596078975375
val: 1253

# jemalloc mem test.
$ g++ -std='c++11' -g test_jemalloc.cpp -o tjemalloc -DUSE_JEMALLOC -ljemalloc && ./tjemalloc
begin: 1596078980303
end: 1596078980908
val: 605
```

* * *

*   **本文作者：** wenfh2020
*   **本文链接：** [https://wenfh2020.com/2020/07/30/jemalloc/](https://wenfh2020.com/2020/07/30/jemalloc/ "jemalloc 性能测试")
*   **版权声明：** 转载请注明出处，谢谢！

* * *

打赏

**上一篇** [软件性能检测--火焰图🔥](https://wenfh2020.com/2020/07/30/flame-diagram/)

**下一篇** [gettimeofday 获取本地时间](https://wenfh2020.com/2020/08/04/get-local-time/)

[0](https://github.com/wenfh2020/wenfh2020.github.io/issues/28) 条评论

未登录用户

[支持 Markdown 语法](https://guides.github.com/features/mastering-markdown/)预览使用 GitHub 登录

来做第一个留言的人吧！