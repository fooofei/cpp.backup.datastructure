#include <stdio.h>
#include <windows.h>



#define MAX_LENGTH_INSERT_SORT 7 // ������50

void Swap(int &a, int &b)
{
	if(&a == &b)
		return;

	a^= b^= a^= b;
}

int Partition(int* array, int start,int end)
{
	//array[0] = array[start]; // ��ҪĬ���õ�һ��Ԫ����Ϊ��Ŧ ����ʹ����·ѡ��

	int mid = start + ((end-start)>>1); // һ�� (start+end)/2 ����ôд

	if(array[start]>array[end])
		Swap(array[start],array[end]);
	if(array[mid]>array[end])
		Swap(array[mid],array[end]);

	if(array[mid]>array[start])
		Swap(array[mid],array[start]);

	// ��ʱ start ��  ������ ���м�ֵ
	array[0] = array[start];
	while (start<end)
	{
		while (start<end && array[end]>=array[0])
		{
			end--;
		}
		array[start] = array[end];

		while (start<end && array[start]<=array[0])
		{
			start++;
		}
		array[end] = array[start];
	}

	array[start] = array[0];

	return start;
}

void InsertSort(int *array , int start, int end)
{
	int i,j;
	for (i=start+1;i<=end;++i)
	{
		array[0] = array[i];

		for (j=i-1;array[j]>array[0];--j)
		{
			array[j+1] =array[j];
		}

		array[j+1] = array[0];
	}
}


void QuickSort(int* array , int start , int end)
{
	if ((end-start)>MAX_LENGTH_INSERT_SORT)
	{
		while (start<end)
		{
			int pivot = Partition(array,start,end);
			QuickSort(array,start,pivot-1);
			start = pivot+1;  // α�ݹ�  ��ֹʹ�ù����ջ�ڴ�
		}
	} 
	else
	{
		InsertSort(array,start,end);
	}

}


// ����0Ԫ�ز�ʹ��  ʹ�õĻ�����ѧ  
int main()
{

	int a[] =  {0,76,34,85,63,35,23};

	int size = sizeof(a)/sizeof(int);

	QuickSort(a,1,size-1);	
	for (int i =1;i<size;++i)
	{
		printf("%d ",a[i]);
	}

	printf("\n");

	return 0;
}