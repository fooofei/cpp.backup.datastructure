#include <stdio.h>
#include <malloc.h>
#include <iostream.h>
#include <Windows.h>


INT g_Array[6][6] = {0};
void main()
{
            //  卧槽 竟然都是无向图了 还写 {1,2} {2,1}  这.......
	int iData[14][2] = {{1,2},{2,1},{1,5},{5,1},{2,3},{3,2},{2,4},{4,2},{3,4},{4,3},{3,5},{5,3},{4,5},{5,4}};


	int i = 0;
	int j = 0;
	int k = 0;
	
	int TempA = 0;
	int TempB = 0;
	
	for (i=0;i<14;i++)
	{
		for (j=0;j<6;j++)
		{
			for (k=0;k<6;k++)
			{
				TempA = iData[i][0];
				TempB = iData[i][1];

				g_Array[TempA][TempB] = 1;
			}
		}
	}


	printf("无向图\n");


	for (i=1;i<6;i++)
	{
		for (j=1;j<6;j++)
		{

			printf("%d",g_Array[i][j]);
		}

		printf("\n");
	}
}


// 无向图
// 01001
// 10110
// 01011
// 01101
// 10110
// Press any key to continue
