/*
 * =======================================================================
 *       Filename:  AVLTree.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2012年06月15日 21时01分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  szqh97 (), szqh97@163.com
 *        Company:  szqh97
 * =======================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "AVLTree.h"

static int Height(Position p)
{
    if (NULL == p)
	return -1;
    else 
	return p->Height; 	//Height是迭代迭计算的
}

// LL(在根节点的左子树的左孩子节点插入) 右旋  
static Position SingleRotateWithLeft(Position p)
{
    Position Q = p->Left;
    p->Left = Q->Right;
    Q->Right = p;
    p->Height = max(Height(p->Left), Height(p->Right)) + 1;
    Q->Height = max(Height(Q->Left), p->Height) + 1;
    return Q;
}

// RR 左旋
static Position SingleRotateWithRight(Position p)
{
    Position q = p->Right;
    p->Right = q->Left;
    q->Left = q;
    p->Height = max(Height(p->Right), Height(p->Left)) + 1;
    q->Height = max(Height(q->Right), p->Height) + 1;
    return q;
}

// LR 左右旋转
static Position DoubleRotateWithLeft(Position p)
{
    p->Left = SingleRotateWithRight(p->Left);
    return SingleRotateWithLeft(p);
}

//RL 右左双旋转
static Position DoubleRotateWithRight(Position p)
{
    p->Right = SingleRotateWithLeft(p->Right);
    return SingleRotateWithRight(p);
}

//搜索并删除右子树中最小的节点
//D:要删除的节点；T:递归用的树，初始值为D的右子树
//此函数调用时，D必有左右两个儿子
static AVLTree DeleteRightMin(AVLTree D, AVLTree T)
{
    Position Temp;
    //最小节点必定是没有左儿子
    //但是此处没有考虑到左儿子为空的情况
    //此函数删除的是左子树上的右子树
    if (T->Left == NULL)
    {
	Temp = T;
	D->Val = T->Val;
	T = T->Right;
	free(Temp);
    }
    else
	T->Left = DeleteRightMin(D, T->Left);
    return T;
}

//对于单个机电进行AVL调整，用于Delete()函数，Delete2()不用
static AVLTree Rotate(AVLTree T)
{
    if (Height(T->Left) - Height(T->Right) == 2)
    {
	if (Height(T->Left->Left) >= Height(T->Left->Right))
	    T = SingleRotateWithLeft(T);
	else
	    T = DoubleRotateWithLeft(T);
    }
    if (Height(T->Right) - Height(T->Left) == 2)
    {
	if (Height(T->Right->Right) >= Height(T->Right->Left))
	    T = SingleRotateWithRight(T);
	else
	    T = DoubleRotateWithRight(T);
    }
    return T;
}

//把AVLTree清空
AVLTree MakeEmpty(AVLTree T)
{
    if (NULL != T)
    {
	MakeEmpty(T->Left);
	MakeEmpty(T->Right);
	free(T);
    }
    return NULL;
}

//有时间尝试用非递归实现
Position Find(ElementType X, AVLTree T)
{
    if (T == NULL) return NULL;
    if (X < T->Val)
	return Find(X, T->Left);
    else if (X > T->Val)
	return Find(X, T->Right);
    else
	return T;
}

Position FindMin(AVLTree T)
{
    if (NULL == T)
	return NULL;
    else if (T->Left == NULL)
	return T;
    else
	return FindMin(T->Left);
}

Position FindMax(AVLTree T)
{
    if (T == NULL)
	return NULL;
    else if (T->Right == NULL)
	return T;
    else return FindMax(T->Right);
}

AVLTree Insert(ElementType X, AVLTree T)
{
    if (NULL == T)
    {
	T = (AVLTree)malloc(sizeof(AVLTree));
	T->Left = T->Right = NULL;
	T->Height = 0;
	T->Val = X;
    }
    else if(X < T->Val)
    {
	T->Left = Insert(X, T->Left);
	if (Height(T->Left) - Height(T->Right) == 2)
	{
	    if(X < T->Left->Val)
		T = SingleRotateWithLeft(T);
	    else
		T = DoubleRotateWithLeft(T);
	}
    }
    else if(X > T->Val)
    {
	T->Right = Insert(X, T->Right);
	if(Height(T->Right) - Height(T->Left) == 2)
	{
	    if (X > T->Right->Val)
		T = SingleRotateWithRight(T);
	    else
		T = DoubleRotateWithRight(T);
	}
    }
    T->Height = max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

AVLTree Delete2(ElementType X, AVLTree T)
{
    Position Temp;
    if (T == NULL)
	return NULL;
    else if (X < T->Val)
    {
	T->Left = Delete2(X, T->Left);
	if (Height(T->Right) - Height(T->Left) == 2)
	{
	    if (Height(T->Right->Left) > Height(T->Right->Right))
		T = DoubleRotateWithRight(T);
	    else 
		T= SingleRotateWithRight(T);
	}
    }
    else if (X > T->Val)
    {
	T->Right = Delete2(X, T->Right);
	if (Height(T->Left) - Height(T->Right) == 2)
	{
	    if (Height(T->Left->Right) > Height(T->Left->Left))
		T = DoubleRotateWithLeft(T);
	    else 
		T = SingleRotateWithLeft(T);
	}
    }
    else if (T->Left && T->Right)
    {
	T->Right = DeleteRightMin(T, T->Right);
	if (Height(T->Left) - Height(T->Right) == 2)
	{
	    if (Height(T->Left->Right) > Height(T->Left->Left))
		T = DoubleRotateWithLeft(T);
	    else
		T = SingleRotateWithLeft(T);
	}
    }
    else
    {
	Temp = T;
	if (T->Left == NULL)
	    T = T->Right;
	else if (T->Right == NULL)
	    T = T->Left;
	free(Temp);
    }
}

ElementType GetAt(Position p)
{
    if (p == NULL )
	return -1;
    return p->Val;
}

//有时间把前序和后序遍历都用非递归实现
void InOrder(AVLTree T)
{
    if (T == NULL)
	return ;
    InOrder(T->Left);
    printf("%d(%d) ", T->Val, T->Height);
    InOrder(T->Right);
}
