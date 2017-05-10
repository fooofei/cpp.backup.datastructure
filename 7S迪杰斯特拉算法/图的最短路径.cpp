#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <iomanip>



using namespace std;

#define MAX 7
#define NUM 6
#define INFINITE 10000  //根据情况任意改变


void BuildGraphMatrix(int* p);
void PrintGraphMatrix();

void FindShortPath(int iVal,int iTotal); //这里的传参   顶点1  和  其它顶点的个数


int g_GraphMatrix[MAX][MAX] = {0};   //图数组
int g_Distance[MAX] = {0};

void main()
{
	int iData[7][3] = {{1,2,10},{2,3,20},{2,4,25},{3,5,18},{4,5,22},{4,6,95},{5,6,77}};

	BuildGraphMatrix(&iData[0][0]);

	printf("图的邻接矩阵\n");

	printf("          P1  P2   P3   P4   P5   P6\n");

	PrintGraphMatrix();


	FindShortPath(1,NUM);


	printf("顶点1 到其它节点的最短距离\n");


	int i = 0;
	for (i=1;i<MAX;i++)
	{
		cout<<"顶点1到顶点"<<setw(2)<<i<<"最短距离="<<setw(3)<<g_Distance[i]<<endl;
	}

	cout<<endl;

}

void BuildGraphMatrix(int* p)
{

	int iFrom = 0;
	int iTo = 0;

	int i = 0;
	int j = 0;

	for (i=1;i<MAX;i++)
	{
		for (j=1;j<MAX;j++)
		{
			//自己到自己 (对角线)

			if (i==j)
			{
				g_GraphMatrix[i][j] = 0;
			}

			else
			{
				g_GraphMatrix[i][j] = INFINITE;
			}

		}
	}



	i = 0;

	while (i<MAX)
	{
		iFrom = p[i*3];    //是二维数组当一维数组使用

		iTo = p[i*3+1];

		g_GraphMatrix[iFrom][iTo] = p[i*3+2];    //	int iData[7][3] = {{1,2,10},{2,3,20},{2,4,25},{3,5,18},{4,5,22},{4,6,95},{5,6,77}};

		i++;
	}
}


void PrintGraphMatrix()
{
	int i = 0;
	int j = 0;

	for (i=1;i<MAX;i++)
	{
		printf("Point%d",i);

		for (j=1;j<MAX;j++)
		{
			if (g_GraphMatrix[i][j]==INFINITE)
			{
			
				cout<<setw(5)<<'x';
			}

			else
			{
			
				cout<<setw(5)<<g_GraphMatrix[i][j];
			}
		}

		printf("\n");
	}
}


void FindShortPath(int iVal,int iTotal)
{
	int iFlag[MAX] = {0};
	int iShortPath = INFINITE;   //记录最短距离根据情况变化
	int iShortVal = 1;         //记录最短距离的顶点
	

	int i = 0;
	int j = 0;


	for (i=1;i<=iTotal;i++)         //	int iData[7][3] = {{1,2,10},{2,3,20},{2,4,25},{3,5,18},{4,5,22},{4,6,95},{5,6,77}};
	{
		iFlag[i] = 0;

		g_Distance[i] = g_GraphMatrix[iVal][i];
		
	}

	iFlag[iVal] = 1;

	g_Distance[iVal] = 0;  //自己

	for (i=1;i<=iTotal-1;i++)
	{
		iShortPath = INFINITE;

		for (j=1;j<=iTotal;j++)
		{
			if (iFlag[j]==0&&iShortPath>g_Distance[j])
			{
				iShortPath = g_Distance[j];

				iShortVal = j;

			}
		}

	
		iFlag[iShortVal] = 1;
		
		//计算
		
		for (j=1;j<=iTotal;j++)
		{
			if (iFlag[j]==0&&g_Distance[iShortVal]+g_GraphMatrix[iShortVal][j]<g_Distance[j])
			{
				g_Distance[j] = g_Distance[iShortVal]+g_GraphMatrix[iShortVal][j];
			}
		}

  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
}