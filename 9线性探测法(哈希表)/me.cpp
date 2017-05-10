#include <stdio.h>
#include <windows.h>

#define MAXDATA 7
#define MAXHASH 10


int Hash[MAXHASH];
int Data[MAXDATA];

void CreateHash(int nData)
{
	int nIndex = nData%MAXHASH;

	while (1)
	{
		if (Hash[nIndex]==-1)
		{
			Hash[nIndex] = nData;
			break;
		}
		else
		{
			nIndex = (nIndex+1)% MAXHASH;
		}
	}
	
}

void Print( int *p , int n)
{
	int i =0;
	for (i=0;i<n;i++)
	{
		printf("%4d",p[i]);
	}
	printf("\n");
}

int main()
{
	int i =0;

	for (i=0;i<MAXHASH;i++)
	{
		Hash[i] = -1;
	}

	for (i=0;i<MAXDATA;i++)
	{
		Data[i]  =rand()%MAXDATA+1;
	}

	Print(Data,MAXDATA);

	for (i=0;i<MAXDATA;i++)
	{
		CreateHash(Data[i]);
	}

	Print(Hash,MAXHASH);
}

// 7   2   7   6   4   3   6
// -1  -1   2   3   4  -1   6   7   7   6
// Press any key to continue
