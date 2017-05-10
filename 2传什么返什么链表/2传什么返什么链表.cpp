//强调返回值的链表

#include <iostream>
using namespace std;

typedef struct tagNODE
{
	int data;
	tagNODE* pNext;

}NODE,*PNODE;

PNODE  CreateNode(PNODE pNodeTemp);

void TravelAndFreeList(PNODE* ppHead);


int main()
{
	try{
		PNODE pNodeFirst = new NODE;
		printf("在此键入数据:");
		cin>>pNodeFirst->data;

		pNodeFirst->pNext =	NULL;
		PNODE pHead = pNodeFirst;


		int i = 0;
		for (i=0;i<3 && (NULL != pNodeFirst);i++)
		{
			pNodeFirst = CreateNode(pNodeFirst);
		}

		TravelAndFreeList(&pHead);
		return 0;
	}catch(bad_alloc&){
		
	}
	
}

void TravelAndFreeList(PNODE* ppHead)
{
	PNODE pNodeTemp = *ppHead;
	while (pNodeTemp!=NULL)
	{
		printf("%d ",pNodeTemp->data);
		
		pNodeTemp = pNodeTemp->pNext;

		delete *ppHead;
		*ppHead = pNodeTemp;
	}
	printf("\n");
}

PNODE  CreateNode(PNODE pNodeTemp) 
{
	try{
		pNodeTemp->pNext = new NODE;
		pNodeTemp->pNext->pNext=NULL;

		cout<<"在此键入数据:";
		cin>>pNodeTemp->pNext->data;

		return pNodeTemp->pNext;
	}catch(bad_alloc&){
		return NULL;
	}
	
	
}