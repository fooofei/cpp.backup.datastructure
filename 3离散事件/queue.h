#pragma once
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <assert.h>
using namespace std;


typedef struct tagQUEUELEMENT
{
	int iArrivalTime;//客户到达时间
	int iDuration;//客户停留 办理业务的时间
}QUEUELEMENT,*PQUEUELEMENT;

typedef struct tagQUEUENODE
{
	QUEUELEMENT queueData;
	tagQUEUENODE * pNext;
}QUEUENODE,*PQUEUENODE;

class CQueue
{
private:
	PQUEUENODE m_pHead;
	int m_nNodeCount;
public:
	CQueue();
	~CQueue();
	VOID InitQueue(VOID);
	VOID EnQueue(QUEUELEMENT queueElement);
	QUEUELEMENT DeQueue(VOID);
	int GetQueueLength(VOID) const ;
	BOOL IsEmpty(VOID) const ;
	QUEUELEMENT GetHeadElement(VOID);
};

CQueue::CQueue()
{
	m_pHead = NULL;
	m_nNodeCount =0;
	//InitQueue();
}
CQueue::~CQueue()
{
	if(m_nNodeCount > 0)
		_tprintf(_T("队列完事不空哦\n"));

	PQUEUENODE pNodeTemp = m_pHead;

	while (pNodeTemp != NULL)
	{
		m_pHead = m_pHead->pNext;
		delete pNodeTemp;
		pNodeTemp = m_pHead;
	}
	m_nNodeCount =0;
}
VOID CQueue::InitQueue(VOID)
{
	try
	{
		m_pHead = new QUEUENODE;
	}
	catch(bad_alloc&)
	{
		delete m_pHead;
		m_pHead = NULL;
	}
	m_pHead->pNext = NULL;
	m_nNodeCount =0;
}
VOID CQueue::EnQueue(QUEUELEMENT queueElement)
{
	PQUEUENODE pNodeNew = (PQUEUENODE)malloc(sizeof(QUEUENODE));
	assert( pNodeNew != NULL);
	pNodeNew->queueData  = queueElement;
	pNodeNew->pNext = NULL;

	PQUEUENODE pNodeTemp = m_pHead;
	//链接到尾部
	while (pNodeTemp->pNext != NULL)
		pNodeTemp = pNodeTemp->pNext;

	pNodeTemp->pNext = pNodeNew;
	m_nNodeCount ++;
}
QUEUELEMENT CQueue::DeQueue(VOID)
{
	QUEUELEMENT queueElement = { -1 , -1};
	if(m_nNodeCount > 0)
	{
		PQUEUENODE pNodeTemp = m_pHead->pNext;
		queueElement = pNodeTemp->queueData;
		m_pHead->pNext = pNodeTemp->pNext;
		delete pNodeTemp;
		m_nNodeCount--;
	}
	return queueElement;
}
int CQueue::GetQueueLength(VOID) const
{
	return m_nNodeCount;
}
BOOL CQueue::IsEmpty(VOID) const
{
	return ((m_pHead->pNext == NULL)&&( m_nNodeCount ==0));
}
QUEUELEMENT CQueue::GetHeadElement(VOID)
{
	QUEUELEMENT queueElement = {-1 , -1};
	if(!IsEmpty())
		queueElement =m_pHead->pNext->queueData;
	return queueElement;
}