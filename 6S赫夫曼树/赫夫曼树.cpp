#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <iostream.h>


typedef struct _BITREE_ 
{
	int a;
	_BITREE_* pLeft;
	_BITREE_* pRight;
}BiTree,*pBiTree;


typedef struct _HUFFMANTREE_ 
{
	int iWeight;

	int iParent;
	int iLeft;
	int iRight;
}HuffManTree,*pHuffManTree;


#define UINT_MAX      0xffffffff  // ˵��  ��������΢���  ��һ��ͷ�ļ�#include <LIMITS.H> ΢���Ѿ������� UINT_MAX   ���ǿ�����

void CreateBiTree(pBiTree* pBiTreeTemp);

pHuffManTree InitHuffManTree();


void CreateArray(pHuffManTree& pHuffManTreeTemp,pBiTree pBiTreeTemp);


void CreateHuffManTree(pHuffManTree& pHuffManTreeTemp);

int GetNode(pHuffManTree& pHuffManTreeTemp,int i);

void SelectNode(pHuffManTree& pHuffManTreeTemp,int i,int* m,int* n);


void DestroyTree(pBiTree* pBiTreeTemp);

void DestroyHuffManTree(pHuffManTree& pHuffManTreeTemp);


int g_iCount = 0;

int g_iKey = 1;



void main()
{
	int i = 0;

	pBiTree pBiTreeTemp = NULL;

	CreateBiTree(&pBiTreeTemp);

	pHuffManTree pHuffManTreeTemp = InitHuffManTree();


	CreateArray(pHuffManTreeTemp,pBiTreeTemp);



	//printf("%d",g_iCount);



	for (i=1;i<g_iKey;i++)
	{
		printf("Weight:%d  ",pHuffManTreeTemp[i].iWeight);
	}


	printf("\n");


	printf("New Array Weight:\n");
	
	
	CreateHuffManTree(pHuffManTreeTemp);
	
	for (i=1;i<=2*g_iCount-1;i++)
	{
		printf("%d ",pHuffManTreeTemp[i].iWeight);
	}

	DestroyTree(&pBiTreeTemp);

	DestroyHuffManTree(pHuffManTreeTemp);
}

void CreateBiTree(pBiTree* pBiTreeTemp)
{
	int iInput = 0;
	
	scanf("%d",&iInput);

	if (iInput==0)
	{
		return;
	}

	else
	{
		*pBiTreeTemp = (pBiTree)malloc(sizeof(BiTree));

		(*pBiTreeTemp)->a = iInput;

		(*pBiTreeTemp)->pLeft = (*pBiTreeTemp)->pRight = NULL;


		CreateBiTree(&(*pBiTreeTemp)->pLeft);

		CreateBiTree(&(*pBiTreeTemp)->pRight);


		g_iCount++;
	}
}



pHuffManTree InitHuffManTree()
{

	int iNum = 2*g_iCount-1; // ע�����
	pHuffManTree pHuffManTreeTemp = (pHuffManTree)malloc(sizeof(HuffManTree)*(iNum+1));

	for (int i=0;i<=iNum;i++)
	{
		pHuffManTreeTemp[i].iLeft = 0;
		pHuffManTreeTemp[i].iRight = 0;
		pHuffManTreeTemp[i].iParent = 0;
		pHuffManTreeTemp[i].iWeight = 0;
	}

  //  memset(pHuffManTreeTemp,0,sizeof(sizeof(HuffManTree)*(iNum+1)));  // ������ôд

	return pHuffManTreeTemp;
}

void CreateHuffManTree(pHuffManTree& pHuffManTreeTemp)
{
	int i = 0;
	int m = 0;
	int n = 0;

	for (i=g_iCount+1;i<=2*g_iCount-1;i++) // ע�����Լ��Ĵ������������ ��ֵ��Χ�б仯  �Ҿ������Լ��ĺ����  Ҫͳһ�淶
	{
		SelectNode(pHuffManTreeTemp,i-1,&m,&n);


		pHuffManTreeTemp[m].iParent = pHuffManTreeTemp[n].iParent = i;

		pHuffManTreeTemp[i].iLeft = m;
		pHuffManTreeTemp[i].iRight = n;


		pHuffManTreeTemp[i].iWeight = pHuffManTreeTemp[m].iWeight + pHuffManTreeTemp[n].iWeight;


	}
}


void SelectNode(pHuffManTree& pHuffManTreeTemp,int i,int* m,int* n)
{
	*m = GetNode(pHuffManTreeTemp,i);

	*n = GetNode(pHuffManTreeTemp,i);

	int Temp = 0;

	if (*m>*n)//  ��������ò����Ƚ�  �������Լ�д�Ĵ��� �Ҷ�ʡ���� 
	{
		Temp = *m;
		*m = *n;
		*n = Temp;
	}
}

int GetNode(pHuffManTree& pHuffManTreeTemp,int i)
{
	unsigned int nOver = UINT_MAX;


	int j = 0;
	int Flag = 0;

	for (j=1;j<=i;j++)
	{
		if (pHuffManTreeTemp[j].iWeight < nOver && pHuffManTreeTemp[j].iParent==0)
		{
			nOver = pHuffManTreeTemp[j].iWeight;

			Flag = j;
		}
	}


	pHuffManTreeTemp[Flag].iParent = 1;

	return Flag;
}




void CreateArray(pHuffManTree& pHuffManTreeTemp,pBiTree pBiTreeTemp)
{
	if (pBiTreeTemp)
	{
		pHuffManTreeTemp[g_iKey].iWeight = pBiTreeTemp->a;

		g_iKey++;

		CreateArray(pHuffManTreeTemp,pBiTreeTemp->pLeft);

		CreateArray(pHuffManTreeTemp,pBiTreeTemp->pRight);
	}
}





void DestroyTree(pBiTree* pBiTreeTemp)
{
	if (*pBiTreeTemp)
	{
		if ((*pBiTreeTemp)->pLeft)
		{
			DestroyTree(&(*pBiTreeTemp)->pLeft);
		}

		if ((*pBiTreeTemp)->pRight)
		{
			DestroyTree(&(*pBiTreeTemp)->pRight);
		}

		free(*pBiTreeTemp);

		*pBiTreeTemp = NULL;
	}
}


void DestroyHuffManTree(pHuffManTree& pHuffManTreeTemp)
{
	if (pHuffManTreeTemp)
	{
		free(pHuffManTreeTemp);
	}

	pHuffManTreeTemp = NULL;
}

// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// Weight:1  Weight:2  Weight:3  Weight:4  Weight:5  Weight:6  Weight:7  Weight:8
// Weight:9
//        New Array Weight:
// 1 2 3 4 5 6 7 8 9 3 6 9 12 15 18 27 45 Press any key to continue
