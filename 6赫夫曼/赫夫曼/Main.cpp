#include "NodeType.h"
#include <windows.h>
#define UNIT_MAX 0xffffffff // 4294967295
void CreateHuffManTree(pHuffManTree &pHuffManTreeTemp, int NodeCount);
int  GetNode(pHuffManTree  &pHuffManTreeTemp , int Num);
void CreateArrayFormBiTreeToHuffManTree(pHuffManTree &pHuffManTreeTemp , pBTNode pRoot , int &Num);
void DestroyHuffManTree(pHuffManTree &pHuffManTreeTemp);
void InitHuffManTree(pHuffManTree &pHuffManTreeTemp , int NodeCount);
void DestroyBiTree(pBTNode &pRoot);
void CreateBiTree(pBTNode &pRoot , int &NodeCount);
void PreOrderTraverse(pBTNode pRoot);
void HuffManCode(pHuffManTree &pHuffManTreeTemp , int n);
int main()
{
	int NodeCount = 0;

	pBTNode pRoot = NULL;

	CreateBiTree(pRoot,NodeCount);

	PreOrderTraverse(pRoot);
	cout<<endl;


	pHuffManTree pHuffManTreeTemp = NULL;
	InitHuffManTree(pHuffManTreeTemp, NodeCount);

	int Num = 1;

	CreateArrayFormBiTreeToHuffManTree(pHuffManTreeTemp,pRoot,Num);

	CreateHuffManTree(pHuffManTreeTemp,NodeCount);
	

	int i = 0; 

	for(i = 1;i<2*NodeCount;i++)
	{
		cout<<pHuffManTreeTemp[i].Weight<<" ";
	}

	cout<<endl;

	HuffManCode(pHuffManTreeTemp,NodeCount);

	DestroyBiTree(pRoot);

	DestroyHuffManTree(pHuffManTreeTemp);
}


void CreateBiTree(pBTNode &pRoot , int &NodeCount)
{
	char c ;
	cin>>c ;
	if(atoi(&c)==Nil)
	{
		pRoot=NULL;
		return ;
	}
	else
	{
		pRoot = new BTNode ;

		pRoot->Data = atoi(&c);

		NodeCount ++;

		CreateBiTree(pRoot->pLNext ,NodeCount);

		CreateBiTree(pRoot->pRNext , NodeCount);
	}
}

void DestroyBiTree(pBTNode &pRoot)
{
	if(pRoot!=NULL)
	{
		DestroyBiTree(pRoot->pLNext);

		DestroyBiTree(pRoot->pRNext);

		delete pRoot;

		pRoot = NULL;
	}
}


void InitHuffManTree(pHuffManTree &pHuffManTreeTemp , int NodeCount)
{
	int i = 0;
	
	pHuffManTreeTemp = new HuffManTree[2*NodeCount];
	for(i = 0;i<2*NodeCount;i++)
	{
		pHuffManTreeTemp[i].Weight = 0;

		pHuffManTreeTemp[i].LNext = 0;

		pHuffManTreeTemp[i].RNext = 0;

		pHuffManTreeTemp[i].Parent = 0;
	}
}

void DestroyHuffManTree(pHuffManTree &pHuffManTreeTemp)
{
	if(pHuffManTreeTemp!=NULL)
	{
		delete[] pHuffManTreeTemp;
	}

	pHuffManTreeTemp = NULL;
}

void CreateArrayFormBiTreeToHuffManTree(pHuffManTree &pHuffManTreeTemp , pBTNode pRoot , int &Num)
{
	if(pRoot!=NULL)
	{
		

		pHuffManTreeTemp[Num].Weight = pRoot->Data ;

		Num++;

		CreateArrayFormBiTreeToHuffManTree(pHuffManTreeTemp,pRoot->pLNext,Num);

		CreateArrayFormBiTreeToHuffManTree(pHuffManTreeTemp,pRoot->pRNext,Num);
	}
}

int  GetNode(pHuffManTree  &pHuffManTreeTemp , int Num)
{
	unsigned int nOver = UNIT_MAX ;

	int i= 0 ;

	int Flag = 0;
	for(i = 1;i<Num;i++)
	{
		if(pHuffManTreeTemp[i].Weight<nOver && pHuffManTreeTemp[i].Parent == 0)
		{
			nOver = pHuffManTreeTemp[i].Weight ;

			Flag = i;
		}
	}

	pHuffManTreeTemp[Flag].Parent = 1; 
	return Flag;
}

void CreateHuffManTree(pHuffManTree &pHuffManTreeTemp, int NodeCount)
{
	int m = 0;
	int n = 0;

	int i = 0;

	for(i = NodeCount+1;i<2*NodeCount;i++)
	{
		m = GetNode(pHuffManTreeTemp,i);

		n = GetNode(pHuffManTreeTemp,i);

		pHuffManTreeTemp[m].Parent = pHuffManTreeTemp[n].Parent = i;

		pHuffManTreeTemp[i].LNext = m;

		pHuffManTreeTemp[i].RNext = n;

		pHuffManTreeTemp[i].Weight = pHuffManTreeTemp[n].Weight +pHuffManTreeTemp[m].Weight;
	}
}

void PreOrderTraverse(pBTNode pRoot)
{
	if(pRoot!=NULL)
	{
		cout<<(TElem )pRoot->Data<<" ";

		PreOrderTraverse(pRoot->pLNext);

		PreOrderTraverse(pRoot->pRNext);
	}
}
void HuffManCode(pHuffManTree &pHuffManTreeTemp , int n)
{
	int c = 0;
	int f = 0;
	int i = 0;
	int start = 0;

	char *p = new char[n];

	p[n-1] = '\0';
	for(i =1;i<=n;i++)
	{
		c = i;
		f = pHuffManTreeTemp[i].Parent;

		start = n-1;
		while(f!=0)
		{
			if(pHuffManTreeTemp[f].LNext==c)
			{
				p[--start] = '0';
			}
			else
			{
				p[--start] = '1';
			}

			c = f;
			f = pHuffManTreeTemp[f].Parent;
		}

		cout<<pHuffManTreeTemp[i].Weight<<"µÄºÕ·òÂü±àÂëÊÇ"<<&p[start]<<endl;
	}

	delete []p;
	 p = NULL;
}