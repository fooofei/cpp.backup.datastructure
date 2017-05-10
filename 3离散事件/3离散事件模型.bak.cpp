#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>
#include <malloc.h>
#include <math.h>

//  ��Ĵ����д���  �����˺ü���
#define Queue  4   //�ͻ�����Ϊ  4

#define IntervalTime  5  //���ڵ������û�Ϊ  5

#define BigTime 30  //�û�����ʱ��





typedef struct _EVENT_  //�����¼�
{
	int iOccurTime;  //�¼�����ʱ��
	int iType;       //�����¼�  -1 �Ƿ����¼�  ���ָô�������¼�
}Event,*pEvent;


//�����¼�����
typedef struct _NODE_
{
	Event  EventData;
	_NODE_* pNext;
}Node,*pNode;


typedef struct _LIST_
{
	pNode pHead;
	pNode pTail;
	int iLen;
}List,*pList;


//��������е�����Ԫ��

typedef struct _QUEUEELEMENT_ 
{
	int iArrivalTime;     //����ʱ��
	int iDuration;        //������Ҫ��ʱ��
}QueueElement,*pQueueElement;


typedef struct _QUEUENODE_
{
	QueueElement QueueData;
	_QUEUENODE_ *pNext;
}QNode,*pQueueNode;

typedef struct _LINKQUEUE_
{
	pQueueNode pFront;
	pQueueNode pRear;
}LinkQueue,*pLinkQueue;



//�¼���������

bool InitList(pList pListTemp);//����һ���ս��  ���ӵ� pListTemp 

void InsertList(pList pListTemp,Event EventTemp,int (*CompareTime)(Event,Event));

bool ListEmpty(pList pListTemp);

pNode GetListHead(pList pListTemp);



void DelFirst(pList pListTemp,pNode& pNodeHead,pNode& pNodeTemp);
// ɾ�� pNodeHead ֮���һ���ڵ�  ���� ͨ��pNodeTemp ����һ�����¼��Ľ��   
Event GetCurElem(pNode pNodeTemp);




bool InitQueue(pLinkQueue pLinkQueueTemp);//����  ���� �յ�ͷ�ڵ� 

int QueueLength(LinkQueue LinkQueueTemp);

void InsertQueue(pLinkQueue pLinkQueueTemp,QueueElement QueueElementTemp);

void DeQueue(pLinkQueue pLinkQueueTemp,pQueueElement pQueueElementTemp);



void GetHead(pLinkQueue pLinkQueueTemp,pQueueElement pQueueElementTemp);

bool QueueEmpty(LinkQueue LinkQueueTemp);



List ListTemp;   // �¼�����

Event EventCurrent; //��ǰ�û�

Event EventNext;                  //	�¸��û�


QueueElement CustomData;

LinkQueue QueueTemp[Queue];

int TotalTime = 0;  //�ۼƿͻ�����ʱ��
int CustomNum = 0;  //�ͻ�����
int CloseTime = 0;

int CompareTime(Event a,Event b);
void OpenForDay();

void Random(int* m,int* n);

int Mini(LinkQueue* LinkQueueTemp);

void BankCalc();

void CustomArrived();   //����ͻ��ĵ���

void CustomDeparture();  //�����뿪


void main()
{

	printf("Input CloseTime\n");


	scanf("%d",&CloseTime);


	BankCalc();

	//�ͷ� �ڴ�

// 	if(ListTemp.pHead->pNext!=NULL)
// 	{
// 		printf("SHABI\n");
// 	}

	if (QueueLength(QueueTemp[0])>0)
	{
		printf("SHABI\n");//��ӡɵ�� ˵�����в�û����� 
	}
	pNode pNodeTemp = ListTemp.pHead;


	while (pNodeTemp!=NULL)
	{
		ListTemp.pHead = ListTemp.pHead->pNext;


		free(pNodeTemp);


		pNodeTemp = ListTemp.pHead;
	}





	
}


int CompareTime(Event a,Event b)
{

	return  (a.iOccurTime - b.iOccurTime);  //1  ���� -1 ������
	//����ֵ����     ������ 
	
}


void Random(int* m,int* n)
{
	*m = rand()%BigTime+1;

	*n = rand()%IntervalTime+1;
}


//��������4�������г�Ա���ٵĲ�����

int Mini(LinkQueue* LinkQueueTemp)
{
	int a[Queue] = {0};

	int i = 0;
	for (i=0;i<Queue;i++)
	{
		a[i] = QueueLength(LinkQueueTemp[i]);
	}


	//�������������ҵ�����һ������������

	int j = 0;


	for (i=1;i<Queue;i++)  //ð�ݵĵ�һѭ��     
	{
		if (a[i]<a[0])
		{
			a[0] = a[i];  //  4  5   2  1

			j = i;     
		}
	}

	return j;      
}



void OpenForDay()
{
	InitList(&ListTemp);

	//����һ�¼����� ʱ��Ϊ 0
	
	EventCurrent.iOccurTime = 0;

	EventCurrent.iType = -1;// ����


	//���¼��������ǵ��¼�������

	InsertList(&ListTemp,EventCurrent,CompareTime);

	//�����ǵ�4���������

	int i = 0;
	for (i=0;i<Queue;i++)
	{
		InitQueue(&QueueTemp[i]);
	}


}


void CustomArrived()
{

	CustomNum++;
	
	int DurtTime = 0; //����ʱ��
	int InterTime = 0;//������Ҫ��ʱ��
	Random(&DurtTime,&InterTime);     //   �ͻ�����ʱ��Ϳͻ���ͻ�֮��ļ��ʱ���������

	
	EventNext.iOccurTime = EventCurrent.iOccurTime + InterTime;
	
	EventNext.iType = -1; //����
	
	
	//Ҫ�����ʱ����бȽ�
	
	if (EventNext.iOccurTime<CloseTime)   
	{
		
		//�����¼��������ǵ��¼�����
		
		InsertList(&ListTemp,EventNext,CompareTime);


	}	
		
		//���㳤����̵Ķ���
		
		int i = Mini(QueueTemp); //��ö��е����������û�����
		
		QueueElement QueueDataTemp;
		
		
		QueueDataTemp.iArrivalTime = EventCurrent.iOccurTime;
		
		QueueDataTemp.iDuration = DurtTime;
		
		
		InsertQueue(&QueueTemp[i],QueueDataTemp); //�������
		
		if (QueueLength(QueueTemp[i])==1)
		{
			//  �����뿪�¼��������¼�����
			
			
			EventNext.iOccurTime = EventCurrent.iOccurTime + DurtTime;
			
			EventNext.iType = i;
			
			InsertList(&ListTemp,EventNext,CompareTime);
		}
		
		
		
	
}

void CustomDeparture()
{
	//�Ӷ�����ɾ�������û�������ʱ�����

	int i = 0;

	i = EventCurrent.iType;

	DeQueue(&QueueTemp[i],&CustomData);//����Ԫ��


	TotalTime += EventCurrent.iOccurTime - CustomData.iArrivalTime;//????


	//����ö�����֮����û������뵽�¼�������


	if (!QueueEmpty(QueueTemp[i]))
	{
		GetHead(&QueueTemp[i],&CustomData);


		EventNext.iOccurTime = EventCurrent.iOccurTime + CustomData.iDuration;//���� 

		EventNext.iType = i;

		InsertList(&ListTemp,EventNext,CompareTime);
	}


	
}


void BankCalc()
{
	OpenForDay();

	pNode pNodeTemp = NULL;

	pNode pNodeHead = GetListHead(&ListTemp);

	while (!ListEmpty(&ListTemp))
	{

		DelFirst(&ListTemp,pNodeHead,pNodeTemp);

		EventCurrent.iOccurTime = GetCurElem(pNodeTemp).iOccurTime;


		EventCurrent.iType = GetCurElem(pNodeTemp).iType;


		free(pNodeTemp);


		if (EventCurrent.iType==-1)
		{
			CustomArrived();
		}

		else
		{
			CustomDeparture();
		}
	}

	printf("Custom Count:%d   %d Min    Average Time%d Min\n",CustomNum,TotalTime,TotalTime/CustomNum);
}

void DelFirst(pList pListTemp,pNode& pNodeHead,pNode& pNodeTemp)
{
	// ɾ�� pNodeHead ֮��ĵڶ����ڵ�  ���� ͨ��pNodeTemp ����ȥ 

	   pNodeTemp = pNodeHead->pNext;

	   if (pNodeTemp!=NULL)
	   {
		   pNodeHead->pNext = pNodeTemp->pNext;

		   if (pNodeHead->pNext==NULL)
		   {
			   pListTemp->pTail = pNodeHead;
		   }

		   pListTemp->iLen--;
	   }

}


Event GetCurElem(pNode pNodeTemp)
{ 
	return pNodeTemp->EventData;
}


bool InitList(pList pListTemp)//����һ���ս��  ���ӵ� pListTemp 
{
	
	pNode pNodeTemp = (pNode)malloc(sizeof(Node));

	if (pNodeTemp!=NULL)
	{
		pListTemp->iLen = 0;
		pListTemp->pHead = pListTemp->pTail = pNodeTemp;

		pNodeTemp->pNext = NULL;


		return true;
	}

	else
	{
		return false;
	}

}

void InsertList(pList pListTemp,Event EventTemp,int (*CompareTime)(Event,Event))
{
	pNode pNodePre = pListTemp->pHead;

	pNode pNodeTemp = pNodePre->pNext;

	while (pNodeTemp!=NULL&&CompareTime(pNodeTemp->EventData,EventTemp)<0)  // �ȽϷ���ʱ��  
	{											//���뵽  pNodePre  pNodeTemp ֮��
		pNodePre = pNodeTemp;

		pNodeTemp = pNodeTemp->pNext;
	}


	pNode pNodeNew = (pNode)malloc(sizeof(Node));

	if (pNodeNew!=NULL)
	{

		pNodeNew->EventData = EventTemp;

		pNodeNew->pNext = NULL;

	}

	else
	{
		return;
	}


	pNodePre->pNext = pNodeNew;

	pNodeNew->pNext = pNodeTemp;
	

	pListTemp->iLen++;

	//��һ�嵽β��

	if (pNodeTemp==NULL)
	{
		pListTemp->pTail = pNodeNew;
	}


}

bool ListEmpty(pList pListTemp)
{ 
	if(pListTemp->iLen)
	{
		return false;
	}
	else
	{
		return true;
	}
 }


pNode GetListHead(pList pListTemp)
{ 
	return pListTemp->pHead;
}



bool InitQueue(pLinkQueue pLinkQueueTemp) //����  ���� �յ�ͷ�ڵ� 
{

	pLinkQueueTemp->pFront = pLinkQueueTemp->pRear = (pQueueNode)malloc(sizeof(QNode));

	if (pLinkQueueTemp->pFront==NULL)
	{
		return false;
	}

	else
	{
		pLinkQueueTemp->pFront->pNext = NULL;
	
		return true;
	}
}



int QueueLength(LinkQueue LinkQueueTemp)
{
	int i=0;
	pQueueNode pNodeTemp;
	pNodeTemp=LinkQueueTemp.pFront;

	while(pNodeTemp!=LinkQueueTemp.pRear)
	{
		i++;
		pNodeTemp = pNodeTemp->pNext;
	}
	return i;
 }


void InsertQueue(pLinkQueue pLinkQueueTemp,QueueElement QueueElementTemp)
{
	pQueueNode pQueueNodeTemp = (pQueueNode)malloc(sizeof(QNode));

	if (pQueueNodeTemp!=NULL)
	{
		pQueueNodeTemp->QueueData = QueueElementTemp;

		pQueueNodeTemp->pNext = NULL;

		pLinkQueueTemp->pRear->pNext = pQueueNodeTemp;

		pLinkQueueTemp->pRear = pQueueNodeTemp;
	}

	else
	{
		return;
	}
}



void DeQueue(pLinkQueue pLinkQueueTemp,pQueueElement pQueueElementTemp){

	pQueueNode pQueueNodeTemp = NULL;
	if (pLinkQueueTemp->pFront==pLinkQueueTemp->pRear)
	{
		return;
	}

	else
	{
		pQueueNodeTemp = pLinkQueueTemp->pFront->pNext;

		*pQueueElementTemp = pQueueNodeTemp->QueueData;   //���е�ͷ�ǿսڵ�

		pLinkQueueTemp->pFront->pNext = pQueueNodeTemp->pNext;


		if (pLinkQueueTemp->pRear==pQueueNodeTemp)
		{
			pLinkQueueTemp->pRear = pLinkQueueTemp->pFront;
		}


		free(pQueueNodeTemp);


	}

}

void GetHead(pLinkQueue pLinkQueueTemp,pQueueElement pQueueElementTemp) 
{ 
	pQueueNode pQueueNodeTemp = NULL;

	if(pLinkQueueTemp->pFront==pLinkQueueTemp->pRear)
	{
		return;
	}
	pQueueNodeTemp=pLinkQueueTemp->pFront->pNext;
	
	*pQueueElementTemp=pQueueNodeTemp->QueueData;

}


bool QueueEmpty(LinkQueue LinkQueueTemp)
{ 
	if(LinkQueueTemp.pFront->pNext==NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
 }



// Input CloseTime
// 30
// Custom Count:17   250 Min    Average Time14 Min
// Press any key to continue




// Input CloseTime
// 10
// Custom Count:4   54 Min    Average Time13 Min
// Press any key to continue
