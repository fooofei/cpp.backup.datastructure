//设有编号1,2,3，4.。。n 个人围城一圈 从第一个人开始报数   报到 m 的
// 停止报数 报m的人出圈  再从它的下一个起重新报数，报到m时停止报数 ，报m 的人出圈  直到所有人出圈为止

#include <stdio.h>
#include <malloc.h>

typedef struct tagNODE
{
	int Data;
	struct tagNODE *pNext;
}NODE,*PNODE;


/************************************************************************/
/*       构成 1,2,3...NodeCount 的循环链表                   */
/************************************************************************/
void CreateList(PNODE &pHead ,PNODE &pTail ,int NodeCount)
{
	int i = 0;
	for (i =0;i<NodeCount;i++)
	{
		PNODE pNodeNew = (PNODE)malloc(sizeof(NODE));
		pNodeNew->Data = i+1;
		pNodeNew->pNext =  NULL;
		
		// 头插法
		if(pHead == NULL)
		{
			pHead = pTail = pNodeNew;
			pNodeNew->pNext = pHead;
		}
		else
		{
			pTail->pNext = pNodeNew;
			pTail = pNodeNew;
			pTail->pNext = pHead;
		}

	}

}


/************************************************************************/
/* 输出链表                                                            */
/************************************************************************/
void TravelList(PNODE pHead)
{
	if(pHead!=NULL)
	{
		printf("%d ",pHead->Data);
		PNODE pTemp = pHead->pNext;

		while (pTemp!=pHead)
		{
			printf("%d ",pTemp->Data);
			pTemp = pTemp->pNext;
		}

		printf("\n");
	}


}

/************************************************************************/
/* 约瑟夫链表 并将出局的结点 free                                  */
/************************************************************************/
void Joseoh(PNODE &pHead,int NodeCount ,int m,int iStart)  //从start 开始报数
{
	int i = 0;
	int j = 0;

	for (i=1;i<NodeCount+iStart-1;++i)
	{
		pHead = pHead->pNext;
	}

	PNODE pStart = pHead;

	PNODE pPre = NULL;

	PNODE pDel = NULL;
	for (i = 0;i<NodeCount;i++)  //曾试过  用 while(pHead!=NULL)  但是内存报错

	{
		for (j =1;j<m;j++)
		{
			pHead = pHead->pNext;
		}

		pDel  = pHead->pNext;

		pHead->pNext  = pDel->pNext;

		printf("%d ",pDel->Data);

		free(pDel) ;

	}

	printf("\n");
}	

/************************************************************************/
/* 可以这样模拟约瑟夫                                                  */
/************************************************************************/
long Jose(long n,long m,long k)
{
	for (int i = 1;i<=n;++i)
	{
		k = (k+m)%i +1;
	}
	return k;
}

int main ()
{

	PNODE pHead = NULL ,pTail = NULL;
	int NodeCount = 5;

	int i;
	for (i = 1;i<=NodeCount;++i)
	{
		CreateList(pHead,pTail,i);
		printf("链表编号：");
		TravelList(pHead);

		printf("约瑟夫环(死亡顺序):");
		Joseoh(pHead,i,4,2);
		pHead = NULL;
		pTail = NULL;
	}
	printf("Jose_Test:%d\n",Jose(5,4,2));
	return 0;

}

//One Possible Answer
// 1 2 3 4 5 6 7 8
// 约瑟夫环
// 3 6 1 5 2 8 4 7