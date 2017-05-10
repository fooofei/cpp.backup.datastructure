#include <stdio.h>
#include <malloc.h>

#include <string.h>


#define LH  1
#define EH  0
#define RH  -1


typedef struct  _DATA_ 
{
	int a;    //����
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


void L_Rotate(pBiTree& pBiTreeTemp);  //����

void R_Rotate(pBiTree& pBiTreeTemp);  //����


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


			if (bTaller)  //���뵽����   Ҫ����ƽ�⴦��
			{
				 switch(pBiTreeTemp->bf)
				 {
				 case LH:/* ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
					 {
						 LeftBalance(pBiTreeTemp);

						 bTaller = false;
						 break;
					 }

				 case EH: /* ԭ�����������ȸߣ��������������߶�ʹ������ */
					 {

						 pBiTreeTemp->bf = LH;

						 bTaller = true;



						 break;
					 }

				 case  RH: /* ԭ�����������������ߣ������������ȸ� */
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

				case LH:   /* ԭ�����������������ߣ������������ȸ� */
					{
						pBiTreeTemp->bf = EH;

						bTaller = false;
						break;
					}

				case EH: /* ԭ�����������ȸߣ��������������߶�ʹ������ */
					{
						pBiTreeTemp->bf = RH;


						break;
					}

				case RH: /* ԭ�����������������ߣ���Ҫ����ƽ�⴦�� */
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
	case LH:  /* �½�������*T�����ӵ��������ϣ�Ҫ������������ */
		{
			pBiTreeTemp->bf = p->bf = EH;


			R_Rotate(pBiTreeTemp);
			break;
		}

	case  RH: /* �½�������*T�����ӵ��������ϣ�Ҫ��˫������ */
		{
			q = p->pRight;

			switch(q->bf)   //û�ж����Ҫ
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


			//��Ҫ   
			R_Rotate(pBiTreeTemp->pLeft);

			L_Rotate(pBiTreeTemp);
			break;//��ε�� ͼ  9.12 (f g ����)   pag 246
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
	case RH: /* �½�������*T���Һ��ӵ��������ϣ�Ҫ������������ */
		{
			pBiTreeTemp->bf = p->bf = EH;
			
			
			L_Rotate(pBiTreeTemp);
			break;
		}
		
	case  LH:  /* �½�������*T���Һ��ӵ��������ϣ�Ҫ��˫������ */
		{
			q = p->pLeft;
				
			switch(q->bf)   //û�ж����Ҫ
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
			
			
			//��Ҫ   
			R_Rotate(pBiTreeTemp->pRight);
			
			L_Rotate(pBiTreeTemp);
			break;//��ε�� ͼ  9.12 (f g ����)   pag 246
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