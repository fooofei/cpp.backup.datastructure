#include <stdio.h>
#include <windows.h>
//�ٹ�ϣ������һ��ʼ������һϵ�еĹ�ϣ���������ʹ�õ�һ�ֹ�ϣ���������쳣ʱ�͸��õڶ��֣�����ڶ���Ҳ�����쳣����õ�����
//һֱ��û�з����쳣Ϊֹ
//����
//:����1 key%n;
//:����2 key*key
//:����3 key*key%n
//�ȵ�

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
	printf("���� %d \t",nIndex);

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
// ���� 0
// ���� 1
// ���� 2    18   2   2  26
// ���� 3    11  19  19   3
// ���� 4    12  28  12  28
// ���� 5     5   5
// ���� 6    30   6   6
// ���� 7    23  15   7
// Press any key to continue