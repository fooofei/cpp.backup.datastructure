#include <iostream>
#include <stdio.h>
using namespace std;


#define  EIGHT 4    // 这里可以更改为  4   16 

// queen 的索引 代表列  数组的值代表行
int iQueenArray[EIGHT]; //每一列挨个前进    逐步记录每一行

int g_iNum = 0;

void InitQueen();

void DecidePos(int iValue);

int Attack(int Row,int Col);

void Print();

void main()
{

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

	if (iValue>=EIGHT)
	{
		Print(); // 其实打印完之后   iValue 是 4  但是我们的皇后阵列
		// 中不会成为这样的矩形 应该是正方形才对, 因为他找不到 所以自己才回溯
		// 
	}

	while(i<EIGHT)
	{
		if(!Attack(i,iValue)) //因为索引代表列  所以 需要判断行 和对角线
		{
			iQueenArray[iValue] = i;
	
			DecidePos(iValue+1);
	
		}

		i++;
	}
}

int Attack(int Row,int Col)
{
	int i = 0;

	while(i<Col)
	{

		////判断两皇后是否在同一列或者同一对角线上
		if(iQueenArray[i]==Row||abs(iQueenArray[i]-Row)==abs(i-Col))
		{
			return 1;
		}

		i++;

	}

	return 0;
}

void Print()
{
	int i = 0;
	int j = 0;
	g_iNum++;


	for(i=0;i<EIGHT;i++)
	{
		for(j=0;j<EIGHT;j++)
		{
			if(iQueenArray[j] == i)
			{
				printf("(%d,%d)",i+1,iQueenArray[i] + 1); // 我们都 +1 打印的是位置了 不再是索引
			}
		}
		
	}printf("\n");
}