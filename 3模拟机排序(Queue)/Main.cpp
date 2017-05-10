#include <iostream>
#include "QUEUE.H"
using namespace std;



void inline displayArray(int array[], int size)
{
	int i;
	for (i=0;i<size;i++)
	{
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

/************************************************************************/
/* 适合1位数和两位数                                                  */
/************************************************************************/
int main()
{
	QUEUE<int> One[10];
	
	int iNum[] = {23,123,154,54,34,65,12,32,43,66,11,13,14,45,67,78,89,77,88,44,17,49};
	const int c_array_size = sizeof(iNum)/sizeof(int);

	int i =0;

	cout<<"排序之前iNum\n";
	displayArray(iNum,c_array_size);

	

	cout<<"第一次入队\n";
	for (i= 0;i<c_array_size;i++)
	{
		One[iNum[i]%10].enQueue(iNum[i]);
	}


	int j =0;
	int iCount = 0;
	for (i=0;i<10;i++)
	{
		while (!One[i].isEmpty())
		{
			One[i].deQueue(&j);
			iNum[iCount] = j;
			iCount++;
		}
	}

	cout<<"第一次入队之后出队iNum\n";
	displayArray(iNum,c_array_size);

	cout<<"第二次入队\n";

	for (i= 0;i<c_array_size;i++)
	{
		One[(iNum[i]/10)%10].enQueue(iNum[i]);
	}

	iCount=0;
	for (i=0;i<10;i++)
	{
		while (!One[i].isEmpty())
		{
			One[i].deQueue(&j);
			iNum[iCount] = j;
			iCount++;
		}
	}
	cout<<"第二次入队后出队iNum\n";
	displayArray(iNum,c_array_size);
}