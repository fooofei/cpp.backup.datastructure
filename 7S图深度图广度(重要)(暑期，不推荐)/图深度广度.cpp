#include <stdio.h>
#include <malloc.h>


#define SIZE 10

#define MAX  100

//����ͼ�Ľṹ��

typedef struct _GRAPHIC_
{
	int Vertex;     //������Ϣ(Ϊ�˱�����һ�������ֵ)
	 _GRAPHIC_* pNext;  //ָ����һ�����������

}Graphic,*pGraphic;

//����һ�����������Ľṹ��

Graphic Head[SIZE+1];


//Ϊ����������ı�־����
int   Visited[SIZE+1];






//������������ָ������������ʱѧϰͼ�ļܹ����Բ�����ѭ������
int g_nRear = -1;
int g_nHead = -1;

//����һ����������
int Queue[MAX] ={0};




//��ʼ��
void InitilizeElement();

//����ͼ

void CreateGraphic(int* Temp,int Num);

void TravelGraphic();

//������Ȳ���
void DeepFirstSearch(int Current);

//������Ȳ���
void BroadFirstSearch(int Current);

int InQueue(int Value);
int OutQueue();


//�ͷ��ڴ�

void FreeMemory();



//����������
void OperaterPro();

int main()
{
	
	//���ñ�����������Ҫ����һ����ά������Ϊ������������ӵ�

	int TwoLine[30][2] = {{1,2},{2,1},{1,4},{4,1},{1,7},{7,1},{2,4},{4,2},{2,8},{8,2},{2,5},{5,2},
	{3,5},{5,3},{3,6},{6,3},{4,7},{7,4},{4,8},{8,4},{5,8},{8,5},{5,6},{6,5},{5,9},{9,5},
	{6,9},{9,6},{9,10},{10,9}};
	
	
	
	int* Temp = (int*)TwoLine;
	//��ʼ������Ľṹ������

//	char c = 'A';
	int i = 0;
	for (i=1;i<=SIZE;i++)
	{
		Head[i].Vertex = i;      //�趨����ֵ
		Head[i].pNext = NULL;
	}

	//��ʼ����־���麯��
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
		
		Visited[i] = 0;              //��ʼ����־����
	}
}

void CreateGraphic(int* Temp,int Num)
{
	int i = 0;

	//������������Ϊ�˽������е�������ȡ����
	int nFrom = 0;
	int nTo = 0;

	pGraphic ptr;

	for (i=0;i<Num;i++)
	{
	/*	
		//���ǽ���ά�����е�����ɨ��������д�ӡ
		
		printf("%d",*(Temp+2*i));

		printf("\n");
		printf("%d",*(Temp+2*i+1));

		printf("\n");*/

	
		nFrom = *(Temp+2*i);

		nTo = *(Temp+2*i+1);


		//��̬�����ڴ沢�Ҵ��������ʼ��

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

			//��ѯ������ҽ���������

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
	//  ����ͼ�Ĺ���
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
		printf("1...����ͼ   2...������Ȳ���   3...������Ȳ���\n");
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



//������Ȳ���ͨ���õ��ݹ�ķ���
void DeepFirstSearch(int Current)
{
	//�趨��־����

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


//������Ȳ���ͨ���õ����еķ���
void BroadFirstSearch(int Current)
{
	//����һ���������

	pGraphic ptr;
	InQueue(Current);  //Ϊ���ܹ����������ѭ��

	//���ñ�־����
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
				InQueue(ptr->Vertex);//���Ӳ������ñ�־Ϊ1

				Visited[ptr->Vertex] = 1;


				printf("%d  ",ptr->Vertex);
			}

			//����

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

