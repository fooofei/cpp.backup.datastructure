// 自己写的 没有测试
#include <stdio.h>
#include <WINDOWS.H>

typedef struct _BTNODE_
{
		int Data;
		_BTNODE_* pLNext;
		_BTNODE_* pRNext;
		_BTNODE_* pParent;
}BTNode,*pBTNode;

#define  QUEUESIZESTEP 5 // 队列长度每一步加和
#define  QUEUEDATA pBTNode  // 每次使用 需要更改的数据类型
class QUEUE
{
protected:

	int m_nBase;
	int m_nTop;
	int m_nQueueLen;
	int m_nQueueMAX;
	QUEUEDATA* m_pData;
public:

	BOOL InitQueue();
	BOOL EnQueue(QUEUEDATA Data);
	BOOL DeQueue(QUEUEDATA &Data);
	BOOL QueueIsEmpty();
	int GetQueueLen();
	BOOL DestroyQueue();
};

VOID CreateBiTree(pBTNode &pRoot,pBTNode pParent);
VOID PreOrderTraverse(pBTNode pRoot);
VOID InOrderTraverse(pBTNode pRoot);
VOID PosOrderTraverse(pBTNode pRoot);
VOID DestroyBiTree(pBTNode &pRoot);	
VOID LevelOrderTraverse(pBTNode pRoot);
BOOL  BiTreeEmpty(pBTNode pRoot);
int BiTreeDepth(pBTNode pRoot);
int GetRoot(pBTNode pRoot);
int GetValue(pBTNode pNodeTemp);
VOID Assign(pBTNode pNodeTemp,int iValue);
pBTNode GetPoint(pBTNode pRoot, int e);
int GetParent(pBTNode pRoot,int e);
int LeftChild(pBTNode pRoot, int e);
int RightChild(pBTNode pRoot, int e);
int LeftSibling(pBTNode pRoot, int e);
int RightSibling (pBTNode pRoot, int e);
VOID InsertChild(pBTNode pNodeInsert,BOOL LR,pBTNode pRootNew);
VOID DelChild(pBTNode pNodeDel,BOOL LR);
pBTNode NearestCommonAncestor(pBTNode p, pBTNode q);// 查找p，q的最近公共祖先并将其返回。

int main(int argc , char* argv[])
{

		pBTNode pRoot = NULL;

		CreateBiTree(pRoot,NULL);

		printf("PreOrderTraverse\n");
		PreOrderTraverse(pRoot);

		printf("\nInOrderTraverse\n");


		InOrderTraverse(pRoot);

		printf("\nPosOrderTraverse\n");

		PosOrderTraverse(pRoot);

		printf("\nLevelOrderTraverse\n");

		LevelOrderTraverse(pRoot);

		printf("\nDepth%d\n",BiTreeDepth(pRoot));

		DestroyBiTree(pRoot);
		return 0;
}


VOID CreateBiTree(pBTNode &pRoot,pBTNode pParent)
{
		TCHAR Data = 0;

		scanf(" %c",&Data);
		if (Data=='#')
		{
				pRoot = NULL;
		}

		else
		{
				if (NULL==(pRoot=(pBTNode)malloc(sizeof(BTNode))))
				{
						return;
				}

				memset(pRoot,0,sizeof(pBTNode));

				pRoot->Data = Data;

				pRoot->pParent = pParent;

				CreateBiTree(pRoot->pLNext,pRoot);

				CreateBiTree(pRoot->pRNext,pRoot);
		}
}//CreateBiTree

VOID PreOrderTraverse(pBTNode pRoot)
{
		if (pRoot)
		{
				printf("%c ",pRoot->Data);

				PreOrderTraverse(pRoot->pLNext);

				PreOrderTraverse(pRoot->pRNext);
		}

}// PreOrderTraverse

VOID InOrderTraverse(pBTNode pRoot)
{
		if (pRoot)
		{
				InOrderTraverse(pRoot->pLNext);

				printf("%c ",pRoot->Data);


				InOrderTraverse(pRoot->pRNext);
		}
}// InOrderTraverse

VOID PosOrderTraverse(pBTNode pRoot)
{
		if (pRoot)
		{
				PosOrderTraverse(pRoot->pLNext);

				PosOrderTraverse(pRoot->pRNext);

				printf("%c ",pRoot->Data);
		}
}// PosOrderTraverse
VOID DestroyBiTree(pBTNode &pRoot)
{
		if (pRoot)
		{
				DestroyBiTree(pRoot->pLNext);
				DestroyBiTree(pRoot->pRNext);

				free(pRoot);

				pRoot = NULL;
		}
}// DestroyBiTree		


VOID LevelOrderTraverse(pBTNode pRoot)
{
		if (!pRoot)
		{
				return ;
		}

		QUEUE Q;

		Q.InitQueue();

		Q.EnQueue(pRoot);

		while (!Q.QueueIsEmpty())
		{
				Q.DeQueue(pRoot);

				printf("%c ",pRoot->Data);

				if (pRoot->pLNext)
				{
						Q.EnQueue(pRoot->pLNext);
				}

				if (pRoot->pRNext)
				{
						Q.EnQueue(pRoot->pRNext);
				}
		}
		Q.DestroyQueue();
}// LevelOrderTraverse


BOOL  BiTreeEmpty(pBTNode pRoot)
{

		if (pRoot)
		{
				return FALSE;
		}
		return TRUE;
}// BiTreeEmpty

int BiTreeDepth(pBTNode pRoot)
{

		int i = 0;

		int j = 0;

		if (!pRoot)
		{
				return 0;
		}
		if (pRoot->pLNext)
		{
				i = BiTreeDepth(pRoot->pLNext);
		}

		if (pRoot->pRNext)
		{
				j = BiTreeDepth(pRoot->pRNext);
		}

		return i>j?i+1:j+1;
}// BiTreeDepth

int GetRoot(pBTNode pRoot)
{
		if (pRoot)
		{
				return pRoot->Data;
		}

		return '#';
}// GetRoot

int GetValue(pBTNode pNodeTemp)
{
		if (pNodeTemp)
		{
				return pNodeTemp->Data;
		}

		return '#';
}// GetValue

VOID Assign(pBTNode pNodeTemp,int iValue)
{
		if (pNodeTemp)
		{
				pNodeTemp->Data = iValue;
		}
}

pBTNode GetPoint(pBTNode pRoot, int e)
{
		if (!pRoot)
		{
				return NULL;
		}

		QUEUE Q;

		Q.InitQueue();

		Q.EnQueue(pRoot);

		while (!Q.QueueIsEmpty())
		{
				Q.DeQueue(pRoot);

				if (pRoot->Data==e)
				{
						Q.DestroyQueue();
						return pRoot;
				}

				if (pRoot->pLNext)
				{
						Q.EnQueue(pRoot->pLNext);
				}

				if (pRoot->pRNext)
				{
						Q.EnQueue(pRoot->pRNext);
				}
		}
		Q.DestroyQueue();
}// GetPoint

int GetParent(pBTNode pRoot,int e)
{
		if (pRoot&&GetPoint(pRoot,e)&&GetPoint(pRoot,e)->pParent)
		{
				return GetPoint(pRoot,e)->pParent->Data;
		}

		return '#';

}// GetPoint

int LeftChild(pBTNode pRoot, int e)
{
		if (pRoot&&GetPoint(pRoot,e)&&GetPoint(pRoot,e)->pLNext)
		{
				return	GetPoint(pRoot,e)->pLNext->Data;
		}

		return '#';
	
}// LeftChild

int RightChild(pBTNode pRoot, int e)
{
		if (pRoot&&GetPoint(pRoot,e)&&GetPoint(pRoot,e)->pRNext)
		{
				return GetPoint(pRoot,e)->pRNext->Data;
		}

		return '#';
}//RightChild

int LeftSibling(pBTNode pRoot, int e)
{
		if (pRoot&&GetPoint(pRoot,e)&&GetPoint(pRoot,e)!=pRoot&&GetPoint(pRoot,e)->pParent
				&&GetPoint(pRoot,e)->pParent->pLNext!=GetPoint(pRoot,e))
		{
				return GetPoint(pRoot,e)->pParent->pLNext->Data;
		}

		return '#';
}// LeftSibling

int RightSibling (pBTNode pRoot, int e)
{

		if (pRoot&&GetPoint(pRoot,e)&&GetPoint(pRoot,e)!=pRoot&&GetPoint(pRoot,e)->pParent
				&&GetPoint(pRoot,e)->pParent->pRNext!=GetPoint(pRoot,e))
		{
				return GetPoint(pRoot,e)->pParent->pRNext->Data;
		}

		return '#';
}// RightSibling


VOID InsertChild(pBTNode pNodeInsert,BOOL LR,pBTNode pRootNew)
{

		if (!pNodeInsert)
		{
				return;
		}

		if (!LR)
		{
				pRootNew->pRNext = pNodeInsert->pLNext;

				if (pNodeInsert->pLNext)
				{	
						pNodeInsert->pLNext->pParent = pRootNew;
				}
				pNodeInsert->pLNext = pRootNew;

				pRootNew->pParent = pNodeInsert;
		}

		else
		{
				pRootNew->pRNext = pNodeInsert->pRNext;

				if (pNodeInsert->pRNext)
				{
						pNodeInsert->pRNext->pParent = pRootNew;
				}


				pNodeInsert->pRNext = pRootNew;

				pRootNew->pParent = pNodeInsert;
		}

}// InsertChild


VOID DelChild(pBTNode pNodeDel,BOOL LR)
{

		if (!pNodeDel)
		{
				return;
		}
		if (!LR)
		{
				DestroyBiTree(pNodeDel->pLNext);
		}
		else
		{
				DestroyBiTree(pNodeDel->pRNext);
		}
}// DelChild



pBTNode NearestCommonAncestor(pBTNode p, pBTNode q)
{

  pBTNode pNodeTemp = NULL;

  while (p)
  {
    p = p->pParent;

    pNodeTemp = q;

    while (pNodeTemp)
    {
      if (p==pNodeTemp->pParent)
      {
        return p;
      }

      pNodeTemp = pNodeTemp->pParent;
    }
  }
}// NearestCommonAncestor
BOOL QUEUE::InitQueue()
{
	
	if (NULL==(m_pData = (QUEUEDATA*)malloc(sizeof(QUEUEDATA)*QUEUESIZESTEP)))
	{
		return FALSE;
	}

	memset(m_pData,0,sizeof(QUEUEDATA)*QUEUESIZESTEP);

	m_nTop = m_nBase = m_nQueueLen = 0;

	m_nQueueMAX = QUEUESIZESTEP;

	return TRUE;
}
BOOL QUEUE::EnQueue(QUEUEDATA Data)
{
	if (m_nTop==m_nQueueMAX-1)
	{
		
		if (NULL==(m_pData = (QUEUEDATA*)realloc(m_pData,sizeof(QUEUEDATA)*(m_nQueueMAX+QUEUESIZESTEP))))
		{
			return FALSE;
		}

		memset(&m_pData[m_nQueueMAX],0,sizeof(QUEUEDATA)*QUEUESIZESTEP);

		m_nQueueMAX += QUEUESIZESTEP;
	}

	m_pData[m_nTop++] = Data;

	++m_nQueueLen;

	return TRUE;
}
BOOL QUEUE::DeQueue(QUEUEDATA &Data)
{
	if (QueueIsEmpty())
	{
		Data = *(QUEUEDATA*)0;  // 这里可能需要更改  

		return FALSE;
	}

	Data = m_pData[m_nBase++];

	--m_nQueueLen;

	return TRUE;
}
BOOL QUEUE::QueueIsEmpty()
{
	if (m_nBase==m_nTop)
	{
		return TRUE;
	}

	return FALSE;
}
int QUEUE::GetQueueLen()
{
	return m_nQueueLen;
}
BOOL QUEUE::DestroyQueue()
{
	if (NULL==m_pData)
	{
		return FALSE;
	}

	free(m_pData);

	m_pData = NULL;

	m_nTop = m_nBase = m_nQueueMAX = 0 ;

	m_nQueueLen = -1;

	return TRUE;
}

