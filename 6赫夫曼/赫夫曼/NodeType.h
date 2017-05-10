#pragma once 
#include <iostream>
using namespace std;

typedef int TElem ;

TElem Nil = 0;
typedef struct _BTNODE_
{
	_BTNODE_* pLNext;
	_BTNODE_* pRNext;
	TElem Data;
}BTNode,*pBTNode;

typedef struct _HUFFMANTREE_
{
	TElem Weight;

	TElem LNext;
	TElem RNext;
	TElem Parent;
}HuffManTree,*pHuffManTree;