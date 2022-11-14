### 启动方式

将 main、MatGraph、set、sort 这4个cpp文件放到同一个目录，点击main.cpp运行



### 展示

#### 图1的数据

![1.png (345×170) (lhhhs233.cn)](https://php.lhhhs233.cn/img/数据结构/图/并查集实现Kruskal/1.png)



```c
6 9
1 3 11
2 4 13
3 5 3
4 5 4
1 2 6
3 4 7
0 1 1
2 3 9
0 2 2
```

- 结果

![1.png (345×170) (lhhhs233.cn)](https://php.lhhhs233.cn/img/数据结构/图/并查集实现Kruskal/1的生成树.png)

```c
输入:
6 9
1 3 11
2 4 13
3 5 3
4 5 4
1 2 6
3 4 7
0 1 1
2 3 9
0 2 2
图g的存储结构:
   0   1   2 INF INF INF
   1   0   6  11 INF INF
   2   6   0   9  13 INF
 INF  11   9   0   7   3
 INF INF  13   7   0   4
 INF INF INF   3   4   0
  边(1,0), 权值为1
  边(2,0), 权值为2
  边(5,3), 权值为3
  边(5,4), 权值为4
  边(3,2), 权值为9
最小生成树的权值是19
```





#### 图2的数据

![1.png (345×170) (lhhhs233.cn)](https://php.lhhhs233.cn/img/数据结构/图/并查集实现Kruskal/2.png)



```c
5 8
0 1 1
0 2 3
0 3 4
0 4 7
1 2 2
2 3 5
2 4 8
3 4 6
```

- 结果

![1.png (345×170) (lhhhs233.cn)](https://php.lhhhs233.cn/img/数据结构/图/并查集实现Kruskal/2的生成树.png)



```c
输入:
5 8
0 1 1
0 2 3
0 3 4
0 4 7
1 2 2
2 3 5
2 4 8
3 4 6
图g的存储结构:
   0   1   3   4   7
   1   0   2 INF INF
   3   2   0   5   8
   4 INF   5   0   6
   7 INF   8   6   0
  边(1,0), 权值为1
  边(2,1), 权值为2
  边(3,0), 权值为4
  边(4,3), 权值为6
最小生成树的权值是13
```





#### 图3的数据

![1.png (345×170) (lhhhs233.cn)](https://php.lhhhs233.cn/img/数据结构/图/并查集实现Kruskal/3.png)

```c
9 15
0 1 10
0 5 11
1 2 18
1 6 16
1 8 12
2 8 8
2 3 22
3 4 20
3 6 24
3 7 16
3 8 21
4 7 7
4 5 26
5 6 17
6 7 19
```

- 结果

![1.png (345×170) (lhhhs233.cn)](https://php.lhhhs233.cn/img/数据结构/图/并查集实现Kruskal/3的最小生成树.png)



```c
输入:
9 15
0 1 10
0 5 11
1 2 18
1 6 16
1 8 12
2 8 8
2 3 22
3 4 20
3 6 24
3 7 16
3 8 21 
4 7 7
4 5 26
5 6 17
6 7 19 
图g的存储结构:
   0  10 INF INF INF  11 INF INF INF
  10   0  18 INF INF INF  16 INF  12
 INF  18   0  22 INF INF INF INF   8
 INF INF  22   0  20 INF  24  16  21
 INF INF INF  20   0  26 INF   7 INF
  11 INF INF INF  26   0  17 INF INF
 INF  16 INF  24 INF  17   0  19 INF
 INF INF INF  16   7 INF  19   0 INF
 INF  12   8  21 INF INF INF INF   0
  边(7,4), 权值为7
  边(8,2), 权值为8
  边(1,0), 权值为10
  边(5,0), 权值为11
  边(8,1), 权值为12
  边(6,1), 权值为16
  边(7,3), 权值为16
  边(7,6), 权值为19
最小生成树的权值是99
```

