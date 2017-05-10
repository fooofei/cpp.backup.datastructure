#include <iostream>
#include "SRANDARRAY.H"
using namespace std;

int Partition(int a[],int Left,int Right)
{
	int Temp = a[Left];

	while(Left<Right)
	{
		while(Left<Right && a[Right]>=Temp)
		{
			Right--;
		}
   
     a[Left]  =  a[Right]; 

		while(Left<Right && a[Left]<=Temp)
		{
			Left++;
		}
   
     a[Right] = a[Left];
    
	}

  a[Left] = Temp;
	return Right;
}

void QuickSort(int a[], int Left,int Right)
{
	if(Left<Right)
	{
		int m = Partition(a,Left,Right);

		QuickSort(a,Left,m-1);

		QuickSort(a,m+1,Right);
	}
}


void  QuickSort_X(int a[], int Left,int Right)
{
  if(Left<Right)
  {
     int i = Left;

     int j = Right;

     int temp = a[i];

     while (i<j)
     {
       while (i<j&&a[j]>=temp)
       {
         --j;
       }
       a[i] = a[j];

       while (i<j &&a[i]<=temp)
       {
         ++i;
       }
       a[j] = a[i];
     }
  
  
     a[i] = temp;

     QuickSort_X(a,Left,i-1);

     QuickSort_X(a,i+1,Right);
  }
}


// 效果不如我自己的好 奇怪 为什么速度比我的慢了四倍呢 
int main()
{

  int a[] = {1,4,2,3};

  int size = sizeof(a)/sizeof(int);

	int i =0;
	
	QuickSort(a,0,size-1);
	for (i=0;i<size;++i)
	{
		printf("%d ",a[i]);
	}

	/*

  SRANDARRAY<int> Array;
  
  const int N = 100000;
  
  clock_t start, end;
  
  
  Array.CreateArray(1,N);
  
  srand(time(NULL));
  
  start = clock();
  
  QuickSort_X(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
  
  end = clock();
  
  printf("QuickSort:%5d\n",(end - start));
  
  
  Array.DestroyArray();*/

  return 0;
}