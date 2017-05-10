#include <stdio.h>
#include <windows.h>

#define MAXSIZE 5
#define INVALID_VALUE INFINITE // 学习宏定义
#define EMPTY_VALUE 0
typedef int ElemType;

typedef struct _NODE{

	ElemType Data;
	int Cur;
}SLinkList[MAXSIZE];

// 一个数组只生成一个静态链表 的基本操作(13个) 
// 1、了解内存池的概念 2、熟练头插法

// 构造一个空的链表，表头为L的最后一个单元L[MAXSIZE-1]，其余单元链成 
// 一个备用链表，表头为L的第一个单元L[0]，“0”表示空指针/
bool InitList(SLinkList L);
// 初始条件：线性表L已存在。操作结果：将L重置为空表 
bool ClearList(SLinkList L);

// 若L是空表，返回TRUE；否则返回FALSE
bool ListEmpty(SLinkList L);

/* 返回L中数据元素个数 */
int ListLength(SLinkList L);

// 用e返回L中第i个元素的值
bool GetElem(SLinkList L,int iPosition,ElemType &e);

/* 在静态单链线性表L中查找第1个值为e的元素。若找到，则返回它在L中的 */
/* 位序，否则返回0。（与其它LocateElem()的定义不同) */
int LocateElem(SLinkList L,ElemType e);

/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
bool PriorElem(SLinkList L,ElemType cur_e,ElemType &pre_e);

/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */
bool NextElem(SLinkList L,ElemType cur_e,ElemType& next_e);


/* 若备用链表非空,则返回分配的结点下标(备用链表的第一个结点),否则返回0 */
int Malloc(SLinkList space);
/* 将下标为k的空闲结点回收到备用链表(成为备用链表的第一个结点) */
bool Free(SLinkList space,int k);

/* 在L中第i个元素之前插入新的数据元素e */
bool ListInsert(SLinkList L,int iPosition,ElemType e);
bool AppendTail(SLinkList L,ElemType e);
/* 删除在L中第i个数据元素e，并返回其值 */
bool ListDelete(SLinkList L,int iPosition,ElemType &e); // 按照位置删除
bool ListDelete(SLinkList L,ElemType e); // 按照元素删除 返回索引 不是位置 
// 删都删了  不用返回索引了

/* 初始条件:线性表L已存在 */
/* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
bool ListTraverse(SLinkList L,void (*VisitFunc)(ElemType));

//////////////////////////////////////////////////////////////////////////
///* 算法2.17  依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A) */
   /* 的静态链表，S为其头指针。假设备用空间足够大，space[0].cur为备用空间的头指针 */
void Difference(SLinkList L,int &s);


//////////////////////////////////////////////////////////////////////////
void Visit(ElemType e)
{
	printf("%d ",e);
}
int main()
{
	
	SLinkList L;
	//int s ;
//	Difference(L,s);

	InitList(L);
	ClearList(L);
	return 0;

}

// 与严蔚敏的代码不相同 但思路相同
// 从始至终只有一个静态链表
void Difference(SLinkList L,int &s)
{
	InitList(L);
	int r  =s ;
	int i = 0;
	int j =0;
	int iCount_a = 0;
	printf("输入A表元素个数:");
	scanf("%d",&iCount_a);
	ElemType e;
	for (j=0;j<iCount_a;++j)
	{
		printf("输入A表元素:\n");
		scanf("%d",&e);
		AppendTail(L,e); // 插到尾部
	}
	printf("输出A表：");
	ListTraverse(L,Visit);

	printf("输入B表元素个数:");
	int iCount_b = 0;
	scanf("%d",&iCount_b);

	for(j=0;j<iCount_b;++j)
	{
		printf("输入B表元素:\n");
		scanf("%d",&e);
		if (LocateElem(L,e) == 0) // 没有找到 添加进去
		{
			AppendTail(L,e);
		}
		else// 找到了 删除之
		{
			ListDelete(L,e);
		}
	}

	printf("Difference之后，A表：");
	ListTraverse(L,Visit);
}


bool ListDelete(SLinkList L,ElemType e)
{
	int iIndex = MAXSIZE-1;

	while (L[iIndex].Cur != 0 && L[L[iIndex].Cur].Data != e) // 有下一个结点 并且 不为 e
	{
		iIndex = L[iIndex].Cur;
	}
	
	if (L[iIndex].Cur != 0)
	{
		int iFree = L[iIndex].Cur; // 保存值
		L[iIndex].Cur = L[L[iIndex].Cur].Cur;
		Free(L,iFree); // 注意这里Free哪个  自己就犯错了
		return true;
	}


	return false;
}

/* 初始条件:线性表L已存在 */
/* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
bool ListTraverse(SLinkList L,void (*VisitFunc)(ElemType))
{
	if(L == NULL)
		return false;
	int i = L[MAXSIZE-1].Cur;

	while(i)
	{
		VisitFunc(L[i].Data);
		i = L[i].Cur;
	}

	printf("\n");

	return true;

}

/* 删除在L中第i个数据元素e，并返回其值 */
bool ListDelete(SLinkList L,int iPosition,ElemType &e)
{
	int j,k = MAXSIZE-1;
	if(iPosition<1 || iPosition>ListLength(L))
		return false;
	for (j=1;j<iPosition;++j)
	{
		k = L[k].Cur;
	}

	j = L[k].Cur;
	L[k].Cur = L[j].Cur;
	e = L[j].Data;
	Free(L,j);

	return true;
}	
/* 在L中第i个元素之前插入新的数据元素e */
bool ListInsert(SLinkList L,int iPosition,ElemType e)
{
	int i,j,k = MAXSIZE-1;

	if(iPosition <1 || iPosition>ListLength(L)+1)
		return false;

	i = Malloc(L);

	if (i)
	{
		L[i].Data = e;
		for (j=1;j<iPosition;j++)
		{
			k = L[k].Cur;
		}
		L[i].Cur = L[k].Cur;  // 头插法
		L[k].Cur= i;

		return true;
	}
	return false;

}
// 插到链表尾部
bool AppendTail(SLinkList L,ElemType e)
{
	if(ListLength(L)>=MAXSIZE-2)
		return false; // 没有空间

	int iIndex = Malloc(L);

	if(iIndex == 0)
		return false; // 没有空间

	L[iIndex].Data = e;
	L[iIndex].Cur = 0; // 是尾部

	int i = MAXSIZE-1; // 链表头

	while (L[i].Cur != 0) // 有没有到达最后一个结点
	{
		i = L[i].Cur;	 // 下移 找到尾部
	}

	L[i].Cur = iIndex; // 链接到尾部

	return true;
}

/* 将下标为k的空闲结点回收到备用链表(成为备用链表的第一个结点) */
bool Free(SLinkList space,int k)
{
	if(space == NULL)
		return false;
	space[k].Cur = space[0].Cur;  // 使用头插法放到备用链表的头部
	space[0].Cur = k;

	return true;
}

/* 若备用链表非空,则返回分配的结点下标(备用链表的第一个结点),否则返回0 */
int Malloc(SLinkList space)
{
	int i = space[0].Cur;
	if (i)
	{
		space[0].Cur = space[i].Cur;
	}

	return i;
}

/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */
bool NextElem(SLinkList L,ElemType cur_e,ElemType& next_e)
{
	int j,i = LocateElem(L,cur_e);

	if (i)
	{
		j = L[i].Cur;
		if (j)
		{
			next_e = L[j].Data;
			return true;
		}
	}

	next_e = INVALID_VALUE;
	return false;
}

/* 初始条件：线性表L已存在 */
/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
bool PriorElem(SLinkList L,ElemType cur_e,ElemType &pre_e)
{
	int j = L[MAXSIZE-1].Cur,i =L[j].Cur ;

	while (i && cur_e != L[i].Data)
	{
		j = i;
		i = L[i].Cur;
	}

	if(i && L[i].Data == cur_e)
	{
		pre_e = L[j].Data;
		return true;
	}
	pre_e = INVALID_VALUE;
	return false;
}
/* 在静态单链线性表L中查找第1个值为e的元素。若找到，则返回它在L中的 */
/* 位序，否则返回0。（与其它LocateElem()的定义不同) */
int LocateElem(SLinkList L,ElemType e)
{
	int i = L[MAXSIZE-1].Cur;

	while (i && L[i].Data !=e)
	{
		i = L[i].Cur;
	}
	return i;
}
// 用e返回L中第i个元素的值
bool GetElem(SLinkList L,int iPosition,ElemType &e)
{
	int i,k = MAXSIZE-1;
	if(iPosition <1 || iPosition>ListLength(L))
	{
		e = INVALID_VALUE;
		return false;
	}
	for (i=1;i<=iPosition;++i)
	{
		k = L[k].Cur;
	}
	e = L[k].Data;
	return true;

}
/* 返回L中数据元素个数 */
int ListLength(SLinkList L)
{
	int j =0,i = L[MAXSIZE-1].Cur; // i指向第一个元素

	while (i)
	{
		i = L[i].Cur;
		j++;
	}

	return j;

}


// 若L是空表，返回TRUE；否则返回FALSE
bool ListEmpty(SLinkList L)
{
	return (L[MAXSIZE-1].Cur ==0);
}

// 初始条件：线性表L已存在。操作结果：将L重置为空表 
bool ClearList(SLinkList L)
{
	
	int i,j=0,k=0;
	i = L[MAXSIZE-1].Cur;// 链表第一个结点的位置
	L[MAXSIZE-1].Cur =EMPTY_VALUE; // 链表空
	k = L[0].Cur;// 备用链表第一个结点的位置
	L[0].Cur = i;// 把链表的结点连到备用链表的表头
	while (i) // 没有链表尾
	{
		j =i;
		i = L[i].Cur;
	}
	L[j].Cur = k;  // 意思就是使用头插法 将链表插到备用链表的头部
	return true;

/*
	// 或者 这个更好理解
	int i, j ,k ;

	i = L[MAXSIZE -1 ].Cur;
	L[MAXSIZE -1].Cur = EMPTY_VALUE;

	while (i)
	{
		// 一下两步是头插法
		L[i].Cur = L[0].Cur;
		L[0].Cur = i;
	
		i = L[i].Cur; // 链表后移

	}

	return true;*/
}

// 构造一个空的链表，表头为L的最后一个单元L[MAXSIZE-1]，其余单元链成 
// 一个备用链表，表头为L的第一个单元L[0]，“0”表示空指针/
bool InitList(SLinkList L)
{
	L[MAXSIZE-1].Cur =EMPTY_VALUE; // L的最后一个单元为空链表的表头
	for (int i=0;i<MAXSIZE-2;++i)
	{
		L[i].Cur = i+1;
	}
	L[MAXSIZE-2].Cur = 0;  //无意义因为 每次都是从表头找值  根本不从这里开始
	return true;
}
