#include <iostream>
#include <stdio.h>
using namespace std;


#define  EIGHT 4    // ������Ը���Ϊ  4   16 

// queen ������ ������  �����ֵ������
int iQueenArray[EIGHT]; //ÿһ�а���ǰ��    �𲽼�¼ÿһ��

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
		Print(); // ��ʵ��ӡ��֮��   iValue �� 4  �������ǵĻʺ�����
		// �в����Ϊ�����ľ��� Ӧ���������βŶ�, ��Ϊ���Ҳ��� �����Լ��Ż���
		// 
	}

	while(i<EIGHT)
	{
		if(!Attack(i,iValue)) //��Ϊ����������  ���� ��Ҫ�ж��� �ͶԽ���
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

		////�ж����ʺ��Ƿ���ͬһ�л���ͬһ�Խ�����
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
				printf("(%d,%d)",i+1,iQueenArray[i] + 1); // ���Ƕ� +1 ��ӡ����λ���� ����������
			}
		}
		
	}printf("\n");
}