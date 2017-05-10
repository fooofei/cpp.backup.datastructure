#include <iostream>
#include <windows.h>
using namespace std;


typedef struct _BITREE_
{
	int Data;
	_BITREE_* pLNext;
	_BITREE_* pRNext;
}BiTree,*pBiTree;

void DestroyBiTree(pBiTree &pBiTreeTemp);
void InsertBiTree(pBiTree &pBiTreeTemp, int Data );
void DelBiTree(pBiTree &pBiTreeTemp,int Data);
void DelBiTreeNode(pBiTree &pBiTreeTemp);
void TravelTree(pBiTree pBiTreeTemp);
void DelBiTreeNode(pBiTree &pBiTreeTemp);


int main()
{
	pBiTree pBiTreeTemp = NULL;
	int Data[5] = {1,2,3,4,5};

	int i = 0;
	for(i=0;i<5;i++)
	{
		InsertBiTree(pBiTreeTemp,Data[i]);


	}

	TravelTree(pBiTreeTemp);

	cout<<endl;

	DelBiTree(pBiTreeTemp,4);

	TravelTree(pBiTreeTemp);

	cout<<endl;

	DestroyBiTree(pBiTreeTemp);
}



void DestroyBiTree(pBiTree &pBiTreeTemp)
{
	if(pBiTreeTemp!=NULL)
	{
		DestroyBiTree(pBiTreeTemp->pLNext);

		DestroyBiTree(pBiTreeTemp->pRNext);

		delete pBiTreeTemp ;

		pBiTreeTemp = NULL;
	}
}


void SearchBiTreeNode(pBiTree &pBiTreeTemp ,int Data ,pBiTree pBiTreeFather,pBiTree &pBiTreeNew, bool &Flag)
{
	if(pBiTreeTemp==NULL)
	{
		pBiTreeNew = pBiTreeFather;

		Flag = false;
	}

	else if(pBiTreeTemp->Data ==  Data)
	{
		pBiTreeNew = pBiTreeTemp;

		Flag = true;
	}
	else if(pBiTreeTemp ->Data>Data)
	{
		SearchBiTreeNode(pBiTreeTemp->pLNext,Data,pBiTreeTemp,pBiTreeNew,Flag);
	}

	else
	{
		SearchBiTreeNode(pBiTreeTemp->pRNext,Data,pBiTreeTemp,pBiTreeNew,Flag);
	}
}

void InsertBiTree(pBiTree &pBiTreeTemp, int Data )
{


	bool Flag;

	pBiTree pBiTreeFather = NULL;

	SearchBiTreeNode(pBiTreeTemp,Data,NULL,pBiTreeFather,Flag);

	if(Flag==false)
	{
		pBiTree pBiTreeNew = new BiTree;

		pBiTreeNew->Data = Data;

		pBiTreeNew->pLNext = pBiTreeNew->pRNext = NULL;

		if(pBiTreeTemp == NULL)
		{
			pBiTreeTemp = pBiTreeNew;
		}

		else
		{
			if(pBiTreeFather->Data>Data)
			{
				pBiTreeFather->pLNext = pBiTreeNew;
			}
			else
			{
				pBiTreeFather->pRNext = pBiTreeNew ;
			}
		}
	}
}


void DelBiTree(pBiTree &pBiTreeTemp,int Data)
{
	if(pBiTreeTemp!=NULL)
	{
		if(pBiTreeTemp->Data== Data)
		{
			DelBiTreeNode(pBiTreeTemp);
		}

		else if(pBiTreeTemp->Data > Data)
		{
			DelBiTree(pBiTreeTemp->pLNext,Data);
		}

		else
		{
			DelBiTree(pBiTreeTemp->pRNext,Data);
		}
	}
}


void DelBiTreeNode(pBiTree &pBiTreeTemp)
{

	pBiTree pBiTreeCur = NULL;

	if(pBiTreeTemp->pRNext==NULL)
	{
		pBiTreeCur = pBiTreeTemp ;
		pBiTreeTemp = pBiTreeTemp->pLNext;
		delete pBiTreeCur;
	}

	else if(pBiTreeTemp->pLNext==NULL)
	{
		pBiTreeCur = pBiTreeTemp;

		pBiTreeTemp = pBiTreeTemp->pRNext;
		delete pBiTreeCur;
	}

	else
	{
		pBiTreeCur = pBiTreeTemp;

		pBiTree pBiTreeTravel = pBiTreeTemp->pLNext;

		while(pBiTreeTravel->pRNext!=NULL)
		{
			pBiTreeCur = pBiTreeTravel;

			pBiTreeTravel = pBiTreeTravel->pRNext;
		}

		pBiTreeTemp->Data = pBiTreeTravel->Data;

		if(pBiTreeCur==pBiTreeTemp)
		{
			pBiTreeCur->pLNext = pBiTreeTravel->pLNext;
		}

		else
		{
			pBiTreeCur->pRNext = pBiTreeTravel->pLNext;
		}

		delete pBiTreeTravel;
	}


}

void TravelTree(pBiTree pBiTreeTemp)
{
	if(pBiTreeTemp!=NULL)
	{
		TravelTree(pBiTreeTemp->pLNext);

		cout<<pBiTreeTemp->Data<<" ";

		TravelTree(pBiTreeTemp->pRNext);
	}
}
