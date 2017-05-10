#include <iostream.h>
#include <malloc.h>
#include <windows.h>
#include <AFXTEMPL.H>
typedef struct _NODE_ 
{
	void* pData;
	_NODE_* pNext;
}Node,*pNode;


typedef struct BLOCK_LIST 
{
	void* pBlock;      //�����ڴ�
	pNode pNodeEmpty;  //���ɿռ�����ͷָ��
	pNode pHead;       //����ͷָ��
	UINT uDataSize;    //���ݸ���
	UINT uMaxDataCount; //������ݽڵ����

	UINT uFreeCount;    //���ɿռ�ڵ�����
}BlockList,*pBlockList;



pBlockList BlockListCreate(UINT uDataSize,UINT uMaxDataCount);
void BlockListDestroy(pBlockList& pBlockListTemp);
int BlockListInsertHead(pBlockList pBlockListTemp,void* pData,UINT uDataLen);
void BlockListFree(pBlockList pBlockListTemp,void* pData);
int BlockListDelHead(pBlockList pBlockListTemp);
void* BlockListAlloc(pBlockList pBlockListTemp);

int main()
{

	pBlockList pBlockListNew = BlockListCreate(20,2);

	ASSERT(pBlockListNew!=NULL);

//	pNode pNodeNew =(pNode) BlockListAlloc(pBlockListNew);

//	strcpy((char*)pNodeNew->pData,"Hello");

//	BlockListFree(pBlockListNew,pNodeNew); // �Żص� pNodeEmpty   ��BlockListDelHead �������ܲ��

	//�����ڴ� 


	//һ�����


 	BlockListInsertHead( pBlockListNew,"World",6);
 
 	BlockListDelHead(pBlockListNew);
	


	BlockListDestroy(pBlockListNew);

    return 0;
}


pBlockList BlockListCreate(UINT uDataSize,UINT uMaxDataCount)
{
	pBlockList pBlockListTemp = NULL;

	pNode pNodeTemp = NULL;

	int i = 0;
															// 2		//20
	pBlockListTemp = (pBlockList)malloc(sizeof(BlockList)+uMaxDataCount*(uDataSize+sizeof(Node)));


	if (pBlockListTemp!=NULL)
	{
		pBlockListTemp->pBlock = (void*)((char*)pBlockListTemp+sizeof(BLOCK_LIST));
	}

	//����������

	pBlockListTemp->pNodeEmpty = (pNode)pBlockListTemp->pBlock;


	pNodeTemp = pBlockListTemp->pNodeEmpty;



// 	for (i=0;i<uMaxDataCount-1;i++)
// 	{
// 		pNodeTemp->pNext = (pNode)((char*)pNodeTemp+sizeof(Node)+uDataSize);
// 
// 		pNodeTemp = pNodeTemp->pNext;         //˵��һ��  ������Ŀ¼�� �ڴ�ͼ ����֪��  ���uDataSize���׵�ַ��ŵ�
// 												//pNodeTemp->pData �ͺܺ�   ��֪��Ϊʲô������  ����ʹ�õ�ʱ��Ҳ���� ������Ѱ�ҵ�ַ 
// 												//��Ȼ������  �Ϳ��Žṹ��͹̶����ǵ� 
// 												//���ǵ���Ҫ���ϵ�ʱ�� ���� ���forѭ����ִ��һ��  
// 												//����  ����Ϊ����Ĵ���
// 	}


	for (i=0;i<uMaxDataCount;i++)
	{
		pNodeTemp->pData = (void*)((BYTE*)pNodeTemp+sizeof(Node));
		if (i<uMaxDataCount-1)
		{
			pNodeTemp->pNext = (pNode)((char*)pNodeTemp+sizeof(Node)+uDataSize);
			
			pNodeTemp = pNodeTemp->pNext;
		}
	}

	pNodeTemp->pNext = NULL;


	pBlockListTemp->pHead = NULL;

	pBlockListTemp->uMaxDataCount = uMaxDataCount;

	pBlockListTemp->uDataSize = uDataSize;

	pBlockListTemp->uFreeCount = uMaxDataCount;


	return pBlockListTemp;

}


void BlockListDestroy(pBlockList& pBlockListTemp)
{
	if (pBlockListTemp!=NULL)
	{
		free(pBlockListTemp);

		pBlockListTemp = NULL; //���� 
	}
}
												
												//ʹ�õ��ڴ��ַ��������Node�� //���ݵĴ�С
int BlockListInsertHead(pBlockList pBlockListTemp,void* pData,UINT uDataLen)
{
	pNode pNodeTemp = NULL;

	if (uDataLen>pBlockListTemp->uDataSize)
	{
		return -1;
	}

	pNodeTemp = pBlockListTemp->pNodeEmpty;  //ʹ���ڴ�

	if (pNodeTemp!=NULL)
	{
		pBlockListTemp->pNodeEmpty = pNodeTemp->pNext;
	}
	else
	{
		return -1;
	}

	//���԰�  pNodeTemp->pData  ����������ڴ棿���������Ҽ��ϵ�   Or 	pNodeTemp->pData = pData;
	memcpy(pNodeTemp->pData,pData,uDataLen);




	
	pNodeTemp->pNext = pBlockListTemp->pHead;  //��������ô��Ϥ��ͷ�巨

	
	pBlockListTemp->pHead = pNodeTemp;

	pBlockListTemp->uFreeCount--;


	return 1;  //����Ϊ 1
}


int BlockListDelHead(pBlockList pBlockListTemp)
{
	pNode pNodeTemp = NULL;

	if (pBlockListTemp==NULL||pBlockListTemp->pHead==NULL)
	{
		return -1;
	}

	pNodeTemp = pBlockListTemp->pHead;

	pBlockListTemp->pHead = pBlockListTemp->pHead->pNext;


	pNodeTemp->pNext = pBlockListTemp->pNodeEmpty; //�Żؿ���������ͷ�巨

	pBlockListTemp->pNodeEmpty = pNodeTemp;

	pBlockListTemp->uFreeCount++;

	return 1;
}


void* BlockListAlloc(pBlockList pBlockListTemp)
{
	pNode pNodeTemp = NULL;

	pNodeTemp = pBlockListTemp->pNodeEmpty;

	if (pNodeTemp!=NULL)
	{
		pBlockListTemp->pNodeEmpty = pNodeTemp->pNext;

		pBlockListTemp->uFreeCount--;

		pNodeTemp->pNext = NULL;//Ϊ�˰�ȫ����  ���� 

		return (void*)pNodeTemp; //���صĵ�ַ��  Node �ĵ�ַ
	}

	return NULL;
}


void BlockListFree(pBlockList pBlockListTemp,void* pData)
{
	pNode pNodeTemp = NULL;

	pNodeTemp = (pNode)pData;   //С������

	pNodeTemp->pNext = pBlockListTemp->pNodeEmpty;  //ͷ�巨 ���ȥ

	pBlockListTemp->pNodeEmpty = pNodeTemp;

	pBlockListTemp->uFreeCount++;
}