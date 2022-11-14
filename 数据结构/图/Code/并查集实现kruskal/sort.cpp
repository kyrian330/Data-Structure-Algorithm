/*
 * @描述: 对图的邻接矩阵按权值进行排序
 * @作者: 星队
 * @创建时间: 2022/11/13 20:34
 */

#include <stdio.h>
typedef struct edge {
    int u;
    int v;
    int w;
} Edge;

void SortEdge(Edge E[], int e) {
    int i, j;
    Edge temp;
    for (i=1; i<e; i++) {
        temp = E[i];
        for (j=i-1; j>=0 && temp.w < E[j].w; j--)
            E[j+1] = E[j];
        E[j+1] = temp;
    }
}

