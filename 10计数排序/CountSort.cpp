#include <STDIO.H>
#include <WINDOWS.H>


void CountSort(int a[], int iStart, int iEnd);
int main()
{

	int a[] = {3,8,2,6,9};

	int Count = sizeof(a)/sizeof(int);
	CountSort(a,0,Count-1);
	printf("\nAfter:");
	for (int i = 0;i<Count;++i)
	{
		printf("%d ",a[i]);
	}
	return 0;
}


void CountSort(int a[], int iStart, int iEnd)
{
	if(a == NULL || iEnd<=iStart)
		return;
	int i,CountMax = a[iStart];

	for (i=iStart+1;i<=iEnd;++i)
	{
		if(CountMax<a[i])
			CountMax = a[i];
	}

	int *table = new int[CountMax+1];
	memset(table,0,sizeof(int)*(CountMax+1));

	for (i=iStart;i<=iEnd;++i)
	{
		table[a[i]] ++;
	}

	for (i=1;i<=CountMax;++i)
	{
		table[i] += table[i-1];
	}

	//int *pTemp = new int[iEnd-iStart+1];
	int* pTemp = (int*)malloc(sizeof(int)*(iEnd-iStart+2));
	memset(pTemp,0,sizeof(int)*(iEnd-iStart+2));

	for (i=iStart;i<=iEnd;++i)
	{
		pTemp[table[a[i]]] = a[i];
		table[a[i]]--;
	}

	int j = 1;
	for (i = iStart;i<=iEnd;++i,++j)
	{
		a[i] = pTemp[j];
	}

	delete[] table;
	//delete[] pTemp;
	free(pTemp);
}