#include <stdio.h>
#include <malloc.h>
#include <iostream.h>
#include <Windows.h>


typedef struct _NODE_ 
{
	int iVal;
	_NODE_* pNext;
}Node,*pNode;


Node g_Head[6] = {NULL};
void main()
{

	int iData[14][2] = {{1,2},{2,1},{1,5},{5,1},{2,3},{3,2},{2,4},{4,2},{3,4},{4,3},{3,5},{5,3},{4,5},{5,4}};


	int i = 0;
	int j = 0;
	int k = 0;
	
 
	pNode p1 = NULL;
	pNode p2 = NULL;
	
	for (i=1;i<=5;i++) // 5 个顶点 
	{
		g_Head[i].iVal = i;
		g_Head[i].pNext = NULL;

		printf("顶点%d:",i);

		p1 = &g_Head[i];
		for (j=0;j<14;j++) // 14 条弧
		{
			if (iData[j][0]==i) 
			{
				p2 = (pNode)malloc(sizeof(Node));

				p2->iVal = iData[j][1];

				p2->pNext = NULL;

				while (p1!=NULL)
				{
					p1 = p1->pNext;
				}

				p1 = p2;

				printf("%d",p1->iVal);
			}
	
		}

		printf("\n");
	}


}

// 顶点1:25
// 顶点2:134
// 顶点3:245
// 顶点4:235
// 顶点5:134
// Press any key to continue
