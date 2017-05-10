#include <stdio.h>
#include <windows.h>


#define INVALID_VALUE INFINITE // winbase.h  无效值

typedef int ElemType;

typedef struct _NODE{
	ElemType Data;
	struct _NODE* pNext;
}NODE,*PNODE;

// 单链表线性表 基本操作12 个 (扩展操作10个) 
// 严蔚敏课本2.3 节 有头节点的单链表

/* 操作结果：构造一个空的线性表L */

bool InitList(PNODE &pHead);

/* 初始条件：线性表L已存在。操作结果：销毁线性表L */
bool DestroyList(PNODE &pHead);

/* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
bool ClearList(PNODE pHead);

/* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
bool ListEmpty(PNODE pHead);

/* 初始条件：线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(PNODE pHead);

/* L为带头结点的单链表的头指针。当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
bool GetElem(PNODE pHead,int iPosition, ElemType &e);

/* 初始条件: 线性表L已存在,compare()是数据元素判定函数(满足为1,否则为0) */
/* 操作结果: 返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在,则返回值为0 */
int LocateElem(PNODE pHead,ElemType e,bool (*CompareFunc)(ElemType,ElemType));

/* 初始条件: 线性表L已存在 */
/* 操作结果: 若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱, */
/*           返回OK;否则操作失败,pre_e无定义,返回INFEASIBLE(不可实行的) */
// 我有话说：严蔚敏真他妈奇怪 LocateElem 还有个比较函数指针的参数，这里怎么就木有了
//						憋不住 我自己加上了CompareFunc 参数  我有强迫症
bool PriorElem(PNODE pHead,ElemType cur_e,ElemType& pre_e,bool (*CompareFunc)(ElemType,ElemType));

/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           返回OK;否则操作失败，next_e无定义，返回INFEASIBLE */
bool NextElem(PNODE pHead,ElemType cur_e,ElemType& next_e,bool(*CompareFunc)(ElemType,ElemType));

/* 在带头结点的单链线性表L中第i个位置之前插入元素e */
bool ListInsert(PNODE pHead,int iPosition,ElemType e);



/* 在带头结点的单链线性表L中，删除第i个元素,并由e返回其值 */
bool ListDelete(PNODE pHead,int iPosition,ElemType &e);
// 假定条件 pNodeDel 是链表中的结点
bool ListDelete(PNODE pHead,PNODE pNodeDel);

/* 初始条件：线性表L已存在 */
/* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
bool ListTraverse(PNODE pHead,void (*VisitFunc)(ElemType));


//////////////////////////////////////////////////////////////////////////
bool AppendHead(PNODE pHead,ElemType e);
bool AppendTail(PNODE pHead,ElemType e);
//////////////////////////////////////////////////////////////////////////
// 合并链表
bool ListMerge(PNODE &pHead_a,PNODE &pHead_b,PNODE &pHead_c);

bool ListMerge_Recursion(PNODE &pHead_a,PNODE &pHead_b,PNODE &pHead_c) ;// 递归的方法 合并链表

//////////////////////////////////////////////////////////////////////////
// 链表倒置
bool ListReverse(PNODE pHead); // 链表的倒置

//////////////////////////////////////////////////////////////////////////
// 使用冒泡循环排序链表  为 ListMerge 函数做准备
bool ListBubbleSort(PNODE pHead,bool(*CompareFunc)(ElemType,ElemType));

//////////////////////////////////////////////////////////////////////////
// 输出链表倒数第几个结点 返回的是结点的指针
PNODE GetReverseElem(PNODE pHead,int iPosition, ElemType &e);

//////////////////////////////////////////////////////////////////////////

// 校验是否在链表中
bool IsInList(PNODE pHead,PNODE pNodeCheck); 
bool IsInList(PNODE pHead,ElemType e , bool (*CompareFunc)(ElemType,ElemType));
//////////////////////////////////////////////////////////////////////////
bool Compare(ElemType a,ElemType b)
{
	return (a==b);
}

void Visit(ElemType e)
{
	if(e == INVALID_VALUE)
		printf("无效数据 ");
	else 
	printf("%d ",e);
}

int main()
{

		PNODE pHead;
	int i =0;
	ElemType e = INVALID_VALUE , e0 = INVALID_VALUE;
	printf("初始化链表\n");
	InitList(pHead);
	printf("链表空不空 (空1)(不空0):%d\n",ListEmpty(pHead));
	printf("向链表插入五个数据\n");
	for (i=1;i<6;++i)
	{
		ListInsert(pHead,i,i);
	}
	printf("链表长度：%d,输出链表",ListLength(pHead));
	ListTraverse(pHead,Visit);
	printf("链表空不空 (空1)(不空0):%d\n",ListEmpty(pHead));
	printf("ClearList,输出:");
	ClearList(pHead);
	ListTraverse(pHead,Visit);
	printf("链表空不空 (空1)(不空0):%d\n",ListEmpty(pHead));

	for (i=1;i<11;++i)
	{
		ListInsert(pHead,i,i);
	}

	printf("插入10个数之后,长度%d:",ListLength(pHead));
	ListTraverse(pHead,Visit);

	GetElem(pHead,5,e);
	printf("得到第5个元素：%d\n",e);

	for (i=1;i<3;++i)
	{
		GetElem(pHead,i,e0);
		if(PriorElem(pHead,e0,e,Compare))
			printf("%d元素的前驱%d\n",e0,e);
	}

	for (i=ListLength(pHead)-1;i<=ListLength(pHead);++i)
	{
		GetElem(pHead,i,e0);
		if(NextElem(pHead,e0,e,Compare))
			printf("%d元素的后继%d\n",e0,e);
	}

	int k = ListLength(pHead);

	for (i = k+1;i>=k;i--)
	{
		if(ListDelete(pHead,i,e))
			printf("删除元素%d\n",e);
	}

	printf("最后一次输出链表,长度%d,",ListLength(pHead));
	ListTraverse(pHead,Visit);

	PNODE pHead_b,pHead_c;
	InitList(pHead_b);
	InitList(pHead_c);

	for (i=10;i<13;++i)
	{
		ListInsert(pHead_b,i-9,i);
	}

	printf("B链表:");
	ListTraverse(pHead_b,Visit);

	printf("合并:\n");
	ListMerge(pHead,pHead_b,pHead_c);

	ListTraverse(pHead_c,Visit);

	DestroyList(pHead_b);
	DestroyList(pHead_c);
	printf("销毁链表\n");
	DestroyList(pHead);


	printf("***************ListTraverse**********************************\n");

	InitList(pHead);
	
	for (i=0;i<5;++i)
	{
		ListInsert(pHead,i,i);
	}

	ListReverse(pHead);
	printf("打印链表\n");
	ListTraverse(pHead,Visit);
	DestroyList(pHead);



	printf("*************ListMerge_Recursion*********************************\n");
	InitList(pHead);
	InitList(pHead_b);
	InitList(pHead_c);
	ListInsert(pHead,1,1);
	ListInsert(pHead,2,3);
	ListInsert(pHead,3,5);
	ListInsert(pHead_b,1,2);
	ListInsert(pHead_b,2,4);
	ListInsert(pHead_b,3,6);

	printf("ListA:");
	ListTraverse(pHead,Visit);
	printf("ListB:");
	ListTraverse(pHead_b,Visit);

	ListMerge_Recursion(pHead->pNext,pHead_b->pNext,pHead_c->pNext);
	printf("ListC:");
	ListTraverse(pHead_c,Visit);
	DestroyList(pHead);
	DestroyList(pHead_b);
	DestroyList(pHead_c);

	

/*
// Test GetReverseElem
	PNODE pHead;
	InitList(pHead);
	AppendHead(pHead,23);
	AppendTail(pHead,34);
	AppendTail(pHead,45);
	AppendTail(pHead,56);
	ElemType e;
	GetReverseElem(pHead,5,e);
	Visit(e);
	DestroyList(pHead);
	*/
	return 0;
}


bool IsInList(PNODE pHead,PNODE pNodeCheck)
{
	if(pHead == NULL || pHead->pNext == NULL || pNodeCheck== NULL)
		return false;

	while (pHead->pNext!= NULL && pHead->pNext != pNodeCheck)
	{
		pHead = pHead->pNext;
	}
	return (pHead->pNext != NULL);
} 
bool IsInList(PNODE pHead,ElemType e , bool (*CompareFunc)(ElemType,ElemType))
{
	if(pHead == NULL || pHead->pNext == NULL)
		return false;
	pHead = pHead->pNext;
	while (pHead != NULL && !CompareFunc(e,pHead->Data))
	{
		pHead = pHead->pNext;
	}
	return (pHead != NULL);
}

bool ListDelete(PNODE pHead,PNODE pNodeDel)
{
	if(pHead == NULL || pHead->pNext == NULL || pNodeDel == NULL)
		return false;
	if(pNodeDel->pNext != NULL)
	{
		pNodeDel->Data = pNodeDel->pNext->Data; // 转移删除结点  现在删除pNodeDel->pNext
		PNODE pNodeFree = pNodeDel->pNext;
		pNodeDel->pNext = pNodeFree->pNext;
		free(pNodeFree);
	}
	else
	{
		while (pHead->pNext != pNodeDel)
		{
			pHead = pHead->pNext;
		}
		pHead->pNext = NULL;
		
		free(pNodeDel);
	}
	return true;
}

// 使用递归 头结点不能为空 所以传参的时候  需要注意
bool ListMerge_Recursion(PNODE &pHead_a,PNODE &pHead_b,PNODE &pHead_c)
{
	if (pHead_a == NULL)
	{
		pHead_c = pHead_b;
		pHead_b = NULL;
		return true;
	}

	if (pHead_b == NULL)
	{
		pHead_c = pHead_a;
		pHead_a = NULL;
		return true;
	}

	
	if (pHead_a->Data <= pHead_b->Data)
	{
		pHead_c = pHead_a;
		PNODE pNodeTemp = pHead_a->pNext;
		pHead_a = NULL;
		ListMerge_Recursion(pNodeTemp,pHead_b,pHead_c->pNext);
		
	}

	else
	{
			pHead_c = pHead_b;
			PNODE pNodeTemp = pHead_b->pNext;
			pHead_b = NULL;
			ListMerge_Recursion(pHead_a,pNodeTemp,pHead_c->pNext);
	}
	return true;
}

bool ListBubbleSort(PNODE pHead,bool(*CompareFunc)(ElemType,ElemType))
{
	PNODE p1 = NULL;
	PNODE p2 =NULL;
	ElemType DataTemp = {0};
	
	
	for (p1=pHead;p1!=NULL;p1=p1->pNext)
	{
		for (p2= p1->pNext;p2!=NULL;p2= p2->pNext)
		{
			if (CompareFunc(p1->Data,p2->Data)) //从小到大排列 
			{
				DataTemp = p1->Data;
				p1->Data  =  p2->Data;
				p2->Data = DataTemp;
			}
			
		}
		}
	return true;
}


bool ListReverse(PNODE pHead)
{
	if(pHead == NULL)
		return false;

	PNODE pNodePre = NULL;
	PNODE pNodeTemp = pHead->pNext;
	pHead->pNext = NULL;

	while (pNodeTemp != NULL)  // 使用两个指针  一个结点一个结点的拆解 然后使用头插法链接到 原链表
	{
		pNodePre = pNodeTemp;
		pNodeTemp = pNodeTemp->pNext;
		
		// 链接 
		pNodePre->pNext = pHead->pNext;
		pHead->pNext  = pNodePre;
	}

	return true;
}

bool ListMerge(PNODE &pHead_a,PNODE &pHead_b,PNODE &pHead_c)
{
	if(pHead_a == NULL || pHead_b == NULL)
		return false;
	PNODE pNodeTemp = pHead_c;
	PNODE pNodeTemp_a = pHead_a->pNext;
	PNODE pNodeTemp_b = pHead_b->pNext;
	pHead_b->pNext = NULL;
	pHead_a->pNext = NULL;
	while (pNodeTemp_a != NULL &&
		pNodeTemp_b != NULL)
	{
		if(pNodeTemp_a->Data <= pNodeTemp_b->Data)
		{
			pNodeTemp->pNext = pNodeTemp_a;
			pNodeTemp = pNodeTemp->pNext;
			pNodeTemp_a = pNodeTemp_a->pNext;
		}	
		else
		{
			pNodeTemp->pNext = pNodeTemp_b;
			pNodeTemp = pNodeTemp->pNext;
			pNodeTemp_b = pNodeTemp_b->pNext;
		}
	}
	pNodeTemp->pNext = (pNodeTemp_a != NULL)?pNodeTemp_a:pNodeTemp_b;

	return true;
}

/* 初始条件：线性表L已存在 */
/* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
bool ListTraverse(PNODE pHead,void (*VisitFunc)(ElemType))
{
	if(pHead == NULL || VisitFunc== NULL)
		return false;

	pHead = pHead->pNext;
	while (pHead != NULL)
	{
		VisitFunc(pHead->Data);
		pHead = pHead->pNext;
	}

	printf("\n");

	return true;
}

 /* 在带头结点的单链线性表L中，删除第i个元素,并由e返回其值 */
bool ListDelete(PNODE pHead,int iPosition,ElemType &e)
{
	if(pHead == NULL || iPosition>ListLength(pHead))
	{
		e = INVALID_VALUE;
		return false;
	}
	int i =1;

	PNODE pNodePre = pHead;

	while (pNodePre != NULL && i<iPosition)
	{
		i++;
		pNodePre = pNodePre->pNext;
	}

	e = pNodePre->pNext->Data;

	PNODE pNodeFree = pNodePre->pNext;

	pNodePre->pNext = pNodeFree->pNext;

	free(pNodeFree);

	return true;
}

/* 在带头结点的单链线性表L中第i个位置之前插入元素e */
bool ListInsert(PNODE pHead,int iPosition,ElemType e)
{
	if(pHead == NULL || iPosition-1>ListLength(pHead)|| iPosition<=0)
		return false;
	int i =1;
	
	PNODE pNodePre = pHead;

	while (pNodePre != NULL && i<iPosition)
	{
		pNodePre = pNodePre->pNext;
		i++;
	}

	PNODE pNodeNew = static_cast<PNODE>(malloc(sizeof(NODE)));
	if(pNodeNew == NULL)
		return false;
	pNodeNew->Data = e;

	pNodeNew->pNext = pNodePre->pNext;
	pNodePre->pNext = pNodeNew;

	return true;
}

/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           返回OK;否则操作失败，next_e无定义，返回INFEASIBLE */
bool NextElem(PNODE pHead,ElemType cur_e,ElemType& next_e,bool(*CompareFunc)(ElemType,ElemType))
{
	if(pHead == NULL || CompareFunc == NULL)
	{
		next_e = INVALID_VALUE;
		return false;
	}
		
	PNODE pNodePre= pHead;

	while (pNodePre->pNext != NULL)
	{
		if(CompareFunc(cur_e,pNodePre->Data))
		{
			next_e = pNodePre->pNext->Data;
			return true;
		}
		pNodePre = pNodePre->pNext;
	}

	next_e =INVALID_VALUE;
	return false;
}

/* 初始条件: 线性表L已存在 */
/* 操作结果: 若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱, */
/*           返回OK;否则操作失败,pre_e无定义,返回INFEASIBLE(不可实行的) */
// 我有话说：严蔚敏真他妈奇怪 LocateElem 还有个比较函数指针的参数，这里怎么就木有了
//						憋不住 我自己加上了CompareFunc 参数  我有强迫症
bool PriorElem(PNODE pHead,ElemType cur_e,ElemType& pre_e,bool (*CompareFunc)(ElemType,ElemType))
{
	if(pHead == NULL || CompareFunc== NULL)
	{
		pre_e = INVALID_VALUE;
		return false;
	}
	
	PNODE pNodePre = pHead;

	while (pNodePre->pNext !=NULL)
	{
		if(CompareFunc(cur_e,pNodePre->pNext->Data))
		{
			pre_e = pNodePre->Data;
			return true;
		}
		pNodePre= pNodePre->pNext;
	}

	pre_e = INVALID_VALUE;
	return false;
}

/* 初始条件: 线性表L已存在,compare()是数据元素判定函数(满足为1,否则为0) */
/* 操作结果: 返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在,则返回值为0 */
int LocateElem(PNODE pHead,ElemType e,bool (*CompareFunc)(ElemType,ElemType))
{
	if(pHead == NULL || CompareFunc == NULL)
		return -1;
	int iIndex = 0;
	PNODE pNodeTemp = pHead->pNext;
	while (pNodeTemp != NULL)
	{
		iIndex++;
		if(CompareFunc(e,pNodeTemp->Data))
			return iIndex;
		pNodeTemp = pNodeTemp->pNext;
	}

	return 0;
}

/* L为带头结点的单链表的头指针。当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
bool GetElem(PNODE pHead,int iPosition, ElemType &e)
{
	if(pHead == NULL || iPosition>ListLength(pHead)) // 这里跟严蔚敏代码有所不同
	{
		e = INVALID_VALUE;
		return false;
	}
	int i =1;
	PNODE pNodeTemp = pHead->pNext;

	while (pNodeTemp!= NULL && i<iPosition)
	{
		pNodeTemp = pNodeTemp->pNext;
		i++;
	}

	if(pNodeTemp == NULL || i>iPosition)
	{
		e = INVALID_VALUE;
		return false;
	}
	e = pNodeTemp->Data;
	return true;
}

/* 初始条件：线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(PNODE pHead)
{
	if(pHead == NULL)
		return -1;
	int nLen =0;
	PNODE pNodeTemp = pHead->pNext;
	while (pNodeTemp != NULL)
	{
		pNodeTemp = pNodeTemp->pNext;
		nLen++;
	}

	return nLen;
}

/* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
bool ListEmpty(PNODE pHead)
{
	if(pHead == NULL)
		return false;

	return (pHead->pNext == NULL);
}

/* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
bool ClearList(PNODE pHead)
{
	if(pHead == NULL)
	{
		return false;
	}
	
	PNODE pNodeTemp = NULL;
	PNODE pNodePre = pHead->pNext;
	while (pNodePre != NULL)
	{
		pNodeTemp = pNodePre->pNext;
		free(pNodePre);
		pNodePre = pNodeTemp;
	}

	pHead->pNext = NULL;
	return true;
}

/* 初始条件：线性表L已存在。操作结果：销毁线性表L */
bool DestroyList(PNODE &pHead)
{
	if(pHead == NULL)
	{
		return false;	
	}

	PNODE pNodeTemp = NULL;
	
	while(pHead != NULL)
	{
		pNodeTemp = pHead;
		pHead = pHead->pNext;
		free(pNodeTemp);
	}

	pHead =NULL;

	return true;

	// or

// 	while (pHead != NULL)
// 	{
// 		pNodeTemp = pHead->pNext;
// 
// 		free(pHead);
// 
// 		pHead = pNodeTemp;
// 	}
}

/* 操作结果：构造一个空的线性表L */
bool InitList(PNODE &pHead)
{
	pHead = static_cast<PNODE>(malloc(sizeof(NODE)));
	if(pHead == NULL)
	{
		return false;
	}

	memset(pHead,0,sizeof(NODE));

	return true;
}

bool AppendHead(PNODE pHead,ElemType e)
{
	if(pHead == NULL)
		return false;

	PNODE pNodeNew = reinterpret_cast<PNODE>(malloc(sizeof(NODE))); // reinterpret_cast 是类型强转

	if (pNodeNew == NULL)
		return false;
	pNodeNew->Data = e;

	pNodeNew->pNext = pHead->pNext;
	pHead->pNext = pNodeNew;
	return true;
}
bool AppendTail(PNODE pHead,ElemType e)
{
	if(pHead == NULL)
		return false;
	
	PNODE pNodeNew = static_cast<PNODE>(malloc(sizeof(NODE)));
	
	if (pNodeNew == NULL)
		return false;
	pNodeNew->Data = e;
	pNodeNew->pNext = NULL;

	// 找到链表的尾部
	PNODE pTail = pHead;

	while (pTail->pNext != NULL)
	{
		pTail = pTail->pNext;
	}
	pTail->pNext = pNodeNew;
	return true;
}


PNODE GetReverseElem(PNODE pHead,int iPosition, ElemType &e)
{
	if(pHead == NULL || iPosition<1 || iPosition>ListLength(pHead))
	{
		e = INVALID_VALUE;
		return false;
	}
	// 头结点 是个 空结点
	PNODE pFast = pHead->pNext; 
	PNODE pSlow = pHead->pNext;

	while ((iPosition-- )&& pFast !=NULL)
	{
		pFast = pFast->pNext;
	}

	while (pFast != NULL)
	{
		pFast = pFast->pNext;

		pSlow = pSlow->pNext;
	}

	e = pSlow->Data;
	return pSlow;
}

