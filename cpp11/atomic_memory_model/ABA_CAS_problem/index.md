---
title: ABA问题 - 简书
category: default
tags: 
  - www.jianshu.com
created_at: 2020-09-23 17:46:04
original_url: https://www.jianshu.com/p/b0add05bdede
---

# ABA问题

[![](assets/1600854364-dfdf65375d3023e3ce23f4fc83fd1a94.jpg)](https://www.jianshu.com/u/93eaa63b8cba)

[疯癫的猪猪猪](https://www.jianshu.com/u/93eaa63b8cba)关注

0.1372019.03.22 15:01:18字数 408阅读 3,092

CAS会导致“ABA问题”。

线程1准备用CAS将变量的值由A替换为C，在此之前，线程2将变量的值由A替换为B，又由B替换为A，然后线程1执行CAS时发现变量的值仍然为A，所以CAS成功。但实际上这时的现场已经和最初不同了，尽管CAS成功，但可能存在潜藏的问题。

现有一个用单向链表实现的堆栈，栈顶为A，这时线程T1已经知道A.next为B，然后希望用CAS将栈顶替换为B；

在T1执行上面这条指令之前，线程T2介入，将A、B出栈，再pushD、C、A；

此时轮到线程T1执行CAS操作，检测发现栈顶仍为A，所以CAS成功，栈顶变为B，但实际上B.next为null，所以此时的情况变为：堆栈中只有B一个元素，C和D组成的链表不再存在于堆栈中，C、D丢掉了。

Java并发包为了解决这个问题，提供了一个带有标记的原子引用类“AtomicStampedReference”，它可以通过控制变量值的版本来保证CAS的正确性。每次在执行数据的修改操作时，都会带上一个版本号，一旦版本号和数据的版本号一致就可以执行修改操作并对版本号执行+1操作，否则就执行失败。

2人点赞

[日记本](https://www.jianshu.com/nb/28825725)

"小礼物走一走，来简书关注我"

赞赏支持还没有人赞赏，支持一下

[![  ](assets/1600854364-dfdf65375d3023e3ce23f4fc83fd1a94.jpg)](https://www.jianshu.com/u/93eaa63b8cba)

[疯癫的猪猪猪](https://www.jianshu.com/u/93eaa63b8cba "疯癫的猪猪猪")

总资产1 (约0.11元)共写了9066字获得4个赞共2个粉丝

关注

---------------------------------------------------


原网址: [访问](https://www.jianshu.com/p/b0add05bdede)

创建于: 2020-09-23 17:46:04

目录: default

标签: `www.jianshu.com`

