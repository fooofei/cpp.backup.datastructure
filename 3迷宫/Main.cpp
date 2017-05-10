
#include <iostream>
#include <Windows.h>
#include "stack.h"
using namespace std;
#define MAX  3
//����һ����ά���� ����ʼ��

int iNum[MAX][MAX] = {
	// 	{1,1,1,0},
	// 	{0,0,1,1},
	// 	{0,1,1,0},
	// 	{1,1,1,1}

	{1,0,0},
	{1,1,1},
	{0,1,1}
};


typedef struct tagPOSITION
{
	int Row;
	int Col;
}POSITION,*PPOSITION;


void visit(POSITION p)
{
	printf("Row=%d,Col=%d\n" ,p.Row,p.Col);
}

void InitFlag(int flag[][MAX])//��ʼ���Թ�
{
	int i = 0;
	int j = 0;
	for (i=0;i<MAX;i++)
	{
		for (j=0;j<MAX;j++)
		{
			flag[i][j] = -1;
		}
	}
}

int main ()
{
	int iFlag[MAX][MAX] = {0};//��������
	bool bEndFlag = false;
	InitFlag(iFlag);
	STACK<POSITION> Object;
	//��ʼ����
	POSITION StartPos;
	StartPos.Row = 0;
	StartPos.Col = 0;
	//��������
	POSITION EndPos;
	EndPos.Row = 2;
	EndPos.Col = 2;

	POSITION PosNew = {0};
	POSITION PosCurrent= {0};

	Object.push(StartPos);
	iFlag[StartPos.Row][StartPos.Col] = 1;

	int i = 0;
	while(!Object.isEmpty()&&bEndFlag==false)
	{
		 Object.top(PosCurrent);


		// �ĸ�����
		for (i=0;i<4;i++)
		{
			if (i==0)
			{
				PosNew.Row = PosCurrent.Row+1;
				PosNew.Col = PosCurrent.Col;
			}
			else if (i==1)
			{	
				PosNew.Row = PosCurrent.Row-1;
				PosNew.Col = PosCurrent.Col;
			}

			else if (i==2)
			{
				PosNew.Row = PosCurrent.Row;
				PosNew.Col = PosCurrent.Col+1;
			}

			else
			{

				PosNew.Row = PosCurrent.Row;
				PosNew.Col = PosCurrent.Col-1;
			}
			if (iNum[PosNew.Row][PosNew.Col]==1&&iFlag[PosNew.Row][PosNew.Col]==-1)//���Ե� �ͽ�ջ
			{
				if(PosNew.Row==EndPos.Row&&PosNew.Col==EndPos.Col )
				{
					bEndFlag = true;
				}
				Object.push(PosNew);
				iFlag[PosNew.Row][PosNew.Col]=1;

				break;
			}

			if (PosNew.Row<0||PosNew.Row>3||PosNew.Col<0||PosNew.Col>3)//Խ������
			{
				continue;
			}
			// 
			// 			if (PosNew.Row==EndPos.Row&&PosNew.Col==EndPos.Col )//�ս��  ��Ҫд &&g_iFlag[PosNew.Row][PosNew.Col]==-1
			// 			{													//Ϊ��ֹ������������׷����������׿������Ĵ���  �ش��޸İ汾
			// 				Object.Push(PosNew);
			// 				g_iFlag[PosNew.Row][PosNew.Col]=1;
			// 				
			// 				break;
			// 			}

		}
		if (i==4)
		{
			Object.pop(NULL);
		}


	}

	Object.traverse(visit);

}


