#include <stdio.h>
#include <iostream>


using namespace std;


/*
		123     147
		456     258
        789     369
  
*/

int main()
{
	int m = 0;
	int n = 0;   //����m*n�о���
	printf("Input �����������\n");

	scanf("%d",&m);

	scanf("%d",&n);
	int* p = NULL;
	int* q = NULL;


	p = new int[m*n];

	q = new int[m*n];


	printf("Input Matrix Content\n");

	int i = 0;
	int j = 0;
	for (i=1;i<=m;i++)
	{
		for (j=1;j<=n;j++)
		{
			scanf("%d",&(p[(i-1)*n+(j-1)]));
		}
	}


	printf("m*n���������Ϊ��\n");

	for (i=1;i<=m;i++)
	{
		for (j=1;j<=n;j++)
		{
			printf("%d   ",(p[(i-1)*n+(j-1)]));
		}

		printf("\n");
	}


	//ת�þ���

	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
		{
			q[(j-1)*n+i-1] = p[(i-1)+(j-1)*n];
		}
	}


	printf("n*m���������Ϊ��\n");



	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
		{
			printf("%d   ",(q[(j-1)*n+(i-1)]));
		}
		
		printf("\n");
	}




	delete p;

	delete q;


}