/*
 * @描述: 拓扑排序
 * @作者: 纵横
 * @创建时间: 2022/11/15 21:55
 */

#include <stdio.h>
#include <malloc.h>
#include "MatGraph.cpp"
#include "AdjGraph.cpp"

// 邻接矩阵 转换成 邻接表
void MatToAdj(MatGraph g, AdjGraph *&G) {
    int i, j;
    ArcNode *p;
    G = (AdjGraph *)malloc(sizeof(AdjGraph));
    for (i=0; i<g.n; i++) {
        G->adjlist[i].in = 0;   // 入度起始都是0
        G->adjlist[i].data = i;  // 顶点信息就设置为顶点下标
        G->adjlist[i].firstarc = NULL;
    }
    for (i=0; i<g.n; i++)  // 检查邻接矩阵中每个元素
        for (j=0; j<=g.n; j++)
            if (g.edges[i][j]!=0 && g.edges[i][j]!=INF) {  // 有一条边
                p=(ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->weight = g.edges[i][j];
                p->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc = p;
                G->adjlist[j].in++;    // 该顶点的入度 +1
            }
    G->n=g.n; G->e=g.e;
}


// 拓扑排序, 若GL无回路, 则输出拓扑排序序列并返回1, 若有回路返回0
int TopologicalSort(AdjGraph* G)
{
    ArcNode *p;
    int i, k, gettop;
    int top = 0;
    int count = 0;
    int *stack;
    stack = (int *)malloc(G->n * sizeof(int) );

    for(i = 0; i<G->n; i++)
        if(G->adjlist[i].in == 0)
            stack[++top]=i;
    while(top != 0) {
        gettop = stack[top];  --top; // 出栈
        printf("%d -> ",G->adjlist[gettop].data);  ++count;
        // 遍历该顶点的所有边结点
        p = G->adjlist[gettop].firstarc;
        while(p) {
            k = p->adjvex;
            if( !(-- G->adjlist[k].in) ) // 将i号顶点的邻接点的入度减1, 如果减1后为0, 则入栈
                stack[++top] = k;
            p = p->nextarc;
        }
    }
    printf("\n");
    if(count < G->n)
        return 0;
    else
        return 1;
}


int main()
{
    AdjGraph *G;
    MatGraph g;
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
    MatToAdj(g, G);
    printf("图G的邻接表:\n");  DispAdj(G);

    // 求度
    printf("图G中所有顶点的入度:\n");
    printf("  顶点\t度\n");
    for (int i=0; i<G->n; i++)
        printf("   %d\t%d\n",i,Degree(G,i));

    int result=TopologicalSort(G);
    printf("result:%d",result);
    DestroyMat(g);
    DestroyAdj(G);
}

/*
14 20
0 4 1
0 5 1
0 11 1
1 2 1
1 4 1
1 8 1
2 5 1
2 6 1
2 9 1
3 2 1
3 13 1
4 7 1
5 8 1
5 12 1
6 5 1
8 7 1
9 10 1
9 11 1
10 13 1
12 9 1
*/
