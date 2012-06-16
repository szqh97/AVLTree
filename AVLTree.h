/*
 * =======================================================================
 *       Filename:  AVLTree.h
 *    Description:  AVL树，用C语言实现
 *        Version:  1.0
 *        Created:  2012年06月15日 20时54分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  szqh97 (), szqh97@163.com
 *        Company:  szqh97
 * =======================================================================
 */
#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef int ElementType;
struct _AVLNode;
typedef struct _AVLNode AVLNode;
typedef AVLNode* Position;
typedef AVLNode* AVLTree;

///////////////////////////////////
struct _AVLNode
{
    ElementType Val;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

///////////////////////////////////

AVLTree MakeEmpty(AVLTree);
Position Find(ElementType, AVLTree);
Position FindMin(AVLTree);
Position FindMax(AVLTree);
AVLTree Insert(ElementType, AVLTree);
AVLTree Delete(ElementType, AVLTree);
AVLTree Delete2(ElementType, AVLTree);
ElementType GetAt(Position);
void InOrder(AVLTree);
inline int max(int x, int y){return x > y ? x : y;}


#endif
