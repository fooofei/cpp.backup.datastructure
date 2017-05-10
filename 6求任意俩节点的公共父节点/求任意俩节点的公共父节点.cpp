#include <windows.h>
#include <stdio.h>

#define MAX_QUEUE_SIZE	20

struct ANode
{
	int a;
	int left;
	int right;
	int parent;
};

struct TNode
{
	int a;
	int index;// 在TArray 中的索引
	TNode* pParent;
	TNode* pLeft;
	TNode* pRight;
};

TNode* pRoot;

struct MQueue
{
	int Front;
	int Rear;
}one;

TNode* queueData[MAX_QUEUE_SIZE];

void InitQueue()
{
	one.Front = one.Rear = -1;
}

void InQueue(TNode* pTemp)
{
	queueData[++one.Front%MAX_QUEUE_SIZE] = pTemp;
}

TNode* OutQueue()
{
	return queueData[++one.Rear%MAX_QUEUE_SIZE];
}



void CreateTree(TNode*& pRoot,ANode a[],int m)
{
	pRoot = (TNode*)malloc(sizeof(TNode));// 创建根节点

	pRoot->a = a[m-1].a;

	pRoot->index = m-1;

	pRoot->pParent = NULL;
	pRoot->pLeft = NULL;
	pRoot->pRight = NULL;

	InitQueue();

	InQueue(pRoot);

	while (one.Front!=one.Rear)
	{
		TNode* pTemp = OutQueue();

		if (a[pTemp->index].left!=-1)
		{
			int index = a[pTemp->index].left;

			TNode* pLeft = (TNode*)malloc(sizeof(TNode));

			pLeft->a = a[index].a;
			pLeft->index = index;
			pLeft->pParent = pTemp;
			pLeft->pLeft = pLeft->pRight = NULL;

			pTemp->pLeft = pLeft;

			InQueue(pLeft);
		}

		if (a[pTemp->index].right!=-1)
		{
			int index = a[pTemp->index].right;

			TNode* pRight = (TNode*)malloc(sizeof(TNode));

			pRight->a = a[index].a;
			pRight->pParent = pTemp;
			pRight->index = index;
			pRight->pLeft = pRight->pRight = NULL;

			pTemp->pRight = pRight;

			InQueue(pRight);
		}
	}
}

void FindFather(TNode* pRoot)
{
	int a = 0;
	int b = 0;

	scanf("%d%d",&a,&b);

	InitQueue();

	InQueue(pRoot);

	TNode* pTemp;

	while (one.Front!=one.Rear)
	{
		pTemp = OutQueue();
		
		if (pTemp->a==a)// 先找到 a  的节点 
		{
			break;
		}
		
		if (pTemp->pLeft!=NULL)
		{
			InQueue(pTemp->pLeft);
		}
		if (pTemp->pRight!=NULL)
		{
			InQueue(pTemp->pRight);
		}
	}

	// 然后从 A 节点 往上找 把 A 节点 的父节点 当 根 来 层次遍历 这个树 找到 b 就打印 A 的父节点
	TNode* pFather = pTemp->pParent;


	while (pFather!=NULL)
	{
		InitQueue();
		
		InQueue(pFather);
		
		while (one.Front!=one.Rear)
		{
			pTemp = OutQueue();

			if (pTemp!=pFather&&pTemp->a==b)
			{
				printf("%d\n",pFather->a);

				return;
			}

			if (pTemp->pLeft!=NULL)
			{
				InQueue(pTemp->pLeft);
			}
			if (pTemp->pRight!=NULL)
			{
				InQueue(pTemp->pRight);
			}
		}
		pFather = pFather->pParent;
	}
}

void main()
{
	int a[4] = {1,2,3,4};// 所有的叶子节点// 本程序 只针对满二叉树
	
	int m = 2*4 -1;// 树的所有节点个数

	ANode* TArray = (ANode*)malloc(sizeof(ANode)*m);

	for (int i=0;i<4;i++)
	{
		TArray[i].a = a[i];
	}

	for (i=0;i<m;i++)
	{
		TArray[i].left = -1;
		TArray[i].parent = -1;
		TArray[i].right = -1;
	}
	
	i = 0;// 左孩子对应索引
	int j = 1;// 右孩子对应索引
	for (int k=4;k<m;k++)
	{
		TArray[k].a = TArray[i].a + TArray[j].a;// 父节点的数据 是 俩个孩子相加的结果

		TArray[k].left = i;
		TArray[k].right = j;

		TArray[i].parent = k;
		TArray[j].parent = k;
		
		i += 2;
		j += 2;		
	}

	// 将 TArray 变成 链树 

	CreateTree(pRoot,TArray,m);

	// 找共同父节点
	FindFather(pRoot);
}