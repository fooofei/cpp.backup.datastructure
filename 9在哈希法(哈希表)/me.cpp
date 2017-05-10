#include <stdio.h>
#include <windows.h>
//再哈希法就是一开始先设置一系列的哈希函数，如果使用第一种哈希函数出现异常时就改用第二种，如果第二种也出现异常则改用第三种
//一直到没有发生异常为止
//例如
//:方法1 key%n;
//:方法2 key*key
//:方法3 key*key%n
//等等

typedef struct _HASHNODE_
{
	int Data;
	_HASHNODE_ *pNext;
}HashNode,*pHashNode;


#define  HASHNODENUM 8
#define  HASHDATANUM 20

HashNode HashNodeTemp[HASHNODENUM];


void CreateHash(int nData)
{
	int nIndex = nData%HASHNODENUM;

	pHashNode pHashNodeTravel = NULL;

	pHashNode pHashNodeNew  = new HashNode;

	if (pHashNodeNew==NULL)
	{
		return;
	}

	pHashNodeNew->pNext = NULL;
	pHashNodeNew->Data = nData;

	pHashNodeTravel = HashNodeTemp[nIndex].pNext;

	if (pHashNodeTravel==NULL)
	{
		HashNodeTemp[nIndex].pNext = pHashNodeNew;
	}
	else
	{
		while (pHashNodeTravel->pNext!=NULL)
		{
			pHashNodeTravel = pHashNodeTravel->pNext;
		}

		pHashNodeTravel->pNext = pHashNodeNew;
	}
}

void PrintHash(int nIndex)
{
	printf("索引 %d \t",nIndex);

	pHashNode pHashNodeTravel = HashNodeTemp[nIndex].pNext;

	while (pHashNodeTravel!=NULL)
	{
		printf("%4d",pHashNodeTravel->Data);

		pHashNodeTravel = pHashNodeTravel->pNext;
	}

	printf("\n");
}
int main()
{
	int i =0;
	for (i=0;i<HASHNODENUM;i++)
	{
		HashNodeTemp[i].Data = -1;
		HashNodeTemp[i].pNext = NULL;

	}

	int nData[HASHDATANUM] = {0};

	for (i=0;i<HASHDATANUM;i++)
	{
		nData[i] = rand()%30+1;
		printf("%4d",nData[i]);
		if (i%8==7)
		{
			printf("\n");
		}
	}
	printf("\n");

	for (i=0;i<HASHDATANUM;i++)
	{
		CreateHash(nData[i]);
	}

	for(i=0;i<HASHNODENUM;i++)
	{
		PrintHash(i);

	}


}  


// 12  18   5  11  30   5  19  19
// 23  15   6   6   2  28   2  12
// 26   3  28   7
// 索引 0
// 索引 1
// 索引 2    18   2   2  26
// 索引 3    11  19  19   3
// 索引 4    12  28  12  28
// 索引 5     5   5
// 索引 6    30   6   6
// 索引 7    23  15   7
// Press any key to continue