//////////////////////////////////////////////////////////////////////////
//ListLoop_no_head.h
// 没有头结点的 单向循环链表  
// 一般来说  环都是这样的  从头链接脚
//
// ********
// *			*
// ********
// 
// 但也有可能是这样的
// ************
// 	   *			*
// 		 ********
#include <stdio.h>
#include <windows.h>

typedef int ElemType;

// 链表结点 结构体
typedef struct tagNODE{
	ElemType Data;
	struct tagNODE* pNext;
}NODE,*PNODE;

// 没有头结点  就没有了 InitList
// 链表的基本函数  
bool AppendHead(PNODE &pHead,ElemType e);
bool AppendHead_NotLoop(PNODE &pHead,ElemType e);
bool DestroyList(PNODE &pHead);
bool ListTraverse(PNODE pHead);

// 给定一个单链表，只给出头指针h：
// 
// 1、如何判断是否存在环？
// 
// 2、如何知道环的长度？
// 
// 3、如何找出环的连接点在哪里？
// 
// 4、带环链表的长度是多少？
// 
// 
// 
// 解法：
// 
// 1、对于问题1，使用追赶的方法，设定两个指针slow、fast，从头指针开始，每次分别前进1步、2步。如存在环，则两者相遇；如不存在环，fast遇到NULL退出。
// 
// 2、对于问题2，记录下问题1的碰撞点p，slow、fast从该点开始，再次碰撞所走过的操作数就是环的长度s。
// 
// 3、问题3：有定理：碰撞点p到连接点的距离=头指针到连接点的距离，因此，分别从碰撞点、头指针开始走，相遇的那个点就是连接点。
// 
// 该定理的证明可参考：http://fayaa.com/tiku/view/7/
// 
// 4、问题3中已经求出连接点距离头指针的长度，加上问题2中求出的环的长度，二者之和就是带环单链表的长度

// 链表的考点函数
bool IsExitLoop(PNODE pHead) ;// 判断是否存在环  主要是算法需要记住

int LoopLength(PNODE pHead);

// 寻找环连接点（入口点）
PNODE FindLoopPort(PNODE pHead);

// 两个链表是否相交
bool IsCross(PNODE pHead_a,PNODE pHead_b);

int main()
{
	PNODE pHead = NULL;
	AppendHead_NotLoop(pHead,23);
	AppendHead_NotLoop(pHead,34);
	AppendHead_NotLoop(pHead,45);
	PNODE pHead_b = NULL;
	
	AppendHead_NotLoop(pHead_b,56);
	AppendHead_NotLoop(pHead_b,67);
	pHead_b->pNext->pNext = pHead->pNext;

	
	printf("是否存在相交%d\n",IsCross(pHead,pHead_b));
	return 0;
}

//
// 两个链表是否相交 (已验证)
//
bool IsCross(PNODE pHead_a,PNODE pHead_b)
{
	if(pHead_a == NULL || pHead_b == NULL)
		return false;
	// 要首先判断有没有环

	bool bLoop_a = IsExitLoop(pHead_a);
	bool bLoop_b = IsExitLoop(pHead_b);

	if(bLoop_a !=bLoop_b)
		return false; // 一个有环  一个无环

	if(!bLoop_a && !bLoop_b)// 都无环
	{
		// 找到两个链表的尾部
		PNODE pTail_a = pHead_a;
		while(pTail_a->pNext!=NULL)
			pTail_a = pTail_a->pNext;

		PNODE pTail_b = pHead_b;
		while(pTail_b->pNext != NULL)
			pTail_b = pTail_b->pNext;

		return (pTail_a==pTail_b);
	}
	else
	{
		// 找到环的  入口 
		PNODE pCirclePort_a = FindLoopPort(pHead_a);
		PNODE pCirclePore_b = FindLoopPort(pHead_b);

		PNODE pTemp = pCirclePort_a->pNext;

		while (pTemp != pCirclePort_a)
		{
			if(pTemp == pCirclePore_b)
				return true;
			pTemp = pTemp->pNext;
		}

		return false;
	}

	return false;
}

//
// 找到链表环的入口
//
PNODE FindLoopPort(PNODE pHead)
{
	if(pHead == NULL)
		return NULL;
		PNODE pSlow = pHead;
		PNODE pFast = pHead;
		
		while (pFast && pFast->pNext)
		{
			pSlow = pSlow->pNext;
			pFast = pFast->pNext->pNext;
			
			if(pSlow == pFast)
			{
				break;
			}
		}
		
		if(pFast == NULL || pFast->pNext == NULL)
			return NULL;
		
		pSlow = pHead;
		
		while (pSlow != pFast)
		{
			pSlow = pSlow->pNext;
			pFast = pFast->pNext;
		}
		
		return pSlow;
}
//
// 如果链表存在环 求环的长度
//
int LoopLength(PNODE pHead)
{
	if(pHead == NULL)
		return false;
	PNODE pSlow = pHead;
	PNODE pFast = pHead;
	PNODE pLoop = NULL;
	
	while (pFast && pFast->pNext)
	{
		pSlow = pSlow->pNext;
		pFast = pFast->pNext->pNext;
		
		if(pSlow == pFast)
		{
			pLoop = pSlow;
			break;
		}
	}

	pSlow = pLoop;
	pFast = pLoop;
	int iCount = 0;

	while(pFast && pFast->pNext)
	{
		pSlow = pSlow->pNext;
		pFast = pFast->pNext->pNext;

		++iCount;
		if (pSlow == pFast)
			break;
	
	}

	return iCount;
}

//
// 判断是否存在环  主要是算法需要记住
//
bool IsExitLoop(PNODE pHead) 
{
	if(pHead == NULL)
		return false;
	PNODE pSlow = pHead;
	PNODE pFast = pHead;
	
	while (pFast!= NULL && pFast->pNext !=NULL)
	{
		pSlow = pSlow->pNext;
		pFast = pFast->pNext->pNext;
		
		if(pSlow == pFast)
			break;
	}
	
	
	return !(pFast == NULL || pFast->pNext == NULL);
}


//
// 以下是 链表的基本函数 头插法(有环 无环)、销毁链表、打印链表
//

bool AppendHead(PNODE &pHead,ElemType e)
{
	PNODE pNodeNew = static_cast<PNODE>(malloc(sizeof(NODE)));
	if(pNodeNew == NULL)
		return false;

	pNodeNew->Data = e;
	if (pHead == NULL)
	{
		pHead = pNodeNew;
		pHead->pNext = pHead; // form loop
	}
	else
	{
		PNODE pTail = pHead;
		while (pTail->pNext != pHead)
		{
			pTail = pTail->pNext;
		}
		pNodeNew->pNext = pHead;
		pHead = pNodeNew;
    pTail ->pNext = pHead;
	}
	return true;
}


bool AppendHead_NotLoop(PNODE &pHead,ElemType e)
{
	PNODE pNodeNew = static_cast<PNODE>(malloc(sizeof(NODE)));
	if(pNodeNew == NULL)
		return false;
	
	pNodeNew->Data = e;
	if(pHead == NULL)
	{	
		pHead = pNodeNew;
		pHead->pNext = NULL;
	}
	else
	{
		pNodeNew->pNext = pHead;
		pHead = pNodeNew;
	}
	
	return true;
}
bool DestroyList(PNODE &pHead)
{
	if(pHead == NULL)
		return false;
	PNODE pHeadTemp = pHead->pNext;
	PNODE pNodeNext = NULL;
		while (pHeadTemp != pHead) // 没有到达表尾
		{
			pNodeNext = pHeadTemp->pNext;
			free(pHeadTemp);
			pHeadTemp = pNodeNext;
		}
		free(pHead); // 释放头结点
		pHead = NULL;
		
	return true;
}

bool ListTraverse(PNODE pHead)
{
	if(pHead == NULL)
		return false;
	printf("%d ",pHead->Data);
	
	PNODE pNodeNext = pHead->pNext;
	while (pNodeNext != pHead)
	{
		printf("%d ",pNodeNext->Data);
		pNodeNext = pNodeNext->pNext;
	}
	printf("\n");
	return true;
}