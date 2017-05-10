

#include <stdio.h>
#include <queue>
#include <malloc.H>

typedef struct tagBTNODE
{
	int iData;
	tagBTNODE* pLeft;
	tagBTNODE* pRight;
}BTNODE,*PBTNODE;

void CreateBiTree(PBTNODE &pRoot)
{
	int iData = 0;
	scanf_s(" %c",&iData);

	if (iData=='#')
	{
		pRoot = NULL;
	}

	else
	{
		if(NULL==(pRoot = (PBTNODE)malloc(sizeof(BTNODE))))
		{
			return ;
		}

		memset(pRoot,0,sizeof(BTNODE));

		pRoot->iData = iData;

		CreateBiTree(pRoot->pLeft);

		CreateBiTree(pRoot->pRight);
	}
}// CreateBiTree

void DestroyBiTree(PBTNODE &pRoot)
{
	if (NULL != pRoot)
	{
		DestroyBiTree(pRoot->pLeft);

		DestroyBiTree(pRoot->pRight);

		free(pRoot);

		pRoot = NULL;
	}
}// DestroyBiTree

bool IsComplateBiTree(PBTNODE pRoot) // 如何判断是否是完全二叉树呢  广度优先遍历
{
	if(NULL == pRoot)
	{
		return true;
	}

	std::queue<PBTNODE> Q;
	Q.push(pRoot);
	while(!Q.empty())
	{
		pRoot = Q.front();
		Q.pop();

		if(NULL == pRoot)
		{
			while(!Q.empty())
			{
				pRoot = Q.front();
				Q.pop();
				if(NULL != pRoot)
				{
					return false;
				}
			}

			return true;
		}
		else
		{
			Q.push(pRoot->pLeft);
			Q.push(pRoot->pRight);
		}

	}

	return true;
}// IsComplateTree

void PreOrderTraverse(PBTNODE pRoot)
{
	if(NULL != pRoot)
	{
		printf("%c ",pRoot->iData);

		PreOrderTraverse(pRoot->pLeft);

		PreOrderTraverse(pRoot->pRight);
	}
}// PreOrderTraverse

int main(int argc, char* argv[])
{

	PBTNODE pRoot = NULL;

	CreateBiTree(pRoot);

	PreOrderTraverse(pRoot);

	printf("\nComplateBiTree %d \n",IsComplateBiTree(pRoot));

	DestroyBiTree(pRoot);
	return 0;
}

