#include <stdio.h>
#include <windows.h>


#define INVALID_VALUE INFINITE // winbase.h  ��Чֵ

typedef int ElemType;

typedef struct _NODE{
	ElemType Data;
	struct _NODE* pNext;
}NODE,*PNODE;

// ���������Ա� ��������12 �� (��չ����10��) 
// ��ε���α�2.3 �� ��ͷ�ڵ�ĵ�����

/* �������������һ���յ����Ա�L */

bool InitList(PNODE &pHead);

/* ��ʼ���������Ա�L�Ѵ��ڡ�����������������Ա�L */
bool DestroyList(PNODE &pHead);

/* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
bool ClearList(PNODE pHead);

/* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
bool ListEmpty(PNODE pHead);

/* ��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(PNODE pHead);

/* LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
bool GetElem(PNODE pHead,int iPosition, ElemType &e);

/* ��ʼ����: ���Ա�L�Ѵ���,compare()������Ԫ���ж�����(����Ϊ1,����Ϊ0) */
/* �������: ����L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
/*           ������������Ԫ�ز�����,�򷵻�ֵΪ0 */
int LocateElem(PNODE pHead,ElemType e,bool (*CompareFunc)(ElemType,ElemType));

/* ��ʼ����: ���Ա�L�Ѵ��� */
/* �������: ��cur_e��L������Ԫ��,�Ҳ��ǵ�һ��,����pre_e��������ǰ��, */
/*           ����OK;�������ʧ��,pre_e�޶���,����INFEASIBLE(����ʵ�е�) */
// ���л�˵����ε����������� LocateElem ���и��ȽϺ���ָ��Ĳ�����������ô��ľ����
//						�ﲻס ���Լ�������CompareFunc ����  ����ǿ��֢
bool PriorElem(PNODE pHead,ElemType cur_e,ElemType& pre_e,bool (*CompareFunc)(ElemType,ElemType));

/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
/*           ����OK;�������ʧ�ܣ�next_e�޶��壬����INFEASIBLE */
bool NextElem(PNODE pHead,ElemType cur_e,ElemType& next_e,bool(*CompareFunc)(ElemType,ElemType));

/* �ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e */
bool ListInsert(PNODE pHead,int iPosition,ElemType e);



/* �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ��,����e������ֵ */
bool ListDelete(PNODE pHead,int iPosition,ElemType &e);
// �ٶ����� pNodeDel �������еĽ��
bool ListDelete(PNODE pHead,PNODE pNodeDel);

/* ��ʼ���������Ա�L�Ѵ��� */
/* �������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
bool ListTraverse(PNODE pHead,void (*VisitFunc)(ElemType));


//////////////////////////////////////////////////////////////////////////
bool AppendHead(PNODE pHead,ElemType e);
bool AppendTail(PNODE pHead,ElemType e);
//////////////////////////////////////////////////////////////////////////
// �ϲ�����
bool ListMerge(PNODE &pHead_a,PNODE &pHead_b,PNODE &pHead_c);

bool ListMerge_Recursion(PNODE &pHead_a,PNODE &pHead_b,PNODE &pHead_c) ;// �ݹ�ķ��� �ϲ�����

//////////////////////////////////////////////////////////////////////////
// ������
bool ListReverse(PNODE pHead); // ����ĵ���

//////////////////////////////////////////////////////////////////////////
// ʹ��ð��ѭ����������  Ϊ ListMerge ������׼��
bool ListBubbleSort(PNODE pHead,bool(*CompareFunc)(ElemType,ElemType));

//////////////////////////////////////////////////////////////////////////
// ����������ڼ������ ���ص��ǽ���ָ��
PNODE GetReverseElem(PNODE pHead,int iPosition, ElemType &e);

//////////////////////////////////////////////////////////////////////////

// У���Ƿ���������
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
		printf("��Ч���� ");
	else 
	printf("%d ",e);
}

int main()
{

		PNODE pHead;
	int i =0;
	ElemType e = INVALID_VALUE , e0 = INVALID_VALUE;
	printf("��ʼ������\n");
	InitList(pHead);
	printf("����ղ��� (��1)(����0):%d\n",ListEmpty(pHead));
	printf("����������������\n");
	for (i=1;i<6;++i)
	{
		ListInsert(pHead,i,i);
	}
	printf("�����ȣ�%d,�������",ListLength(pHead));
	ListTraverse(pHead,Visit);
	printf("����ղ��� (��1)(����0):%d\n",ListEmpty(pHead));
	printf("ClearList,���:");
	ClearList(pHead);
	ListTraverse(pHead,Visit);
	printf("����ղ��� (��1)(����0):%d\n",ListEmpty(pHead));

	for (i=1;i<11;++i)
	{
		ListInsert(pHead,i,i);
	}

	printf("����10����֮��,����%d:",ListLength(pHead));
	ListTraverse(pHead,Visit);

	GetElem(pHead,5,e);
	printf("�õ���5��Ԫ�أ�%d\n",e);

	for (i=1;i<3;++i)
	{
		GetElem(pHead,i,e0);
		if(PriorElem(pHead,e0,e,Compare))
			printf("%dԪ�ص�ǰ��%d\n",e0,e);
	}

	for (i=ListLength(pHead)-1;i<=ListLength(pHead);++i)
	{
		GetElem(pHead,i,e0);
		if(NextElem(pHead,e0,e,Compare))
			printf("%dԪ�صĺ��%d\n",e0,e);
	}

	int k = ListLength(pHead);

	for (i = k+1;i>=k;i--)
	{
		if(ListDelete(pHead,i,e))
			printf("ɾ��Ԫ��%d\n",e);
	}

	printf("���һ���������,����%d,",ListLength(pHead));
	ListTraverse(pHead,Visit);

	PNODE pHead_b,pHead_c;
	InitList(pHead_b);
	InitList(pHead_c);

	for (i=10;i<13;++i)
	{
		ListInsert(pHead_b,i-9,i);
	}

	printf("B����:");
	ListTraverse(pHead_b,Visit);

	printf("�ϲ�:\n");
	ListMerge(pHead,pHead_b,pHead_c);

	ListTraverse(pHead_c,Visit);

	DestroyList(pHead_b);
	DestroyList(pHead_c);
	printf("��������\n");
	DestroyList(pHead);


	printf("***************ListTraverse**********************************\n");

	InitList(pHead);
	
	for (i=0;i<5;++i)
	{
		ListInsert(pHead,i,i);
	}

	ListReverse(pHead);
	printf("��ӡ����\n");
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
		pNodeDel->Data = pNodeDel->pNext->Data; // ת��ɾ�����  ����ɾ��pNodeDel->pNext
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

// ʹ�õݹ� ͷ��㲻��Ϊ�� ���Դ��ε�ʱ��  ��Ҫע��
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
			if (CompareFunc(p1->Data,p2->Data)) //��С�������� 
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

	while (pNodeTemp != NULL)  // ʹ������ָ��  һ�����һ�����Ĳ�� Ȼ��ʹ��ͷ�巨���ӵ� ԭ����
	{
		pNodePre = pNodeTemp;
		pNodeTemp = pNodeTemp->pNext;
		
		// ���� 
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

/* ��ʼ���������Ա�L�Ѵ��� */
/* �������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
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

 /* �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ��,����e������ֵ */
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

/* �ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e */
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

/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
/*           ����OK;�������ʧ�ܣ�next_e�޶��壬����INFEASIBLE */
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

/* ��ʼ����: ���Ա�L�Ѵ��� */
/* �������: ��cur_e��L������Ԫ��,�Ҳ��ǵ�һ��,����pre_e��������ǰ��, */
/*           ����OK;�������ʧ��,pre_e�޶���,����INFEASIBLE(����ʵ�е�) */
// ���л�˵����ε����������� LocateElem ���и��ȽϺ���ָ��Ĳ�����������ô��ľ����
//						�ﲻס ���Լ�������CompareFunc ����  ����ǿ��֢
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

/* ��ʼ����: ���Ա�L�Ѵ���,compare()������Ԫ���ж�����(����Ϊ1,����Ϊ0) */
/* �������: ����L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
/*           ������������Ԫ�ز�����,�򷵻�ֵΪ0 */
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

/* LΪ��ͷ���ĵ������ͷָ�롣����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
bool GetElem(PNODE pHead,int iPosition, ElemType &e)
{
	if(pHead == NULL || iPosition>ListLength(pHead)) // �������ε������������ͬ
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

/* ��ʼ���������Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
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

/* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
bool ListEmpty(PNODE pHead)
{
	if(pHead == NULL)
		return false;

	return (pHead->pNext == NULL);
}

/* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
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

/* ��ʼ���������Ա�L�Ѵ��ڡ�����������������Ա�L */
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

/* �������������һ���յ����Ա�L */
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

	PNODE pNodeNew = reinterpret_cast<PNODE>(malloc(sizeof(NODE))); // reinterpret_cast ������ǿת

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

	// �ҵ������β��
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
	// ͷ��� �Ǹ� �ս��
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

