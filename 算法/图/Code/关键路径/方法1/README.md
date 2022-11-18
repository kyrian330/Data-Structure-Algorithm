根据拓扑序列找出关键路径的经典算法。

​		拓扑排序时间复杂度为 O(n+e)，初始化数组的时间复杂度为 O(n)，计算 ltv数组、以及最后一个双重循环的时间复杂度都为 O(n+e)，所有的常数系数可以忽略，算法最终的时间复杂度仍然是 O(n+e)。



- 图示


![50](C:\Users\TF\Desktop\离线版本\算法\图\img\图进阶算法\50.png)



- 数据


```
10 13
0 1 3
0 2 4
1 3 5
1 4 6
2 3 8
2 5 7
3 4 3
4 6 9
4 7 4
5 7 6
6 9 2
7 8 5
8 9 3
```



- 结果


```c
输入:
10 13
0 1 3
0 2 4
1 3 5
1 4 6
2 3 8
2 5 7
3 4 3
4 6 9
4 7 4
5 7 6
6 9 2
7 8 5
8 9 3
输出:
图G的邻接矩阵:
   0   3   4 INF INF INF INF INF INF INF
 INF   0 INF   5   6 INF INF INF INF INF
 INF INF   0   8 INF   7 INF INF INF INF
 INF INF INF   0   3 INF INF INF INF INF
 INF INF INF INF   0 INF   9   4 INF INF
 INF INF INF INF INF   0 INF   6 INF INF
 INF INF INF INF INF INF   0 INF INF   2
 INF INF INF INF INF INF INF   0   5 INF
 INF INF INF INF INF INF INF INF   0   3
 INF INF INF INF INF INF INF INF INF   0
图G的邻接表:
  [0] -> 2(4)->1(3)
  [1] -> 4(6)->3(5)
  [2] -> 5(7)->3(8)
  [3] -> 4(3)
  [4] -> 7(4)->6(9)
  [5] -> 7(6)
  [6] -> 9(2)
  [7] -> 8(5)
  [8] -> 9(3)
  [9]
拓扑序列:  0 -> 1 -> 2 -> 3 -> 4 -> 6 -> 5 -> 7 -> 8 -> 9 ->
etv:    0 -> 3 -> 4 -> 12 -> 15 -> 11 -> 24 -> 19 -> 24 -> 27 ->
ltv:    0 -> 7 -> 4 -> 12 -> 15 -> 13 -> 25 -> 19 -> 24 -> 27 ->
<v0 - v2> length: 4
<v2 - v3> length: 8
<v3 - v4> length: 3
<v4 - v7> length: 4
<v7 - v8> length: 5
<v8 - v9> length: 3
```