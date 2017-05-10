#include <stdio.h>
#include <malloc.h>
#include <string.h>

//�����������ĸ����� ��������ֵҪ�ȸ��ڵ�ֵС  �ҽڵ��ֵ�ȸ��ڵ�ֵ��

typedef struct  _DATA_ 
{
	int a;    //����
}Data,*pData;



typedef struct _BITREE_ 
{
	Data DataTemp;
	_BITREE_* pLeft;
	_BITREE_* pRight;
}BiTree,*pBiTree;


bool InitBiTree(pBiTree& pBiTreeTemp);

void DestroyTree(pBiTree& pBiTreeTemp);

bool InsertBiTree(pBiTree& pBiTreeTemp,Data DataTemp);

void SearchBiTreeNode(pBiTree& pBiTreeTemp,Data DataTemp,pBiTree pBiTreeFather,
					  pBiTree& pBiTreeNew,bool& bFlag);

void TravelTree(pBiTree& pBiTreeTemp);


void DelNode(pBiTree& pBiTreeTemp);

bool DelBiTree(pBiTree& pBiTreeTemp,Data DataTemp);

void main()
{
	pBiTree pBiTreeTemp = NULL;


	//����һ����ά���齫���ݲ��뵽���ǵĶ�����������

	Data DataArray[6] = {{45},{12},{53},{3},{37},{24}};


	int i = 0;

	for (i=0;i<6;i++)
	{
		InsertBiTree(pBiTreeTemp,DataArray[i]);
	}



	DelBiTree(pBiTreeTemp,DataArray[3]);


	TravelTree(pBiTreeTemp);

	DestroyTree(pBiTreeTemp);

}


bool InitBiTree(pBiTree& pBiTreeTemp)
{
	pBiTreeTemp = NULL;

	return true;
}



void DestroyTree(pBiTree& pBiTreeTemp)
{
	if (pBiTreeTemp)
	{
		if (pBiTreeTemp->pLeft)
		{
			DestroyTree(pBiTreeTemp->pLeft);
		}
		if (pBiTreeTemp->pRight)
		{
			DestroyTree(pBiTreeTemp->pRight);
		}

		free(pBiTreeTemp);
	}
}

void SearchBiTreeNode(pBiTree& pBiTreeTemp,Data DataTemp,pBiTree pBiTreeFather,
					  pBiTree& pBiTreeNew,bool& bFlag)
{
	if (!pBiTreeTemp)
	{

		pBiTreeNew = pBiTreeFather;
		bFlag = false;
	}

	else if (pBiTreeTemp->DataTemp.a==DataTemp.a)
	{
		bFlag = true;

		pBiTreeNew = pBiTreeTemp;
	}

	else if (pBiTreeTemp->DataTemp.a>DataTemp.a)
	{
		SearchBiTreeNode(pBiTreeTemp->pLeft,DataTemp,pBiTreeTemp,pBiTreeNew,bFlag);
	}

	else
	{
		SearchBiTreeNode(pBiTreeTemp->pRight,DataTemp,pBiTreeTemp,pBiTreeNew,bFlag);
	}
}


bool InsertBiTree(pBiTree& pBiTreeTemp,Data DataTemp)
{
	pBiTree pBiTreeNew = NULL;

	pBiTree pBiTreeFather = NULL;


	bool bFlag = false;


	SearchBiTreeNode(pBiTreeTemp,DataTemp,NULL,pBiTreeFather,bFlag);
	
	if (!bFlag)
	{
		pBiTreeNew = (pBiTree)malloc(sizeof(BiTree));

		pBiTreeNew->DataTemp = DataTemp;

		pBiTreeNew->pLeft = pBiTreeNew->pRight = NULL;

		if (pBiTreeTemp==NULL)
		{
			pBiTreeTemp = pBiTreeNew;
		}

		else
		{
			if (pBiTreeFather->DataTemp.a>DataTemp.a)
			{
				pBiTreeFather->pLeft = pBiTreeNew;
			}
			else
			{
				pBiTreeFather->pRight = pBiTreeNew;
			}
		}

		return true;

	}

	
	return false;
	
}

bool DelBiTree(pBiTree& pBiTreeTemp,Data DataTemp)
{
	if (!pBiTreeTemp)
	{
		return false;
	}

	else
	{
		if (pBiTreeTemp->DataTemp.a==DataTemp.a)
		{
			DelNode(pBiTreeTemp);
		}

		else if (pBiTreeTemp->DataTemp.a>DataTemp.a)
		{
			DelBiTree(pBiTreeTemp->pLeft,DataTemp);
		}

		else
		{
			DelBiTree(pBiTreeTemp->pRight,DataTemp);
		}

		return true;
	}
}

void DelNode(pBiTree& pBiTreeTemp)   //{45,1},{12,2},{53,3},{3,4},{37,5},{24,6}
{

/*
						 45
                     12     53           
                   3    37
                     24    (39)   
                       (35)
*/	                
	
	pBiTree pBiTreeCurrent = NULL;
	if (!pBiTreeTemp->pRight)   // ������Ϊ��                     
	{ 
		pBiTreeCurrent = pBiTreeTemp;

		pBiTreeTemp = pBiTreeTemp->pLeft;

		free(pBiTreeCurrent);
	}

	else if (!pBiTreeTemp->pLeft)                // ������Ϊ��
	{
		pBiTreeCurrent = pBiTreeTemp;

		pBiTreeTemp = pBiTreeTemp->pRight;

		free(pBiTreeCurrent);
	}

	else                      // ����
	{

		pBiTreeCurrent = pBiTreeTemp;

		pBiTree pBiTreeTravel = pBiTreeTemp->pLeft;
		
/*
						 45
                     12     53           
                   3    37
                     24    (39)   
                       (35)
*/
		while (pBiTreeTravel->pRight)   //����ǰ��
		{

			pBiTreeCurrent = pBiTreeTravel;

			pBiTreeTravel = pBiTreeTravel->pRight;
		}
		
		pBiTreeTemp->DataTemp = pBiTreeTravel->DataTemp;

		if (pBiTreeCurrent!=pBiTreeTemp)
		{
			pBiTreeCurrent->pRight = pBiTreeTravel->pLeft; //ɾ��45 ʱ
		}

		else
		{
			pBiTreeCurrent->pLeft = pBiTreeTravel->pLeft;  //ɾ��12ʱ
		}



		free(pBiTreeTravel);


	}


}





void TravelTree(pBiTree& pBiTreeTemp)
{
	if (pBiTreeTemp)
	{
		TravelTree(pBiTreeTemp->pLeft);

		printf("%d  ",pBiTreeTemp->DataTemp.a);

		TravelTree(pBiTreeTemp->pRight);
	}
}
