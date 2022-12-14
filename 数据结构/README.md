### 😎 作者

⭐️ 星队 :star2:

:calendar: 创建日期

2021-7-16 —— 2021-8-22

> 请仅做个人学习、研究使用





### :pencil2: 第一次重构

:calendar: 日期

2022-11-10 —— ？

因忙于其他事情，2022-11-24起停更。

:clipboard: 重构内容

1. 使用 Markdown 基本语法编写文档。:memo:
2. 对每个数据结构进行更加详细的介绍。:thumbsup:
3. 增加了大量插画，便于读者理解。:baby:
4. 编码风格更加严谨、规范。:ghost:

### 😎 负责人

:strawberry: 草莓夹心糖 :candy:

---

### 😋 开场白

​	传统的顺序存储结构，比如数组。查找操作的时间复杂度是O(1)，而插入、删除操作，需要移动大量元素，时间复杂度是O(n)。

![1](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/README.img/11.png)



​		举个例子，我们要管理一堆票据，可能有一张，但也可能有一亿张，事先不知道数量，难道我们要申请100G的大数组等着吗？假如用户有一百万张票据，如果用数组进行操作，删除然后添加票据，是每次删除让后面五百万张往前移一格呢、还是每次添加从头搜索空闲格子？如何区分空闲格子和值为0的数据？搞区分的话是多占用空间呢还是占用数据值域？占用了值域会不会使得数据处理变得格外复杂？会不会一不小心就和正常数据混淆？万一拿来区分的字段在某个版本后废弃不用、或者扩充值域了呢？显然，这些都是很棘手的问题。

​		那么，有没有一种高效的数据结构来处理上述问题呢？其实，链表就是，链表适合解决动态数量的数据存。

​		传统的单链表，有一个数据域，一个指针域，指针域指向下一个结构相同的结点，如图。

![2](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/README.img/12.png)

​		单链表这样的链式存储结构，在序列的插入和删除操作上，将时间复杂度降到了O(1)，而查找操作的时间复杂度，升到了O(n)。

---

​		那么，为了在时间上优化它，我们将一个结点的指针域增加成两个，一个指向左边，一个指向右边，把它设计成二叉树的结构，像常见的排序二叉树，通过与根节点的比较来快速确定数据是在左子树还是右子树。这样就得到了O(logN)的查询效率。

![3](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/README.img/13.png)

---

​		可是，日常生活中的数据都具有很强的不确定性，这时候二叉树可能 “偏” 得很厉害；极端情况下甚至会 “退化” 成单链表 （这样的话，绝大多数结点的左或右指针都空着，不仅空间消耗更高，而且查询效率没有丝毫提升）。

![4](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/README.img/14.png)



​		因此我们需要研究怎么样的二叉树才能有最好的查询效率、怎样才能保持二叉树的良好性能，于是就出现了满二叉树、平衡二叉树、红黑树等概念/算法

---

​		但这样空间占用就比单链表更多了。怎么办呢？

​		堆是一种优化到极致的二叉树；它实际上就是一个数组，左右结点对应的数组下标可以直接计算出来，这就省掉了指向子结点的指针。不过，指针没了，灵活管理不定量数据、低消耗的插入删除等好处也没了。

​		所以出现了一个折中的方案—— B树，把结点做大一些，多存储一些数据，让若干数据共用一组指针，就像一种 “半堆半树” 的数据结构。这样一来，能用更少的指针得到差不多的性能，这就把空间占用问题和高消耗的插入删除问题给解决了，同时查找效率仍然保持在O(logN)。

​		顺带的，这也避免了需要连续读取数据时不停的顺着指针跳转的问题，因此是一种非常适合磁盘存储的数据结构。

---



​		说了那么多，你觉得学数据结构的目的是什么？目的就是让你学会因地制宜地、灵活地组织数据——而且随便你搞出多么奇怪的数据结构、多么复杂的数据组织形式，你都能清晰的给出它（对某个特定任务）的时间 / 空间复杂度。

​		当你能掌握到这个程度时，你完全可以将满二叉树、红黑树、AVL树、B树、B+树的定义统统忘掉；但只要有需要，你随时随地都能把你面对的数据整进一个结合了二叉树和队列优点的、不知道该叫什么的数据结构里——从而以最高效率完成你面对的任务。

​		拿程序设计语言的术语来说，链表的定义并不是 final class List<T>，而是abstract class List<T>——前者是 “这是一个现成的完美品”  “用就对了别管它怎么实现也别试图改进它”；后者是 “这并不是一个完美的现成品”  “你必须彻底搞明白它的设计思路”  “你必须自己改进它” ……

​		所以说数据结构与算法这一块知识，是一个整体框架，不应该习惯性地分章节摘开、把明显具有演进关系的概念割裂成一个个 final class讲解/学习。

​		另外，如果你追求的是扎实的基本功，而不是暴力AC，我都建议你再仔细地学习一遍数据结构与算法。
