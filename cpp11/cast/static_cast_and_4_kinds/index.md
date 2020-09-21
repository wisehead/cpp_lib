---
title: static_cast ，reinterpret_cast - 猿人谷6 - 博客园
category: default
tags: 
  - www.cnblogs.com
created_at: 2020-09-21 19:12:13
original_url: https://www.cnblogs.com/heyonggang/p/3361643.html
---


# static_cast ，reinterpret_cast - 猿人谷6 - 博客园

用法：static\_cast < type-id > ( expression )

该运算符把expression转换为type-id类型，但没有运行时类型检查来保证转换的安全性。它主要有如下几种用法：

①用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换。

进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；

进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。

②用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。

③把空指针转换成目标类型的空指针。

④把任何类型的表达式转换成void类型。

注意：static\_cast不能转换掉expression的const、volatile、或者\_\_unaligned属性。

C++中static\_cast和reinterpret\_cast的区别

C++ primer第五章里写了编译器隐式执行任何类型转换都可由static\_cast显示完成;reinterpret\_cast通常为操作数的位模式提供较低层的重新解释

1、C++中的static\_cast执行非多态的转换，用于代替C中通常的转换操作。因此，被做为**显式类型转换使用**。比如：

```plain
int i;
float f = 166.71;
i = static_cast<int>(f);
```

此时结果，i的值为166。

2、C++中的reinterpret\_cast主要是**将数据从一种类型的转换为另一种类型**。所谓“通常为操作数的位模式提供较低层的重新解释”也就是说将数据以二进制存在形式的重新解释。比如：

```plain
int i;
char *p = "This is an example.";
i = reinterpret_cast<int>(p);
```

此时结果，i与p的值是完全相同的。reinterpret\_cast的作用是说将指针p的值以二进制（位模式）的方式被解释为整型，并赋给i，//i 也是指针，整型指针；一个明显的现象是在**转换前后没有数位损失**。

* * *

C++同时提供了4种新的强制类型转换形式（通常称为新风格的或C++风格的强制转 型）：const\_cast(expression)、dynamic\_cast(expression)、 reinterpret\_cast(expression)和 static\_cast(expression)，每一种都适用于特定的目的，具体如下：

（1）**dynamic\_cast** 主要用于执行“安全的向下转型(safe downcasting)”，也就是说，要确定一个对象是否是一个继承体系中的一个特定类型。支持父类指针到子类指针的转换，这种转换时最安全的转换。它 是唯一不能用旧风格语法执行的强制类型转换，也是唯一可能有重大运行时代价的强制转换。

（2）**static\_cast** 可以被用于强制隐形转换（例如，non-const对象转换为const对象，int转型为double，等等），它还可以用于很多这样的转换的反向转换 （例如，void\*指针转型为有类型指针，基类指针转型为派生类指针），但是它不能将一个const对象转型为non-const对象（只有 const\_cast能做到），它最接近于C-style的转换。应用到类的指针上，意思是说它允许子类类型的指针转换为父类类型的指针（这是一个有效的隐式转换），同时，也能够执行相反动作：转换父类为它的子类。

在这最后例子里，被转换的父类没有被检查是否与目的类型相一致。  
代码：  
class Base {};  
class Derived : public Base {};  
  
Base \*a = new Base;  
Derived \*b = static\_cast<Derived \*>(a);  
'static\_cast'除了操作类型指针，也能用于执行类型定义的显式的转换，以及基础类型之间的标准转换:  
代码:  
double d = 3.14159265;  
int i = static\_cast<int>(d);

（3）**const\_cast**一般用于强制消除对象的常量性。它是唯一能做到这一点的C++风格的强制转型。这个转换能剥离一个对象的const属性，也就是说允许你对常量进行修改。

代码:  
class C {};  
const C \*a = new C;  
C \*b = const\_cast<C \*>(a);  

（4）**reinterpret\_cast** 是特意用于底层的强制转型，导致实现依赖（就是说，不可移植）的结果，例如，将一个指针转型为一个整数。这样的强制类型在底层代码以外应该极为罕见。操作 结果只是简单的从一个指针到别的指针的值得二进制拷贝。在类型之间指向的内容不做任何类型的检查和转换。

旧风格 的强制转型依然合法，但是新的形式更可取。首先，在代码中它们更容易识别（无论是人还是像grep这样的工具都是如此），这样就简化了在代码中寻找类型系 统被破坏的地方的过程。其次，更精确地指定每一个强制转型的目的，使得编译器诊断使用错误成为可能。例如，试图使用一个const\_cast以外的新风格 强制转型来消除常量性，代码将无法编译。

---------------------------------------------------


原网址: [访问](https://www.cnblogs.com/heyonggang/p/3361643.html)

创建于: 2020-09-21 19:12:13

目录: default

标签: `www.cnblogs.com`

