/*
 * @描述: 图的遍历实现
 * @作者: 星队
 * @创建时间: 2022/11/11 18:20
 */
#include <stdio.h>
#include "AdjGraph.cpp"
#include "MatGraph.cpp"
int book[MAXVEX];


// 对邻接表深搜
void DFS1(AdjGraph *G,int v) {
    int w; ArcNode *p;
    printf("%d ",v);
    book[v] = 1;
    p=G->adjlist[v].firstarc;
    while (p!=NULL)	{
        w = p->adjvex;
        if (book[w]==0)
            DFS1(G,w);
        p = p->nextarc;
    }
}


// 对邻接矩阵深搜
void DFS2(MatGraph g, int v) {

    printf("%d ", v);    // 输出被访问顶点的 编号
    book[v] = 1;
    for(int i=0; i<g.n; i++)
        if(g.edges[v][i]!=0 && g.edges[v][i]!=INF && book[i] == 0)   // 找v顶点未被访问过的相邻点i
            DFS2(g, i);
}



// 对邻接表广搜
void BFS1(AdjGraph *G, int v)	{
    int i, w, book[MAXVEX];
    int Qu[MAXVEX], front=0, rear=0;
    ArcNode *p;
    for (i=0; i<G->n; i++) book[i] = 0;
    printf("%d ",v);
    book[v] = 1;
    rear = (rear+1) % MAXVEX;
    // rear = (rear=1)%MAXVEX;
    Qu[rear] = v;

    while (front!=rear)	{
        front = (front+1) % MAXVEX;
        w = Qu[front];
        p = G->adjlist[w].firstarc;
        while (p!=NULL)	{
            if (book[p->adjvex]==0)	{
                printf("%d ",p->adjvex);
                book[p->adjvex] = 1;
                rear = (rear+1)%MAXVEX;
                Qu[rear] = p->adjvex;
            }

            p = p->nextarc;
        }
    }
}


// 对邻接矩阵广搜
void BFS2(MatGraph g, int v) {

    int i, w;
    int book[MAXVEX], Qu[MAXVEX];
    int front = 0, rear = 0;
    for(i = 0; i < g.n; i ++)  book[i] = 0;
    printf("%d ", v);
    book[v] = 1;
    // 将初始顶点 进队
    rear = (rear+1)%MAXVEX;
    Qu[rear] = v;
    while(front != rear) {
        front = (front + 1) % MAXVEX;
        w = Qu[front];
        for(i=0; i<g.n; i++) {
            if(g.edges[w][i]!=0 && g.edges[w][i]!=INF && book[i] == 0) {
                // 以下三步, 访问、标记、进队
                printf("%d ", i);
                book[i] = 1;
                rear = (rear+1)%MAXVEX;
                Qu[rear] = i;
            }
        }
    }
}


// 初始化标记数组
void init(int n) {
    for(int i=0; i<n; i++)  book[i] = 0;
}


int main()
{
    AdjGraph* G;    // 新建图的邻接表 G
    MatGraph g;     // 新建图的邻接表 g
    int n = 5, e = 7;
    int A[MAXVEX][MAXVEX] ={{0, 1, 0, 1, 0},
                            {1, 0, 1, 0, 0},
                            {0, 1, 0, 1, 1},
                            {1, 0, 1, 0, 1},
                            {0, 0, 1, 1, 0},
    };

    CreateGraph(G, A, n, e);
    printf("图的邻接表 :\n");  DispGraph(G);
    printf("\n");
    CreateGraph(g, A, n, e);
    printf("图的邻接矩阵 :\n");  DispGraph(g);

    init(n);
    printf("DFS1: ");  DFS1(G, 0);  printf("\n");
    printf("BFS1: ");  BFS1(G, 0);  printf("\n");

    init(n);
    printf("DFS2: ");  DFS2(g, 0);  printf("\n");
    printf("BFS2: ");  BFS2(g, 0);  printf("\n");
}