---
title: C++11_emplace_back的优点 - 简书
category: default
tags: 
  - www.jianshu.com
created_at: 2020-09-22 14:44:57
original_url: https://www.jianshu.com/p/1fb2daf66582?native.theme=1
---

# C++11\_emplace\_back的优点

[![](assets/1600757097-80ee4fb4a46a1bf9709c79bd1e6cd0b6.jpg)](https://www.jianshu.com/u/cdcff6d8e571)

[JasonLiThirty](https://www.jianshu.com/u/cdcff6d8e571)关注

2020.02.03 16:26:14字数 291阅读 2,497

**视频教程：[https://www.bilibili.com/video/av86157003](https://links.jianshu.com/go?to=https%3A%2F%2Fwww.bilibili.com%2Fvideo%2Fav86157003)**

# **emplace\_back的特点**

*   当调用push\_back或insert成员函数时，是把元素类型的对象传递给它们，这些对象被拷贝到容器中。而当我们调用一个emplace系列函数时，则是将相应参数传递给元素类型的构造函数。
*   这样emplace\_back能就地通过参数构造对象，不需要拷贝操作，相比push\_back能更好的避免内存的拷贝和移动，提升容器插入元素的性能。
*   大多数情况都应该使用emplace系列函数：emplace; emplace\_back; emplace\_hit; emplace\_fornt; emplace\_after

# **emplace系列函数**需要有对应的构造函数

*   emplace函数需要对应的参数对象有对应的构造函数，不然编译报错
*   emplace函数在容器中直接构造元素。传递给emplace函数的参数必须与元素类型的构造函数相匹配

```cpp
#include<iostream>
#include<list>


struct A
{
    int x;
    double y;

    A()
    {
        x = 0;
        y = 1.0;
    }

    A(int a, double b)
    {
        x = a;
        b = y;
    }
};

int main()
{
    std::list<A> listSample;
    listSample.emplace_back(1, 2.0);
    std::cout << listSample.size() << std::endl;
    return 0;
}
```

# emplace\_back和push\_back的简单比较

```cpp
///////////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/container/vector/emplace_back
namespace {
    struct President {
        std::string name;
        std::string country;
        int year;


        President(std::string p_name, std::string p_country, int p_year)
            : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
        {
            std::cout << "I am being constructed.\n";
        }
        President(President&& other)
            : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
        {
            std::cout << "I am being moved.\n";
        }
        President& operator=(const President& other) = default;
    };
}


int emplacevspush()
{
    std::cout << "test_emplace_2()" << std::endl;
    /*
    The following code uses emplace_back to append an object of type President to a std::vector.
    It demonstrates how emplace_back forwards parameters to the President constructor and shows
    how using emplace_back avoids the extra copy or move operation required when using push_back.
    */
    std::vector<President> elections;
    std::cout << "emplace_back:\n";
    elections.emplace_back("Nelson Mandela", "South Africa", 1994);


    std::vector<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));


    std::cout << "\nContents:\n";
    for (President const& president : elections) {
        std::cout << president.name << " was elected president of "
            << president.country << " in " << president.year << ".\n";
    }
    for (President const& president : reElections) {
        std::cout << president.name << " was re-elected president of "
            << president.country << " in " << president.year << ".\n";
    }


    return 0;
}

//output
emplace_back:
I am being constructed.


push_back:
I am being constructed.
I am being moved.


Contents:
Nelson Mandela was elected president of South Africa in 1994.
Franklin Delano Roosevelt was re-elected president of the USA in 1936.
```

**如例子所示，使用emplace\_back函数可以减少一次拷贝或移动构造的过程，提升容器插入数据的效率**



