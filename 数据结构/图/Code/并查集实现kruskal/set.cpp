/*
 * @描述: 并查集, 路径压缩
 * @作者: 星队
 * @创建时间: 2022/11/13 20:46
 */

#include <stdio.h>
#define MAXV 100
int f[MAXV];

void Init(int n) {
    for(int i=0; i<n; i++)  f[i] = i;
}


int find(int x) {
    if (f[x] == x)
        return x;
    else {
        f[x] = find(f[x]);
        return find(f[x]);
    }
}


int merge(int i, int j) {
    if (find(i) != find(j)) {
        f[find(j)]=find(i);
        return 1;
    }
    return 0;
}