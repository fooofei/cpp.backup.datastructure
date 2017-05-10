#include <stdio.h>
#include <malloc.h>

#include <string.h>


#define LH  1
#define EH  0
#define RH  -1


typedef struct  _DATA_ 
{
	int a;    //数据
}Data,*pData;



typedef struct _BITREE_ 
{
	Data DataTemp;

	int bf;
	_BITREE_* pLeft;
	_BITREE_* pRight;
}BiTree,*pBiTree;


bool InitBiTree(pBiTree& pBiTreeTemp);

void DestroyTree(pBiTree& pBiTreeTemp);


void L_Rotate(pBiTree& pBiTreeTemp);  //左旋

void R_Rotate(pBiTree& pBiTreeTemp);  //右旋


void LeftBalance(pBiTree& pBiTreeTemp);

void RightBalance(pBiTree& pBiTreeTemp);

void TravelTree(pBiTree& pBiTreeTemp);


bool InsertAVL(pBiTree& pBiTreeTemp,int e,bool& bTaller);
 
void main()
{

	bool bTaller = false;

	pBiTree pBiTreeTemp;

	InitBiTree(pBiTreeTemp);

	int e[10] = {13,24,37,90,53};

	for (int i=0;i<5;i++)
	{
		InsertAVL(pBiTreeTemp,e[i],bTaller);
	}

	
	TravelTree(pBiTreeTemp);
	
	DestroyTree(pBiTreeTemp);



}


bool InsertAVL(pBiTree& pBiTreeTemp,int e,bool& bTaller)
{
	if (!pBiTreeTemp)
	{
		pBiTreeTemp = (pBiTree)malloc(sizeof(BiTree));

		pBiTreeTemp->bf = EH;

		pBiTreeTemp->DataTemp.a = e;

		pBiTreeTemp->pLeft = pBiTreeTemp->pRight = NULL;

		bTaller = true;
	}

	else
	{
		if (pBiTreeTemp->DataTemp.a==e)
		{
			bTaller = false;

			return false;
		}

		if (pBiTreeTemp->DataTemp.a>e)
		{
			if (!InsertAVL(pBiTreeTemp->pLeft,e,bTaller))
			{
				return false;
			}


			if (bTaller)  //插入到树中   要进行平衡处理
			{
				 switch(pBiTreeTemp->bf)
				 {
				 case LH:/* 原本左子树比右子树高，需要作左平衡处理 */
					 {
						 LeftBalance(pBiTreeTemp);

						 bTaller = false;
						 break;
					 }

				 case EH: /* 原本左、右子树等高，现因左子树增高而使树增高 */
					 {

						 pBiTreeTemp->bf = LH;

						 bTaller = true;



						 break;
					 }

				 case  RH: /* 原本右子树比左子树高，现左、右子树等高 */
					 {
						 pBiTreeTemp->bf = EH;

						 bTaller = false;
						 break;
					 }
				 }
			}
		}



		else
		{
			if(!InsertAVL(pBiTreeTemp->pRight,e,bTaller))
			{
				return false;
			}

			if (bTaller)
			{
				switch(pBiTreeTemp->bf)
				{

				case LH:   /* 原本左子树比右子树高，现左、右子树等高 */
					{
						pBiTreeTemp->bf = EH;

						bTaller = false;
						break;
					}

				case EH: /* 原本左、右子树等高，现因右子树增高而使树增高 */
					{
						pBiTreeTemp->bf = RH;


						break;
					}

				case RH: /* 原本右子树比左子树高，需要作右平衡处理 */
					{
						RightBalance(pBiTreeTemp);
		  
						bTaller = false;
						break;
					}
				}
			}
		}
	}



	return true;
}



void L_Rotate(pBiTree& pBiTreeTemp)
{
	pBiTree p;

	p = pBiTreeTemp->pRight;

	pBiTreeTemp->pRight = p->pLeft;


	p->pLeft = pBiTreeTemp;

	pBiTreeTemp = p;



}

void R_Rotate(pBiTree& pBiTreeTemp)
{
	pBiTree p;
	
	p = pBiTreeTemp->pLeft;
	
	pBiTreeTemp->pLeft = p->pRight;
	
	
	p->pRight = pBiTreeTemp;
	
	pBiTreeTemp = p;
}




void LeftBalance(pBiTree& pBiTreeTemp)  
{
	pBiTree p;

	p = pBiTreeTemp->pLeft;

	pBiTree q;


	switch(p->bf)
	{
	case LH:  /* 新结点插入在*T的左孩子的左子树上，要作单右旋处理 */
		{
			pBiTreeTemp->bf = p->bf = EH;


			R_Rotate(pBiTreeTemp);
			break;
		}

	case  RH: /* 新结点插入在*T的左孩子的右子树上，要作双旋处理 */
		{
			q = p->pRight;

			switch(q->bf)   //没有多大重要
			{

				case LH:
					{
						pBiTreeTemp->bf = RH;

						p->bf = EH;
						break;
					}

				case RH:
					{
						pBiTreeTemp->bf = EH;

						p->bf = LH;
						break;
					}

				case EH:
					{
						pBiTreeTemp->bf = p->bf = EH;
						break;
					}
			}


			//重要   
			R_Rotate(pBiTreeTemp->pLeft);

			L_Rotate(pBiTreeTemp);
			break;//严蔚敏 图  9.12 (f g 过程)   pag 246
		}
	}
}


void RightBalance(pBiTree& pBiTreeTemp)
{
	pBiTree p;
	
	p = pBiTreeTemp->pRight;
	
	pBiTree q;


	
	switch(p->bf)
	{
	case RH: /* 新结点插入在*T的右孩子的右子树上，要作单左旋处理 */
		{
			pBiTreeTemp->bf = p->bf = EH;
			
			
			L_Rotate(pBiTreeTemp);
			break;
		}
		
	case  LH:  /* 新结点插入在*T的右孩子的左子树上，要作双旋处理 */
		{
			q = p->pLeft;
				
			switch(q->bf)   //没有多大重要
			{
				
				case LH:
					{
						pBiTreeTemp->bf = EH;
						
						p->bf = RH;
						break;
					}
					
				case RH:
					{
						pBiTreeTemp->bf = LH;
						
						p->bf = EH;
						break;
					}
					
				case EH:
					{
						pBiTreeTemp->bf = p->bf = EH;
						break;
					}
			}
			
			
			//重要   
			R_Rotate(pBiTreeTemp->pRight);
			
			L_Rotate(pBiTreeTemp);
			break;//严蔚敏 图  9.12 (f g 过程)   pag 246
		}
	}
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



void TravelTree(pBiTree& pBiTreeTemp)
{
	if (pBiTreeTemp)
	{
		TravelTree(pBiTreeTemp->pLeft);
		
		printf("%d  ",pBiTreeTemp->DataTemp.a);
		
		TravelTree(pBiTreeTemp->pRight);
	}
}