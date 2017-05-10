#include <stdio.h>
#include <malloc.h>
#include <string.h>

//BYTE*   #include <windows.h>

typedef struct  _SPACENODE_            //�ýṹ�ǵ�������
{
	int iPos;
	_SPACENODE_* pNext;
}SPACENODE,*pSPACENODE;              


typedef struct _SPACELIST_ {
	void*		 pBlock;			 /* һ�������ڴ� */
	pSPACENODE   pHead;				 /* ���ɿռ�����ͷ���ڵ� */
	int        uFreeCount;			 /* ���ɿռ�ڵ�ĸ��� */
}SPACELIST,*pSPACELIST;


typedef struct _DSPACENODE_
{
	_DSPACENODE_* pNext;
	_DSPACENODE_* pPre;
	pSPACELIST    pSpaceList;
	int           iFlag;
	int           iPos;
}DSPACENODE,*pDSPACENODE;

typedef struct _DSPACELIST_ 
{

	pDSPACENODE pDSNode;                      /* ����������ÿռ���DSPACENODE���� */
	pDSPACENODE pEmpty;                       /* ���ÿռ����û�б�ʹ�õĽڵ������ͷ */
	pDSPACENODE pHead;
	pDSPACENODE pTail;
	int         iDataCount;
	int         iDataSize;
	int         DSNodeCount;
	int         iUsedDSNodeCount;

}DSPACELIST,*pDSPACELIST;





pDSPACELIST CreateDSpaceList(int iDSNodeCount,int iDataCount,int iDataSize);

pSPACELIST CreateSpaceList(int iDataCount,int iDataSize,int iPos);

void DSpaceListDestroy(pDSPACELIST& pDSpaceListTemp);
void SpaceDestroy(pSPACELIST& pSpaceListTemp);

void SpaceListFree(pSPACELIST& pSpaceListTemp,void* pData);

void DSpaceListFree(pDSPACELIST pDSpaceListTemp,void* pData);

void* DSpaceListAlloc(pDSPACELIST& pDSpaceListTemp);

void* SpaceListAlloc(pSPACELIST& pSpaceListTemp);

int main()
{

	pDSPACELIST pSPACELISTNew = CreateDSpaceList(2,2,20);

	
	char *p[5] = {0};
	int i =0;

	for (i=0;i<5;i++)
	{
		p[i] = (char*)DSpaceListAlloc(pSPACELISTNew);
		strcpy(p[i],"Hello");
	}

	for (i=0;i<5;i++)
	{
		printf("%s\n",p[i]);
		DSpaceListFree(pSPACELISTNew,p[i]);

	}


	DSpaceListDestroy(pSPACELISTNew);

}



pSPACELIST CreateSpaceList(int iDataCount,int iDataSize,int iPos) 
{

	pSPACELIST pSpaceListTemp = NULL;

	pSPACENODE pSpaceNodeTemp = NULL;

	pSpaceListTemp = (pSPACELIST)malloc(sizeof(SPACELIST)+iDataCount*(iDataSize+sizeof(SPACENODE)));



	if (pSpaceListTemp!=NULL)
	{
		pSpaceListTemp->pBlock = (void*)((char*)pSpaceListTemp+sizeof(SPACELIST));


		pSpaceListTemp->pHead = (pSPACENODE)(pSpaceListTemp->pBlock);


		pSpaceNodeTemp = pSpaceListTemp->pHead;


		int i = 0;
		for (i=0;i<iDataCount;i++)
		{
			pSpaceNodeTemp->iPos = iPos;

			if (i<iDataCount-1)//����  ��
			{
				pSpaceNodeTemp->pNext = (pSPACENODE)((char*)(pSpaceNodeTemp)+sizeof(SPACENODE)+iDataSize);

				pSpaceNodeTemp = pSpaceNodeTemp->pNext;
			}


		}


		pSpaceNodeTemp->pNext = NULL;

		pSpaceListTemp->uFreeCount = iDataCount;
	}


	return pSpaceListTemp;





}


pDSPACELIST CreateDSpaceList(int iDSNodeCount,int iDataCount,int iDataSize)
{
	pDSPACELIST pDSpaceListTemp = NULL;

	int i = 0;

	pDSpaceListTemp = (pDSPACELIST)malloc(sizeof(DSPACELIST));

	if (pDSpaceListTemp==NULL)
	{
		return NULL;
	}

	else
	{
		pDSpaceListTemp->pDSNode = (pDSPACENODE)malloc(sizeof(DSPACENODE)*iDSNodeCount);

		if (pDSpaceListTemp->pDSNode==NULL)
		{
			free(pDSpaceListTemp);
			return NULL;
		}

		else
		{
			for (i=0;i<iDSNodeCount-1;i++)  //��ʼ����һ�ڵ�  //
			{
				pDSpaceListTemp->pDSNode[i].pNext = &(pDSpaceListTemp->pDSNode[i+1]);

				// Ҳ����	pDSpaceListTemp->pDSNode[i].pNext = pDSpaceListTemp->pDSNode[i] + sizeof(DSPACENODE);

				pDSpaceListTemp->pDSNode[i].iPos = i;
			}


			for (i=1;i<iDSNodeCount;i++)    //��ʼ�������ڵ�
			{
				pDSpaceListTemp->pDSNode[i].pPre = NULL; //û�и���˫��

				pDSpaceListTemp->pDSNode[i].pSpaceList = NULL;


				pDSpaceListTemp->pDSNode[i].iFlag = 0;
			}

			//��ʼ�������һ���ڵ�

			pDSpaceListTemp->pDSNode[iDSNodeCount-1].pNext = NULL;

			pDSpaceListTemp->pDSNode[iDSNodeCount-1].iPos = iDSNodeCount-1;


			pDSpaceListTemp->pEmpty = &(pDSpaceListTemp->pDSNode[1]); // ���� 0??


			pDSpaceListTemp->pDSNode[0].pSpaceList = CreateSpaceList(iDataCount,iDataSize,0);

			//ֻ�ڵ�һ���ڵ������ �����ڴ�
			//iPos ���� 0 
			if (pDSpaceListTemp->pDSNode[0].pSpaceList==NULL)
			{
				free(pDSpaceListTemp->pDSNode);

				free(pDSpaceListTemp);

				return NULL;
			}

			else  //��0Ԫ�ز��뵽����
			{
				pDSpaceListTemp->pHead = pDSpaceListTemp->pTail = &(pDSpaceListTemp->pDSNode[0]);

				pDSpaceListTemp->pHead->pPre = pDSpaceListTemp->pTail->pNext = NULL;


				pDSpaceListTemp->pDSNode[0].iFlag = 1;

				pDSpaceListTemp->iDataCount = iDataCount; //�����¼�������������ܴ����ݵ���Ŀ

				pDSpaceListTemp->iDataSize = iDataSize;

				pDSpaceListTemp->DSNodeCount = iDSNodeCount;

				pDSpaceListTemp->iUsedDSNodeCount = 1;

			}

		}
	}

	return pDSpaceListTemp;
}



void DSpaceListDestroy(pDSPACELIST& pDSpaceListTemp)
{
	int i = 0;

	if (pDSpaceListTemp!=NULL)
	{
		for (i=0;i<pDSpaceListTemp->DSNodeCount;i++)
		{
			if (pDSpaceListTemp->pDSNode[i].pSpaceList!=NULL)
			{
				SpaceDestroy(pDSpaceListTemp->pDSNode[i].pSpaceList);
			}
		}

		free(pDSpaceListTemp);

		pDSpaceListTemp = NULL; //��
	}
}



void SpaceDestroy(pSPACELIST& pSpaceListTemp)
{
	if (pSpaceListTemp!=NULL)
	{
		free(pSpaceListTemp);

		pSpaceListTemp = NULL;//���� ��
	}

}

void* SpaceListAlloc(pSPACELIST& pSpaceListTemp)
{
	pSPACENODE pSpaceNodeTemp = NULL;


	pSpaceNodeTemp = pSpaceListTemp->pHead;


	if (pSpaceNodeTemp!=NULL)
	{
		pSpaceListTemp->pHead = pSpaceNodeTemp->pNext;

		pSpaceNodeTemp->pNext  = NULL;  //��

		pSpaceListTemp->uFreeCount--;

		return (void*)((char*)pSpaceNodeTemp+sizeof(SPACENODE));// ���� uDataSize ��ַ
	}


	return NULL;
}

void* DSpaceListAlloc(pDSPACELIST& pDSpaceListTemp)
{

	int i = 0;

	void* pData = NULL;

	pDSPACENODE pDSpaceNodeTemp ;
	//   0 Ԫ�� 
	pDSpaceNodeTemp = pDSpaceListTemp->pHead;       

	if (pDSpaceNodeTemp!=NULL)
	{
		pData = SpaceListAlloc(pDSpaceNodeTemp->pSpaceList);


		if (pDSpaceNodeTemp->pSpaceList->uFreeCount==0)     /* ͷ���ڵ�ָ��Ŀ��ÿռ����û�����ɿռ䣬��ͷ���ڵ㵯�� */
		{
			pDSpaceListTemp->pHead = pDSpaceNodeTemp->pNext;  //pDSpaceNodeTemp  ��Ҫ�� Ҳ���ͷ�  ���  

			if (pDSpaceListTemp->pHead!=NULL)
			{
				pDSpaceListTemp->pHead->pPre = NULL;         //��δ�����
			}
			
			// pTail û�й�   ����  ��  
			else //pTail==NULL
			{
				pDSpaceListTemp->pTail = NULL;
			}
			pDSpaceNodeTemp->iFlag = 0;
		}


	}

	else
	{
		//���·���  (�Ȳ��Һ����)


		if (pDSpaceListTemp->pEmpty==NULL)
		{
			int j = 0;

			//�����ڴ�
			int iLen = 2* pDSpaceListTemp->DSNodeCount;
			pDSPACENODE p = NULL;


			p = (pDSPACENODE)malloc(sizeof(DSPACENODE)*iLen);


			if (p==NULL)
			{
				return NULL;
			}

			//�����ݿ����µ��ڴ���

			for (i=0;i<pDSpaceListTemp->DSNodeCount;i++)
			{

				//ע��������㷨�����е��ο�ͼ
				if (pDSpaceListTemp->pDSNode[i].pNext!=NULL)
				{
					p[i].pNext = &(p[(pDSpaceListTemp->pDSNode[i].pNext)->iPos]);//.............
				}

				else
				{
					p[i].pNext = NULL;
				}

				if (pDSpaceListTemp->pDSNode[i].pPre!=NULL)
				{
					p[i].pPre = &(p[(pDSpaceListTemp->pDSNode[i].pPre)->iPos]);
				}
				else
				{
					p[i].pPre = NULL;
				}


				p[i].pSpaceList = pDSpaceListTemp->pDSNode[i].pSpaceList;

				p[i].iFlag = pDSpaceListTemp->pDSNode[i].iFlag;

				p[i].iPos = i;
			}

			pDSpaceListTemp->DSNodeCount = iLen;

			free(pDSpaceListTemp->pDSNode);

			pDSpaceListTemp->pDSNode = p;



			/* ���³�ʼ����������Ӳ��ֵ����� */


			for (j=i;j<pDSpaceListTemp->DSNodeCount-1;j++)
			{
				pDSpaceListTemp->pDSNode[j].pSpaceList = NULL;
				pDSpaceListTemp->pDSNode[j].iFlag = 0;
				pDSpaceListTemp->pDSNode[j].pNext = &(pDSpaceListTemp->pDSNode[j+1]);
				pDSpaceListTemp->pDSNode[j].pPre = NULL;  //�ֲ���pPre  ��֪��Ҫ���к���
				pDSpaceListTemp->pDSNode[j].iPos = j;
			}

			//���ڵ�ĳ�ʼ��

			pDSpaceListTemp->pDSNode[j].pSpaceList = NULL;
			pDSpaceListTemp->pDSNode[j].pNext = NULL;
			pDSpaceListTemp->pDSNode[j].iFlag = 0;
			pDSpaceListTemp->pDSNode[j].pPre = NULL;
			pDSpaceListTemp->pDSNode[j].iPos = j;


			pDSpaceListTemp->pEmpty = &(pDSpaceListTemp->pDSNode[i]);  //���¶�λ
			//iDataCount ��ô���䣿����


		}


		//if pEmpty !=NULL
		//����

		pDSpaceNodeTemp = pDSpaceListTemp->pEmpty;

		pDSpaceListTemp->pEmpty = pDSpaceListTemp->pEmpty->pNext;

		//pDSpaceNodeTemp->pNext =NULL;//Ҫ��Ҫ?


		pDSpaceNodeTemp->pSpaceList = CreateSpaceList(pDSpaceListTemp->iDataCount,pDSpaceListTemp->iDataSize,pDSpaceNodeTemp->iPos);

		if (pDSpaceNodeTemp->pSpaceList!=NULL)
		{
			pDSpaceListTemp->iUsedDSNodeCount++;

			//���ýڵ���뵽����

			pDSpaceNodeTemp->pPre = NULL;

			pDSpaceNodeTemp->pNext = pDSpaceListTemp->pTail;  //???


			if (pDSpaceListTemp->pTail!=NULL)
			{
				pDSpaceListTemp->pTail->pNext = pDSpaceNodeTemp;
			}

			else
			{
				pDSpaceListTemp->pHead = pDSpaceNodeTemp;
			}

			pDSpaceListTemp->pTail = pDSpaceNodeTemp;

			pDSpaceNodeTemp->iFlag = 1;  //�ýڵ��Ѿ����뵽������

			pData = SpaceListAlloc(pDSpaceNodeTemp->pSpaceList);


		}


	}

	return pData;


}



//�ͷ��ڴ��Ƿǳ������ҪС�Ĵ���

void SpaceListFree(pSPACELIST& pSpaceListTemp,void* pData)
{

	pSPACENODE pSpaceNodeTemp = NULL;

	pSpaceNodeTemp = (pSPACENODE)((char*)pData-sizeof(pSPACENODE));


	pSpaceNodeTemp->pNext = pSpaceListTemp->pHead;

	pSpaceListTemp->pHead = pSpaceNodeTemp;

	pSpaceListTemp->uFreeCount++;
}


void DSpaceListFree(pDSPACELIST pDSpaceListTemp,void* pData)
{

	pSPACENODE pSpaceNodeTemp = (pSPACENODE)((char*)pData-sizeof(SPACENODE));

	pDSPACENODE pDSpaceNodeTemp = &(pDSpaceListTemp->pDSNode[pSpaceNodeTemp->iPos]);


	//�ж��Ƿ��ͷ������ڵ��ڴ�
	if (pDSpaceNodeTemp->pSpaceList->uFreeCount == pDSpaceListTemp->iDataCount)//�Ҳ�֪������ж���ʲô��˼ 
	{
		/* �ͷŴ˽ڵ�ָ��Ŀ��ÿռ�� */

		SpaceDestroy(pDSpaceNodeTemp->pSpaceList);

		pDSpaceNodeTemp->pSpaceList = NULL;


		//��˫��������ɾ��

		if (pDSpaceNodeTemp->pPre != NULL )
		{
			pDSpaceNodeTemp->pPre->pNext = pDSpaceNodeTemp->pNext;
		}
		if (pDSpaceNodeTemp->pNext != NULL )
		{
			pDSpaceNodeTemp->pNext->pPre = pDSpaceNodeTemp->pPre;
		}
		if (pDSpaceListTemp->pHead == pDSpaceNodeTemp)//  ����������Ĵ���  Ҫ��==
		{
			pDSpaceListTemp->pHead = pDSpaceNodeTemp->pNext;
		}
		if (pDSpaceListTemp->pTail == pDSpaceNodeTemp)
		{
			pDSpaceListTemp->pTail = pDSpaceNodeTemp->pPre;
		}


		//���ýڵ���ӵ�����pEmpty ��


		pDSpaceNodeTemp->pNext = pDSpaceListTemp->pEmpty;
		pDSpaceNodeTemp->pPre = NULL;
		pDSpaceNodeTemp->iFlag = 0;
		pDSpaceListTemp->pEmpty = pDSpaceNodeTemp;


		pDSpaceListTemp->iUsedDSNodeCount--;

	}
	else
	{
		SpaceListFree(pDSpaceNodeTemp->pSpaceList,pData);

		if (pDSpaceNodeTemp->iFlag==0)     //���ڵ�ȫ����ռ��ʱ�ǲ��������е�����Ҫ��ӻ�����
		{
			pDSpaceNodeTemp->pPre = pDSpaceListTemp->pTail;

			pDSpaceNodeTemp->pNext = NULL;


			if (pDSpaceListTemp->pTail!=NULL)
			{
				pDSpaceListTemp->pTail->pNext = pDSpaceNodeTemp;
			}
			else            //ֻ��һ���ڵ��ʱ��
			{
				pDSpaceListTemp->pHead = pDSpaceNodeTemp;
			}

			pDSpaceListTemp->pTail = pDSpaceNodeTemp;

			pDSpaceNodeTemp->iFlag = 1;
		}
	}
}