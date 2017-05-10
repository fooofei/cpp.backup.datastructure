#include <stdio.h>
#include <malloc.h>
#include <iostream.h>
#include <Windows.h>


INT g_Array[5][5] = {0};
void main()
{

	int iData[5][2] = {{1,2},{2,1},{2,3},{2,4},{4,3}};


	int i = 0;
	int j = 0;

	
	int TempA = 0;
	int TempB = 0;
	

	for (i=0;i<5;i++)
	{
		for (j=0;j<5;j++)
		{
			TempA = iData[i][0];
			TempB = iData[i][1];

			g_Array[TempA][TempB] = 1;
		}
	}
	


	printf("有向图\n");


	for (i=1;i<5;i++)
	{
		for (j=1;j<5;j++)
		{

			printf("%d",g_Array[i][j]);
		}

		printf("\n");
	}
}

// 有向图
// 0100
// 1011
// 0000
// 0010
// Press any key to continue
