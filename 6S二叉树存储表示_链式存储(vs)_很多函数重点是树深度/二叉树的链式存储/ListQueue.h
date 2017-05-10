#pragma  once 
#include <iostream>
using namespace std;


#include "NodeType.h"

class ListQueue
{
public:


	pQueueNode pFront;
	pQueueNode pRear;
	int iLen;
	bool InitListQueue();
	bool DestroyListQueue();
	bool ListQueueIsEmpty();
	int ListQueueLength();
	bool EnListQueue(pBTNode e);
	bool DeListQueue(pBTNode &e);
	

};

bool ListQueue::InitListQueue()
{
	pFront = pRear = new QueueNode;
	if(pFront==NULL)
	{
		return false;

	}
	else
	{
		pRear->pNext = NULL;
		iLen = 0;
		return true ;
	}
	
}

bool ListQueue::DestroyListQueue()
{
	if (pFront==NULL)
	{
		return false;
	}
	pQueueNode pQueueNodeTemp = pFront;
	while(pFront!=NULL)
	{
		pFront = pFront->pNext;
		delete pQueueNodeTemp;
		pQueueNodeTemp = pFront;
	}

	pFront = pRear = NULL;

	iLen = -1;

	return true ;
}

bool ListQueue::ListQueueIsEmpty()
{
	if(pFront==pRear)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int ListQueue::ListQueueLength()
{
	return iLen;
}


bool ListQueue::EnListQueue(pBTNode e)
{
	pQueueNode pQueueNodeTemp = new QueueNode;

	if (pQueueNodeTemp == NULL)
	{
		return false;
	}
	else
	{
		pQueueNodeTemp->Data = e;

		pQueueNodeTemp->pNext = NULL;

		pRear->pNext = pQueueNodeTemp ;

		pRear = pQueueNodeTemp;

		return true;
	}

}

bool ListQueue::DeListQueue(pBTNode &e)
{
	if (ListQueueIsEmpty())
	{
		return false;  
	}
	else
	{

		e = pFront->pNext->Data;

		pFront = pFront ->pNext ;

		if (pFront->pNext==NULL)
		{
			pRear = pFront ;
		}

		return true;

	}
}


