#include <stdio.h>
#include <windows.h>


// ��ͷ�ս��� ˫������
typedef int ElemType;
#define  INVALID_VALUE -1

typedef struct tagNODE{

	ElemType Data;
	struct tagNODE* pPrior;
	struct tagNODE* pNext;
}NODE,*PNODE;


// ˫��������������� ����  ���������ʵ��


/* �������������һ���յ����Ա�L */
bool InitList(PNODE *pHead);

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
bool AppendHead(PNODE pHead,ElemType e);
bool AppendTail(PNODE pHead,ElemType e);


/* �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ��,����e������ֵ */
bool ListDelete(PNODE pHead,int iPosition,ElemType &e);
// �o����ַ ɾ��  �ٶ����� pNodeDel ���������Ľ��
bool ListDelete(PNODE pHead,PNODE pNodeDel); 

/* ��ʼ���������Ա�L�Ѵ��� */
/* �������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
bool ListTraverse(PNODE pHead,void (*VisitFunc)(ElemType));


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
	(*pHead)->pPrior = NULL; //ÿ�ζ���Ҫ�� ���� ������ �Ͳ�дָ����
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
	pNodeTemp->pPrior = NULL;

	while (pNodeTemp != NULL)  // ʹ������ָ��  һ�����һ�����Ĳ�� Ȼ��ʹ��ͷ�巨���ӵ� ԭ����
	{
		pNodePre = pNodeTemp;
		pNodeTemp = pNodeTemp->pNext;
		
		// ���� 
		pNodePre->pNext = pHead->pNext;
		if(pHead->pNext != NULL)
			pHead->pNext->pPrior = pNodePre;
		pHead->pNext  = pNodePre;
		pNodePre->pPrior = pHead;
	
	}

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
	if(pNodeFree->pNext != NULL)
		pNodeFree->pNext->pPrior = pNodePre;
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
	if (pNodePre->pNext != NULL)
	{
			pNodePre->pNext->pPrior = pNodeNew;
	}
	pNodePre->pNext = pNodeNew;

	pNodeNew->pPrior = pNodePre;

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

	// ���Ը�  ���Բ��ģ��������յ�������    ����ô��Ҫ�ҵ�cur_e��λ��
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
	pHead->pPrior = NULL;
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

bool AppendHead(PNODE pHead,ElemType e)
{
	if(pHead == NULL)
		return false;

	PNODE pNodeNew = reinterpret_cast<PNODE>(malloc(sizeof(NODE))); // reinterpret_cast ������ǿת
	if (pNodeNew == NULL)
		return false;
	pNodeNew->Data = e;

	pNodeNew->pNext = pHead->pNext;
	if (pHead->pNext != NULL) // ����һ��
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
	// �ҵ������β��
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
