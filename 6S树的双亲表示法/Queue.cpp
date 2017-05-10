#include "Queue.h"




bool InitQueue(pQueue pQueueTemp)
{
	pQueueTemp->pBase =(QueueData*)malloc(MAX*sizeof(QueueData));

	if (pQueueTemp->pBase==NULL)
	{
		return false;
	}

	else
	{
		pQueueTemp->iFront = pQueueTemp->iRear = 0;


		return true;
	}

 
}


bool DestroyQueue(pQueue pQueueTemp)
{ 
	if(pQueueTemp->pBase)
	{
		free(pQueueTemp->pBase);
	}

	pQueueTemp->pBase = NULL;
	
	pQueueTemp->iFront = pQueueTemp->iRear = 0;
	
	return true;
 }



bool EnQueue(pQueue pQueueTemp,QueueData e)
{ 
	if(pQueueTemp->iRear>=MAX)
	{ 
		pQueueTemp->pBase=(QueueData*)realloc(pQueueTemp->pBase,
			(pQueueTemp->iRear+1)*sizeof(QueueData));
		if(!pQueueTemp->pBase)
		{
			return false;
		}
	}
	*(pQueueTemp->pBase+pQueueTemp->iRear)= e;

	pQueueTemp->iRear++;
	
	return true;
 }


bool DeQueue(pQueue pQueueTemp,QueueData* e)
{ 
	if(pQueueTemp->iFront==pQueueTemp->iRear)
	{
		return false;
	}

	*e = pQueueTemp->pBase[pQueueTemp->iFront];

	pQueueTemp->iFront = pQueueTemp->iFront+1;
	
	return true;
 }


bool QueueEmpty(pQueue pQueueTemp)
{
	if (pQueueTemp->iFront==pQueueTemp->iRear)
	{
		return true;
	}

	return false;
}