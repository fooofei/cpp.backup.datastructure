#include <stdio.h>
#include <random>

typedef struct tagNODE
{
	int Data;
	struct tagNODE* pRight;
	struct tagNODE* pDown;

}NODE,*PNODE;

#define  Row  5
#define  Col 5

PNODE pHead = NULL;

PNODE CreateHorList(PNODE &pNodeTemp , int Data);
void FreeList(PNODE &pHead);
PNODE CreateVerList(PNODE &pNodeTemp , int Data);
void TravelList(PNODE pHead);

int main()
{
	pHead = new NODE;
	pHead->pRight = NULL;
	pHead->pDown = NULL;
	pHead->Data = 0;



	int i =0;
	int j =0;

	int Array[Row][Col] = {0};
	for(i=0;i<Row;i++)
	{
		for(j=0;j<Col;j++)
		{
			Array[i][j] = rand()%99+1;
		}
	}

	PNODE pNodeTemp = pHead;
	for(i=0;i<Col;i++)
	{
		pNodeTemp = CreateHorList(pNodeTemp,*(&Array[0][0]+i));
	}




	for (i=1;i<Row;i++)
	{
		pNodeTemp = pHead->pRight;
		while (pNodeTemp->pDown!=NULL)
		{
			pNodeTemp = pNodeTemp->pDown;
		}

		for (j=0;j<Col;j++)
		{
			pNodeTemp = CreateVerList(pNodeTemp,*(&Array[0][0]+i*Col+j));
		}

	}

	TravelList( pHead);

	FreeList(pHead);
	return 0;
}

PNODE CreateHorList(PNODE &pNodeTemp , int Data)
{
	if(pNodeTemp==NULL)
	{
		return NULL;
	}
	pNodeTemp->pRight = new NODE;
	if(pNodeTemp->pRight==NULL)
	{
		return NULL;
	}
	pNodeTemp->pRight->pDown = NULL;
	pNodeTemp->pRight->pRight = NULL;
	pNodeTemp->pRight->Data = Data;

	return pNodeTemp->pRight;
}

PNODE CreateVerList(PNODE &pNodeTemp , int Data)
{

	if(pNodeTemp==NULL)
	{
		return NULL;
	}
	PNODE pNodeTravel = NULL;
	pNodeTemp->pDown = new NODE;
	pNodeTemp->pDown ->Data = Data;
	pNodeTemp->pDown->pDown = NULL;
	pNodeTemp->pDown ->pRight = NULL;


	pNodeTravel = pHead->pRight;
	while (pNodeTravel->pDown!=NULL)
	{
		pNodeTravel = pNodeTravel->pDown;
	}
	while(pNodeTravel->pRight!=NULL)  //只要他一走 那就不是第一个节点  避免使用全局变量
	{
		pNodeTravel =  pNodeTravel->pRight;

	} 

	if (pNodeTravel!=pNodeTemp->pDown)//pNodeTemp!=pHead->pRight  这样做是不行的   哥写的代码使用了 bOk 全局变量  不好
	{
		pNodeTravel->pRight = pNodeTemp->pDown;
	}	

	return pNodeTemp->pRight;
}


void TravelList(PNODE pHead)
{
	PNODE pNodeCol = pHead->pRight;
	PNODE pNodeRow  = NULL;

	while (pNodeCol!=NULL)
	{
		pNodeRow = pNodeCol;
		while(pNodeRow!=NULL)
		{
			printf("%d  ",pNodeRow->Data);
			pNodeRow = pNodeRow->pRight;
		}
		printf("\n");
		pNodeCol = pNodeCol->pDown;
	}
}

void FreeList(PNODE &pHead)
{

	PNODE pNodeRow = NULL;
	PNODE pNodeRowTemp = NULL;
	PNODE pNodeCol = NULL;
	PNODE pNodeColTemp = NULL;


	pNodeRow = pHead->pRight;
	pNodeRowTemp =  pNodeRow;
	while (pNodeRowTemp!=NULL)
	{

		pNodeCol = pNodeRow->pRight;
		pNodeColTemp = pNodeCol;
		while(pNodeColTemp!=NULL)
		{
			pNodeCol = pNodeCol->pRight;
			delete pNodeColTemp;
			pNodeColTemp = pNodeCol;
		}

		pNodeRow = pNodeRow->pDown;
		delete pNodeRowTemp;
		pNodeRowTemp = pNodeRow;
	}

	delete pHead;
	pHead = NULL;
}