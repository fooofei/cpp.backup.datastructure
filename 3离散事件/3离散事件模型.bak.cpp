#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>
#include <malloc.h>
#include <math.h>

//  哥的代码有错误  更改了好几处
#define Queue  4   //客户队列为  4

#define IntervalTime  5  //相邻的两个用户为  5

#define BigTime 30  //用户耽搁时间





typedef struct _EVENT_  //定义事件
{
	int iOccurTime;  //事件发生时间
	int iType;       //何种事件  -1 是发生事件  数字该窗口完成事件
}Event,*pEvent;


//定义事件链表
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


//定义队列中的数据元素

typedef struct _QUEUEELEMENT_ 
{
	int iArrivalTime;     //到达时间
	int iDuration;        //办理需要的时间
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



//事件有序链表

bool InitList(pList pListTemp);//创建一个空结点  连接到 pListTemp 

void InsertList(pList pListTemp,Event EventTemp,int (*CompareTime)(Event,Event));

bool ListEmpty(pList pListTemp);

pNode GetListHead(pList pListTemp);



void DelFirst(pList pListTemp,pNode& pNodeHead,pNode& pNodeTemp);
// 删除 pNodeHead 之后的一个节点  并且 通过pNodeTemp 返回一个有事件的结点   
Event GetCurElem(pNode pNodeTemp);




bool InitQueue(pLinkQueue pLinkQueueTemp);//队列  具有 空的头节点 

int QueueLength(LinkQueue LinkQueueTemp);

void InsertQueue(pLinkQueue pLinkQueueTemp,QueueElement QueueElementTemp);

void DeQueue(pLinkQueue pLinkQueueTemp,pQueueElement pQueueElementTemp);



void GetHead(pLinkQueue pLinkQueueTemp,pQueueElement pQueueElementTemp);

bool QueueEmpty(LinkQueue LinkQueueTemp);



List ListTemp;   // 事件链表

Event EventCurrent; //当前用户

Event EventNext;                  //	下个用户


QueueElement CustomData;

LinkQueue QueueTemp[Queue];

int TotalTime = 0;  //累计客户逗留时间
int CustomNum = 0;  //客户总数
int CloseTime = 0;

int CompareTime(Event a,Event b);
void OpenForDay();

void Random(int* m,int* n);

int Mini(LinkQueue* LinkQueueTemp);

void BankCalc();

void CustomArrived();   //处理客户的到达

void CustomDeparture();  //处理离开


void main()
{

	printf("Input CloseTime\n");


	scanf("%d",&CloseTime);


	BankCalc();

	//释放 内存

// 	if(ListTemp.pHead->pNext!=NULL)
// 	{
// 		printf("SHABI\n");
// 	}

	if (QueueLength(QueueTemp[0])>0)
	{
		printf("SHABI\n");//打印傻逼 说明队列并没有清空 
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

	return  (a.iOccurTime - b.iOccurTime);  //1  或是 -1 被返回
	//返回值问题     加括号 
	
}


void Random(int* m,int* n)
{
	*m = rand()%BigTime+1;

	*n = rand()%IntervalTime+1;
}


//计算我们4个队列中成员最少的并返回

int Mini(LinkQueue* LinkQueueTemp)
{
	int a[Queue] = {0};

	int i = 0;
	for (i=0;i<Queue;i++)
	{
		a[i] = QueueLength(LinkQueueTemp[i]);
	}


	//从整形数据中找到最大的一个并返回索引

	int j = 0;


	for (i=1;i<Queue;i++)  //冒泡的第一循环     
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

	//当第一事件发送 时间为 0
	
	EventCurrent.iOccurTime = 0;

	EventCurrent.iType = -1;// 更改


	//将事件插入我们的事件链表中

	InsertList(&ListTemp,EventCurrent,CompareTime);

	//将我们的4个队列清空

	int i = 0;
	for (i=0;i<Queue;i++)
	{
		InitQueue(&QueueTemp[i]);
	}


}


void CustomArrived()
{

	CustomNum++;
	
	int DurtTime = 0; //到达时间
	int InterTime = 0;//办理需要的时间
	Random(&DurtTime,&InterTime);     //   客户到达时间和客户与客户之间的间隔时间随机产生

	
	EventNext.iOccurTime = EventCurrent.iOccurTime + InterTime;
	
	EventNext.iType = -1; //更改
	
	
	//要与关门时间进行比较
	
	if (EventNext.iOccurTime<CloseTime)   
	{
		
		//将该事件插入我们的事件链表
		
		InsertList(&ListTemp,EventNext,CompareTime);


	}	
		
		//计算长度最短的队列
		
		int i = Mini(QueueTemp); //获得队列的索引将该用户插入
		
		QueueElement QueueDataTemp;
		
		
		QueueDataTemp.iArrivalTime = EventCurrent.iOccurTime;
		
		QueueDataTemp.iDuration = DurtTime;
		
		
		InsertQueue(&QueueTemp[i],QueueDataTemp); //插入队列
		
		if (QueueLength(QueueTemp[i])==1)
		{
			//  设置离开事件并插入事件链表
			
			
			EventNext.iOccurTime = EventCurrent.iOccurTime + DurtTime;
			
			EventNext.iType = i;
			
			InsertList(&ListTemp,EventNext,CompareTime);
		}
		
		
		
	
}

void CustomDeparture()
{
	//从队列中删除我们用户并计算时间耗用

	int i = 0;

	i = EventCurrent.iType;

	DeQueue(&QueueTemp[i],&CustomData);//队列元素


	TotalTime += EventCurrent.iOccurTime - CustomData.iArrivalTime;//????


	//处理该队列中之后的用户并插入到事件链表中


	if (!QueueEmpty(QueueTemp[i]))
	{
		GetHead(&QueueTemp[i],&CustomData);


		EventNext.iOccurTime = EventCurrent.iOccurTime + CustomData.iDuration;//更改 

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
	// 删除 pNodeHead 之后的第二个节点  并且 通过pNodeTemp 返回去 

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


bool InitList(pList pListTemp)//创建一个空结点  连接到 pListTemp 
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

	while (pNodeTemp!=NULL&&CompareTime(pNodeTemp->EventData,EventTemp)<0)  // 比较发生时间  
	{											//插入到  pNodePre  pNodeTemp 之间
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

	//万一插到尾部

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



bool InitQueue(pLinkQueue pLinkQueueTemp) //队列  具有 空的头节点 
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

		*pQueueElementTemp = pQueueNodeTemp->QueueData;   //队列的头是空节点

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
