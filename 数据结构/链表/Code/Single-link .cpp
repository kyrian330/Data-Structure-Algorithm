#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node {
    ElemType data;       // 数据域
    struct node *next;   // 指针域
} Node;                  // 单链表结点裂类型


// 初始化
void InitList(Node *& L) {
    L = (Node *)malloc(sizeof(Node));
    L->next = NULL;
}


// 尾插法建表
void Create(Node *& L, ElemType a[], int n) {
    Node *s, *r;
    int i;
    L = (Node *)malloc(sizeof(Node));
    r = L;
    for (i=0; i<n; i++) {
        s = (Node *)malloc(sizeof(Node));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next=NULL;
}


// 插入元素
int InsElem(Node *& L, int i, ElemType x) {
    int j = 0;
    Node *p = L, *s;
    if (i<=0) return 0;
    while (p!=NULL && j<i-1) {
        j++;
        p = p->next;
    }
    if (p==NULL)
        return 0;
    else {
        s = (Node *)malloc(sizeof(Node));
        s->data = x;
        s->next = p->next;
        p->next = s;
        return 1;
    }
}


// 删除第 i 个元素
int DelElem(Node *&L, int i) {
    int j = 0;
    Node *p = L;
    if (i<=0) return 0;
    while (p!=NULL && j<i-1) {
        j++;
        p = p->next;
    }
    if (p==NULL)
        return 0;
    else {
        Node *q;
        q = p->next;
        if (q==NULL)
            return 0;
        else {
            p->next = q->next;
            free(q);
            return 1;
        }
    }
}


// 获取第 i 个元素
int GetElem(Node *L, int i) {
    int j = 0;
    Node *p = L;
    if (i<=0) return 0;
    while (p!=NULL && j<i) {
        j++;
        p = p->next;
    }
    if (p==NULL)
        return 0;
    else
        return p->data;
}


// 输出单链表
void DispList(Node *L) {
    Node *p = L->next;
    while (p!=NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


// 销毁表
void DestroyList(Node *& L) {
    Node *pre = L,*p = pre->next;
    while (p!=NULL) {
        free(pre);
        pre = p; p = p->next;
    }
    free(pre);
}

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