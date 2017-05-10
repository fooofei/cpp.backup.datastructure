#include <stdio.h>
#include <windows.h>


// 有头空结点的 双向链表
typedef int ElemType;
#define  INVALID_VALUE -1

typedef struct tagNODE{

	ElemType Data;
	struct tagNODE* pPrior;
	struct tagNODE* pNext;
}NODE,*PNODE;


// 双向链表跟单向链表 类似  函数搬过来实现


/* 操作结果：构造一个空的线性表L */
bool InitList(PNODE *pHead);

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
bool AppendHead(PNODE pHead,ElemType e);
bool AppendTail(PNODE pHead,ElemType e);


/* 在带头结点的单链线性表L中，删除第i个元素,并由e返回其值 */
bool ListDelete(PNODE pHead,int iPosition,ElemType &e);
// 給结点地址 删除  假定条件 pNodeDel 是这个链表的结点
bool ListDelete(PNODE pHead,PNODE pNodeDel); 

/* 初始条件：线性表L已存在 */
/* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
bool ListTraverse(PNODE pHead,void (*VisitFunc)(ElemType));


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
	InitList(&pHead);
	AppendTail(pHead,23);
	AppendTail(pHead,34);
	AppendTail(pHead,45);
	ListDelete(pHead,pHead->pNext);
	ListTraverse(pHead,Visit);
	DestroyList(pHead);
	return 0;
}


bool ListDelete(PNODE pHead,PNODE pNodeDel)
{
	if(pHead == NULL ||pHead->pNext == NULL|| pNodeDel==NULL)
		return false;

	if(pNodeDel->pPrior != NULL)
		pNodeDel->pPrior->pNext = pNodeDel->pNext;
	if(pNodeDel->pNext != NULL)
		pNodeDel->pNext->pPrior = pNodeDel->pPrior;
	return true;
}


bool InitList(PNODE *pHead)
{
	*pHead = static_cast<PNODE>(malloc(sizeof(NODE)));
	if(NULL == *pHead)
		return false;
	(*pHead)->Data = INVALID_VALUE;
	(*pHead)->pNext = NULL;
	(*pHead)->pPrior = NULL; //每次都需要家 括弧 累死了 就不写指针了
	return true;
}

bool ListTraverse(PNODE pHead,void (*VisitFunc)(ElemType))
{
	if(pHead == NULL || VisitFunc == NULL)
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
	pNodeTemp->pPrior = NULL;

	while (pNodeTemp != NULL)  // 使用两个指针  一个结点一个结点的拆解 然后使用头插法链接到 原链表
	{
		pNodePre = pNodeTemp;
		pNodeTemp = pNodeTemp->pNext;
		
		// 链接 
		pNodePre->pNext = pHead->pNext;
		if(pHead->pNext != NULL)
			pHead->pNext->pPrior = pNodePre;
		pHead->pNext  = pNodePre;
		pNodePre->pPrior = pHead;
	
	}

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
	if(pNodeFree->pNext != NULL)
		pNodeFree->pNext->pPrior = pNodePre;
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
	if (pNodePre->pNext != NULL)
	{
			pNodePre->pNext->pPrior = pNodeNew;
	}
	pNodePre->pNext = pNodeNew;

	pNodeNew->pPrior = pNodePre;

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

	// 可以改  可以不改，继续按照单链表做    但怎么都要找到cur_e的位置
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
	pHead->pPrior = NULL;
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

bool AppendHead(PNODE pHead,ElemType e)
{
	if(pHead == NULL)
		return false;

	PNODE pNodeNew = reinterpret_cast<PNODE>(malloc(sizeof(NODE))); // reinterpret_cast 是类型强转
	if (pNodeNew == NULL)
		return false;
	pNodeNew->Data = e;

	pNodeNew->pNext = pHead->pNext;
	if (pHead->pNext != NULL) // 有下一个
		pHead->pNext->pPrior = pNodeNew;
	pHead->pNext = pNodeNew;
	pNodeNew->pPrior = pHead;
	
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
	pNodeNew->pPrior = pTail;
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
