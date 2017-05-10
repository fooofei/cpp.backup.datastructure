#include <stdio.h>
#include <malloc.h>
#include <string.h>

//BYTE*   #include <windows.h>

typedef struct  _SPACENODE_            //该结构是单项数组
{
	int iPos;
	_SPACENODE_* pNext;
}SPACENODE,*pSPACENODE;              


typedef struct _SPACELIST_ {
	void*		 pBlock;			 /* 一块连续内存 */
	pSPACENODE   pHead;				 /* 自由空间链表头部节点 */
	int        uFreeCount;			 /* 自由空间节点的个数 */
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

	pDSPACENODE pDSNode;                      /* 用来管理可用空间表的DSPACENODE数组 */
	pDSPACENODE pEmpty;                       /* 可用空间表中没有被使用的节点链表表头 */
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

			if (i<iDataCount-1)//更改  加
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
			for (i=0;i<iDSNodeCount-1;i++)  //初始化第一节点  //
			{
				pDSpaceListTemp->pDSNode[i].pNext = &(pDSpaceListTemp->pDSNode[i+1]);

				// 也就是	pDSpaceListTemp->pDSNode[i].pNext = pDSpaceListTemp->pDSNode[i] + sizeof(DSPACENODE);

				pDSpaceListTemp->pDSNode[i].iPos = i;
			}


			for (i=1;i<iDSNodeCount;i++)    //初始化其他节点
			{
				pDSpaceListTemp->pDSNode[i].pPre = NULL; //没有赋予双向

				pDSpaceListTemp->pDSNode[i].pSpaceList = NULL;


				pDSpaceListTemp->pDSNode[i].iFlag = 0;
			}

			//初始化化最后一个节点

			pDSpaceListTemp->pDSNode[iDSNodeCount-1].pNext = NULL;

			pDSpaceListTemp->pDSNode[iDSNodeCount-1].iPos = iDSNodeCount-1;


			pDSpaceListTemp->pEmpty = &(pDSpaceListTemp->pDSNode[1]); // 不是 0??


			pDSpaceListTemp->pDSNode[0].pSpaceList = CreateSpaceList(iDataCount,iDataSize,0);

			//只在第一个节点进行了 申请内存
			//iPos 设置 0 
			if (pDSpaceListTemp->pDSNode[0].pSpaceList==NULL)
			{
				free(pDSpaceListTemp->pDSNode);

				free(pDSpaceListTemp);

				return NULL;
			}

			else  //将0元素插入到链表
			{
				pDSpaceListTemp->pHead = pDSpaceListTemp->pTail = &(pDSpaceListTemp->pDSNode[0]);

				pDSpaceListTemp->pHead->pPre = pDSpaceListTemp->pTail->pNext = NULL;


				pDSpaceListTemp->pDSNode[0].iFlag = 1;

				pDSpaceListTemp->iDataCount = iDataCount; //大结点记录了申请了所有能存数据的数目

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

		pDSpaceListTemp = NULL; //加
	}
}



void SpaceDestroy(pSPACELIST& pSpaceListTemp)
{
	if (pSpaceListTemp!=NULL)
	{
		free(pSpaceListTemp);

		pSpaceListTemp = NULL;//更改 加
	}

}

void* SpaceListAlloc(pSPACELIST& pSpaceListTemp)
{
	pSPACENODE pSpaceNodeTemp = NULL;


	pSpaceNodeTemp = pSpaceListTemp->pHead;


	if (pSpaceNodeTemp!=NULL)
	{
		pSpaceListTemp->pHead = pSpaceNodeTemp->pNext;

		pSpaceNodeTemp->pNext  = NULL;  //加

		pSpaceListTemp->uFreeCount--;

		return (void*)((char*)pSpaceNodeTemp+sizeof(SPACENODE));// 返回 uDataSize 地址
	}


	return NULL;
}

void* DSpaceListAlloc(pDSPACELIST& pDSpaceListTemp)
{

	int i = 0;

	void* pData = NULL;

	pDSPACENODE pDSpaceNodeTemp ;
	//   0 元素 
	pDSpaceNodeTemp = pDSpaceListTemp->pHead;       

	if (pDSpaceNodeTemp!=NULL)
	{
		pData = SpaceListAlloc(pDSpaceNodeTemp->pSpaceList);


		if (pDSpaceNodeTemp->pSpaceList->uFreeCount==0)     /* 头部节点指向的可用空间表已没有自由空间，将头部节点弹出 */
		{
			pDSpaceListTemp->pHead = pDSpaceNodeTemp->pNext;  //pDSpaceNodeTemp  不要了 也不释放  奇怪  

			if (pDSpaceListTemp->pHead!=NULL)
			{
				pDSpaceListTemp->pHead->pPre = NULL;         //如何处理都行
			}
			
			// pTail 没有管   更改  加  
			else //pTail==NULL
			{
				pDSpaceListTemp->pTail = NULL;
			}
			pDSpaceNodeTemp->iFlag = 0;
		}


	}

	else
	{
		//重新分配  (先查找后分配)


		if (pDSpaceListTemp->pEmpty==NULL)
		{
			int j = 0;

			//扩大内存
			int iLen = 2* pDSpaceListTemp->DSNodeCount;
			pDSPACENODE p = NULL;


			p = (pDSPACENODE)malloc(sizeof(DSPACENODE)*iLen);


			if (p==NULL)
			{
				return NULL;
			}

			//将数据拷贝新的内存中

			for (i=0;i<pDSpaceListTemp->DSNodeCount;i++)
			{

				//注意这里的算法不难有点晕看图
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



			/* 重新初始化扩大后增加部分的数据 */


			for (j=i;j<pDSpaceListTemp->DSNodeCount-1;j++)
			{
				pDSpaceListTemp->pDSNode[j].pSpaceList = NULL;
				pDSpaceListTemp->pDSNode[j].iFlag = 0;
				pDSpaceListTemp->pDSNode[j].pNext = &(pDSpaceListTemp->pDSNode[j+1]);
				pDSpaceListTemp->pDSNode[j].pPre = NULL;  //又不用pPre  不知道要他有何用
				pDSpaceListTemp->pDSNode[j].iPos = j;
			}

			//最后节点的初始化

			pDSpaceListTemp->pDSNode[j].pSpaceList = NULL;
			pDSpaceListTemp->pDSNode[j].pNext = NULL;
			pDSpaceListTemp->pDSNode[j].iFlag = 0;
			pDSpaceListTemp->pDSNode[j].pPre = NULL;
			pDSpaceListTemp->pDSNode[j].iPos = j;


			pDSpaceListTemp->pEmpty = &(pDSpaceListTemp->pDSNode[i]);  //重新定位
			//iDataCount 怎么不变？？？


		}


		//if pEmpty !=NULL
		//查找

		pDSpaceNodeTemp = pDSpaceListTemp->pEmpty;

		pDSpaceListTemp->pEmpty = pDSpaceListTemp->pEmpty->pNext;

		//pDSpaceNodeTemp->pNext =NULL;//要不要?


		pDSpaceNodeTemp->pSpaceList = CreateSpaceList(pDSpaceListTemp->iDataCount,pDSpaceListTemp->iDataSize,pDSpaceNodeTemp->iPos);

		if (pDSpaceNodeTemp->pSpaceList!=NULL)
		{
			pDSpaceListTemp->iUsedDSNodeCount++;

			//将该节点插入到链表

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

			pDSpaceNodeTemp->iFlag = 1;  //该节点已经插入到链表中

			pData = SpaceListAlloc(pDSpaceNodeTemp->pSpaceList);


		}


	}

	return pData;


}



//释放内存是非常经典的要小心处理

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


	//判断是否释放整个节点内存
	if (pDSpaceNodeTemp->pSpaceList->uFreeCount == pDSpaceListTemp->iDataCount)//我不知道这个判断是什么意思 
	{
		/* 释放此节点指向的可用空间表 */

		SpaceDestroy(pDSpaceNodeTemp->pSpaceList);

		pDSpaceNodeTemp->pSpaceList = NULL;


		//从双向链表中删除

		if (pDSpaceNodeTemp->pPre != NULL )
		{
			pDSpaceNodeTemp->pPre->pNext = pDSpaceNodeTemp->pNext;
		}
		if (pDSpaceNodeTemp->pNext != NULL )
		{
			pDSpaceNodeTemp->pNext->pPre = pDSpaceNodeTemp->pPre;
		}
		if (pDSpaceListTemp->pHead == pDSpaceNodeTemp)//  哥这里是真的错了  要用==
		{
			pDSpaceListTemp->pHead = pDSpaceNodeTemp->pNext;
		}
		if (pDSpaceListTemp->pTail == pDSpaceNodeTemp)
		{
			pDSpaceListTemp->pTail = pDSpaceNodeTemp->pPre;
		}


		//将该节点添加到我们pEmpty 中


		pDSpaceNodeTemp->pNext = pDSpaceListTemp->pEmpty;
		pDSpaceNodeTemp->pPre = NULL;
		pDSpaceNodeTemp->iFlag = 0;
		pDSpaceListTemp->pEmpty = pDSpaceNodeTemp;


		pDSpaceListTemp->iUsedDSNodeCount--;

	}
	else
	{
		SpaceListFree(pDSpaceNodeTemp->pSpaceList,pData);

		if (pDSpaceNodeTemp->iFlag==0)     //当节点全部被占满时是不在链表中的所以要添加回链表
		{
			pDSpaceNodeTemp->pPre = pDSpaceListTemp->pTail;

			pDSpaceNodeTemp->pNext = NULL;


			if (pDSpaceListTemp->pTail!=NULL)
			{
				pDSpaceListTemp->pTail->pNext = pDSpaceNodeTemp;
			}
			else            //只有一个节点的时候
			{
				pDSpaceListTemp->pHead = pDSpaceNodeTemp;
			}

			pDSpaceListTemp->pTail = pDSpaceNodeTemp;

			pDSpaceNodeTemp->iFlag = 1;
		}
	}
}