#include "list.h"
#include "queue.h"

#define  QUEUE_NUM 5  //客户队列    
#define  INTERVAL_TIME 5//相邻的两个用户为  5
#define  BIG_TIME 30//用户耽搁时间

CList g_ListTemp;
EVENT g_EventCurrent;
EVENT g_EventNext;
QUEUELEMENT g_CustomData;

CQueue g_QueueTemp[QUEUE_NUM];

int g_iTotalTime ; // 无需初始化 全局变量会自动初始化
int g_iCustomNum;
int g_iCloseTime;

int CompareTime(EVENT a, EVENT b);

void OpenForDay();
int MiniQueue();
void BankCalc();

void CustomArrived();
void CurtomDeparture();
int main()
{
	_tprintf(_T("Input CloseTime\n"));
	_tscanf_s(_T("%d"),&g_iCloseTime);
	BankCalc();
	return 0;
}

int CompareTime(EVENT a, EVENT b)
{
	return (a.iOccurTime-b.iOccurTime);
}

void OpenForDay()
{
	//初始化操作

	g_iTotalTime =0;
	g_iCustomNum = 0;
	g_ListTemp.InitList();

	//第一个客户到达事件

	g_EventCurrent.iOccurTime =0;
	g_EventCurrent.iType =0;

	g_ListTemp.InsertList(g_EventCurrent,CompareTime);

	for (int i=1;i<5;i++)
	{
		g_QueueTemp[i].InitQueue();
	}

}
int MiniQueue()
{
	int i =1;
	int j =1;
	int Num[5] = {0};
	for (i=1;i<QUEUE_NUM;i++)
	{
		Num[i] = g_QueueTemp[i].GetQueueLength();
	}
	Num[0] = Num[1];

	for (i=1;i<QUEUE_NUM;i++)
	{
		if (Num[i]<Num[0])
		{
			Num[0] = Num[i];

			j=i;
		}
	}

	return j;

}
void BankCalc()
{
	OpenForDay();

	EVENT EventTemp = {0};

	while (!g_ListTemp.IsEmpty())
	{
		EventTemp = g_ListTemp.DeleteFirst();

		g_EventCurrent.iOccurTime = EventTemp.iOccurTime;

		g_EventCurrent.iType = EventTemp.iType;

		if (g_EventCurrent.iType==0)
		{
			CustomArrived();
		}
		else
		{
			CurtomDeparture();
		}
	}

	_tprintf(_T("Custom Count:%d   %d Min    Average Time%4.2lf Min\n"),
		g_iCustomNum,g_iTotalTime,(float)g_iTotalTime/g_iCustomNum);
}

void CustomArrived() //一个客户到达队列  先产生下一个客户到达Event  然后产生自己的 离开Event 
{
	g_iCustomNum++;
	int DurTime = rand()%BIG_TIME+1; //当前客户停留时间
	int InterTime = rand()%INTERVAL_TIME+1;


	g_EventNext.iOccurTime = g_EventCurrent.iOccurTime+InterTime; //下一个客户到达时间
	g_EventNext.iType =0;

	if (g_EventNext.iOccurTime<g_iCloseTime)
	{
		g_ListTemp.InsertList(g_EventNext,CompareTime);
	}

	int i = MiniQueue();

	QUEUELEMENT QueueElementTemp = {0};
	QueueElementTemp.iArrivalTime = g_EventCurrent.iOccurTime;
	QueueElementTemp.iDuration = DurTime;

	g_QueueTemp[i].EnQueue(QueueElementTemp);

	if (g_QueueTemp[i].GetQueueLength()==1)  //因为上面已经插入到了 队列 所以  长度不是 0
	{
		g_EventNext.iOccurTime = g_EventCurrent.iOccurTime + DurTime ;
		g_EventNext.iType= i;
		g_ListTemp.InsertList(g_EventNext,CompareTime);
	}
}
void CurtomDeparture()
{
	int i =g_EventCurrent.iType;

	g_CustomData = g_QueueTemp[i].DeQueue();

	g_iTotalTime += g_EventCurrent.iOccurTime - g_CustomData.iArrivalTime;

	//处理该队列中之后的用户并插入到事件链表中

	if (!g_QueueTemp[i].IsEmpty())
	{
		g_CustomData=  g_QueueTemp[i].GetHeadElement();
		g_EventNext.iOccurTime = 	g_EventCurrent.iOccurTime+ g_CustomData.iDuration;

		g_EventNext.iType = i;

		g_ListTemp.InsertList(g_EventNext,CompareTime);
	}

}

//
// Input CloseTime
// 30
// Custom Count:11   209 Min    Average Time19.00 Min
// 请按任意键继续. . .
