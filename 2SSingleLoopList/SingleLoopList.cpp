#include <stdio.h>
#include <WINDOWS.H>

// 设立尾指针的单循环链表(存储结构由c2-2.h定义)的12个基本操作
// 单向循环链表  设立一个头结点就比较舒服了
// 当不设空头结点的时候，我们可以通过两种方法来打印链表1、另外设立一个大结点定一个Len域记录链表长度
//             2、打印的时候把先打印第一个结点，然后把第一个结点做空结点，就跟有空结点的一样了

#define INVALID_VALUE -1 // 定义我们数据的无效值
typedef int ElemType; // 重定义我们的结点数据域
// 链表结点类型 (遵守Windows命名规范)
typedef struct tagNODE{

	ElemType  Data;
	struct tagNODE *pNext;
}NODE,*PNODE;


//////////////////////////////////////////////////////////////////////////
/* 操作结果：构造一个空的线性表L */
bool InitList(PNODE &pHead);
//////////////////////////////////////////////////////////////////////////
/* 操作结果：销毁线性表L */
bool DestroyList(PNODE &pHead);
//////////////////////////////////////////////////////////////////////////
/* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
bool ListEmpty(PNODE pHead);
//////////////////////////////////////////////////////////////////////////
/* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
int ListLength(PNODE pHead);
//////////////////////////////////////////////////////////////////////////
// 链接到链表的头部
bool AppendHead(PNODE pHead,ElemType e);
bool AppendTail(PNODE pHead,ElemType e);
//////////////////////////////////////////////////////////////////////////
/* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
bool ClearList(PNODE &pHead);
//////////////////////////////////////////////////////////////////////////
/* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
bool GetElem(PNODE pHead,int iPosition,ElemType &e);
//////////////////////////////////////////////////////////////////////////
/* 初始条件：线性表L已存在，compare()是数据元素判定函数 */
/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在，则返回值为0 */
int LocateElem(PNODE pHead,ElemType e,bool (*CompareFunc)(ElemType,ElemType));
//////////////////////////////////////////////////////////////////////////
/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
bool PriorElem(PNODE pHead,ElemType cur_e,ElemType &pre_e,bool(*CompareFunc)(ElemType,ElemType));
//////////////////////////////////////////////////////////////////////////

/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */
bool NextElem(PNODE pHead,ElemType cur_e,ElemType &next_e,bool (*CompareFunc)(ElemType,ElemType));
//////////////////////////////////////////////////////////////////////////
/* 在L的第i个位置之前插入元素e */
bool ListInsert(PNODE pHead,int iPosition,ElemType e);
//////////////////////////////////////////////////////////////////////////
/* 删除L的第i个元素,并由e返回其值 */
bool ListDelete(PNODE pHead,int iPosition,ElemType &e);
//////////////////////////////////////////////////////////////////////////
/* 初始条件:L已存在。操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
bool ListTraverse(PNODE pHead,bool (*VisitFunc)(ElemType));
//////////////////////////////////////////////////////////////////////////
bool Visit(ElemType e)
{
	if(e == INVALID_VALUE)
	{
		printf("数据无效. ");
		return false;
	}
	else
	{
		printf("%d ",e);
		return true;
	}
}

bool Compare(ElemType a, ElemType b)
{
	return (a==b);
}

int main()
{
	PNODE pHead;
	InitList(pHead);
	AppendTail(pHead,4);
	AppendTail(pHead,2);
	AppendTail(pHead,1);
	ElemType e;
	ListTraverse(pHead,Visit);
	DestroyList(pHead);
	return 0;
}


bool AppendTail(PNODE pHead,ElemType e)
{
	if(pHead == NULL)
		return false;

	PNODE pNodeNew = static_cast<PNODE>(malloc(sizeof(NODE)));
	if(pNodeNew == NULL)
		return false;
	pNodeNew->Data = e;

	PNODE pNodeNext = pHead->pNext;
	while (pNodeNext->pNext != pHead)
	{
		pNodeNext = pNodeNext->pNext;
	}

	pNodeNew->pNext = pNodeNext->pNext;
	pNodeNext->pNext = pNodeNew;

	return true;
}

/* 初始条件:L已存在。操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
bool ListTraverse(PNODE pHead,bool (*VisitFunc)(ElemType))
{
	if(pHead == NULL)
		return false;

	PNODE pNodeNext = pHead->pNext;
	while (pNodeNext != pHead)
	{
		if(!VisitFunc(pNodeNext->Data))
			return false;
		pNodeNext = pNodeNext->pNext;
	}
	printf("\n");
	return true;
}
/* 删除L的第i个元素,并由e返回其值 */
bool ListDelete(PNODE pHead,int iPosition,ElemType &e)
{
	if(pHead == NULL || iPosition <1 || iPosition>ListLength(pHead))
		return false;

	int i = 1;

	while (i<iPosition)
	{
		pHead = pHead ->pNext; // 这里使用pHead 不会改变链表
		i++;
	}

	PNODE pNodeDel = pHead->pNext;
	e = pNodeDel->Data;

	pHead->pNext = pNodeDel->pNext;

	free(pNodeDel);

	return true;
}

/* 在L的第i个位置之前插入元素e */
bool ListInsert(PNODE pHead,int iPosition,ElemType e)
{
	if(pHead == NULL || iPosition<1 || iPosition >ListLength(pHead)+1)
		return false;
	
	int i = 1;
	while (i<iPosition)
	{
		pHead = pHead->pNext;
		i++;
	}

	PNODE pNodeNew = static_cast<PNODE>(malloc(sizeof(NODE)));
	if(pNodeNew == NULL)
		return false;
	pNodeNew->Data = e;
	pNodeNew->pNext = pHead->pNext;
	pHead->pNext = pNodeNew;
	
	return true;
}
/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */
bool NextElem(PNODE pHead,ElemType cur_e,ElemType &next_e,bool (*CompareFunc)(ElemType,ElemType))
{
		if(pHead == NULL)
			return false;
		PNODE pNodePre = pHead->pNext;
		
		while (pNodePre->pNext != pHead)
		{
			if(CompareFunc(cur_e,pNodePre->Data))
			{
				next_e = pNodePre->pNext->Data;
				return true;
			}
			pNodePre = pNodePre->pNext;
		}
		
		next_e = INVALID_VALUE;
	return false;
}


/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
bool PriorElem(PNODE pHead,ElemType cur_e,ElemType &pre_e,bool(*CompareFunc)(ElemType,ElemType))
{
	if(pHead == NULL)
		return false;
	PNODE pNodePre = pHead->pNext;

	while (pNodePre != pHead)
	{
		if(CompareFunc(cur_e,pNodePre->pNext->Data))
		{
			pre_e = pNodePre->Data;
			return true;
		}
		pNodePre = pNodePre->pNext;
	}

	pre_e = INVALID_VALUE;
	return false;
}

/* 初始条件：线性表L已存在，compare()是数据元素判定函数 */
/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在，则返回值为0 */
int LocateElem(PNODE pHead,ElemType e,bool (*CompareFunc)(ElemType,ElemType))
{
	if(pHead == NULL)
		return -1;
	int iIndex = 0;

	PNODE pNodeNext = pHead->pNext;

	while (pNodeNext != pHead)
	{
		iIndex++;
		if(CompareFunc(e,pNodeNext->Data))
			return iIndex;

		pNodeNext = pNodeNext->pNext;
	}

	return 0;
}


/* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
bool GetElem(PNODE pHead,int iPosition,ElemType &e)
{
	if(pHead == NULL)
		return false;
	if(iPosition<1 || iPosition>ListLength(pHead))
	{
		e = INVALID_VALUE;
		return false;
	}
	int i =1;
	PNODE pNodeNext = pHead->pNext;

	while (i<iPosition)
	{
		i++;
		pNodeNext = pNodeNext->pNext;
	}

	e = pNodeNext->Data;

	return true;
}

// 链接到链表的头部
bool AppendHead(PNODE pHead,ElemType e)
{
	if (pHead == NULL)
		return false;

	PNODE pNodeNew = static_cast<PNODE>(malloc(sizeof(NODE)));
	if(pNodeNew == NULL)
		return false;
	pNodeNew->Data = e;

	pNodeNew->pNext = pHead->pNext;
	pHead->pNext = pNodeNew;

	return true;
}


/* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
int ListLength(PNODE pHead)
{
	if(pHead == NULL)
		return false;

	int nLen = 0;

	PNODE pNodeNext = pHead->pNext;

	while (pNodeNext != pHead)
	{
		nLen++;
		pNodeNext = pNodeNext->pNext;
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
// 严蔚敏的源代码抽风 最后留下了头结点
bool ClearList(PNODE &pHead)
{

 	if(pHead == NULL)
		return false;
 	PNODE pHeadTemp = pHead->pNext;
	PNODE pNodeNext = NULL;

	while (pHeadTemp != pHead)
	{
		pNodeNext = pHeadTemp->pNext;
		free(pHeadTemp);
		pHeadTemp = pNodeNext;
	}
	pHead->pNext = pHead;
	return true;
}	


/* 操作结果：构造一个空的线性表L */
bool InitList(PNODE &pHead)
{
	pHead = static_cast<PNODE>(malloc(sizeof(NODE)));
	if (pHead == NULL)
		return false;
	pHead->Data = INVALID_VALUE;
	pHead->pNext = pHead; // 指针域指向头结点

	return true;

}

/* 操作结果：销毁线性表L */
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