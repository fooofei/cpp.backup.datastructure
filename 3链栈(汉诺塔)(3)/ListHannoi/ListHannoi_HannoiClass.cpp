#include <iostream.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>

typedef struct _DATA_
{
	int a;
}Data,*pData;



typedef struct _NODE_
{
	Data DataTemp;
	_NODE_* pNext;
}Node,*pNode;





class Stack
{
public:
	Stack()
	{
		pHead = pTail = (pNode)malloc(sizeof(Node));


		pTail->pNext = NULL;
	}
	~Stack()
	{}
	Stack(Stack&);

	void PushStack(Data DataTemp);

	Data PopStack();

	int  IsEmpty();

	void ShowList();



private:
	pNode pHead,pTail;

};

void Stack::PushStack(Data DataTemp)
{
	pNode pNodeTemp = (pNode)malloc(sizeof(Node));

	if (pNodeTemp==NULL)
	{
		return;
	}
	else
	{
		pNodeTemp->pNext = NULL;
		pNodeTemp->DataTemp = DataTemp;

		pNodeTemp->pNext = pTail;

		pTail = pNodeTemp;
	}
}

Data Stack::PopStack()
{
	pNode pNodeTemp = NULL;
	Data  DataTemp = {0};
	if (pHead==pTail)
	{
		cout<<"Is Empty"<<endl;

		exit(0);
	}
	else
	{
		pNodeTemp = pTail;
		DataTemp = pNodeTemp->DataTemp;

		pTail = pTail->pNext;

		free(pNodeTemp);
		
		return DataTemp;
	}
}


int Stack::IsEmpty()
{
	if (pHead==pTail)
	{
		return 1;
	}

	return 0;
}


void Stack::ShowList()
{
	pNode pNodeTemp = pTail;
	while (pNodeTemp!=pHead)
	{
		cout<<pNodeTemp->DataTemp.a<<endl;

		pNodeTemp = pNodeTemp->pNext;
	}
}



class Hannoi
{
public:
	Hannoi(int n)
	{
		//在构造函数中进行赋值

		int i = 0;

		Data DataTemp = {0};
		for (i=0;i<n;i++)
		{
			
			DataTemp.a = i+1;
			
			MyHannoi[0].PushStack(DataTemp);
		}
	}

	void MoveHannoi(int n,int x,int y,int z);
	
	~Hannoi()
	{

	}
	public:
	Stack MyHannoi[3];
};


void Hannoi::MoveHannoi(int n,int x,int y,int z)
{

	Data DataTemp;

	if(n==1)
	{
		DataTemp = MyHannoi[x].PopStack();
		
		MyHannoi[y].PushStack(DataTemp);
	}
	
	else 
	{
		MoveHannoi(n-1,x,z,y);  // x source   y dest   z var

		DataTemp = MyHannoi[x].PopStack();

		MyHannoi[y].PushStack(DataTemp);


		MoveHannoi(n-1,z,y,x);     
	}
}



void main()
{
	Hannoi One(5);


	One.MoveHannoi(5,0,1,2);


	One.MyHannoi[1].ShowList();



}