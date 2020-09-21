---
title: C++11新特性--完美转发 - 简书
category: default
tags: 
  - www.jianshu.com
created_at: 2020-09-21 17:28:38
original_url: https://www.jianshu.com/p/25fd8f0f5cb2
---

# C++11新特性--完美转发

[![](assets/1600680518-aedc2b9994eb6a5f5ba3df65c3d0db05.webp)](https://www.jianshu.com/u/e5aab688d70b)

[于天佐](https://www.jianshu.com/u/e5aab688d70b)关注

2018.02.02 19:05:56字数 1,865阅读 6,453

#### 转发的问题

    在模板编程中，常有一种场景是把模板参数转发给另一个函数调用，这时候如果只提供值传递版本会显得效率太低。看一下代码

```cpp
template<class TYPE, class ARG>
TYPE* get_instance(ARG arg)
{
     TYPE* ret;
     ret = new TYPE(arg);
     return ret;
}
```

    代码很简单，就是用ARG参数去初始化一个TYPE类型的对象，然后返回该对象指针。考虑一下如果ARG类型是一个自定义类型，那么这样的值传递会是比较大的性能开销。有没有办法改进一下？看一下代码

```kotlin
template<class TYPE, class ARG>
TYPE* get_instance(const ARG& arg)
{
     TYPE* ret;
     ret = new TYPE(arg);
     return ret;
}
```

    这段代码将传入改为了万能的常量左值引用，可以接受任何类型，可以解决性能开销的问题，但是不够灵活，如果我们想TYPE接受一个右值去初始化呢？那么有没有可以把参数连同类型一起转发的方案呢？C++11提供了这样能力既完美转发。代码如下

```cpp
template<class TYPE, class ARG>
TYPE* get_instance(ARG&& arg)
{
     TYPE* ret;
     ret = new TYPE(std::forward<ARG>(arg));
     return ret;
}
```

形参改为了右值引用么？

#### 两个模板函数推导原则

    解释一下前面留下的问题。在模板函数中（注意是模板函数不是模板类，也不是普通函数，只是模板函数），形如上例中的形参即T&&，如果T是一个推导类型（即模板参数）它的意思并不是右值引用，它有一个专用的名字forwarding reference，它遵循以下的特殊推导规则来推导T的类型：  
1、引用折叠原则（reference collapsing rule），下面以int为类型举例，以区别于模板参数T  
a）int& & (引用的引用) 被转化成 int&  
b）int&& & (rvalue的引用）被传化成 int&  
c）int& && (引用作rvalue) 被转化成 int&  
d）int&& && 被转化成 int&&  
2、推导原则  
以上面模板函数为例，三个特殊之处（左值引用，常量左值引用如预期被推导出来）  
a）如果传入get\_instance的参数是int类型（即左值），那么ARG会被推导为int&，即ARG=int&  
b）如果传入get\_instance的参数是右值int类型（即右值），那么ARG被推导为int，即ARG=int  
c）如果传入get\_instance的参数是const int类型（即常量左值），那么ARG被推导为const int&，即ARG=const int&

###### 注意：为什么这里没有参数类型是右值引用类型的参数？？

###### 其实右值引用是一个左值，即你传入函数的实参类型有可能是一个左值（左值引用，左值，常量左值引用，右值引用），也有可能是一个右值。注意到细微的区别了么？这里本章最后会给出一些代码示例。

以上三个特殊推导之处

结合std::forward代码来看一下

```cpp
template <class _Tp>
inline
_Tp&&
forward(typename remove_reference<_Tp>::type& __t)
{
    return static_cast<_Tp&&>(__t);
}

template<class TYPE, class ARG>
TYPE* get_instance(ARG&& arg)
{
     TYPE* ret;
     ret = new TYPE(std::forward<ARG>(arg));
     return ret;
}
```

现在结合上面两个原则来推导一下：  
a）调用get\_instance传入int类型，ARG推导为int&，传递给std::forward的模板参数就是int&类型，std::forward中的typename remove\_reference<\_Tp>::type为int类型，static\_cast中\_Tp&&类型根据引用折叠，推导为int& &&即int&，最后forward转发为int&类型，完美转发。  
b）调用get\_instance传入int右值类型，ARG推导为int，传递给std::forward的模板参数就是int类型，std::forward中的typename remove\_reference<\_Tp>::type为int类型，static\_cast中\_Tp&&类型根据引用折叠，推导为int&&即int&&，最后forward转发为int&&类型，完美转发。  
c）调用get\_instance传入const int类型，ARG推导为const int&，传递给std::forward的模板参数就是const int&类型，std::forward中的typename remove\_reference<\_Tp>::type为const int类型，static\_cast中\_Tp&&类型根据引用折叠，推导为const int& &&即const int&，最后forward转发为const int&类型，完美转发。  
d）调用get\_instance传入int&类型，ARG推导为int&，传递给std::forward的模板参数就是int&类型，std::forward中的typename remove\_reference<\_Tp>::type为int类型，static\_cast中\_Tp&&类型根据引用折叠，推导为int& &&即int&，最后forward转发为int&类型，完美转发。  
e）调用get\_instance传入const int&类型，ARG推导为const int&，传递给std::forward的模板参数就是const int&类型，std::forward中的typename remove\_reference<\_Tp>::type为int类型，static\_cast中\_Tp&&类型根据引用折叠，推导为const int& &&即const int&，最后forward转发为const int&类型，完美转发。

#### 完美转发

    上面分析的情况即为完美转发，总结一下是模板函数形参形如T&&，结合库函数std::forward来将参数实现类型的完美转发。

#### 代码示例

    用代码来补充说明一下上面留下的问题。

```cpp
template <typename T>
void
wrapper(T&& value)
{
    std::cout<<"T is a ref type(lvalue or rvalue ref)?:"<<std::is_reference<T>::value<<std::endl;
    std::cout<<"T is right value ref?:"<<std::is_rvalue_reference<T>::value<<std::endl; //none T is deduce to rvalue ref
}
static void execute()
{
    int left = 1;
    int &&right = 2;

    wrapper(right); //input is a lvalue
    wrapper(3); //intput is a rvalue
    wrapper(std::move(left)); //input is a rvalue
    wrapper(left); //input is a lvalue
}
```

输出是  
T is a ref type(lvalue or rvalue ref)?:1  
T is right value ref?:0  
T is a ref type(lvalue or rvalue ref)?:0  
T is right value ref?:0  
T is a ref type(lvalue or rvalue ref)?:0  
T is right value ref?:0  
T is a ref type(lvalue or rvalue ref)?:1  
T is right value ref?:0

结果跟我们上述的分析是一致的，T不会推导为右值引用，原因是输入参数只有左值和右值两种，不存在右值引用这种输入。  
简单分析一下前三个wrapper调用的区别，第一句调用right是个右值引用类型的变量，自然可以被取地址，所以它是一个左值。  
第二句调用毋庸置疑传入的是一个右值。  
第三句调用跟第二句的效果一模一样，由于std::move返回了一个右值引用类型的返回值，函数返回值通常是个右值，所以这里它的返回值自然是一个右值。

#### 最后几点值得注意的

    再对比一下完美转发和接受一个右值引用的函数对比。

```csharp
template <typename T>
void
wrapper(T&& value)；

void 
wrapper_none_template(int&& value);
```

    这两个函数的区别是，上面的模板函数即提现c++11所谓的完美转发，T会根据传入实参参数的不同（左值、右值、左值引用、常量左值引用）而推导出不同的类型。  
下面的函数是一个只接受右值实参的函数，如果传入的值不是右值，那么编译会报错。  
    还有一点，用模板函数forwarding reference去进行转发，所有的传入参数最终都是引用类型（左值的和右值的）即不产生值传递所造成的额外构造和析构。之所以提到这一点，主要是针对传入一个右值的情况。前面提到如果传入一个右值int，T会被推导为int，但是形参还是int&&，也就是说形参是一个右值引用，它绑定了一个右值，所以还是一个引用。

1人点赞

[C++11](https://www.jianshu.com/nb/21839833)

"小礼物走一走，来简书关注我"

赞赏支持还没有人赞赏，支持一下

[![  ](assets/1600680518-d923559d5fef8e58ea0f5bc8661e8281.webp)](https://www.jianshu.com/u/e5aab688d70b)

[于天佐](https://www.jianshu.com/u/e5aab688d70b "于天佐")

总资产26 (约2.23元)共写了3.9W字获得46个赞共31个粉丝

关注

---------------------------------------------------


原网址: [访问](https://www.jianshu.com/p/25fd8f0f5cb2)

创建于: 2020-09-21 17:28:38

目录: default

标签: `www.jianshu.com`

