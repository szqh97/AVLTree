/*
 * =======================================================================
 *       Filename:  AVLTreemain.cpp
 *    Description:  main.cpp
 *        Version:  1.0
 *        Created:  2012年06月16日 08时19分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  szqh97 (), szqh97@163.com
 *        Company:  szqh97
 * =======================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"

#define DELET2


int main ( int argc, char *argv[] )
{
    AVLTree Tree = NULL;
    Position Pos = NULL;
    
    Tree = Insert(5, Tree);
    Tree = Insert(2, Tree);
    Tree = Insert(8, Tree);
    Tree = Insert(1, Tree);
    Tree = Insert(3, Tree);
    Tree = Insert(6, Tree);
    Tree = Insert(4, Tree);
    InOrder(Tree);
    printf("/n");
#ifndef DELET2
    Tree = Delete(3,Tree);
#else
    Tree = Delete2(3, Tree);
#endif

    return 0;
}	/* ----------  end of function main  ---------- */


