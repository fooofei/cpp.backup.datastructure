#include <stdio.h>
#include <malloc.h>
#include <windows.h>
typedef struct _SPACENODE_
{
	int iPos;					 //该结构是单项数组
	_SPACENODE_* pNext;
}SpaceNode,*pSpaceNode;

typedef struct _SPACDELIST_
{
	void* pBlock;					//一块连续内存
	int iCount;						//自由空间节点的个数
	pSpaceNode pHead;				//自由空间链表头部节点
}SpaceList,*pSpaceList;


pSpaceList CreateSpaceList(int nCount, int nDataSize)
{
		pSpaceList pSpaceListTemp = (pSpaceList)malloc(sizeof(SpaceList)+nCount*(sizeof(SpaceNode)+nDataSize));

		pSpaceNode pSpaceNodeTemp = NULL;

		if (pSpaceListTemp!=NULL)
		{
			pSpaceListTemp->iCount = nCount;

			pSpaceListTemp->pBlock = (void*)((BYTE*)pSpaceListTemp+sizeof(SpaceList));
											// char*  也可以

			pSpaceListTemp->pHead = (pSpaceNode) pSpaceListTemp->pBlock;

			pSpaceNodeTemp = pSpaceListTemp->pHead;
			
		}



		int i =0;
		for (i=0;i<nCount;i++)
		{
			pSpaceNodeTemp->iPos = i;

			if(i<nCount-1)     
			{
				pSpaceNodeTemp->pNext = (pSpaceNode)((BYTE*)pSpaceNodeTemp+sizeof(SpaceNode)+nDataSize);//总出错

				pSpaceNodeTemp = pSpaceNodeTemp->pNext;
			}
		
		}

		pSpaceNodeTemp->pNext = NULL;  //不要忘记 啊  忘记了对结果没有影响 只是最后一个结点比较难受 但是  总归是不完美的 

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
	// 	使用的时候  先使用第一块内存 依次向下   
// 		不使用内存  收回去的时候先收回去第一块内存 并且收内存使用了头插法  
	pSpaceNode pSpaceNodeNew = (pSpaceNode)((BYTE*)pData - sizeof(SpaceNode));

	pSpaceListTemp->iCount++;

	//方法一 插到头部  对内存使用不美观     此方法简单 

// 	pSpaceNodeNew->pNext = pSpaceListTemp->pHead;//头插法
// 
// 	pSpaceListTemp->pHead = pSpaceNodeNew;

	
	
	//方法二   插到尾部  恢复使用内存之前的现状

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