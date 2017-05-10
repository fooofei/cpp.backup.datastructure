//���б��1,2,3��4.����n ����Χ��һȦ �ӵ�һ���˿�ʼ����   ���� m ��
// ֹͣ���� ��m���˳�Ȧ  �ٴ�������һ�������±���������mʱֹͣ���� ����m ���˳�Ȧ  ֱ�������˳�ȦΪֹ

#include <stdio.h>
#include <malloc.h>

typedef struct tagNODE
{
	int Data;
	struct tagNODE *pNext;
}NODE,*PNODE;


/************************************************************************/
/*       ���� 1,2,3...NodeCount ��ѭ������                   */
/************************************************************************/
void CreateList(PNODE &pHead ,PNODE &pTail ,int NodeCount)
{
	int i = 0;
	for (i =0;i<NodeCount;i++)
	{
		PNODE pNodeNew = (PNODE)malloc(sizeof(NODE));
		pNodeNew->Data = i+1;
		pNodeNew->pNext =  NULL;
		
		// ͷ�巨
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
/* �������                                                            */
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
/* Լɪ������ �������ֵĽ�� free                                  */
/************************************************************************/
void Joseoh(PNODE &pHead,int NodeCount ,int m,int iStart)  //��start ��ʼ����
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
	for (i = 0;i<NodeCount;i++)  //���Թ�  �� while(pHead!=NULL)  �����ڴ汨��

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
/* ��������ģ��Լɪ��                                                  */
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
		printf("�����ţ�");
		TravelList(pHead);

		printf("Լɪ��(����˳��):");
		Joseoh(pHead,i,4,2);
		pHead = NULL;
		pTail = NULL;
	}
	printf("Jose_Test:%d\n",Jose(5,4,2));
	return 0;

}

//One Possible Answer
// 1 2 3 4 5 6 7 8
// Լɪ��
// 3 6 1 5 2 8 4 7