#pragma  once 
#include <iostream>
using namespace std;



typedef char TElemType ;
TElemType Nil = '#' ;
typedef struct _BTNODE_
{
	TElemType Data;
	_BTNODE_* pLNext;
	_BTNODE_* pRNext;
	_BTNODE_* pParent;
}BTNode,*pBTNode;


typedef	struct _QUEUENODE_
{

	 pBTNode  Data;
	_QUEUENODE_* pNext;
}QueueNode,*pQueueNode;