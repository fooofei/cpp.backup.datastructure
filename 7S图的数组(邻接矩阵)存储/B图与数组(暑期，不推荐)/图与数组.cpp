#include <stdio.h>
#include <malloc.h>

#define  SIZE 4


//����һ����λ����ȥ�����ڴ�

int V[SIZE][SIZE] ={{0,1,0,1},{1,1,1,0},{0,1,0,1},{1,1,0,0}};

//����һ���ַ�����

char S[SIZE] = {'A','B','C','D'};

//�����ڴ�Ľṹ��
typedef struct _NODE_
{
	int Index;
	_NODE_* pNext;

}Node,*pNode;




//������б����ַ�ֵ��Ľṹ��

typedef struct _HEADNODE_
{
	char Val;
	pNode pHead;

}HeadNode,*pHeadNode;


pHeadNode ApplyMemory();

void TravelGraphic(pHeadNode p);

void main()
{
	pHeadNode p = NULL;
	p = ApplyMemory();

	TravelGraphic(p);
}



pHeadNode ApplyMemory()
{
	pHeadNode p = (pHeadNode)malloc(sizeof(HeadNode)*SIZE);


	int i = 0;

	int j = 0;

	//����һ��ͷ����һ��β�ڵ�
	pNode pNew = NULL;
	pNode pTail = NULL;
	for (i=0;i<SIZE;i++)
	{
		//���и�ֵ
		(p+i)->Val = S[i];

		(p+i)->pHead = NULL;

		for (j=0;j<SIZE;j++)
		{
			if (V[i][j]==1)
			{
				if ((p+i)->pHead==NULL)
				{
					(p+i)->pHead = (pNode)malloc(sizeof(Node));

					if ((p+i)->pHead==NULL)
					{
						return NULL;
					}

					else
					{
						(p+i)->pHead->Index = j;
						(p+i)->pHead->pNext = NULL;

						pTail = (p+i)->pHead;
					}
				}

				else
				{
						pNew = (pNode)malloc(sizeof(Node));

						if (pNew==NULL)
						{
							return NULL;
						}

					
						pNew->pNext = NULL;
						
						pTail->pNext = pNew;

						pTail = pNew;

						pNew->Index = j;
						
				}
			}
		}
	}



	return p;


}


void TravelGraphic(pHeadNode p)
{
	int i = 0;
	for (i=0;i<SIZE;i++)
	{
		printf("%c ->",(p+i)->Val);

		pNode pTemp = (p+i)->pHead;
		while (pTemp!=NULL)
		{
			printf("%d",pTemp->Index);

			if (pTemp->pNext!=NULL)
			{
				printf(" ->");
			}

			pTemp = pTemp->pNext;
		}

		printf("\n");
	}
}

// A ->1 ->3
// B ->0 ->1 ->2
// C ->1 ->3
// D ->0 ->1
// Press any key to continue

