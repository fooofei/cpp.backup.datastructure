#ifndef QUEUE_H
#define QUEUE_H 

#include <stdio.h>
#include <WINDOWS.H>

#define  QUEUESIZESTEP 3 // 队列长度每一步加和
#define  QUEUEDATA int  // 每次使用 需要更改的数据类型
class QUEUE
{
protected:

	int m_nBase;
	int m_nTop;
	int m_nQueueLen;
	int m_nQueueMAX;
	QUEUEDATA* m_pData;
public:

	BOOL InitQueue();
	BOOL EnQueue(QUEUEDATA Data);
	BOOL DeQueue(QUEUEDATA &Data);
	BOOL QueueIsEmpty();
	int GetQueueLen();
	BOOL DestroyQueue();
};

BOOL QUEUE::InitQueue()
{
	
	if (NULL==(m_pData = (QUEUEDATA*)malloc(sizeof(QUEUEDATA)*QUEUESIZESTEP)))
	{
		return FALSE;
	}

	memset(m_pData,0,sizeof(QUEUEDATA)*QUEUESIZESTEP);

	m_nTop = m_nBase = m_nQueueLen = 0;

	m_nQueueMAX = QUEUESIZESTEP;

	return TRUE;
}
BOOL QUEUE::EnQueue(QUEUEDATA Data)
{
	if (m_nTop==m_nQueueMAX-1)
	{
		
		if (NULL==(m_pData = (QUEUEDATA*)realloc(m_pData,sizeof(QUEUEDATA)*(m_nQueueMAX+QUEUESIZESTEP))))
		{
			return FALSE;
		}

		memset(&m_pData[m_nQueueMAX],0,sizeof(QUEUEDATA)*QUEUESIZESTEP);

		m_nQueueMAX += QUEUESIZESTEP;
	}

	m_pData[m_nTop++] = Data;

	++m_nQueueLen;

	return TRUE;
}
BOOL QUEUE::DeQueue(QUEUEDATA &Data)
{
	if (QueueIsEmpty())
	{
		Data = *(QUEUEDATA*)0;  // 这里可能需要更改  

		return FALSE;
	}

	Data = m_pData[m_nBase++];

	--m_nQueueLen;

	return TRUE;
}
BOOL QUEUE::QueueIsEmpty()
{
	if (m_nBase==m_nTop)
	{
		return TRUE;
	}

	return FALSE;
}
int QUEUE::GetQueueLen()
{
	return m_nQueueLen;
}
BOOL QUEUE::DestroyQueue()
{
	if (NULL==m_pData)
	{
		return FALSE;
	}

	free(m_pData);

	m_pData = NULL;

	m_nTop = m_nBase = m_nQueueMAX = 0 ;

	m_nQueueLen = -1;

	return TRUE;
}
#endif //QUEUE_H

