### Bellman-Ford——解决负权边

​		上节学的Dijkstra算法，边的权值都是正数，因此不会存在一个未拓展到的顶点来使当前路径更短，因而保证了算法的准确性。Bellman-Ford算法非常简单，核心代码只有4行，但可以完美解决有负权边（边的权值为负数）的图。

```c
for (int k = 1; k < n-1 ; ++k)
    for (int i = 1; i <= m ; ++i)
        if (dis[v[i]] > dis[u[i]] + w[i])
            dis[v[i]] = dis[u[i]] + w[i];
```

​		上面代码中，外循环一共循环了 n - 1次（n为顶点个数），内循环循环了m次（m为边的个数），即枚举每一条边。dis数组和Dijkstra算法一样，用来记录源点到各点的最短路径。u、v、w分别表示边的起点、终点、权值。例如第i条边存储在u[i]、v[i]、w[i]中，表示从点u[i]到点v[i]这条边（**u[i] -> v[i]**）权值为w[i]。



```c
if (dis[v[i]] > dis[u[i]] + w[i])
    dis[v[i]] = dis[u[i]] + w[i];
```

​		上面这两行代码，看看能否通过**u[i] -> v[i]**权值为w[i]的这条边，使得1号顶点到v[i]号顶点的距离变短。1号到u[i]号顶点的距离（**dis[u[i]]**）加上**u[i] -> v[i]**这条边（权值为w[i]）是否会比原先1号到v[i]号的路程（**dis[v[i]]**）要短。其实与Dijkstra算法的松弛操作一样，现在要把所有的边都松弛一边，代码如下

```c
for (int i = 1; i <= m ; ++i)
    if (dis[v[i]] > dis[u[i]] + w[i])
        dis[v[i]] = dis[u[i]] + w[i];
```



#### 举例

把每条边都松弛一边会怎样。求下图1号顶点到其余所有顶点的最短路径。

![3](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/3.png)



- 还是用dis数组存储1号顶点到所有顶点的距离。

![4](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/4.png)

​		根据边给出的顺序，我们先处理第一条边 **2 -> 3（2）**，判断**dis[3]**是否大于**dis[2] + 2**，此时dis[3]为INF，dis[2]为INF，所以通过 **2 -> 3（2）**这条边不能使dis[3]值变小，松弛失败。

- 处理第二条边**1 -> 2（-3)，dis[2] > dis[1] + (-3)**，松弛成功。

- 处理第三条边**1 -> 5（5），dis[5] > dis[1] + 5**，松弛成功。
- 处理剩下的边......

对所有边松弛一遍后结果如下:

![5](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/5.png)



这时1到2、1到5号顶点距离都缩短了，接下来再对所有边进行松弛，看看会发生上面。

![6](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/6.png)

​		现在dis[3]、dis[4]也发生了改变。我们发现第一轮松弛后，得到的是源点 “**只能经过一条边**”到达其余顶点的最短路径长度。第二轮松弛之后，得到的是从源点到 “**最多经过两条边**”到达其余各点的最短路径长度。那么需要进行多少轮松弛呢？其实要**进行n - 1**轮，因为在一个含有n个顶点的图中，任意两点之间的最短路径最多包含n - 1条边。



![7](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/7.png)

在这个例子，其实进行3轮松弛后dis数组已经定形了，所以更具体地说，是**最多**进行 n - 1轮松弛。



​		Bellman-Ford算法经常在未达到 n - 1轮松弛前就已算出最短路径，我们可以定义一个check变量来判断本轮松弛是否发生变化，达到优化代码的目的。

#### 完整代码

```c
#include <stdio.h>

int main() {

    int n, m, i, k, inf=999999;
    int dis[10], u[10], v[10], w[10];
    bool check = false;

    scanf("%d %d", &n, &m);   // 读入顶点数、边条数

    for (i = 1; i <= m; ++i)    // 读入边
        scanf("%d %d %d", &u[i], &v[i], &w[i]);
    for (i = 1; i <= n ; ++i)   // 初始化dis数组
        dis[i] = inf;
    dis[1] = 0;

    // Bellman-Ford
    for (k = 1; k < n-1 ; ++k) {
        for (i = 1; i <= m ; ++i) {
            if (dis[v[i]] > dis[u[i]] + w[i]) {
                dis[v[i]] = dis[u[i]] + w[i];
                check = true;
            }
        }
        if (!check)
            break;  // dis数组不再更新, 则提前退出循环
    }
    
    printf("输出\n");
    for (i = 1; i <= n; ++i)
        printf("%d ", dis[i]);
    return 0;
}
```

- 结果

```c
5 5
2 3 2
1 2 -3
1 5 5
4 5 2
3 4 3
输出
0 -3 -1 2 4
```



### Bellman-Ford的队列优化

​		在Bellman-Ford算法中，每次松弛后，有一些点已求得最短路径，此后这些点的估计值会一直保持不变，不再受到后续松弛的影响，但是每次还要判断是否需要松弛，这里浪费了时间。这就启发我们：**每次仅对最短路径估计值发生变化了的顶点的所有出边进行松弛操作。**但如何知道当前哪些点的路径发生了变化呢？这里可以用一个队列来维护这些点。

#### 思路

​		每次选取队首顶点u，对顶点u的所有出边进行松弛操作。例如一条**u -> v**的边，如果通过**u -> v**这条边使得源点到顶点v的路程变短（dis[u] + e[u] [v] < dis[v]），且顶点v不在队列中，就将v放入队尾。注意，同一个顶点同时在队列中出现多次是毫无意义的，所有需要一个book数组来标记。对顶点u的所有出边松弛完后，将u出队。接下来在队列中选取新的队首元素，进行上述操作，直到队列为空。

```c
while (head < tail) {  // 队不空时循环
    k = first[que[head]];   // 队首顶点
    while (k != -1) {    // 扫描当前顶点的所有出边
        if (dis[v[k]] > dis[u[k]] + w[k]) {
            dis[v[k]] = dis[u[k]] + w[k];
            // 用book数组判断顶点v[k]是否在队列中
            // 如果不使用数组标记, 判断一个顶点是否在队列中就需要从head 到 tail循环一遍
            //这很浪费时间
            if (book[v[k]] == 0) {   // v[k]不在队列中
                // 入队
                que[tail] = v[k];
                ++ tail;
                book[v[k]] = 1;  // 标记
            }
        }
        k = next[k];
    }
    // 出队并取消标记
    ++ head;
    book[que[head]] = 0;
}
```



#### 举例

```c
数据 5个顶点 7条边
5 7
1 2 2
1 5 10
2 3 3
2 5 7
3 4 4 
4 5 5
5 3 6
```

![8](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/8.png)

- 首先将1号顶点入队

![9](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/9.png)

​		队首1号顶点的出边有**1 -> 2**、**1 -> 5**。先看**1 -> 2**，因为dis[2] > dis[1] + (**1 -> 2**)，dis[2]值变成2，松弛成功。并且2号顶点不在队列，因此将2号入队。再看**1 -> 5**，dis[5] > dis[1] + (**1 -> 5**)，dis[5] = 10，顶点5入队。结果如下:

![10](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/10.png)



- 1号处理完后，出队（++head），再对下一个队首元素（2号）进行处理

出边**2 -> 5**将1到5顶点的路程缩短（dis[5]更新成9），但是5号**已经**在队列中，因此**不能**再次入队。

![11](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/11.png)

- 依次对剩下的点做相同处理，直到队列为空。最终数组dis和队列que状态如下：

![12](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/12.png)



#### 完整代码

```c
#include <stdio.h>
// 数组实现邻接表来存储这个图(图.md有讲到)

int main() {
    int n, m, i, j, k;
    int u[8], v[8], w[8];    // 数组大小比 m大1
    int first[6], next[8];   // first大小比 n大1, next比 m大1
    int dis[6] = {0}, book[6] = {0};
    int que[101] = {0}, head = 1, tail = 1;
    int inf = 999999;

    scanf("%d %d", &n, &m);   // 输入顶点数、边的个数

    // 初始化
    for (i = 1; i <= n; ++i)  first[i] = -1;

    for (i = 1; i <= n; ++i)  book[i] = 0;

    for (i = 1; i <= n; ++i)  dis[i] = inf;
    dis[1] = 0;

    // 读入边
    for (i = 1; i <= m; ++i) {
        scanf("%d %d %d", &u[i], &v[i], &w[i]);  // 读入边
        // 建表的关键
        next[i] = first[u[i]];
        first[u[i]] = i;
    }

    // 1号入队、标记
    que[tail] = 1;  ++ tail;  book[1] = 1;

    while (head < tail) {
        k = first[que[head]];
        while (k != -1) {
            if (dis[v[k]] > dis[u[k]] + w[k]) {
                dis[v[k]] = dis[u[k]] + w[k];
                if (book[v[k]] == 0) {
                    que[tail] = v[k];
                    ++ tail;
                    book[v[k]] = 1;
                }
            }
            k = next[k];
        }
        ++ head;
        book[que[head]] = 0;
    }

    printf("输出\n");
    for (i = 1; i <= n; ++i)
        printf("%d ", dis[i]);
    return 0;
}
```

- 结果

```c
5 7
1 2 2
1 5 10
2 3 3
2 5 7
3 4 4 
4 5 5
5 3 6
输出
0 2 5 9 9
```



![13](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/13.png)



### 对比和分析

![14](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/img/%E6%9C%80%E7%9F%AD%E8%B7%AF%E5%BE%84/14.png)
