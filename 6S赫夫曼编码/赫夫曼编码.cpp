#include <iostream.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>



#define UINT_MAX      0xffffffff 

typedef struct _BITREE_ 
{

}BiTree,*pBiTree;


typedef struct _HUFFMANTREE_
{
	int iWeight;
	int iParent;
	int iLeft;
	int iRight;

}HuffManTree,*pHuffManTree;



void SelectNode(pHuffManTree& pHuffManTreeTemp,int i,int* m,int* n);
int GetNode(pHuffManTree& pHuffManTreeTemp,int i);

void HuffManCode(pHuffManTree& pHuffManTreeTemp,int* p,int n);

void main()
{
	pHuffManTree pHuffManTreeTemp;

	int iNum = 0;

	printf("Input Num of È¨Öµ\n");


	scanf("%d",&iNum);

	int* p = (int*)malloc(sizeof(int)*iNum);

	int i = 0;

	for (i=0;i<iNum;i++)
	{
		printf("Input È¨Öµ\n");

		scanf("%d",&p[i]);
	}



	HuffManCode(pHuffManTreeTemp,p,iNum);




	printf("HuffManTree Data\n");
	for (i=1;i<=2*iNum-1;i++)
	{
		printf("%d ",pHuffManTreeTemp[i].iWeight);
	}


	printf("\n");
	free(pHuffManTreeTemp);


	free(p);

}

void HuffManCode(pHuffManTree& pHuffManTreeTemp,int* p,int n)
{
	
	if (n<=1)
	{
		return;
	}

	int m = 2*n-1;

	pHuffManTreeTemp = (pHuffManTree)malloc(sizeof(HuffManTree)*(m+1));



	int j = 1;

	for (j=1;j<=n;j++)
	{
		pHuffManTreeTemp[j].iWeight = *p;

		pHuffManTreeTemp[j].iParent = 0;
		pHuffManTreeTemp[j].iRight = 0;
		pHuffManTreeTemp[j].iLeft = 0;

		p++;
	}


	for (;j<=m;j++)
	{
		pHuffManTreeTemp[j].iLeft = pHuffManTreeTemp[j].iParent = pHuffManTreeTemp[j].iRight = 0;

		pHuffManTreeTemp[j].iParent = 0;
	}


	//½¨Á¢ºÕ·òÂüÊ÷

	int s1 = 0;
	int s2 = 0;
	for (j=n+1;j<=m;j++)
	{
		SelectNode(pHuffManTreeTemp,j-1,&s1,&s2);


		pHuffManTreeTemp[s1].iParent= pHuffManTreeTemp[s2].iParent = j;
		pHuffManTreeTemp[j].iLeft=s1;
		pHuffManTreeTemp[j].iRight=s2;
		pHuffManTreeTemp[j].iWeight=pHuffManTreeTemp[s1].iWeight+pHuffManTreeTemp[s2].iWeight;
	}


	//ºÕ·òÂü±àÂë

	char* q=(char*)malloc(n*sizeof(char));
    q[n-1]='\0';


	int start = 0;

	int c = 0;
	int f = 0;
	int i = 0;


	printf("HuffMan Conde:\n");
	for(i=1;i<=n;i++)
	{ 
		start=n-1; 
		for(c=i,f=pHuffManTreeTemp[i].iParent;f!=0;c=f,f=pHuffManTreeTemp[f].iParent)
		{
			if(pHuffManTreeTemp[f].iLeft==c)
			{
				 q[--start]='0';
			}
			
			else
			{
				q[--start]='1';
			}

		}
		
		printf("%s\n",&q[start]);   //´òÓ¡±àÂë

	  }



	free(q);
}




void SelectNode(pHuffManTree& pHuffManTreeTemp,int i,int* m,int* n)
{
	*m = GetNode(pHuffManTreeTemp,i);
	
	*n = GetNode(pHuffManTreeTemp,i);
	
	int Temp = 0;
	
	if (*m>*n)
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
		if (pHuffManTreeTemp[j].iWeight<nOver&&pHuffManTreeTemp[j].iParent==0)
		{
			nOver = pHuffManTreeTemp[j].iWeight;
			
			Flag = j;
		}
	}
	
	
	pHuffManTreeTemp[Flag].iParent = 1;
	
	return Flag;
}