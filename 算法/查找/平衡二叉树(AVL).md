### 平衡二叉树(AVL树)



​		**平衡二叉树，是一种二叉排序树，而且是一种高度平衡的二叉树，其中每个结点的左子树和右子树的高度差不能超过1。**

- 为什么要有平衡二叉树？

​		二叉排序树(搜索树)一定程度上可以提高搜索效率，但是当原序列有序时，例如序列 A = {1，2，3，4，5，6}，构造二叉搜索树，如下图 。

![8](img\查找\8.png)



​		依据此序列构造的二叉搜索树为右斜树，同时二叉树退化成单链表，搜索效率降低为 O(n)。就像查找元素 6 需要查找 6 次。

![9](img\查找\9.png)

​		二叉搜索树的查找效率取决于树的高度，因此保持树的高度最小，即可保证树的查找效率。同样的序列 A，将其改为上图的方式存储，查找元素 6 时只需比较 3 次，查找效率提升一倍。

- 判断平衡二叉树

​		将二叉树上结点的左子树深度减去右子树深度的值称为**平衡因子BF**（Balance Factor），那么平衡二叉树上所有结点的平衡因子只可能是 **-1、0、1**，否则该二叉树就是不平衡的。





![10](img\查找\10.png)

​		平衡二叉树的前提首先是棵二叉排序树，而图二 左孩子 > 根；对于图3的58结点，该结点左子树高度为2，右子树为空，平衡因子 = 2，是不平衡的。

- 最小不平衡子树

​		距离插入结点最近的，且平衡因子的绝对值大于1的结点为根的子树，称为**最小不平衡子树**。如下图，当插入新结点67时，距离它最近的平衡因子绝对值超过1的结点是70（左子树高2，右子树高0），所以从70开始以下的子树为最小不平衡子树。

![11](img\查找\11.png)

#### 构建AVL树

​		将数组a[10] = {3，2，1，4，5，6，7，10，9，8}来构建一棵平衡二叉树。前两位 3、2可以正常构建，到了第三位 ”1“，发现根结点3的bf变成了2，此时整棵树变成了最小不平衡树，需要调整，如图一（结点左上角数字为平衡因子bf）。因为bf值为正，因此需要将树右旋（顺时针旋转），因此2变成了根结点，3成了2的右孩子，这样三个结点bf都为0，非常平衡。

![12](img\查找\12.png)



![13](img\查找\13.png)



​		增加结点4，bf没有超出范围，如图3。增加结点5时，结点3的bf为-2，bf为负值，将最下不平衡子树左旋，如图4，此时整棵树又平衡了。

​		继续，增加结点6，发现结点2的bf变成-2，所以对根左旋，注意此时3本来是4的左孩子，由于旋转后要满足二叉排序树的性质，因此3变成了结点2的右孩子，如图7。增加结点7，同样的左旋，如图8、9。

![14](img\查找\14.png)



​		增加结点10，结构无变化，如图10。增加结点9，此时结点7的bf为-2，理论上只需要旋转最小不平衡子树7、8、9即可，但如果左旋后结点9成了结点10的右孩子，不符合排序树性质，此时不能简单左旋，如图11。

![15](img\查找\15.png)

​		仔细观察图11，发现根本原因是结点7的bf是-2，而结点10的bf是1，它俩一正一负，符号不统一，而前面的几次旋转，最小不平衡子树的根结点与它的子结点符号都是相同的，这就是不能直接旋转的关键。于是我们先将结点9和结点10右旋，10就变成了9的右子树，这是7、9的bf统一了，这时再对以7为根的子树左旋，如图13。接着插入8，情况和刚才类似，6的bf是-2，而它的右孩子9的bf是1，图14，因此先以9为根，右旋得到图15，此时6、7bf同号，左旋6得到最后的平衡二叉树，图16。



![16](img\查找\16.png)

- 总结

​		构建过程中，一旦发现不平衡的情况，就马上处理，bf大于1就右旋，bf小于-1就左旋。插入结点后，若最小不平衡子树根的bf和子树根的bf异号时，先对结点旋转一次使得符号相同，再反向旋转一次才能完成平衡操作，如上例结点9、8插入时。



#### 拆解

- 定义树的结点

```c
typedef struct BiTNode {	// 结点结构
    int data;	// 结点数据
    int bf; // 结点的平衡因子 
    struct BiTNode *lchild, *rchild;	// 左右孩子指针
}BiTNode;
```



- 右旋操作

```c
// 对以p为根的二叉排序树作右旋处理，
// 处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点
void R_Rotate(BiTNode *& P) {
    BiTNode *L;
    L = P->lchild; // L指向P的左子树根结点
    P->lchild = L->rchild; // L的右子树挂接为P的左子树
    L->rchild = P;
    P = L; // P指向新的根结点
}
```

​		R_Rotate函数意思是，当传入一棵二叉排序树P，将它的左孩子结点定义为L，将L的右子树变成P的左子树，再将P改成L的右子树，最后将L替换P成为根结点，这样就完成了一次右旋操作，如下图，三角形代表子树，N代表新结点。



![17](img\查找\17.png)



- 左旋操作

```c
// 对以P为根的二叉排序树作左旋处理，
// 处理之后P指向新的树根结点，即旋转处理之前的右子树的根结点0
void L_Rotate(BiTNode *& P) {
    BiTNode *R;
    R = P->rchild; // R指向P的右子树根结点
    P->rchild = R->lchild; // R的左子树挂接为P的右子树
    R->lchild = P;
    P = R; // P指向新的根结点
}
```

左旋函数和右旋是对称的，不再赘述。



- 左平衡旋转处理函数

```c
#define LH +1 // 左高 
#define EH 0  // 等高 
#define RH -1 // 右高 

// 对以指针T所指结点为根的二叉树作左平衡旋转处理 
// 本算法结束时，指针T指向新的根结点 
void LeftBalance(BiTNode *& T) {
    BiTNode *L, *Lr;
    L = T->lchild; // L指向T的左子树根结点
    switch(L->bf) {  // 检查T的左子树的平衡度，并作相应平衡处理 
        case LH: // 新结点插入在T的左孩子的左子树上，要作单右旋处理 
            T->bf = L->bf = EH;  // ①
            R_Rotate(T);
            break;
        case RH: // 新结点插入在T的左孩子的右子树上，要作双旋处理 
            Lr = L->rchild; // Lr指向T的左孩子的右子树根 
            switch(Lr->bf) {  // ②
               // 修改T及其左孩子的平衡因子 
                case LH: T->bf = RH;
                    L->bf = EH;
                    break;
                case EH: T->bf = L->bf = EH;
                    break;
                case RH: T->bf = EH;
                    L->bf = LH;
                    break;  // ③
            }
            Lr->bf = EH;
            L_Rotate(T->lchild); // 对T的左子树作左旋平衡处理
            R_Rotate(T); // 对T作右旋平衡处理
    }
}
```

1.将T的左孩子赋值给L。

2.当L的平衡因子为 LH，即为1时，说明它和根结点的BF值同号，因此，如上述注释的①，将它们的BF值都改成0，并且下一行进行右旋操作，操作方式如上面的图（8-7-9）所示。

3.当L的平衡因子为 RH，即为-1时，说明它和根结点的BF值**异号**，此时，需要做**双旋处理**。注释②~③，针对L右孩子Lr的BF作判断，修改根结点T和L的BF值，之后将当前Lr的BF改为0（Lr->bf = EH）。下一步，对根结点的左子树进行左旋，如下图8-7-10的第二张图；之后，对根结点右旋，如第三张图，完成平衡操作。



![18](img\查找\18.png)



​		同样的，右平衡旋转处理也非常类似，不再赘述。前面的**构建AVL树**例子中，新增结点9、8就是典型的右平衡旋转，并且双旋完成平衡的例子（**构建AVL树**中的图11、12；图14、15、16）



- 右平衡旋转处理函数

```c
void RightBalance(BiTNode *&T) {
    BiTNode *R, *Rl;
    R = T->rchild; // R指向T的右子树根结点
    switch(R->bf) {
        // 检查T的右子树的平衡度，并作相应平衡处理
        case RH:  // 新结点插入在T的右孩子的右子树上，要作单左旋处理
            T->bf = R->bf=EH;
            L_Rotate(T);
            break;
        case LH:  // 新结点插入在T的右孩子的左子树上，要作双旋处理
            Rl = R->lchild;  // Rl指向T的右孩子的左子树根
            switch(Rl->bf) {
                // 修改T及其右孩子的平衡因子
                case RH: T->bf = LH;
                    R->bf = EH;
                    break;
                case EH: T->bf = R->bf = EH;
                    break;
                case LH: T->bf = EH;
                    R->bf = RH;
                    break;
            }
            Rl->bf = EH;
            R_Rotate(T->rchild);  // 对T的右子树作右旋平衡处理
            L_Rotate(T);   // 对T作左旋平衡处理
    }
}
```



- 插入结点构建AVL树

```c
// 若在平衡的二叉排序树T中不存在和e有相同关键字的结点, 则插入一个
// 数据元素为e的新结点, 并返回1, 否则返回0。若因插入而使二叉排序树
// 失去平衡, 则作平衡旋转处理, 布尔变量taller反映T是否长高。
int InsertAVL(BiTNode *&T,int e,int *taller) {
    if(!T) {   // 空树, 插入当成根结点, 左右孩子先置空。
        // 插入新结点, 树“长高”, 置taller为1
        T=(BiTNode *)malloc(sizeof(BiTNode));
        T->data = e; T->lchild = T->rchild = NULL; T->bf = EH;
        *taller=1;
    }
    else {
        if (e == T->data) {
            // 树中已存在和e有相同关键字的结点则不再插入
            *taller = 0; return 0;
        }
        if (e < T->data) {
            // 应继续在T的左子树中进行搜索
            if(!InsertAVL(T->lchild,e,taller)) // 未插入
                return 0;
            if(*taller)   // 已插入到T的左子树中且左子树“长高”  ①
                switch(T->bf) {  // 检查T的平衡度
                    case LH: // 原本左子树比右子树高，需要作左平衡处理
                        LeftBalance(T);    *taller = 0;  break;
                    case EH: // 原本左、右子树等高, 现因左子树增高而使树增高
                        T->bf = LH; *taller = 1;  break;
                    case RH: // 原本右子树比左子树高，现左、右子树等高
                        T->bf = EH; *taller = 0;  break;  // ②
                }
        }
        else {
            // 应继续在T的右子树中进行搜索
            if(!InsertAVL(T->rchild,e,taller)) // 未插入
                return 0;
            if(*taller) // 已插入到T的右子树且右子树“长高”
                switch(T->bf) { // 检查T的平衡度
                    case LH: // 原本左子树比右子树高, 现左、右子树等高
                        T->bf = EH;  *taller = 0;  break;
                    case EH: // 原本左、右子树等高，现因右子树增高而使树增高
                        T->bf = RH; *taller = 1;  break;
                    case RH: // 原本右子树比左子树高，需要作右平衡处理
                        RightBalance(T); *taller = 0;  break;
                }
        }
    }
    return 1;
}
```

​		在注释①~②里，这时taller为1，说明插入了新结点，此时需要判断T的平衡因子，如果是1，说明左子树更高，需要调用LeftBalance函数进行左平衡旋转处理。如果是0或-1，则说明插入的新结点没有使整棵二叉排序树失去平衡性，只需要修改相关的BF值。在右子树的搜索同理。



- 输出树和序列

```c
// 中序遍历，输出有序序列
void middle_order(BiTNode *T) {
    if (T->lchild != NULL)
        middle_order(T->lchild);
    printf("%d ", T->data);
    if (T->rchild != NULL)
        middle_order(T->rchild);
}

// 输出树
void Display(BiTNode *bt) {
    if (bt!=NULL)
    {  printf("%d",bt->data);  // 输出根结点
        if (bt->lchild!=NULL || bt->rchild!=NULL) {
            printf("(");  // 根结点有左或右孩子时输出'('
            Display(bt->lchild);  // 递归输出左子树
            if (bt->rchild!=NULL) // 有右孩子时输出','
                printf(",");
            Display(bt->rchild);  // 递归输出右子树
            printf(")");  // 输出一个')'
        }
    }
}
```

------



​		讲完了，真是不容易，算法很长，也比较复杂，编程过程中容易在细节上出现错误，但是其思想不能理解。如果需要查找的集合本身无序，在频繁查找的过程需要经常插入和删除，显然需要构建一棵二叉排序树，但不平衡的二叉排序树，查找效率是非常低的，因此构建时，让这棵排序树时平衡二叉树，此时时间复杂度为O(logn)、插入删除也为O(logn)。显然是一种比较理想的动态查找表算法。



#### 完整代码

```c
#include <stdio.h>
#include <stdlib.h>

// 结点结构
typedef struct BiTNode {
    int data;	// 结点数据
    int bf;   // 结点的平衡因子
    struct BiTNode *lchild, *rchild;
}BiTNode;


// 右旋
void R_Rotate(BiTNode *& P) {
    BiTNode *L;
    L = P->lchild;
    P->lchild = L->rchild;
    L->rchild = P;
    P = L;
}


// 左旋
void L_Rotate(BiTNode *& P) {
    BiTNode *R;
    R = P->rchild;
    P->rchild = R->lchild;
    R->lchild = P;
    P = R;
}


#define LH +1 // 左高
#define EH 0  // 等高
#define RH -1 // 右高


// 左平衡旋转处理
void LeftBalance(BiTNode *& T) {
    BiTNode *L, *Lr;
    L = T->lchild;
    switch(L->bf) {
        case LH:
            T->bf = L->bf = EH;
            R_Rotate(T);
            break;
        case RH:
            Lr = L->rchild;
            switch(Lr->bf) {
                case LH: T->bf = RH;
                    L->bf = EH;
                    break;
                case EH: T->bf = L->bf = EH;
                    break;
                case RH: T->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(T->lchild);
            R_Rotate(T);
    }
}


// 右平衡旋转处理
void RightBalance(BiTNode *&T) {
    BiTNode *R, *Rl;
    R = T->rchild;
    switch(R->bf) {
        case RH:
            T->bf = R->bf=EH;
            L_Rotate(T);
            break;
        case LH:
            Rl = R->lchild;
            switch(Rl->bf) {
                case RH: T->bf = LH;
                    R->bf = EH;
                    break;
                case EH: T->bf = R->bf = EH;
                    break;
                case LH: T->bf = EH;
                    R->bf = RH;
                    break;
            }
            Rl->bf = EH;
            R_Rotate(T->rchild);
            L_Rotate(T);
    }
}


// 插入结点
int InsertAVL(BiTNode *&T,int e,int *taller) {
    if(!T) {
        T=(BiTNode *)malloc(sizeof(BiTNode));
        T->data = e; T->lchild = T->rchild = NULL; T->bf = EH;
        *taller=1;
    }
    else {
        if (e == T->data) {
            *taller = 0; return 0;
        }
        if (e < T->data) {
            if(!InsertAVL(T->lchild,e,taller))
                return 0;
            if(*taller)
                switch(T->bf) {
                    case LH:
                        LeftBalance(T);    *taller = 0;  break;
                    case EH:
                        T->bf = LH; *taller = 1;  break;
                    case RH:
                        T->bf = EH; *taller = 0;  break;
                }
        }
        else {
            if(!InsertAVL(T->rchild,e,taller))
                return 0;
            if(*taller)
                switch(T->bf) {
                    case LH:
                        T->bf = EH;  *taller = 0;  break;
                    case EH:
                        T->bf = RH; *taller = 1;  break;
                    case RH:
                        RightBalance(T); *taller = 0;  break;
                }
        }
    }
    return 1;
}


// 中序遍历
void middle_order(BiTNode *T) {
    if (T->lchild != NULL)
        middle_order(T->lchild);
    printf("%d ", T->data);
    if (T->rchild != NULL)
        middle_order(T->rchild);
}


// 输出树
void Display(BiTNode *bt) {
    if (bt!=NULL)
    {  printf("%d",bt->data);
        if (bt->lchild!=NULL || bt->rchild!=NULL) {
            printf("(");
            Display(bt->lchild);
            if (bt->rchild!=NULL)
                printf(",");
            Display(bt->rchild);
            printf(")");
        }
    }
}


int main(void)
{
    int i;
    int a[10]={3,2,1,4,5,6,7,10,9,8};
    BiTNode *T = NULL;
    int taller;
    for(i=0;i<10;i++)
        InsertAVL(T,a[i],&taller);

    middle_order(T);
    printf("\n");
    Display(T);
    return 0;
}
```

- 结果

```c
1 2 3 4 5 6 7 8 9 10
4(2(1,3),7(6(5),9(8,10)))
```

