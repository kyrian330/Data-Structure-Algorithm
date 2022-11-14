### 广搜——层层递进

#### 举例

##### 1.迷宫2.0

上一次我们通过深搜，让搜索者往右走，一直尝试直到走不通。下面我们通过广搜，”一层 一层“扩展来找到星队。



- 最开始搜索者在入口（1，1）处，他下一步可到达的点有（1，2），（2，1）。

![1](img\万能的搜索\1.png)



- 但是星队不在这两个点上，所以要继续探索。

![2](img\万能的搜索\2.png)

- 重复刚才的方法，直到找到星队为止。

![3](img\万能的搜索\3.png)



#### 思路

我们尝试用队列模拟这个过程，用一个结构体实现队列。

```c
struct node que[2501];    // 因为地图大小不超过 50 * 50, 因此队列拓展不超过 2500个
int head, tail;
int a[51][51];    // 存地图
int b[51][51];    // 标记哪些点已经在队列中


// 初始化队列, 将队列设置为空
head = 1;
tail = 1;


// 第一步将（1, 1）放入队列, 并标记（1, 1）已经走过
que[tail].x = 1;
que[tail].y = 1;
que[tail].s = 0;
tail ++;
b[1][1] = 1;
```

![5](img\万能的搜索\5.png)



- 然后从（1，1）开始，先尝试走到（1，2）

```c
// tx、ty表示下一步的坐标
tx = que[head].x;
ty = que[head].y + 1;
```



- 判断是否越界，再判断是否为障碍物或已在路径中

```c
if (tx < 1 || tx > n || ty < 1 || ty > m)
	continue;

if (a[tx][ty] == 0 && b[tx][ty] == 0) {
    ......
}
```



- 若满足上述条件，则将（1，2）入队，并标记该点已经走过。

```c
b[tx][ty] = 1;
que[tail].x = tx;
que[tail].y = ty;
que[tail].s = que[head].s + 1;    // 步数是父亲的步数 + 1
tail ++;
```



![6](img\万能的搜索\6.png)



- 观察地图发现，从（1，1）是可以到达（2，1）的，因此还需将（2，1）也加入队列，代码实现和观察对（1，2）的操作一样。

![7](img\万能的搜索\7.png)

- 对点（1，1）扩展完后，（1，1）对我们已经没用了，此时我们将（1，1）出队。（head ++）此时头节点指向（1，2），我们继续扩展。（3，1）入队。

![8](img\万能的搜索\8.png)

- （1，2）出队，继续搜索，直到找到星队。

![9](img\万能的搜索\9.png)





#### 完整代码

```c
#include <stdio.h>


/*
 * @描述: 广度优先搜索
 * @作者: 星队
 * @创建时间: 2022/10/11 11:16
 */

struct node {

    int x;    // 横坐标
    int y;    // 纵坐标
    int f;    // 父亲在队列中的编号, 本题不需要输出路径, 可以不需要 f
    int s;    // 步数
};


int main() {

    int m, n;
    struct node que[2501];    // 因为地图大小不超过 50 * 50, 因此队列拓展不超过 2500个
    int head, tail;
    int a[51][51];    // 存地图
    int b[51][51];    // 标记哪些点已经在队列中

    printf("请输入 n行, m列的迷宫(n <= 50, m <= 50)\n");
    scanf("%d %d", &n, &m);

    printf("请写入迷宫图\n");
    /**
        0 0 1 0 0
        0 0 0 0 1
        0 0 1 0 0
        0 1 0 0 1
        0 0 0 1 0
    **/
    for (int i = 1; i <=n ; ++i)    // 行和列都是从1开始索引
        for (int j = 1; j <= m ; ++j)
            scanf("%d", &a[i][j]);


    int start_x, start_y, p, q;
    printf("请输入起点和终点坐标\n");
    scanf("%d %d %d %d", &start_x, &start_y, &p, &q);

    // =============== 以上是数据准备 ========================



    int tx, ty;    // 下一个点的坐标

    // 方向数组
    int next [4][2] = {
            {0, 1},    // 向右走(列 + 1)
            {1, 0},    // 向下走(y + 1)
            {0, -1},    // 向左走(x - 1)
            {-1, 0}};    // 向上走(y - 1)


    // 初始化队列, 将队列设置为空
    head = 1;
    tail = 1;


    // 往队列插入迷宫入口坐标
    que[tail].x = start_x;
    que[tail].y = start_y;
    que[tail].f = 0;
    que[tail].s = 0;
    tail ++;
    b[start_x][start_y] = 1;


    bool flag = false;    // 用来标记是否到达终点

    while (head < tail) {    // 队列不空时循环

        // 枚举四个方向
        for (int k = 0; k <=3 ; ++k) {


            // 计算下一个点的坐标
            tx = que[head].x + next[k][0];
            ty = que[head].y + next[k][1];

            // 判断是否越界
            if (tx < 1 || tx > n || ty < 1 || ty > m)
                continue;

            // 判断该点是否可走
            if (a[tx][ty] == 0 && b[tx][ty] != 1) {

                b[tx][ty] = 1;

                // 插入新的点到队列中
                que[tail].x = tx;
                que[tail].y = ty;
                que[tail].f = head;    // 它的父亲是 head

                que[tail].s = que[head].s + 1;    // 步数是父亲的步数 + 1
                tail ++;
            }


            // 如果到达目标点, 则退出循环
            if (tx == p && ty == q) {
                flag = true;
                break;
            }
        }

        if (flag == true)
            break;

        head ++;    // 当一个点扩展完后, head ++才能让后面的点继续扩展
    }


    // 打印队列末尾最后一个点（目标点）的步数
    // 注意 tail是指向队列队尾（即最后一位）的下一个位置, 所以这里需要 -1。
    printf("%d", que[tail - 1].s);    // 队列循环完后, 输出。

    return 0;
}
```

- 输出

```c
请输入 n行, m列的迷宫(n <= 50, m <= 50)
5 5
请写入迷宫图
        0 0 1 0 0
        0 0 0 0 1
        0 0 1 0 0
        0 1 0 0 1
        0 0 0 1 0
请输入起点和终点坐标
1 1 4 4
6
```



#### 拓展例题

##### 1.宝岛探险

​		星队得到一张钓鱼岛航拍图，钓鱼岛由一个主岛和一些附属岛屿组成。如下，0表示海洋，1~9表示陆地的海拔，星队会降落在（6，8）处。请计算出降落地点的岛屿面积（即有多少格子）。

- 地图如下

1 	2 	1	 0	 0	 0	 0	 0	 2	 3
3	 0	 2	 0	 1	 2	 1	 0	 1	 2
4	 0	 1	 0	 1	 2	 3	 2	 0	 1
3	 2	 0	 0	 0	 1	 2	 4	 0	 0
0	 0	 0	 0	 0	 0	 1	 5	 3	 0
0	 1	 2	 1	 0	 1	 5	 **4**	 3	 0
0	 1	 2	 3	 1	 3	 6	 2	 1	 0
0	 0	 3	 4	 8	 9	 7	 5	 0	 0
0	 0	 0	 3	 7	 8	 6	 0	 1	 2
0	 0	 0	 0	 0	 0	 0	 0	 1	 0

​		读懂题目后，你会发现，其实就是从点（6，8）开始搜索，从四个方向尝试，当发现大于0的点就标记，最后就会得到岛屿的面积。



- 1.完整代码（广搜）

```c
#include <stdio.h>

#include<stdio.h>
struct node {
    int x;
    int y;
};

int main()
{
    int num = 0, head = 0, tail = 0;
    int map[11][11], book[11][11] = {0};
    int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}, tx, ty;
    struct node que[1001];
    printf("请输入地图\n");
    for(int i = 1; i <= 10; ++ i)
        for(int j = 1; j <= 10; ++ j)
            scanf("%d",&map[i][j]);
    book[6][8] = 1;
    que[tail].x = 6;
    que[tail].y = 8;
    num ++;
    tail ++;
    while(head < tail)
    {
        for(int i = 0;i < 4;i++)
        {
            tx = que[head].x + next[i][0];
            ty = que[head].y + next[i][1];
            if(tx < 0||tx >= 10||ty < 0||ty >= 10)
                continue;
            if(map[tx][ty] && book[tx][ty] == 0)
            {
                book[tx][ty] = 1;
                num ++;
                que[tail].x = tx;
                que[tail].y = ty;
                tail ++;
            }
        }
        head ++;
    }
    printf("岛屿面积是 %d", num);
    return 0;
}
```

- 结果

```c
请输入地图
1 2 1 0 0 0 0 0 2 3
3 0 2 0 1 2 1 0 1 2
4 0 1 0 1 2 3 2 0 1
3 2 0 0 0 1 2 4 0 0
0 0 0 0 0 0 1 5 3 0
0 1 2 1 0 1 5 4 3 0
0 1 2 3 1 3 6 2 1 0
0 0 3 4 8 9 7 5 0 0
0 0 0 3 7 8 6 0 1 2
0 0 0 0 0 0 0 0 1 0
岛屿面积是 38
```





- 2.完整代码（深搜）

```c
#include <stdio.h>
int book[11][11], map[11][11], sum = 0;
int next[4][2] = {{0, 1},{1, 0},{0, -1},{-1, 0}};

void dfs(int x, int y)
{
    if(x < 0 || x > 10 || y < 0 || y > 10)
        return ;
    if(book[x][y] == 1 || map[x][y] == 0)
        return ;
    sum ++;
    book[x][y] = 1;
    for(int i = 0; i < 4; ++ i)
        dfs(x + next[i][0],y + next[i][1]);
    return ;
}

int main()
{
    printf("请输入地图\n");
    for(int i = 1; i <= 10; ++ i)
        for(int j = 1; j <= 10; ++j)
            scanf("%d", &map[i][j]);
    dfs(6 , 8);
    printf("岛屿面积是 %d", sum);
}
```



- 3.着色法（以某个点为源点对其邻近的点进行着色），将降落的岛屿都改成 -1。

```c
#include <stdio.h>
int book[11][11], map[11][11], sum = 0;
int next[4][2] = {{0, 1},{1, 0},{0, -1},{-1, 0}};

// 在dfs基础上加个参数c就行
void dfs(int x, int y, int c)
{
    if(x < 0 || x > 10 || y < 0 || y > 10)
        return ;
    if(book[x][y] == 1 || map[x][y] == 0)
        return ;
    sum ++;
    book[x][y] = 1;
    map[x][y] = c;    // 染色
    for(int i = 0; i < 4; ++ i)
        dfs(x + next[i][0],y + next[i][1], c);
    return ;
}

int main()
{
    printf("请输入地图\n");
    for(int i = 1; i <= 10; ++ i)
        for(int j = 1; j <= 10; ++j)
            scanf("%d", &map[i][j]);
    dfs(6, 8, -1);
    printf("岛屿面积是 %d\n", sum);

    for(int i = 1; i <= 10; ++ i){
        for(int j = 1; j <= 10; ++ j)
            printf("%3d", map[i][j]);
        printf("\n");
    }
}
```

- 输出

```c
岛屿面积是 38
1  2  1  0  0  0  0  0  2  3
3  0  2  0 -1 -1 -1  0  1  2
4  0  1  0 -1 -1 -1 -1  0  1
3  2  0  0  0 -1 -1 -1  0  0
0  0  0  0  0  0 -1 -1 -1  0
0 -1 -1 -1  0 -1 -1 -1 -1  0
0 -1 -1 -1 -1 -1 -1 -1 -1  0
0  0 -1 -1 -1 -1 -1 -1  0  0
0  0  0 -1 -1 -1 -1  0  1  2
0  0  0  0  0  0  0  0  1  0
```



- 4.求一共有多少个独立的岛屿（对大于0的点着色即可）

```c
#include <stdio.h>
int book[11][11], map[11][11], sum = 0;
int next[4][2] = {{0, 1},{1, 0},{0, -1},{-1, 0}};


void dfs(int x, int y, int c)
{
    if(x < 0 || x > 10 || y < 0 || y > 10)
        return ;
    if(book[x][y] == 1 || map[x][y] == 0)
        return ;
    book[x][y] = 1;
    map[x][y] = c;
    for(int i = 0; i < 4; ++ i)
        dfs(x + next[i][0],y + next[i][1], c);
    return ;
}

int main()
{
    int num = 0;
    printf("请输入地图\n");
    for(int i = 1; i <= 10; ++ i)
        for(int j = 1; j <= 10; ++ j)
            scanf("%d", &map[i][j]);

    for(int i = 1; i <= 10; ++ i){
        for(int j = 1; j <= 10; ++ j)
        {
            if (map[i][j] > 0)    // 对大于0的点染色
            {
                num --;    // 小岛需要染的颜色的编号
                dfs(i, j, num);
            }
        }
    }

    for (int i = 1; i <= 10; ++ i) {
        for (int j = 1; j <= 10 ; ++ j)
            printf("%3d", map[i][j]);
        printf("\n");
    }
    
    printf("一共有 %d个小岛", -num);
}
```

- 输出

```
 -1 -1 -1  0  0  0  0  0 -2 -2
 -1  0 -1  0 -3 -3 -3  0 -2 -2
 -1  0 -1  0 -3 -3 -3 -3  0 -2
 -1 -1  0  0  0 -3 -3 -3  0  0
  0  0  0  0  0  0 -3 -3 -3  0
  0 -3 -3 -3  0 -3 -3 -3 -3  0
  0 -3 -3 -3 -3 -3 -3 -3 -3  0
  0  0 -3 -3 -3 -3 -3 -3  0  0
  0  0  0 -3 -3 -3 -3  0 -4 -4
  0  0  0  0  0  0  0  0 -4  0
  一共有 4个小岛
```



### 水管工游戏

​		一块矩形土地被分成 N行M列单元格，格子上有水管或者树木（如下图（2，4）处有一树木），请旋转管道，构成连通的系统，并输出连通路径。

![10](img\万能的搜索\10.png)



- 设0为树木，1~6表示管道的六种不同摆放方式。

![11](img\万能的搜索\11.png)



- 开始探索

![12](img\万能的搜索\12.png)



![13](img\万能的搜索\13.png)



- 统一规定

​		为了程序方便处理，将进水口在左边用1表示，进水口在上边用2表示，进水口在右边用3表示，进水口在下边用4表示。dfs()函数如下。

```c
void dfs(int x, int y, int front) {    // x,y表示行、列坐标, front表示进水口方向

    // 判断是否越界
    if (x < 1 || x > n || y < 1 || y > m)
        return;

    // 判断管道是否被使用过
    if (book[x][y] == 1)
        return;

    book[x][y] = 1;    // 标记

    // 如果当前是直的水管
    if (a[x][y] == 5 || a[x][y] == 6) {

        if (front == 1)    // 进水口在左边, 只能使用 5号管的摆法
            dfs(x, y + 1, 1);    // 若使用 5号, 则横坐标不变, 纵坐标加1, 所以下一个点为(x, y + 1)

        if (front == 2)    // 进水口在上边, 只能使用 6号管
            dfs(x + 1, y, 2);

        if (front == 3)
            dfs(x, y - 1, 3);
        
        if (front == 4)
            dfs(x - 1, y, 4);
    }
    
    book[x][y] = 0;    // 取消标记
    return;
}

// 上述代码是针对直管的情况, 对弯管的处理方法也是一样。
```



#### 完整代码

```c
#include <stdio.h>
int n, m, a[51][51], book[51][51];
bool flag = false;
// 定义栈, 拿来输出路径
struct node {
    // 横、纵坐标
    int x;
    int y;
}s[100];
int top = 0;

void dfs(int x, int y, int front) {    // x,y表示行、列坐标, front表示进水口方向

    // 一、判断是否到达终点(要放在判断越界之前)
    if (x == n && y == m + 1) {

        flag = true;    // 找到铺设方案
        for (int i = 1; i <= top; ++ i)
            printf("(%d, %d) ",s[i].x, s[i].y);
        return;
    }


    // 二、判断是否越界、管道
    if (x < 1 || x > n || y < 1 || y > m || book[x][y] == 1)
        return;


    book[x][y] = 1;    // 标记
    // 将当前尝试的坐标进栈
    top ++;
    s[top].x = x;
    s[top].y = y;



    // 三、处理直管
    if (a[x][y] == 5 || a[x][y] == 6) {

        if (front == 1)    // 进水口在左边, 只能使用 5号管的摆法
            dfs(x, y + 1, 1);    // 若使用 5号, 则横坐标不变, 纵坐标 + 1, 所以下一个点为(x, y + 1)

        if (front == 2)    // 进水口在上边, 只能使用 6号管
            dfs(x + 1, y, 2);

        if (front == 3)
            dfs(x, y - 1, 3);

        if (front == 4)
            dfs(x - 1, y, 4);
    }


    // 四、处理弯管
    if (a[x][y] >=1 && a[x][y] <= 4) {

        if (front == 1) {    // 进水口在左, 可用3、4管道
            // 3号状态, 左进下出, 下一个点纵坐标不变, 横坐标 + 1
            // 且3号管的出水口为下一个管道的进水口, 所以对下一个点的处理是 dfs(x + 1, y, 2)
            dfs(x + 1, y, 2);
            dfs(x - 1, y, 4);    // 4号状态
        }

        if (front == 2) {    // 上
            dfs(x, y + 1, 1);    // 1号状态
            dfs(x, y - 1, 3);    // 4号状态
        }

        if (front == 3) {    // 右
            dfs(x - 1, y, 4);    // 1号状态
            dfs(x + 1, y, 2);    // 2号状态
        }

        if (front == 4) {    // 下
            dfs(x, y + 1, 1);    // 2号状态
            dfs(x, y - 1, 3);    // 3号状态
        }
    }

    book[x][y] = 0;    // 取消标记
    top --;   // 尝试出栈
    return;
}


int main() {
    printf("输入行(<=50)、列(<=50)的值\n");
    scanf("%d %d", &n, &m);
    printf("输入管道图\n");
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);

    dfs(1,1,1);
    if (!flag)
        printf("没有可行的路径");

    return 0;
}
```

结果

```c
输入行(<=50)、列(<=50)的值
5 4
输入管道图
5 3 5 3
1 5 3 0
2 3 5 1
6 1 1 5
1 5 5 4
(1, 1) (1, 2) (2, 2) (3, 2) (3, 3) (3, 4) (4, 4) (5, 4)
```

