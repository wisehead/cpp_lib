---
title: C++：类模板与模板类 - XYQ全哥 - 博客园
category: default
tags: 
  - www.cnblogs.com
created_at: 2020-05-08 15:47:00
original_url: https://www.cnblogs.com/XYQ-208910/p/4912741.html
---


# C++：类模板与模板类 - XYQ全哥 - 博客园

　　　　　　　　　　　　　　　　　　6.3 类模板和模板类  
  
所谓类模板，实际上是建立一个通用类，其数据成员、成员函数的返回值类型和形参类型不具体指定，用一个虚拟的类型来代表。使用类模板定义对象时，系统会实参的类型来取代类模板中虚拟类型从而实现了不同类的功能。

定义一个类模板与定义函数模板的格式类似，必须以关键字template开始，后面是尖括号括起来的模板参数，然后是类名，其格式如下：

template <typename 类型参数>  
class 类名{  
       类成员声明  
};

或者  
  
template <class 类型参数>  
class 类名{  
       类成员声明  
};  
  
（1）template:是一个声明模板的关键字，它表明声明一个模板  
（2）类型参数：通常用C++标识符表示，如T、Type等，实际上是一个虚拟的类型名，现在未指定它是哪一种具体的类型，但使用类模板时，必须将类型参数实例化。

（3）typename和class的作用相同，都是表示其后面的参数是一个虚拟的类名(即类型参数).  
  
在类声明中，欲采用通用数据类型的数据成员、成员函数的参数或返回类型前面需要加上类型参数。

如建立一个用来实现求两个数最大值的类模板

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

```plain
template<typename T>    //模板声明，其中T为类型参数
    class Compare{
      public:
       Compare(T i,T j)
       {
        x = i;
        y = j;
       }
       T max()
       {
        return (x>y)?x:y;
       } 
      private:
       T x,y; 
    };
```

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

用类模板定义对象时，采用以下形式：  
  
类模板名<实际类型名>对象名\[(实参表列)\];  
  
因此，使用上面求最大值的类型模板的主函数可写成：

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

```plain
 int main()
     {
      Compare<int>com1(3,7);
      Compare<double>com2(12.34,56.78);
      Compare<char>com3('a','x');
      cout<<"其中的最大值是:"<<com1.max()<<endl;
      cout<<"其中的最大值是:"<<com2.max()<<endl;
      cout<<"其中的最大值是:"<<com3.max()<<endl;
      return  0;
     }    
```

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

//例6.6 类模板compare的使用举例

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

```plain
#include<iostream.h>
template<typename T>    //模板声明，其中T为类型参数
class Compare{
  public:
    Compare(T i,T j)
    {
      x = i;
      y = j;
    }
    T max()
     {
      return (x>y)?x:y;
     } 
 private:
    T x,y; 
};
int main()
{
Compare<int>com1(3,7);                       //用类模板定义对象com1，此时T被int替代 
Compare<double>com2(12.34,56.78);            //用类模板定义对象com2，此时T被double替代 
Compare<char>com3('a','x');                  //用类模板定义对象com3，此时T被char替代 
cout<<"其中的最大值是:"<<com1.max()<<endl;   
cout<<"其中的最大值是:"<<com2.max()<<endl;
cout<<"其中的最大值是:"<<com3.max()<<endl;
return  0;
}
/*
程序运行结果是：
其中的最大值是:7
其中的最大值是:56.78
其中的最大值是:x 
*/         
```

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

在以上例子中，成员函数(其中含有类型参数)是定义类体内的。但是，类模板中的成员函数，也可以在类模板外定义。此时，若成员函数中有参数类型存在，则C++有一些特殊的规定：

_（1）需要在成员函数定义之前进行模板声明；  
（2）在成员函数名前缀上"类名<类型参数>::";  
  
在类模板外定义成员函数的一般形式如下：_

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

```plain
temlate<typename 类型参数>
  函数类型 类名<类型参数>::成员函数名(形参表)
  ｛
    函数体； 
   ｝
   
   如上题中成员函数max在类模板外定义时，应该写成：
   template<typename T>
   T Compare<T>::max()
   {
    return (x>y)?x:y;
   } 
```

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

//例6.7 在类模板外定义成员函数函数举例。

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

```plain
#include<iostream.h>
template<typename T>    //模板声明，其中T为类型参数
class Compare{
  public:
    Compare(T i,T j)
    {
      x = i;
      y = j;
    }
    T max(); 
 private:
    T x,y; 
};
template<class T>
T Compare<T>::max()
{
 return (x>y)?x:y;
}
int main()
{
Compare<int>com1(3,7);                       //用类模板定义对象com1，此时T被int替代 
Compare<double>com2(12.34,56.78);            //用类模板定义对象com2，此时T被double替代 
Compare<char>com3('a','x');                  //用类模板定义对象com3，此时T被char替代 
cout<<"其中的最大值是:"<<com1.max()<<endl;   
cout<<"其中的最大值是:"<<com2.max()<<endl;
cout<<"其中的最大值是:"<<com3.max()<<endl;
return  0;
} 
/*
程序运行结果是：
        其中的最大值是:7
        其中的最大值是:56.78
        其中的最大值是:x

  此例中，类模板Compare经实例化后生成了3个类型分别为int、double、char的模板类，这3个模板类
  经实例化后又生成了3个对象com1、com2、com3。类模板代表了一类类，模板类表示某一具体的类。关系如下：
  
                                             类模板
                                            Compare<T>
        实例化成模板类：Compare<int>       Compare<double>     Compare<char>
        实例化模板类对象：com1                 com2                com3
*/
```

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

//例6.8 类模板Stack的使用举例。

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

```plain
#include<iostream.h>
const int size=10;
template<class T>                     //模板声明，其中T为类型参数 
class Stack{                          //类模板为Stack 
 public:
  void init()
  {
   tos=0;
  }
  void push(T ob);                    //声明成员函数push的原型，函数参数类型为T类型
  T pop();                            //声明成员函数pop的原型，其返回值类型为T类型
 private:
  T stack[size];                      //数组类型为T，即是自可取任意类型 
  int tos; 
};
template<class T>                     //模板声明 
void Stack<T>::push(T ob)             //在类模板体外定义成员函数push 
{
  if(tos==size)
   {
    cout<<"Stack is full"<<endl;
    return;
   }
  stack[tos]=ob;
  tos++; 
}
template<typename T>                  //模板声明 
T Stack<T>::pop()                               //在类模板体外定义成员函数push
{
  if(tos==0)
   {
    cout<<"Stack is empty"<<endl;
    return 0;
   }
  tos--; 
  return stack[tos];  
}
int main()
{
 //定义字符堆栈 
 Stack<char> s1;                        //用类模板定义对象s，此时T被char取代
 s1.init();
 s1.push('a');
 s1.push('b');
 s1.push('c'); 
 for(int i=0;i<3;i++){cout<<"pop s1："<<s1.pop()<<endl;}
 
 //定义整型堆栈 
 Stack<int> s2;                        //用类模板定义对象s，此时T被int取代
 s2.init();
 s2.push(1);
 s2.push(3);
 s2.push(5); 
 for(int i=0;i<3;i++){cout<<"pop s2："<<s2.pop()<<endl;} 
 
 return 0; 
}

/*
程序运行结果是：
pop s1：c
pop s1：b
pop s1：a
pop s2：5
pop s2：3
pop s2：1 

 说明：
      （1）在每一个类模板定义之前，都需要在前面加上模板声明，如
           template<typename T>
         或
           tempplate<class T>
           
          并且，类模板在使用时，必须在模板类名字后面缀上<类型参数> ，如
           Stack<T>  
            
      （2）如同模板函数一样，模板类也可以有多个类型参数。        
*/
```

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

//例6.9 有两个类型参数的类模板举例

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

```plain
#include<iostream.h>
template<class QQ,class T>                    //声明模板，具有T1,T2两个类型参数 
class Myclass{                                 //定义模板类Myclass 
  public:
   Myclass(QQ a,T b);
   void show();
  private:
   QQ x;
   T y;
};
template<typename QQ,typename T>
Myclass<QQ,T>::Myclass(QQ a,T b)
{
 x = a;
 y = b;
}
template<class QQ,class T>
void Myclass<QQ,T>::show()
{
 cout<<"x="<<x<<","<<"y="<<y<<endl;
}
int main()
{
 Myclass <int,double>m1(12,0.15);               //用类模板定义对象m1,此时T1,T2分别被int、double取代 
 Myclass <int,char*>m2(12,"This a test.");      //用类模板定义对象m2,此时T1,T2分别被int,char*取代

 m1.show();
 m2.show();
 
 return 0; 
}
/*
程序运行结果是：
x=12,y=0.15
x=12,y=This a test. 
*/
```

[![复制代码](assets/1588924020-48304ba5e6f9fe08f3fa1abda7d326ab.gif)](javascript: "复制代码")

---------------------------------------------------


原网址: [访问](https://www.cnblogs.com/XYQ-208910/p/4912741.html)

创建于: 2020-05-08 15:47:00

目录: default

标签: `www.cnblogs.com`

