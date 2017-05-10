#include <iostream>
#include <stdio.h>
using namespace std;


#define  EIGHT 4    // 这里可以更改为  4   16 

int iQueenArray[EIGHT]; //每一列挨个前进    逐步记录每一行

int g_iNum = 0;

void InitQueen();

void DecidePos(int iValue);

int Attack(int Row,int Col);

void Print();

void main()
{

	InitQueen();
	DecidePos(0);

}


void InitQueen()
{
	for (int i=0;i<EIGHT;i++)
	{
		iQueenArray[i] = -1;
	}
}
void DecidePos(int iValue)
{
	int i = 0;

	while(i<EIGHT)
	{
		if(!Attack(i,iValue))
		{
			iQueenArray[iValue] = i;
			if(iValue==EIGHT-1)
			{
				Print();
			}

			else
			{
				DecidePos(iValue+1);
			}
		}
		
		i++;
	}
}

int Attack(int Row,int Col)
{
	bool bOk = false;
	int iOffsetRow = 0;
	int iOffsetCol = 0;

	int i = 0;

	while(bOk==false && i<Col)
	{
		iOffsetRow = abs(iQueenArray[i]-Row);

		iOffsetCol = abs(i-Col);

			////判断两皇后是否在同一列或者同一对角线上
		if(iQueenArray[i]==Row||iOffsetRow==iOffsetCol)
		{
			bOk = true;
		}

		i++;

	}

	return bOk;
}

void Print()
{
	int i = 0;
	int j = 0;
	g_iNum++;

	cout<<EIGHT<<"皇后"<<g_iNum<<endl;

	for(i=0;i<EIGHT;i++)
	{
		for(j=0;j<EIGHT;j++)
		{
			if(iQueenArray[j] == i)
			{
				printf("#");
			}

			else
			{
				printf(".");
			}

		}
		printf("\n");
	}
}