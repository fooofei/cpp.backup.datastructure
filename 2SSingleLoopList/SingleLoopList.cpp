#include <stdio.h>
#include <WINDOWS.H>

// ����βָ��ĵ�ѭ������(�洢�ṹ��c2-2.h����)��12����������
// ����ѭ������  ����һ��ͷ���ͱȽ������
// �������ͷ����ʱ�����ǿ���ͨ�����ַ�������ӡ����1����������һ�����㶨һ��Len���¼������
//             2����ӡ��ʱ����ȴ�ӡ��һ����㣬Ȼ��ѵ�һ��������ս�㣬�͸��пս���һ����

#define INVALID_VALUE -1 // �����������ݵ���Чֵ
typedef int ElemType; // �ض������ǵĽ��������
// ���������� (����Windows�����淶)
typedef struct tagNODE{

	ElemType  Data;
	struct tagNODE *pNext;
}NODE,*PNODE;


//////////////////////////////////////////////////////////////////////////
/* �������������һ���յ����Ա�L */
bool InitList(PNODE &pHead);
//////////////////////////////////////////////////////////////////////////
/* ����������������Ա�L */
bool DestroyList(PNODE &pHead);
//////////////////////////////////////////////////////////////////////////
/* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
bool ListEmpty(PNODE pHead);
//////////////////////////////////////////////////////////////////////////
/* ��ʼ������L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(PNODE pHead);
//////////////////////////////////////////////////////////////////////////
// ���ӵ������ͷ��
bool AppendHead(PNODE pHead,ElemType e);
bool AppendTail(PNODE pHead,ElemType e);
//////////////////////////////////////////////////////////////////////////
/* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
bool ClearList(PNODE &pHead);
//////////////////////////////////////////////////////////////////////////
/* ����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
bool GetElem(PNODE pHead,int iPosition,ElemType &e);
//////////////////////////////////////////////////////////////////////////
/* ��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж����� */
/* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
/*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
int LocateElem(PNODE pHead,ElemType e,bool (*CompareFunc)(ElemType,ElemType));
//////////////////////////////////////////////////////////////////////////
/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
/*           �������ʧ�ܣ�pre_e�޶��� */
bool PriorElem(PNODE pHead,ElemType cur_e,ElemType &pre_e,bool(*CompareFunc)(ElemType,ElemType));
//////////////////////////////////////////////////////////////////////////

/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣� */
/*           �������ʧ�ܣ�next_e�޶��� */
bool NextElem(PNODE pHead,ElemType cur_e,ElemType &next_e,bool (*CompareFunc)(ElemType,ElemType));
//////////////////////////////////////////////////////////////////////////
/* ��L�ĵ�i��λ��֮ǰ����Ԫ��e */
bool ListInsert(PNODE pHead,int iPosition,ElemType e);
//////////////////////////////////////////////////////////////////////////
/* ɾ��L�ĵ�i��Ԫ��,����e������ֵ */
bool ListDelete(PNODE pHead,int iPosition,ElemType &e);
//////////////////////////////////////////////////////////////////////////
/* ��ʼ����:L�Ѵ��ڡ��������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
bool ListTraverse(PNODE pHead,bool (*VisitFunc)(ElemType));
//////////////////////////////////////////////////////////////////////////
bool Visit(ElemType e)
{
	if(e == INVALID_VALUE)
	{
		printf("������Ч. ");
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

/* ��ʼ����:L�Ѵ��ڡ��������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
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
/* ɾ��L�ĵ�i��Ԫ��,����e������ֵ */
bool ListDelete(PNODE pHead,int iPosition,ElemType &e)
{
	if(pHead == NULL || iPosition <1 || iPosition>ListLength(pHead))
		return false;

	int i = 1;

	while (i<iPosition)
	{
		pHead = pHead ->pNext; // ����ʹ��pHead ����ı�����
		i++;
	}

	PNODE pNodeDel = pHead->pNext;
	e = pNodeDel->Data;

	pHead->pNext = pNodeDel->pNext;

	free(pNodeDel);

	return true;
}

/* ��L�ĵ�i��λ��֮ǰ����Ԫ��e */
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
/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣� */
/*           �������ʧ�ܣ�next_e�޶��� */
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


/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
/*           �������ʧ�ܣ�pre_e�޶��� */
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

/* ��ʼ���������Ա�L�Ѵ��ڣ�compare()������Ԫ���ж����� */
/* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
/*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
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


/* ����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
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

// ���ӵ������ͷ��
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


/* ��ʼ������L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
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


/* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
bool ListEmpty(PNODE pHead)
{
	if(pHead == NULL)
		return false;
	return (pHead->pNext == NULL);
}


/* ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
// ��ε����Դ������ ���������ͷ���
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


/* �������������һ���յ����Ա�L */
bool InitList(PNODE &pHead)
{
	pHead = static_cast<PNODE>(malloc(sizeof(NODE)));
	if (pHead == NULL)
		return false;
	pHead->Data = INVALID_VALUE;
	pHead->pNext = pHead; // ָ����ָ��ͷ���

	return true;

}

/* ����������������Ա�L */
bool DestroyList(PNODE &pHead)
{
	if(pHead == NULL)
		return false;
	PNODE pHeadTemp = pHead->pNext;
	PNODE pNodeNext = NULL;
	while (pHeadTemp != pHead) // û�е����β
	{
		pNodeNext = pHeadTemp->pNext;
		free(pHeadTemp);
		pHeadTemp = pNodeNext;
	}
	free(pHead); // �ͷ�ͷ���
	pHead = NULL;

	return true;
}