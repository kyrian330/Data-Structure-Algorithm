/*
 * @描述: 单链表的实现
 * @作者: 星队
 * @创建时间: 2022/11/19 20:36
 */

#include <stdio.h>
#include <stdlib.h>
#include "SingleLink.cpp" 
#define MAXV 100

int main() {
    int i, n;
    int a[MAXV];
    Node *L;
    InitList(L);
    printf("输入链表结点个数：\n");
    scanf("%d", &n);
    printf("依次输入 %d 个数:\n", n);
    for (i=0; i<n; i++)
        scanf("%d", &a[i]);
    Create(L, a, n);
    printf("单链表L创建成功：\n");
    DispList(L);

    int index=3, data=23;
    printf("在 %d 位置插入数据 %d\n", index, data);
    InsElem(L, index, data);
    DispList(L);

    index = 2;
    printf("删除第 %d 个元素\n", index);
    DelElem(L, index);
    DispList(L);

    index = 5;
    printf("获取第 %d 个元素\n", index);
    printf("%d ", GetElem(L, index));
    return 0;
}