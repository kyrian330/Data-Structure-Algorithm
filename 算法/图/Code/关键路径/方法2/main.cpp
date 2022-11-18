/*
 * @描述: 关键路径
 * @作者: 纵横
 * @创建时间: 2022/11/18 18:20
 */
 
#include <stdio.h>
#include "MatGraph.cpp"
int dis[100];

struct node {
    int adjvex;  // 顶点下标
    int u;
    int v;
    int w;
};
struct node node[12];    // 定义g.e-1个结构体（比边数少1）
int cnt=0;

void bellman(MatGraph g) {
    int i, j, k;
    bool check = false;
    for (i = 0; i < g.n ; ++i)
        dis[i] = -INF;
    dis[0] = 0;

    // Bellman-Ford
    for (k = 0; k < g.n-1 ; ++k) {
        for (i = 0; i < g.e ; ++i) {
            for(j = 0; j < g.e; ++j) {
                if (g.edges[i][j]!=INF && g.edges[i][j]!=0) {
                    if (dis[j] < dis[i] + g.edges[i][j]) {
                        dis[j] = dis[i] + g.edges[i][j];
                        printf("源点 %d 由边 <%d %d> 松弛成功, 路径长%d\n", j, i, j, dis[j]);
                        // 保存相关信息
                        node[cnt].adjvex = j;
                        node[cnt].u = i;
                        node[cnt].v = j;
                        node[cnt].w = dis[j];
                        cnt++;
                        check = true;
                    }
                }
            }
        }
        if (!check)
            break;  // dis数组不再更新, 则提前退出循环
    }
}


int main() {

    MatGraph g;
    int i;
    int n, e;
    int u, v, w;
    printf("输入:\n");
    scanf("%d %d", &n, &e);
    InitMat(g, n, e);    // 初始化
    // 插入边
    for (int i=0; i<e; i++) {
        scanf("%d %d %d", &u, &v, &w);
        InsertEdge(g, u, v, w);
    }
    printf("输出:\n");
    printf("图G的邻接矩阵:\n");  DispMat(g);

    bellman(g);
    printf("输出\n");
    for (i = 0; i < g.n; ++i)
        printf("%d ", dis[i]);

    // 求关键路径
    int adjvex,w1;
    adjvex = node[11].adjvex;   // 先保存最后一条信息, 再往前推导
    w1 = node[11].w;

    printf("\n关键路径：\n");
    printf("<%d %d> ", node[11].u, node[11].v);
    for (i=10; i>0; i--) {    // 只能从后往前取
        // printf("%d %d %d\n", node[i].adjvex, node[i].u, node[i].v, node[i].w);
        if (node[i].adjvex < adjvex && node[i].w < w1) {
            printf("<%d %d> ", node[i].u, node[i].v);
            // 更新信息
            adjvex = node[i].adjvex;
            w1 = node[i].w;
        }
    }
    return 0;
}


/*
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
*/