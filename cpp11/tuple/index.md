---
title: (1条消息) C++ tuple元组的基本用法(总结)_sevenjoin的博客-CSDN博客
category: default
tags: 
  - blog.csdn.net
created_at: 2020-09-22 14:49:55
original_url: https://blog.csdn.net/sevenjoin/article/details/88420885
---

# C++ tuple元组的基本用法(总结)

分类专栏： [C++汇总](https://blog.csdn.net/sevenjoin/category_7945238.html)

版权

**1，元组简介**

    tuple是一个固定大小的不同类型值的集合，是泛化的std::pair。我们也可以把他当做一个通用的结构体来用，不需要创建结构体又获取结构体的特征，在某些情况下可以取代结构体使程序更简洁，直观。std::tuple理论上可以有无数个任意类型的成员变量，而std::pair只能是2个成员，因此在需要保存3个及以上的数据时就需要使用tuple元组了。

    tuple（元组）在c++11中开始引用的。tuple看似简单，其实它是简约而不简单，可以说它是c++11中一个既简单又复杂的东东，关于它简单的一面是它很容易使用，复杂的一面是它内部隐藏了太多细节，要揭开它神秘的面纱时又比较困难。

**2，tuple的创建和初始化**

```cpp
 
std::tuple<T1, T2, TN> t1;            //创建一个空的tuple对象（使用默认构造），它对应的元素分别是T1和T2...Tn类型，采用值初始化。
std::tuple<T1, T2, TN> t2(v1, v2, ... TN);    //创建一个tuple对象，它的两个元素分别是T1和T2 ...Tn类型; 要获取元素的值需要通过tuple的成员get<Ith>(obj)进行获取(Ith是指获取在tuple中的第几个元素，请看后面具体实例)。
std::tuple<T1&> t3(ref&); // tuple的元素类型可以是一个引用
std::make_tuple(v1, v2); // 像pair一样也可以通过make_tuple进行创建一个tuple对象
```

 tuple的元素类型为引用：

```cpp
std::string name;
std::tuple<string &, int> tpRef(name, 30);
// 对tpRef第一个元素赋值，同时name也被赋值 - 引用
std::get<0>(tpRef) = "Sven";
 
// name输出也是Sven
std::cout << "name: " << name << '\n';
```

**3，有关tuple元素的操作**

1.  等价结构体
    

      开篇讲过在某些时候tuple可以等同于结构体一样使用，这样既方便又快捷。如：

```cpp
struct person {
    char *m_name;
    char *m_addr;
    int  *m_ages;
};
 
//可以用tuple来表示这样的一个结构类型，作用是一样的。
std::tuple<const char *, const char *, int>
```

    2. 如何获取tuple元素个数

    当有一个tuple对象但不知道有多少元素可以通过如下查询：

```cpp
// tuple_size
#include <iostream>     // std::cout
#include <tuple>        // std::tuple, std::tuple_size
 
int main ()
{
  std::tuple<int, char, double> mytuple (10, 'a', 3.14);
 
  std::cout << "mytuple has ";
  std::cout << std::tuple_size<decltype(mytuple)>::value;
  std::cout << " elements." << '\n';
 
  return 0;
}
 
//输出结果：
mytuple has 3 elements
```

    3.如何获取元素的值

获取tuple对象元素的值可以通过get<Ith>(obj)方法进行获取；

Ith - 是想获取的元素在tuple对象中的位置。

obj - 是想获取tuple的对象

```cpp
// tuple_size
#include <iostream>     // std::cout
#include <tuple>        // std::tuple, std::tuple_size
 
int main ()
{
  std::tuple<int, char, double> mytuple (10, 'a', 3.14);
 
  std::cout << "mytuple has ";
  std::cout << std::tuple_size<decltype(mytuple)>::value;
  std::cout << " elements." << '\n';
 
  //获取元素
  std::cout << "the elements is: ";
  std::cout << std::get<0>(mytuple) << " ";
  std::cout << std::get<1>(mytuple) << " ";
  std::cout << std::get<2>(mytuple) << " ";
 
  std::cout << '\n';
 
  return 0;
}
 
//输出结果：
mytuple has 3 elements.
the elements is: 10 a 3.14 
```

   tuple不支持迭代，只能通过元素索引(或tie解包)进行获取元素的值。但是给定的索引必须是在编译器就已经给定，不能在运行期进行动态传递，否则将发生编译错误：

```cpp
for(int i=0; i<3; i++)
    std::cout << std::get<i>(mytuple) << " "; //将引发编译错误
```

4.获取元素的类型

 要想得到元素类型可以通过tuple\_element方法获取，如有以下元组对象：

```cpp
std::tuple<std::string, int> tp("Sven", 20);
 
// 得到第二个元素类型
 
std::tuple_element<1, decltype(tp)>::type ages;  // ages就为int类型
 
ages = std::get<1>(tp);
 
std::cout << "ages: " << ages << '\n';
 
//输出结果： 
ages: 20
```

 5.利用tie进行解包元素的值

 如同pair一样也是可以通过tie进行解包tuple的各个元素的值。如下tuple对象有4个元素，通过tie解包将会把这4个元素的值分别赋值给tie提供的4个变量中。

```cpp
#include <iostream>
#include <tuple>
#include <utility>
 
int main(int argc, char **argv) {
    std::tuple<std::string, int, std::string, int> tp;
    tp = std::make_tuple("Sven", 25, "Shanghai", 21);
 
    // 定义接收变量
    std::string name;
    std::string addr;
    int ages;
    int areaCode;
 
    std::tie(name, ages, addr, areaCode) = tp;
    std::cout << "Output: " << '\n';
    std::cout << "name: " << name <<", ";
    std::cout << "addr: " << addr << ", ";
    std::cout << "ages: " << ages << ", ";
    std::cout << "areaCode: " << areaCode << '\n';
 
    return 0;
}
 
//输出结果：
Output: 
name: Sven, addr: Shanghai, ages: 25, areaCode: 21
```

但有时候tuple包含的多个元素时只需要其中的一个或两个元素，如此可以通过std::ignore进行变量占位，这样将会忽略提取对应的元素。可以修改上述例程：

```cpp
#include <iostream>
#include <tuple>
#include <utility>
 
int main(int argc, char **argv) {
    std::tuple<std::string, int, std::string, int> tp;
    tp = std::make_tuple("Sven", 25, "Shanghai", 21);
 
    // 定义接收变量
    std::string name;
    std::string addr;
    int ages;
    int areaCode = 110;
 
    std::tie(name, ages, std::ignore, std::ignore) = tp;
    std::cout << "Output: " << '\n';
    std::cout << "name: " << name <<", ";
    std::cout << "addr: " << addr << ", ";
    std::cout << "ages: " << ages << ", ";
    std::cout << "areaCode: " << areaCode << '\n';
 
    return 0;
}
 
//输出结果：
Output: 
name: Sven, addr: , ages: 25, areaCode: 110
```

   6. tuple元素的引用

      前面已经列举了将引用作为tuple的元素类型。下面通过引用搭配make\_tuple()可以提取tuple的元素值，将某些变量值设给它们，并通过改变这些变量来改变tuple元素的值：

```cpp
#include <iostream>
#include <tuple>
#include <functional>
 
int main(int argc, char **agrv) {
 
    std::tuple<std::string, int, float> tp1("Sven Cheng", 77, 66.1);
 
    std::string name;
    int weight;
    float f;
 
    auto tp2 = std::make_tuple(std::ref(name), std::ref(weight), std::ref(f)) = tp1;
 
    std::cout << "Before change: " << '\n';
    std::cout << "name: " << name << ", ";
    std::cout << "weight: " << weight << ", ";
    std::cout << "f: " << f << '\n';
 
    name = "Sven";
    weight = 80;
    f = 3.14;
 
	std::cout << "After change: " << '\n';
	std::cout << "element 1st: " << std::get<0>(tp2) << ", ";
	std::cout << "element 2nd: " << std::get<1>(tp2) << ", ";
	std::cout << "element 3rd: " << std::get<2>(tp2) << '\n';
 
    return 0;
}
 
//输出结果：
Before change: 
name: Sven Cheng, weight: 77, f: 66.1
After change: 
element 1st: Sven, element 2nd: 80, element 3rd: 3.14
 
 
```



