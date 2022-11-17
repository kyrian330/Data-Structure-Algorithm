#include <stdio.h>
#include <malloc.h>
#include "MatGraph.cpp"
#include "AdjGraph.cpp"

int *etv, *ltv;
int *stack2;
int top2;

// 邻接矩阵 转换成 邻接表
void MatToAdj(MatGraph g, AdjGraph *&G) {
    int i, j;
    ArcNode *p;
    G = (AdjGraph *)malloc(sizeof(AdjGraph));
    G->n=g.n;  G->e=g.e;
    for (i=0; i<g.n; i++) {
        G->adjlist[i].in = 0;
        G->adjlist[i].data = i;
        G->adjlist[i].firstarc = NULL;
    }
    for (i=0; i<g.n; i++)
        for (j=0; j<=g.n; j++)
            if (g.edges[i][j]!=0 && g.edges[i][j]!=INF) {  // 有一条边
                p=(ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->weight = g.edges[i][j];
                p->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc = p;
                G->adjlist[j].in++;    // 该顶点的入度 +1
            }
}


// 拓扑排序
int TopologicalSort(AdjGraph* G) {
    ArcNode *p;
    int i, k, gettop;
    int top = 0;
    int count = 0;
    int *stack;
    stack=(int *)malloc(G->n * sizeof(int) );
    for(i = 0; i<G->n; i++)
        if(G->adjlist[i].in==0)
            stack[++top] = i;

    top2 = 0;
    etv = (int *)malloc(G->n * sizeof(int) ); // 事件最早发生时间数组
    for(i=0; i<G->n; i++)
        etv[i] = 0;    // 初始化
    stack2 = (int *)malloc(G->n * sizeof(int) );  // 初始化拓扑序列栈

    printf("拓扑序列:  ");
    while(top!=0) {
        gettop = stack[top--];
        printf("%d -> ",G->adjlist[gettop].data);   count++;

        stack2[++top2]=gettop;        // 将弹出的顶点序号压入拓扑序列的栈
        p = G->adjlist[gettop].firstarc;
        while(p) {
            k = p->adjvex;
            if( !(-- G->adjlist[k].in) )
                stack[++top] = k;

            if((etv[gettop] + p->weight) > etv[k])    // 求各顶点事件的最早发生时间 etv值
                etv[k] = etv[gettop] + p->weight;

            p = p->nextarc;
        }
    }
    printf("\n");
    if(count < G->n)
        return 1;
    else
        return 0;
}

// 求关键路径, G为有向网, 输出G的各项关键活动
void CriticalPath(AdjGraph* G) {
    ArcNode *p;
    int i, gettop, k, j;
    int ete, lte;  // 声明活动最早发生时间和最迟发生时间变量
    TopologicalSort(G);   // 求拓扑序列，计算数组etv和stack2的值
    ltv=(int *)malloc(G->n*sizeof(int));// 事件最早发生时间数组
    for(i=0; i<G->n; i++)
        ltv[i]=etv[G->n-1];    // 初始化

    printf("etv: \t");
    for(i=0; i<G->n; i++)
        printf("%d -> ",etv[i]);
    printf("\n");

    while(top2!=0) {    // 出栈是求ltv
        gettop=stack2[top2--];
        for(p = G->adjlist[gettop].firstarc; p; p = p->nextarc) {       // 求各顶点事件的最迟发生时间 ltv值
            k = p->adjvex;
            if(ltv[k] - p->weight < ltv[gettop])
                ltv[gettop] = ltv[k] - p->weight;
        }
    }

    printf("ltv: \t");
    for(i=0; i<G->n; i++)
        printf("%d -> ",ltv[i]);
    printf("\n");

    for(j=0; j<G->n; j++) {       // 求ete,lte和关键活动
        for(p = G->adjlist[j].firstarc; p; p = p->nextarc) {
            k = p->adjvex;
            ete = etv[j];        // 活动最早发生时间
            lte = ltv[k] - p->weight; // 活动最迟发生时间
            if(ete == lte)    // 两者相等即在关键路径上
                printf("<v%d - v%d> length: %d \n",G->adjlist[j].data, G->adjlist[k].data, p->weight);
        }
    }
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

    CriticalPath(G);
    DestroyMat(g);
    DestroyAdj(G);
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
