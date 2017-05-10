//////////////////////////////////////////////////////////////////////////
//ListLoop_no_head.h
// û��ͷ���� ����ѭ������  
// һ����˵  ������������  ��ͷ���ӽ�
//
// ********
// *			*
// ********
// 
// ��Ҳ�п�����������
// ************
// 	   *			*
// 		 ********
#include <stdio.h>
#include <windows.h>

typedef int ElemType;

// ������ �ṹ��
typedef struct tagNODE{
	ElemType Data;
	struct tagNODE* pNext;
}NODE,*PNODE;

// û��ͷ���  ��û���� InitList
// ����Ļ�������  
bool AppendHead(PNODE &pHead,ElemType e);
bool AppendHead_NotLoop(PNODE &pHead,ElemType e);
bool DestroyList(PNODE &pHead);
bool ListTraverse(PNODE pHead);

// ����һ��������ֻ����ͷָ��h��
// 
// 1������ж��Ƿ���ڻ���
// 
// 2�����֪�����ĳ��ȣ�
// 
// 3������ҳ��������ӵ������
// 
// 4����������ĳ����Ƕ��٣�
// 
// 
// 
// �ⷨ��
// 
// 1����������1��ʹ��׷�ϵķ������趨����ָ��slow��fast����ͷָ�뿪ʼ��ÿ�ηֱ�ǰ��1����2��������ڻ����������������粻���ڻ���fast����NULL�˳���
// 
// 2����������2����¼������1����ײ��p��slow��fast�Ӹõ㿪ʼ���ٴ���ײ���߹��Ĳ��������ǻ��ĳ���s��
// 
// 3������3���ж�����ײ��p�����ӵ�ľ���=ͷָ�뵽���ӵ�ľ��룬��ˣ��ֱ����ײ�㡢ͷָ�뿪ʼ�ߣ��������Ǹ���������ӵ㡣
// 
// �ö����֤���ɲο���http://fayaa.com/tiku/view/7/
// 
// 4������3���Ѿ�������ӵ����ͷָ��ĳ��ȣ���������2������Ļ��ĳ��ȣ�����֮�;��Ǵ���������ĳ���

// ����Ŀ��㺯��
bool IsExitLoop(PNODE pHead) ;// �ж��Ƿ���ڻ�  ��Ҫ���㷨��Ҫ��ס

int LoopLength(PNODE pHead);

// Ѱ�һ����ӵ㣨��ڵ㣩
PNODE FindLoopPort(PNODE pHead);

// ���������Ƿ��ཻ
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

	
	printf("�Ƿ�����ཻ%d\n",IsCross(pHead,pHead_b));
	return 0;
}

//
// ���������Ƿ��ཻ (����֤)
//
bool IsCross(PNODE pHead_a,PNODE pHead_b)
{
	if(pHead_a == NULL || pHead_b == NULL)
		return false;
	// Ҫ�����ж���û�л�

	bool bLoop_a = IsExitLoop(pHead_a);
	bool bLoop_b = IsExitLoop(pHead_b);

	if(bLoop_a !=bLoop_b)
		return false; // һ���л�  һ���޻�

	if(!bLoop_a && !bLoop_b)// ���޻�
	{
		// �ҵ����������β��
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
		// �ҵ�����  ��� 
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
// �ҵ����������
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
// ���������ڻ� �󻷵ĳ���
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
// �ж��Ƿ���ڻ�  ��Ҫ���㷨��Ҫ��ס
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
// ������ ����Ļ������� ͷ�巨(�л� �޻�)������������ӡ����
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