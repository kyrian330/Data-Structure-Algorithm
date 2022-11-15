/*
 * @描述: 图的邻接表
 */

#include <stdio.h>
#include <malloc.h>
#define MAXVEX 100
#define INF 32767


typedef struct edgenode {
    int adjvex;
    int weight;
    struct edgenode *nextarc;
} ArcNode;

typedef struct vexnode {
    int in;
    int data;
    ArcNode *firstarc;
} VHeadNode;

typedef struct {
    int n, e;
    VHeadNode adjlist[MAXVEX];
} AdjGraph;


// 输出图的邻接表
void DispAdj(AdjGraph *G) {
    ArcNode *p;
    int i;
    for (i=0; i<G->n; i++) {
        printf("  [%d]", i);
        p = G->adjlist[i].firstarc;
        if (p!=NULL)
            printf(" -> ");
        while (p!=NULL) {
            printf("%d",p->adjvex);
            p = p->nextarc;
            if (p!=NULL)  printf("->");
        }
        printf("\n");
    }
}


//求有向图G中顶点v的 入度
int Degree(AdjGraph *G, int v) {
    int i, d=0;
    ArcNode *p;
    if (v<0 || v>=G->n)
        return -1;
    for (i=0; i<G->n; i++) {	// 统计入度
        p = G->adjlist[i].firstarc;
        while (p!=NULL) {
            if (p->adjvex==v)
                d++;
            p=p->nextarc;
        }
    }
    return d;
}


// 销毁图
void DestroyAdj(AdjGraph *&G) {
    int i;
    ArcNode *pre, *p;
    for (i=0; i<G->n; i++) {
        pre = G->adjlist[i].firstarc;
        if (pre!=NULL) {
            p = pre->nextarc;
            while (p!=NULL) {
                free(pre);
                pre=p;  p=p->nextarc;
            }
            free(pre);
        }
    }
    free(G);
}