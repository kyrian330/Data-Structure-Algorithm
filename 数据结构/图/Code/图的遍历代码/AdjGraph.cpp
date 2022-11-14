/*
 * @描述: 图的邻接表
 */

#include <stdio.h>
#include <malloc.h>
#define MAXVEX 100
#define INF 32767

typedef char VertexType[10];
typedef struct edgenode {
    int adjvex;
    int weight;
    struct edgenode *nextarc;
} ArcNode;

typedef struct vexnode {
    VertexType data;
    ArcNode *firstarc;
} VHeadNode;

typedef struct {
    int n, e;
    VHeadNode adjlist[MAXVEX];
} AdjGraph;


// 建图
void CreateGraph(AdjGraph *&G, int A[][MAXVEX], int n, int e) {
    int i, j;
    ArcNode *p;
    G=(AdjGraph *)malloc(sizeof(AdjGraph));
    G->n=n; G->e=e;
    for (i=0; i<G->n; i++)
        G->adjlist[i].firstarc=NULL;
    for (i=0; i<G->n; i++)
        for (j=G->n-1; j>=0; j--)
            if (A[i][j]>0 && A[i][j]<INF) {
                p = (ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->weight = A[i][j];
                p->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc = p;
            }
}


// 输出图的邻接表
void DispGraph(AdjGraph *G) {
    ArcNode *p;
    int i;
    for (i=0; i<G->n; i++) {
        printf("  [%d]", i);
        p = G->adjlist[i].firstarc;
        if (p!=NULL)
            printf(" -> ");
        while (p!=NULL) {
            printf(" %d(%d)",p->adjvex, p->weight);
            p = p->nextarc;
        }
        printf("\n");
    }
}


// 销毁图
void DestroyGraph(AdjGraph *&G) {
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