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
	void* pBlock;      //整块内存
	pNode pNodeEmpty;  //自由空间链表头指针
	pNode pHead;       //链表头指针
	UINT uDataSize;    //数据个数
	UINT uMaxDataCount; //最大数据节点个数

	UINT uFreeCount;    //自由空间节点数量
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

//	BlockListFree(pBlockListNew,pNodeNew); // 放回到 pNodeEmpty   跟BlockListDelHead 函数功能差不多

	//调试内存 


	//一组测试


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

	//建立空链表

	pBlockListTemp->pNodeEmpty = (pNode)pBlockListTemp->pBlock;


	pNodeTemp = pBlockListTemp->pNodeEmpty;



// 	for (i=0;i<uMaxDataCount-1;i++)
// 	{
// 		pNodeTemp->pNext = (pNode)((char*)pNodeTemp+sizeof(Node)+uDataSize);
// 
// 		pNodeTemp = pNodeTemp->pNext;         //说明一下  看工程目录的 内存图 可以知道  这个uDataSize的首地址存放到
// 												//pNodeTemp->pData 就很好   不知道为什么不加上  这样使用的时候也方便 不用再寻找地址 
// 												//当然加上了  就看着结构体就固定了是的 
// 												//但是当我要加上的时候 发现 这个for循环少执行一次  
// 												//于是  更改为下面的代码
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

		pBlockListTemp = NULL; //加上 
	}
}
												
												//使用的内存地址（不包括Node） //数据的大小
int BlockListInsertHead(pBlockList pBlockListTemp,void* pData,UINT uDataLen)
{
	pNode pNodeTemp = NULL;

	if (uDataLen>pBlockListTemp->uDataSize)
	{
		return -1;
	}

	pNodeTemp = pBlockListTemp->pNodeEmpty;  //使用内存

	if (pNodeTemp!=NULL)
	{
		pBlockListTemp->pNodeEmpty = pNodeTemp->pNext;
	}
	else
	{
		return -1;
	}

	//不对啊  pNodeTemp->pData  在哪申请的内存？？还不是我加上的   Or 	pNodeTemp->pData = pData;
	memcpy(pNodeTemp->pData,pData,uDataLen);




	
	pNodeTemp->pNext = pBlockListTemp->pHead;  //依旧是那么熟悉的头插法

	
	pBlockListTemp->pHead = pNodeTemp;

	pBlockListTemp->uFreeCount--;


	return 1;  //更改为 1
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


	pNodeTemp->pNext = pBlockListTemp->pNodeEmpty; //放回空闲链表还是头插法

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

		pNodeTemp->pNext = NULL;//为了安全美观  加上 

		return (void*)pNodeTemp; //返回的地址是  Node 的地址
	}

	return NULL;
}


void BlockListFree(pBlockList pBlockListTemp,void* pData)
{
	pNode pNodeTemp = NULL;

	pNodeTemp = (pNode)pData;   //小心陷阱

	pNodeTemp->pNext = pBlockListTemp->pNodeEmpty;  //头插法 插回去

	pBlockListTemp->pNodeEmpty = pNodeTemp;

	pBlockListTemp->uFreeCount++;
}