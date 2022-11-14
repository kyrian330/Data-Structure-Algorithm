/*
 * @描述: 并查集实现 Kruskal算法
 * @作者: 星队
 * @创建时间: 2022/11/13 21:36
 */

#include <stdio.h>
#include "MatGraph.cpp"
#include "sort.cpp"
#include "set.cpp"
#define MAXE 100

int weight=0;

void kruskal(MatGraph g) {
    int i, j, k;
    Edge E[MAXE];    // 建立存放所有边的数组E
    k = 0;
    for (i=0; i<g.n; i++) {   // 由图的邻接矩阵g产生的边集数组E
        for (j = 0; j <= i; j++) {
            if (g.edges[i][j] != 0 && g.edges[i][j] != INF) {
                E[k].u = i;  E[k].v = j;  E[k].w = g.edges[i][j];
                k++;     // 累计边数
            }
        }
    }
    SortEdge(E, k);   // 排序
//    for (i=0; i<g.e; i++)
//            printf("%d->%d（%d）",E[i].u, E[i].v, E[i].w);

    Init(g.n);  // 初始化 f数组。
    // 从小到大枚举边
    int count = 0;
    for (i=0; i<g.e; i++) {
        // 判断是否连通, 即判断是否在同一集合中
        if (merge(E[i].u, E[i].v)) {  // 如果没连通, 则选用边
            printf("  边(%d,%d), 权值为%d\n", E[i].u, E[i].v, E[i].w);
            ++ count;
            weight += E[i].w;
        }
        if (count == g.n - 1)
            break;
    }
}


int main() {

    MatGraph g;
    int n, e;
    int u, v, w;
    printf("输入:\n");
    scanf("%d %d", &n, &e);  // 读入顶点数, 边数

    InitGraph(g, n, e);   // 初始化图
    // 插入边
    for (int i=0; i<e; i++) {
        scanf("%d %d %d", &u, &v, &w);
        InsertEdge1(g, u, v, w);
    }
    printf("图g的存储结构:\n");  DispGraph(g);
    kruskal(g);
    printf("最小生成树的权值是%d ", weight);
    return 0;
}