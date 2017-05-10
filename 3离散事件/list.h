#pragma once

#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include <assert.h>
using namespace std;

typedef struct tagEVENT
{
	int iOccurTime;
	int iType;
}EVENT,*PEVENT;

typedef struct tagLISTNODE
{
	EVENT eventData;
	tagLISTNODE *pNext;
}LISTNODE,*PLISTNODE;

class CList
{
private:
	PLISTNODE m_pHead;
	int m_nNodeCount;
public:
	CList();
	~CList();
	VOID InitList();
	VOID InsertList(EVENT eventTemp, int (*CompareTime)(EVENT , EVENT));
	EVENT DeleteFirst();
	BOOL IsEmpty() const;
};	
CList::CList()
{
	m_pHead = NULL;
	m_nNodeCount =0;
	//InitList();
}
// 将链表释放
CList::~CList()
{
	if(m_nNodeCount > 0)
		_tprintf(_T("链表完事不空哦\n"));

	PLISTNODE pNodeTemp = m_pHead;
	while (pNodeTemp != NULL)
	{
		m_pHead = m_pHead->pNext;
		delete pNodeTemp;
		pNodeTemp = m_pHead;
	}
	
}
// 初始化链表 构建一个空的链表头结点
VOID CList::InitList()
{

	// for safe 
	try
	{
		m_pHead = new LISTNODE;
	}
	catch(bad_alloc &)
	{
		delete m_pHead;
		m_pHead = NULL;
	}
	m_pHead->pNext = NULL;
	m_nNodeCount =0;
}
VOID CList::InsertList(EVENT eventTemp, int (*CompareTime)(EVENT , EVENT))
{
	PLISTNODE pNodePre = m_pHead;
	PLISTNODE pNodeTemp = pNodePre->pNext;
	//插入到  pNodePre  pNodeTemp 之间
	while (pNodeTemp != NULL && CompareTime(pNodeTemp->eventData , eventTemp) < 0)
	{
		pNodePre = pNodeTemp;
		pNodeTemp = pNodeTemp->pNext;
	}
	PLISTNODE pNodeNew = (PLISTNODE)malloc(sizeof(LISTNODE));
	assert(pNodeNew != NULL);
	pNodeNew->eventData = eventTemp;
	pNodeNew->pNext = pNodePre->pNext;
	pNodePre->pNext = pNodeNew;

	m_nNodeCount++;
}
// 删除第一个有效的结点
EVENT CList::DeleteFirst()
{
	EVENT eventTemp = {-1 ,-1};
	if(m_pHead->pNext != NULL)
	{
		PLISTNODE pNodeTemp = m_pHead->pNext;
		eventTemp = pNodeTemp->eventData;
		m_pHead->pNext = pNodeTemp->pNext;
		delete pNodeTemp;
		m_nNodeCount--;
	}
	return eventTemp;
}
BOOL CList::IsEmpty() const
{
	return ((m_pHead->pNext == NULL) && (m_nNodeCount == 0));
}