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
	int index;// ��TArray �е�����
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
	pRoot = (TNode*)malloc(sizeof(TNode));// �������ڵ�

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
		
		if (pTemp->a==a)// ���ҵ� a  �Ľڵ� 
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

	// Ȼ��� A �ڵ� ������ �� A �ڵ� �ĸ��ڵ� �� �� �� ��α��� ����� �ҵ� b �ʹ�ӡ A �ĸ��ڵ�
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
	int a[4] = {1,2,3,4};// ���е�Ҷ�ӽڵ�// ������ ֻ�����������
	
	int m = 2*4 -1;// �������нڵ����

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
	
	i = 0;// ���Ӷ�Ӧ����
	int j = 1;// �Һ��Ӷ�Ӧ����
	for (int k=4;k<m;k++)
	{
		TArray[k].a = TArray[i].a + TArray[j].a;// ���ڵ������ �� ����������ӵĽ��

		TArray[k].left = i;
		TArray[k].right = j;

		TArray[i].parent = k;
		TArray[j].parent = k;
		
		i += 2;
		j += 2;		
	}

	// �� TArray ��� ���� 

	CreateTree(pRoot,TArray,m);

	// �ҹ�ͬ���ڵ�
	FindFather(pRoot);
}