---
title: C++标准转换运算符reinterpret_cast - lsgxeva - 博客园
category: default
tags: 
  - www.cnblogs.com
created_at: 2020-09-21 19:13:01
original_url: https://www.cnblogs.com/lsgxeva/p/11005293.html
---

# C++标准转换运算符reinterpret\_cast

来源 [https://www.cnblogs.com/codingmengmeng/p/7650885.html](https://www.cnblogs.com/codingmengmeng/p/7650885.html)

## reinterpret\_cast<new\_type> (expression)

reinterpret\_cast运算符是用来处理无关类型之间的转换；它会产生一个新的值，这个值会有与原始参数（expression）有完全相同的比特位。

什么是无关类型？我没有弄清楚，没有找到好的文档来说明类型之间到底都有些什么关系（除了类的继承以外）。后半句倒是看出了reinterpret\_cast的字面意思：重新解释（类型的比特位）。我们真的可以随意将一个类型值的比特位交给另一个类型作为它的值吗？其实不然。

IBM的C++指南里倒是明确告诉了我们reinterpret\_cast可以，或者说应该在什么地方用来转换运算符：

*   从指针类型到一个足够大的整数类型
*   从整数类型或者枚举类型到指针类型
*   从一个指向函数的指针到另一个不同类型的指向函数的指针
*   从一个指向对象的指针到另一个不同类型的指向对象的指针
*   从一个指向类函数成员的指针到另一个指向不同类型的函数成员的指针
*   从一个指向类数据成员的指针到另一个指向不同类型的数据成员的指针

不过我在Xcode中测试了一下，事实上reinterpret\_cast的使用并不局限在上边所说的几项的，任何类型的指针之间都可以互相转换，都不会得到编译错误。上述列出的几项，可能 是Linux下reinterpret\_cast使用的限制，也可能是IBM推荐我们使用reinterpret\_cast的方式。

所以总结来说：reinterpret\_cast用在任意指针（或引用）类型之间的转换；以及指针与足够大的整数类型之间的转换；从整数类型（包括枚举类型）到指针类型，无视大小。

（所谓“足够大的整数类型”，取决于操作系统的参数，如果是32位的操作系统，就需要整型（int）以上的；如果是64位的操作系统，则至少需要长整型（long）。具体大小可以通过sizeof运算符来查看）。

## reinterpret\_cast有何作用

从上边对reinterpret\_cast介绍，可以感觉出reinterpret\_cast是个很强大的运算符，因为它可以无视种族隔离，随便搞。但就像生物的准则，不符合自然规律的随意杂交只会得到不能长久生存的物种。随意在不同类型之间使用reinterpret\_cast，也会造成程序的破坏和不能使用。

比如下边的代码

```plain
typedef int (*FunctionPointer)(int); 
int value = 21; 
FunctionPointer funcP; 
funcP = reinterpret_cast<FunctionPointer> (&value); 
funcP(value); 
```

先用typedef定义一个指向函数的指针类型，所指向的函数接受一个int类型作为参数。然后我用reinterpret\_cast将一个整型的地址转换成该函数类型并赋值给了相应的变量。最后，我还用该整型变量作为参数交给了指向函数的指针变量。

这个过程编译器都成功地编译通过，不过一旦运行我们就会得到“EXC\_BAD\_ACCESS”的运行错误，因为我们通过funcP所指的地址找到的并不是函数入口。

由此可知，reinterpret\_cast虽然看似强大，作用却没有那么广。[IBM的C++指南](http://publib.boulder.ibm.com/infocenter/compbgpl/v9v111/index.jsp?topic=/com.ibm.xlcpp9.bg.doc/language_ref/keyword_reinterpret_cast.htm)、C++之父[Bjarne Stroustrup的FAQ网页](http://www2.research.att.com/~bs/bs_faq2.html#static-cast)和[MSDN的Visual C++](http://msdn.microsoft.com/en-us/library/e0w9f63b%28VS.80%29.aspx)也都指出：错误的使用reinterpret\_cast很容易导致程序的不安全，只有将转换后的类型值转换回到其原始类型，这样才是正确使用reinterpret\_cast方式。

这样说起来，reinterpret\_cast转换成其它类型的目的只是临时地隐藏自己的什么（做个卧底？），要真想使用那个值，还是需要让其露出真面目才行。那到底它在C++中有其怎样存在的价值呢？

[MSDN的Visual C++ Developer Center](http://msdn.microsoft.com/en-us/library/e0w9f63b%28VS.80%29.aspx) 给出了它的使用价值：用来辅助哈希函数。下边是MSNDN上的例子：

[![复制代码](assets/1600686781-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

```plain
// expre_reinterpret_cast_Operator.cpp
// compile with: /EHsc
#include <iostream>
// Returns a hash code based on an address
unsigned short Hash( void *p ) {
    unsigned int val = reinterpret_cast<unsigned int>( p );
    return ( unsigned short )( val ^ (val >> 16));
}

using namespace std;
int main() {
    int a[20];
    for ( int i = 0; i < 20; i++ )
        cout << Hash( a + i ) << endl;
}

//如果跟我一样是64位的系统，可能需要将unsigned int改成 unsigned long才能运行。
```

[![复制代码](assets/1600686781-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

这段代码适合体现哈希的思想，暂时不做深究，但至少看Hash函数里面的操作，也能体会到，对整数的操作显然要对地址操作更方便。在集合中存放整形数值，也要比存放地址更具有扩展性（当然如果存void \*扩展性也是一样很高的），唯一损失的可能就是存取的时候整形和地址的转换（这完全可以忽略不计）。

不过可读性可能就不高，所以在这种情况下使用的时候，就可以用typedef来定义个指针类型：  
`typedef unsigned int PointerType;`

这样不是更棒，当我们在64位机器上运行的时候，只要改成：  
`typedef unsigned long PointerType;`

## 当reinterpret\_cast面对const

[IBM的C++指南](http://publib.boulder.ibm.com/infocenter/compbgpl/v9v111/index.jsp?topic=/com.ibm.xlcpp9.bg.doc/language_ref/keyword_reinterpret_cast.htm)指出:reinterpret\_cast不能像const\_cast那样去除const修饰符。 这是什么意思呢？代码还是最直观的表述：

[![复制代码](assets/1600686781-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

```plain
int main() 
{
    typedef void (*FunctionPointer)(int);
    int value = 21;
    const int* pointer = &value;
    
    //int * pointer_r = reinterpret_cast<int*> (pointer); 
    // Error: reinterpret_cast from type 'const int*' to type 'int*' casts away constness
    
    FunctionPointer funcP = reinterpret_cast<FunctionPointer> (pointer);
}
```

[![复制代码](assets/1600686781-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

例子里，我们像前面[const\_cast一篇](http://www.cnblogs.com/ider/archive/2011/07/22/cpp_cast_operator_part2.html)举到的例子那样，希望将指向const的指针用运算符转换成非指向const的指针。但是当实用reinterpret\_cast的时候，编译器直接报错组织了该过程。这就体现出了const\_cast的独特之处。

但是，例子中还有一个转换是将指向const int的指针付给指向函数的指针，编译顺利通过编译，当然结果也会跟前面的例子一样是无意义的。

如果我们换一种角度来看，这似乎也是合理的。因为  
`const int* p = &value;  
int * const q = &value;`

这两个语句的含义是不同的，前者是"所指内容不可变"，后者则是"指向的地址不可变"（[具体参考此处](http://en.wikipedia.org/wiki/Const-correctness)）。因此指向函数的指针默认应该就带有"所指内容不可变"的特性。

毕竟函数在编译之后，其操作过程就固定在那里了，我们唯一能做的就是传递一些参数给指针，而无法改变已编译函数的过程。所以从这个角度来想，上边例子使用reinterpret\_cast从const int \* 到FunctionPointer转换就变得合理了，因为它并没有去除const限定

Director: [Jim Fawcett](http://www.ecs.syr.edu/faculty/fawcett/handouts/webpages/FawcettHome.htm)

1.  [C++ Language Tutorial - Type Casting](http://www.cplusplus.com/doc/tutorial/typecasting/)
2.  [Object Oriented Design](http://www.ecs.syr.edu/faculty/fawcett/handouts/webpages/CSE687.htm)
3.  [IBM Complilers - XL C/C++ V9.0 for Linux - The reinterpret\_cast operator (C++ only)](http://publib.boulder.ibm.com/infocenter/compbgpl/v9v111/index.jsp?topic=/com.ibm.xlcpp9.bg.doc/language_ref/keyword_reinterpret_cast.htm)
4.  [Bjarne Stroustrup's C++ Style and Technique FAQ](http://www2.research.att.com/~bs/bs_faq2.html)
5.  [MSDN Visual C++ Developer Center - reinterpret\_cast Operator](http://msdn.microsoft.com/en-us/library/e0w9f63b%28VS.80%29.aspx)

\================ End

---------------------------------------------------


原网址: [访问](https://www.cnblogs.com/lsgxeva/p/11005293.html)

创建于: 2020-09-21 19:13:01

目录: default

标签: `www.cnblogs.com`

