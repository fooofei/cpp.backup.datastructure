#include <stdio.h>
#include <malloc.h>
#include <string.h>

//二叉排序树的概念是 左子树的值要比父节点值小  右节点的值比父节点值大

typedef struct  _DATA_ 
{
	int a;    //数据
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


	//定义一个二维数组将数据插入到我们的二叉排序树中

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
	if (!pBiTreeTemp->pRight)   // 右子树为空                     
	{ 
		pBiTreeCurrent = pBiTreeTemp;

		pBiTreeTemp = pBiTreeTemp->pLeft;

		free(pBiTreeCurrent);
	}

	else if (!pBiTreeTemp->pLeft)                // 左子树为空
	{
		pBiTreeCurrent = pBiTreeTemp;

		pBiTreeTemp = pBiTreeTemp->pRight;

		free(pBiTreeCurrent);
	}

	else                      // 都有
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
		while (pBiTreeTravel->pRight)   //查找前驱
		{

			pBiTreeCurrent = pBiTreeTravel;

			pBiTreeTravel = pBiTreeTravel->pRight;
		}
		
		pBiTreeTemp->DataTemp = pBiTreeTravel->DataTemp;

		if (pBiTreeCurrent!=pBiTreeTemp)
		{
			pBiTreeCurrent->pRight = pBiTreeTravel->pLeft; //删除45 时
		}

		else
		{
			pBiTreeCurrent->pLeft = pBiTreeTravel->pLeft;  //删除12时
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
