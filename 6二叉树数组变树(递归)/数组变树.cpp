#include <STDIO.H>
#include <WINDOWS.H>
#define  ARRARSIZE 8
typedef struct _BTNODE_
{
		int Data;

		_BTNODE_* pLNext;
		_BTNODE_* pRNext;
}BTNode,*pBTNode;

VOID CreateBiTree(pBTNode &pRoot, int *T, int iIndex)
{
		pRoot = (pBTNode)malloc(sizeof(BTNode));

		memset(pRoot,0,sizeof(BTNode));

		pRoot->Data = T[iIndex];

		if (2*iIndex<ARRARSIZE)
		{
				CreateBiTree(pRoot->pLNext,T,2*iIndex);
		}

		if (2*iIndex+1<ARRARSIZE)
		{
				CreateBiTree(pRoot->pRNext,T,2*iIndex+1);
		}
}

VOID PreOrderTraverse(pBTNode pRoot)
{
		if (pRoot)
		{
				printf("%d ",pRoot->Data);
				PreOrderTraverse(pRoot->pLNext);
				PreOrderTraverse(pRoot->pRNext);
		}
}


VOID DestroyBiTree(pBTNode& pRoot)
{
		if (pRoot)
		{
				if (pRoot->pLNext)
				{
						DestroyBiTree(pRoot->pLNext);
				}
				if (pRoot->pRNext)
				{
						DestroyBiTree(pRoot->pRNext);
				}

				free(pRoot);

				pRoot = NULL;
		}
}


int main()
{
		int a[ARRARSIZE] = {0,1,2,3,4,5,6,7};

		pBTNode pRoot = NULL;

		CreateBiTree(pRoot,a,1);

		PreOrderTraverse(pRoot);

		DestroyBiTree(pRoot);

		return 0;
}