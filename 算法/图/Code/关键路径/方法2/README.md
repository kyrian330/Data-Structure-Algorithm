​		先用 Bellman-Ford 求出最长路径和松弛过程中的信息，再根据信息推导出关键路径。bellman-ford算法时间复杂度是 O(n*e)，推导关键路径的时间复杂度是O(n)，总的来说不是一个高效的算法。因为这个做法是自创的，所以代码不够严谨和规范，也不太符合求工程中最优方案的思想，这里先挖个坑，要是以后有优化方案再更新。

```c
创建时间: 2022/11/18 17:21
```



- 图示

![50](https://github.com/kyrian330/Data-Structure-Algorithm/blob/main/%E7%AE%97%E6%B3%95/%E5%9B%BE/img/%E5%9B%BE%E8%BF%9B%E9%98%B6%E7%AE%97%E6%B3%95/50.png)





- 数据

```c
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
源点 1 由边 <0 1> 松弛成功, 路径长3
源点 2 由边 <0 2> 松弛成功, 路径长4
源点 3 由边 <1 3> 松弛成功, 路径长8
源点 4 由边 <1 4> 松弛成功, 路径长9
源点 3 由边 <2 3> 松弛成功, 路径长12
源点 5 由边 <2 5> 松弛成功, 路径长11
源点 4 由边 <3 4> 松弛成功, 路径长15
源点 6 由边 <4 6> 松弛成功, 路径长24
源点 7 由边 <4 7> 松弛成功, 路径长19
源点 9 由边 <6 9> 松弛成功, 路径长26
源点 8 由边 <7 8> 松弛成功, 路径长24
源点 9 由边 <8 9> 松弛成功, 路径长27
输出
0 3 4 12 15 11 24 19 24 27
关键路径：
<8 9> <7 8> <4 7> <3 4> <2 3> <0 2>
```

