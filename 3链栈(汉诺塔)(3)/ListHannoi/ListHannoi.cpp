#include <stdio.h>
#include <iostream>
using namespace std;


typedef struct _NODE_
{
	int Data;
	_NODE_* pNext;
}Node,*pNode;

//Ð´Ò»¸öÁ´Õ»
class Stack
{
public:
	pNode pHead;
	int nNodeCount;
public:
	void InitStack();
	void Push(int Data);
	int Pop();
	
};

void Stack::InitStack()
{
	pHead = NULL;
	nNodeCount = 0;
}
void Stack::Push(int Data)
{
	pNode pNodeNew = new Node;
	pNodeNew->Data = Data;
	pNodeNew->pNext = NULL;
	
	pNodeNew->pNext = pHead;
	pHead = pNodeNew;
	nNodeCount ++;
}
int Stack::Pop()
{
	while (pHead!=NULL)
	{
		pNode pNodeTemp = pHead;
		int a = pNodeTemp->Data;
		
		pHead = pHead ->pNext;

		delete pNodeTemp;
		
		return a;

		nNodeCount --;
	}
	return 0;

}

void MoveHannoi(int n , Stack& x ,Stack& y , Stack& z)
{
	if (n>0)
	{
		
		MoveHannoi(n-1,x,z,y);
		int Data = x.Pop();
		y.Push(Data);
		MoveHannoi(n-1,z,y,x);


	}
}

void main()
{
	Stack  Hannoi[3];
	Hannoi[0].InitStack();
	Hannoi[1].InitStack();
	Hannoi[2].InitStack();

	int Num = 5;

	int i  = 0;

	for (i=0;i<Num;i++)
	{
		Hannoi[0].Push(i+1);
	}

	MoveHannoi(Num,Hannoi[0],
	Hannoi[1],
	Hannoi[2]); 

	for (i=0;i<Num;i++)
	{
		int Data = Hannoi[1].Pop();
		printf("%d ",Data);
	}



}


//5 4 3 2 1 Press any key to continue