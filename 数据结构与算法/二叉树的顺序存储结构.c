//
//  main.m
//  数据结构与算法
//
//  Created by Jianmei on 2017/11/14.
//  Copyright © 2017年 Jianmei. All rights reserved.
//

/*
#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100
#define MAX_TREE_SIZE 100

typedef int Status;
typedef int TElemType;
typedef TElemType SqBiTree[MAX_TREE_SIZE];

typedef struct
{
    int level,order; // 结点的层,本层序号(按满二叉树计算)
}Position;

TElemType Nil=0;

Status visit(TElemType c)
{
    printf("%d",c);
    return OK;
}

//构造空二叉树
Status InitBiTree(SqBiTree T)
{
    int i;
    for (i=0; i<MAX_TREE_SIZE; i++) {
        T[i]=0;
    }
    return OK;
}

// 按层序次序输入二叉树中结点的值(字符型或整型), 构造顺序存储的二叉树T
Status CreateBiTree(SqBiTree T)
{
    int i=0;
    printf("请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤%d:\n",MAX_TREE_SIZE);
    while(i<10)
    {
        T[i]=i+1;
        
        if(i!=0&&T[(i+1)/2-1]==0&&T[i]!=0)
        {
            printf("出现无双亲的非根结点%d\n",T[i]);
            exit(ERROR);
        }
        i++;
    }
    while(i<MAX_TREE_SIZE)
    {
        T[i]=0;
        i++;
    }
    
    return OK;
}

// 初始条件: 二叉树T存在。操作结果: 返回T的深度
int BiTreeDepth(SqBiTree T)
{
    int i,j=-1;
    for (i=MAX_TREE_SIZE-1; i>=0; i--) {
        if (T[i]!=Nil) {
            break;
        }
    }
    do {
        j++;
    } while (i>=powl(2, j));
    return j;
}
// 操作结果: 若T为空二叉树,则返回TRUE,否则FALSE
Status BiTreeEmpty(SqBiTree T)
{
    if (T[0]==Nil) {
        return TRUE;
    }
    else
        return FALSE;
}
// 初始条件: 二叉树T存在
// 操作结果:  当T不空,用e返回T的根,返回OK;否则返回ERROR,e无定义
Status Root(SqBiTree T,TElemType *e)
{
    if (BiTreeEmpty(T)) {
        return ERROR;
    }
    else
    {
        *e = T[0];
        return OK;
    }
    
}

// 初始条件: 二叉树T存在,e是T中某个结点(的位置)
// 操作结果: 返回处于位置e(层,本层序号)的结点的值
TElemType Value(SqBiTree T,Position e)
{
    return T[(int)powl(2,e.level-1)+e.order-2];
    
}

// 初始条件: 二叉树T存在,e是T中某个结点(的位置)
// 操作结果: 给处于位置e(层,本层序号)的结点赋新值value
Status Assign(SqBiTree T,Position e,TElemType value)
{
    int i = (int)powl(2, e.level-1)+e.order-2;
    if (value!=Nil && T[i/2]==Nil) {
        return ERROR;
    }
    else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil))
        return ERROR;
    T[i]=value;
    return OK;
}

// 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂
TElemType Parent(SqBiTree T,TElemType e)
{
    int i;
    if (T[0]==Nil) {
        return Nil;
    }
    for (i =1; i<=MAX_TREE_SIZE; i++) {
        if (T[i]==e) {
            return T[(i+1)/2-1];
        }
    }
    return Nil;
}
// 初始条件: 二叉树T存在,e是T中某个结点
// 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂
TElemType LeftChild(SqBiTree T,TElemType e)
{
    int i;
    if (T[0]==Nil) {
        return Nil;
    }
    for (i=1; i<MAX_TREE_SIZE; i++) {
        if (T[i] ==e) {
            return T[i*2+1];
        }
    }
    return Nil;
}
// 初始条件: 二叉树T存在,e是T中某个结点
// 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂
TElemType RightChild(SqBiTree T,TElemType e)
{
    int i;
    if(T[0]==Nil)
        return Nil;
    for(i=0;i<=MAX_TREE_SIZE-1;i++)
        if(T[i]==e)
            return T[i*2+2];
    return Nil;
}
// 初始条件: 二叉树T存在,e是T中某个结点
// 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂
TElemType LeftSibling(SqBiTree T,TElemType e)
{
    int i;
    if(T[0]==Nil)
        return Nil;
    for(i=1;i<=MAX_TREE_SIZE-1;i++)
        if(T[i]==e&&i%2==0)
            return T[i-1];
    return Nil;
}

// 初始条件: 二叉树T存在,e是T中某个结点
// 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂
TElemType RightSibling(SqBiTree T,TElemType e)
{
    int i;
    if(T[0]==Nil)
        return Nil;
    for(i=1;i<=MAX_TREE_SIZE-1;i++)
        if(T[i]==e&&i%2)
            return T[i+1];
    return Nil;
}

void PreTraverse(SqBiTree T,int e)
{
    visit(T[e]);
    if (T[2*e+1]!=Nil) {
        PreTraverse(T, 2*e+1);
    }
    if (T[2*e+2]!=Nil) {
        PreTraverse(T, 2*e+2);
    }
}
// 初始条件: 二叉树存在
// 操作结果: 先序遍历T。
Status PreOrderTraverse(SqBiTree T)
{
    if (!BiTreeEmpty(T)) {
        PreTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

void InTraverse(SqBiTree T,int e)
{
    if (T[2*e+1]!=Nil) {
        InTraverse(T, 2*e+1);
    }
    visit(T[e]);
    if (T[2*e+2]!=Nil) {
        InTraverse(T, 2*e+2);
    }
}
// 初始条件: 二叉树存在
// 操作结果: 中序遍历T。
Status InOrderTraverse(SqBiTree T)
{
    if (!BiTreeEmpty(T)) {
        InTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

void PostTraverse(SqBiTree T,int e)
{
    if (T[2*e+1]!=Nil) {
        PostTraverse(T, 2*e+1);
    }
    if (T[2*e+2]!=Nil) {
        PostTraverse(T, 2*e+2);
    }
    visit(T[e]);
}


// 初始条件: 二叉树T存在
// 操作结果: 后序遍历T。
Status PostOrderTraverse(SqBiTree T)
{
    if (!BiTreeEmpty(T)) {
        PostTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

// 层序遍历二叉树
void LevelOrderTraverse(SqBiTree T)
{
    int i=MAX_TREE_SIZE-1,j;
    while (T[i]==Nil) {
        i--;
    }
    for (j=0; j<=i; j++) {
        if (T[i]!=Nil) {
            visit(T[j]);
        }
    }
    printf("\n");
}
int main(int argc, const char * argv[]) {
    
    @autoreleasepool {
        // insert code here...
        
        Status i;
        Position p;
        TElemType e;
        SqBiTree T;
        InitBiTree(T);
        CreateBiTree(T);
        printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
        i=Root(T,&e);
        if(i)
            printf("二叉树的根为：%d\n",e);
        else
            printf("树空，无根\n");
        
        p.level=4;
        p.order=5;
        e=Value(T, p);
        printf("待修改结点的原值为%d请输入新值:50 ",e);
        e =4;
        //        Assign(T, p, e);
        //        Parent(T, e);
        //        printf("结点%d的双亲为%d,左右孩子分别为%d,%d",e,Parent(T,e),LeftChild(T, e),RightChild(T, e));
        printf("前序遍历二叉树:\n");
        PreOrderTraverse(T);
        printf("中序遍历二叉树:\n");
        InOrderTraverse(T);
        printf("后序遍历二叉树:\n");
        PostOrderTraverse(T);
        printf("层序遍历二叉树:\n");
        LevelOrderTraverse(T);
        
    }
    return 0;
}

*/
