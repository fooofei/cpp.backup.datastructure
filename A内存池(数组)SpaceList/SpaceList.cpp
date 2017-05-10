#include <stdio.h>
#include <malloc.h>
#include <windows.h>
typedef struct _SPACENODE_
{
	int iPos;					 //�ýṹ�ǵ�������
	_SPACENODE_* pNext;
}SpaceNode,*pSpaceNode;

typedef struct _SPACDELIST_
{
	void* pBlock;					//һ�������ڴ�
	int iCount;						//���ɿռ�ڵ�ĸ���
	pSpaceNode pHead;				//���ɿռ�����ͷ���ڵ�
}SpaceList,*pSpaceList;


pSpaceList CreateSpaceList(int nCount, int nDataSize)
{
		pSpaceList pSpaceListTemp = (pSpaceList)malloc(sizeof(SpaceList)+nCount*(sizeof(SpaceNode)+nDataSize));

		pSpaceNode pSpaceNodeTemp = NULL;

		if (pSpaceListTemp!=NULL)
		{
			pSpaceListTemp->iCount = nCount;

			pSpaceListTemp->pBlock = (void*)((BYTE*)pSpaceListTemp+sizeof(SpaceList));
											// char*  Ҳ����

			pSpaceListTemp->pHead = (pSpaceNode) pSpaceListTemp->pBlock;

			pSpaceNodeTemp = pSpaceListTemp->pHead;
			
		}



		int i =0;
		for (i=0;i<nCount;i++)
		{
			pSpaceNodeTemp->iPos = i;

			if(i<nCount-1)     
			{
				pSpaceNodeTemp->pNext = (pSpaceNode)((BYTE*)pSpaceNodeTemp+sizeof(SpaceNode)+nDataSize);//�ܳ���

				pSpaceNodeTemp = pSpaceNodeTemp->pNext;
			}
		
		}

		pSpaceNodeTemp->pNext = NULL;  //��Ҫ���� ��  �����˶Խ��û��Ӱ�� ֻ�����һ�����Ƚ����� ����  �ܹ��ǲ������� 

		return pSpaceListTemp;
}



void FreeSpaceList(pSpaceList &pSpaceListTemp)
{
	if (pSpaceListTemp!=NULL)
	{
		free(pSpaceListTemp);
	}

}

void* Alloc(pSpaceList &pSpaceListTemp)
{
	if (pSpaceListTemp)
	{
		pSpaceNode pSpaceNodeTemp = pSpaceListTemp->pHead;
		pSpaceListTemp->pHead = pSpaceNodeTemp->pNext;

		pSpaceListTemp->iCount--;

		return (void*)((BYTE*)pSpaceNodeTemp+sizeof(SpaceNode));
	}

	return NULL;
}

void Free(pSpaceList &pSpaceListTemp,void* pData)
{
	// 	ʹ�õ�ʱ��  ��ʹ�õ�һ���ڴ� ��������   
// 		��ʹ���ڴ�  �ջ�ȥ��ʱ�����ջ�ȥ��һ���ڴ� �������ڴ�ʹ����ͷ�巨  
	pSpaceNode pSpaceNodeNew = (pSpaceNode)((BYTE*)pData - sizeof(SpaceNode));

	pSpaceListTemp->iCount++;

	//����һ �嵽ͷ��  ���ڴ�ʹ�ò�����     �˷����� 

// 	pSpaceNodeNew->pNext = pSpaceListTemp->pHead;//ͷ�巨
// 
// 	pSpaceListTemp->pHead = pSpaceNodeNew;

	
	
	//������   �嵽β��  �ָ�ʹ���ڴ�֮ǰ����״

	pSpaceNode pSpaceNodeTemp = pSpaceListTemp->pHead;
	if (pSpaceListTemp->pHead==NULL)
	{
		pSpaceNodeNew->pNext = pSpaceListTemp->pHead;

		pSpaceListTemp->pHead = pSpaceNodeNew;
	}
	else
	{
		while (pSpaceNodeTemp->pNext!=NULL)
		{
			pSpaceNodeTemp = pSpaceNodeNew->pNext;
		}
		pSpaceNodeTemp->pNext = pSpaceNodeNew;

		pSpaceNodeNew->pNext = NULL;
	}
}
int  main()
{
	pSpaceList pSpaceListTemp = CreateSpaceList(2,20);

	char* p[2] = {0};

	int i =0;
	for (i=0;i<2;i++)
	{
		p[i] =(char*) Alloc(pSpaceListTemp);

		strcpy(p[i],"hello");
	}
	

	for(i =0;i<2;i++)
	{
		printf("%s ",p[i]);
		Free(pSpaceListTemp,p[i]);

	}

	FreeSpaceList(pSpaceListTemp);

    return 0;
}