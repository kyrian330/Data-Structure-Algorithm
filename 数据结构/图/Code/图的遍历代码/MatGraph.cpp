/*
 * @描述: 图的邻接矩阵
 */

#include <stdio.h>
#define MAXVEX 100
#define INF 32767
typedef char VertexType[10];

typedef struct vertex {
    int adjvex;
    VertexType data;
} VType;

typedef struct graph {
    int n, e;
    VType vexs[MAXVEX];
    int edges[MAXVEX][MAXVEX];
} MatGraph;


// 建图
void CreateGraph(MatGraph &g, int A[][MAXVEX], int n, int e) {
    int i, j;
    g.n=n; g.e=e;
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            g.edges[i][j] = A[i][j];
}


// 初始化, 手动插入边的时候用
void InitGraph(MatGraph &g, int n, int e) {
    int i, j;
    g.n=n; g.e=e;
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            if (i==j) g.edges[i][j]=0;  // 对角线置0
            else g.edges[i][j] = INF;
}


// 输出图
void DispGraph(MatGraph g) {
    int i, j;
    for (i=0; i<g.n; i++) {
        for (j=0; j<g.n; j++)
            if (g.edges[i][j]<INF)
                printf("%4d", g.edges[i][j]);
            else
                printf("%4s", "INF");
        printf("\n");
    }
}


// 添加顶点
void AddaVex(MatGraph &g) {
    g.n++;
}


// 无向图插入边
int InsertEdge1(MatGraph &g, int u, int v, int w) {
    if (u<0 || u>=g.n || v<0 || v>=g.n)
        return 0;	// 顶点编号错误返回0
    g.edges[u][v] = w;
    g.edges[v][u] = w;
    g.e++;
    return 1;
}


// 有向图插入边
int InsertEdge2(MatGraph &g, int u, int v, int w) {
    if (u<0 || u>=g.n || v<0 || v>=g.n)
        return 0;	// 顶点编号错误返回0
    g.edges[u][v] = w;
    g.e++;
    return 1;
}


// 销毁图
void DestroyGraph(MatGraph g) {

}