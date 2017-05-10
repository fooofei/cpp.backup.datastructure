#include "CycleQueue.h"


#include <iostream>
using namespace std;
//使用循环队列打印杨辉三角


void displayYanghuiTriangle(int row)
{

	CCycleQueue<int> Obj(row);

	int i = 0;
	int x = 0;
	int j = 0;
	int y =0;
	int k = 0;
	for (i=0;i<row;i++)
	{
		cout<<" ";
	}
	cout<<1<<endl;
	Obj.EnQueue(1);  //  1 3 3  1
	for (i=2;i<=row;i++) // i = 4
	{
		for (k=0;k<row-i+1;k++)
		{
			cout<<" ";
		}
		Obj.EnQueue(1);
		for(j=1;j<i;j++)
		{
			Obj.DeQueue(x);
			cout<<x<<" ";
			Obj.GetBase(y);
			Obj.EnQueue(x+y);
		}
		cout<<1<<endl;

	}
}

int main ()
{
	
	cout<<"输入行数\n";
	int Row = 0;
	cin>>Row;

	displayYanghuiTriangle(Row);
	return 0;
}