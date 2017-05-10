#include <stdio.h>
#include <malloc.h>


#define SIZE 10

#define MAX  100

//创建图的结构体

typedef struct _GRAPHIC_
{
	int Vertex;     //顶点信息(为了保存下一个坐标的值)
	 _GRAPHIC_* pNext;  //指向下一个顶点的坐标

}Graphic,*pGraphic;

//设置一个顶点的数组的结构体

Graphic Head[SIZE+1];


//为查找所定义的标志数组
int   Visited[SIZE+1];






//定义两个队列指针在这里我们时学习图的架构所以不考虑循环队列
int g_nRear = -1;
int g_nHead = -1;

//定义一个队列数组
int Queue[MAX] ={0};




//初始化
void InitilizeElement();

//构建图

void CreateGraphic(int* Temp,int Num);

void TravelGraphic();

//深度优先查找
void DeepFirstSearch(int Current);

//广度优先查找
void BroadFirstSearch(int Current);

int InQueue(int Value);
int OutQueue();


//释放内存

void FreeMemory();



//主操作函数
void OperaterPro();

int main()
{
	
	//设置边线数组我们要定义一个二维数组因为是两点进行连接的

	int TwoLine[30][2] = {{1,2},{2,1},{1,4},{4,1},{1,7},{7,1},{2,4},{4,2},{2,8},{8,2},{2,5},{5,2},
	{3,5},{5,3},{3,6},{6,3},{4,7},{7,4},{4,8},{8,4},{5,8},{8,5},{5,6},{6,5},{5,9},{9,5},
	{6,9},{9,6},{9,10},{10,9}};
	
	
	
	int* Temp = (int*)TwoLine;
	//初始化顶点的结构体数组

//	char c = 'A';
	int i = 0;
	for (i=1;i<=SIZE;i++)
	{
		Head[i].Vertex = i;      //设定顶点值
		Head[i].pNext = NULL;
	}

	//初始化标志数组函数
	InitilizeElement();
	


	printf("1:A 2:B 3:C 4:D 5:E\n");
	printf("6:F 7:G 8:H 9:I 10:J\n");

	CreateGraphic(Temp,30);

	OperaterPro();

	FreeMemory();

	



}

void InitilizeElement()
{
	
	int i = 0;
	for (i=1;i<=SIZE;i++)
	{
		
		Visited[i] = 0;              //初始化标志数组
	}
}

void CreateGraphic(int* Temp,int Num)
{
	int i = 0;

	//定义两个变量为了将数组中的数据提取出来
	int nFrom = 0;
	int nTo = 0;

	pGraphic ptr;

	for (i=0;i<Num;i++)
	{
	/*	
		//这是将二维数组中的数据扫描出来进行打印
		
		printf("%d",*(Temp+2*i));

		printf("\n");
		printf("%d",*(Temp+2*i+1));

		printf("\n");*/

	
		nFrom = *(Temp+2*i);

		nTo = *(Temp+2*i+1);


		//动态申请内存并且创建链表初始化

		pGraphic pNew = (pGraphic)malloc(sizeof(Graphic));

		if (pNew == NULL)
		{
			return;
		}

		else
		{
			pNew->pNext = NULL;
			pNew->Vertex = nTo;

			ptr = &Head[nFrom];

			//查询链表便且将链表连接

			while (ptr->pNext!=NULL)
			{
				ptr = ptr->pNext;
			}

			ptr->pNext = pNew;
		}

	}
}


void TravelGraphic()
{
	//  测试图的构成
	int i = 1;
	for (i=1;i<=SIZE;i++)
	{
		printf("%d  ",Head[i].Vertex);
        
		pGraphic pTemp = &Head[i];
		
		while(pTemp->pNext!=NULL)
		{
			printf("%d   ",pTemp->pNext->Vertex);

			pTemp = pTemp->pNext;
		}

		printf("\n");
	}

}

void FreeMemory()
{
	pGraphic pTemp,pDel;
	
	int i = 1;
	int j = 0;
	for (i=1;i<=SIZE;i++)
	{
		
        
		pDel = Head[i].pNext;
		
		while(pTemp!=NULL)
		{
						
			pTemp = pDel->pNext;

			free(pDel);

			pDel = pTemp;
		}
		
		j++;
	}

	printf("Finished Free %d\n",j);
}


void OperaterPro()
{
	char Index;
	int  Current = 0;
	do 
	{
		printf("1...遍历图   2...广度优先查找   3...深度优先查找\n");
		scanf(" %c",&Index);
		switch (Index)
		{
		case '1':
			{
				
				TravelGraphic();
				break;
			}
			
		case '2':
			{
				printf("Input Num\n");
				scanf(" %d",&Current);
				BroadFirstSearch(Current);
				
				break;
			}

		case '3':
			{
				printf("Input Num\n");
				scanf(" %d",&Current);
				DeepFirstSearch(Current);

				
				break;
			}
			
		default:
			{
				printf("Error");
				
				break;
			}
		}
		
		InitilizeElement();
		
		printf("Continue...Yes/No\n");
		
		scanf(" %c",&Index);
		
	} while (Index =='y'||Index=='Y');
	
}



//深度优先查找通常用到递归的方法
void DeepFirstSearch(int Current)
{
	//设定标志数组

	Visited[Current] = 1;

	printf("%d   ",Current);



	pGraphic ptr = Head[Current].pNext;

	while (ptr!=NULL)
	{
		if (Visited[ptr->Vertex]==0)
		{
			DeepFirstSearch(ptr->Vertex);
		}

		ptr = ptr->pNext;
	}
}


//广度优先查找通常用到队列的方法
void BroadFirstSearch(int Current)
{
	//将第一个顶点入队

	pGraphic ptr;
	InQueue(Current);  //为了能够进入下面的循环

	//设置标志数组
	Visited[Current] = 1;

	printf("%d  ",Current);

	while (g_nHead!=g_nRear)
	{
		Current = OutQueue();

		ptr = Head[Current].pNext;
		while (ptr!=NULL)
		{
			if (Visited[ptr->Vertex]==0)
			{
				InQueue(ptr->Vertex);//进队并且设置标志为1

				Visited[ptr->Vertex] = 1;


				printf("%d  ",ptr->Vertex);
			}

			//下移

			ptr = ptr->pNext;
		}
	}
}


int InQueue(int Value)
{
	if (g_nRear>=MAX)
	{
		return -1;
	}

	g_nRear++;

	Queue[g_nRear] = Value;

}

int OutQueue()
{
	if (g_nRear==g_nHead)
	{
		return -1;
	}

	g_nHead++;

	return Queue[g_nHead];
}

