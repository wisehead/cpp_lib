---
title: Boost 库的使用入门 - 简书
category: default
tags: 
  - www.jianshu.com
created_at: 2020-07-02 20:14:15
original_url: https://www.jianshu.com/p/855c8e786441
---

# Boost 库的使用入门


参考自： [Boost: Getting Started on Unix Variants](https://link.jianshu.com/?t=https%3A%2F%2Fwww.boost.org%2Fdoc%2Flibs%2F1_66_0%2Fmore%2Fgetting_started%2Funix-variants.html)

1.  下载好之后，解压。  
    2）编译安装 Boost 库。按默认的提示的话：  
    `$./bootstrap.sh` 然后 `$./b2 install`  
    第二步的编译需要一定时间(我的 2014-mid Pro 花了大约半小时多)。 默认编译好的库的安装地址在 `/usr/local` 目录。  
    可通过 `$./bootstrap.sh --help` 来查看编译选项。

3）写一个简单的 thread demo

```c
#include <boost/thread.hpp>
#include<iostream>

using namespace std;

boost::mutex mx;

void wait(int sec){
    boost::this_thread::sleep(boost::posix_time::seconds(sec));
}

int main(int argc, const char * argv[]){
    cout << "Wait 3 seconds " << endl;
    wait(3);
    cout << "Done!" << endl;
    return 0;
}
```

4） 编译链接 `$ clang++ -lboost_thread -lboost_system main.cpp -o main`

5.  运行

```jsx
$./main
Wait 3 seconds
Done!
```

值得注意的是，如果提示找不到 boost\_thread ，那检查一下 `/usr/local/lib` 目录下是否有名为 `libboost_thread.dylib` 的库。 有可能你是使用 `brew install boost` 安装的，但是 brew 安装时默认启用了 `multi thread` 所以上面的编译选项则应该改为 . `$clang++ -lboost_thread-mt -lboost_system main.cpp -o main`


