#pragma once

#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <string.h>






#define MAX 100


typedef struct _QUEUEDATA_ 
{
	int a;
	int iIndex;
}QueueData,*pQueueData;

typedef struct _QUEUE_
{
	pQueueData pBase; 
	int iFront; 
	int iRear; 
 }Queue,*pQueue;



bool InitQueue(pQueue pQueueTemp);

bool DestroyQueue(pQueue pQueueTemp);
bool EnQueue(pQueue pQueueTemp,QueueData e);
bool DeQueue(pQueue pQueueTemp,pQueueData e);

bool QueueEmpty(pQueue pQueueTemp);


