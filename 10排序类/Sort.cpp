#include <STDIO.H>
#include <ASSERT.H>
#include <MATH.H>
#include "SRANDARRAY.H"

// 经过对比测试  我得到的结论是 我需要掌握 快速排序  希尔排序 堆排序 


#define MAX_LENGTH_INSERT_SORT 7 // 或者50  快速排序中使用插入排序的域阀值

template <typename SORTDATA>
class SORT
{
public:
  void SelectSort(SORTDATA a[], int iStart, int iEnd);

  void InsertSort(SORTDATA a[], int iStart, int iEnd);

  void QuickSort_Old(SORTDATA a[], int iStart, int iEnd);
	void QuickSort_New(SORTDATA a[], int iStart, int iEnd); // 2013-1-11 学习大话数据结构之后 优化了算法

  void HeapSort(SORTDATA a[], int iStart,  int iEnd);

  void BubbleSort(SORTDATA a[], int iStart, int iEnd);

  void CockTailSort(SORTDATA a[], int iStart, int iEnd);// 鸡尾酒排序(双向冒泡排序)

  void ShellSort(SORTDATA a[], int iStart, int iEnd);

  void MergeSort(SORTDATA a[], int iStart, int iEnd);
protected:
  void Swap(SORTDATA &a, SORTDATA &b);
  int Partition(SORTDATA a[], int iStart, int iEnd);
  void Sift(SORTDATA a[], int iStart , int iEnd);
  void Merge(SORTDATA a[], int iStart, int iMid , int iEnd);
};




int main()
{

	
  // 这种测试 应该不准   

  SRANDARRAY<int> Array;

  SORT<int> Sort;

  const int N = 500;

  clock_t start, end;


  
  Array.CreateArray(1,N);
  
  srand(time(NULL));
  
  start = clock();
  
  Sort.MergeSort(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
  
  end = clock();
  
  printf("MergeSort:%5d\n",(end - start));
  
  
  Array.DestroyArray();
  
  
  //////////////////////////////////////////////////////////////////////////

  Array.CreateArray(1,N);  // 一百万的时候 希尔排序是可以的  快速排序就会栈溢出
  
  srand(time(NULL));
  
  start = clock();
  
  Sort.ShellSort(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
  
  end = clock();
  
  printf("ShellSort:%5d\n",(end - start));
  
  Array.DestroyArray();

  //////////////////////////////////////////////////////////////////////////
 
  Array.CreateArray(1,N);
  
  srand(time(NULL));
  
  start = clock();
  
  Sort.QuickSort_Old(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
  
  end = clock();
  
  printf("QuickSort_Old:%5d\n",(end - start));
  

	Array.DisplayArray();
  Array.DestroyArray();


	//////////////////////////////////////////////////////////////////////////

	 Array.CreateArray(1,N);
	 
	 srand(time(NULL));
	 
	 start = clock();
	 
	 Sort.QuickSort_New(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
	 
	 end = clock();
	 
	 printf("QuickSort_New:%5d\n",(end - start));
	 
	 Array.DisplayArray();
	 
  Array.DestroyArray();
 

  //////////////////////////////////////////////////////////////////////////

    Array.CreateArray(1,N);
    
    srand(time(NULL));

    start = clock();
    
  //  Sort.SelectSort(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
    
    end = clock();
    
    printf("SelectSort:%5d\n",(end - start));

    Array.DestroyArray();

//////////////////////////////////////////////////////////////////////////


    Array.CreateArray(1,N);
    
    srand(time(NULL));
    
    start = clock();
    
    Sort.InsertSort(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
    
    end = clock();
    
    printf("InsertSort:%5d\n",(end - start));
    
    Array.DestroyArray();
   
//////////////////////////////////////////////////////////////////////////



  Array.CreateArray(1,N);
  
  srand(time(NULL));
  
  start = clock();
  
  Sort.HeapSort(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
  
  end = clock();
  
  printf("HeapSort:%5d\n",(end - start));

  Array.DestroyArray();


    //////////////////////////////////////////////////////////////////////////


  Array.CreateArray(1,N);
  
  srand(time(NULL));
  
  start = clock();
  
 // Sort.BubbleSort(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
  
  end = clock();
  
  printf("BubbleSort:%5d\n",(end - start));
  
  Array.DestroyArray();



  //////////////////////////////////////////////////////////////////////////

  Array.CreateArray(1,N);
  
  srand(time(NULL));
  
  start = clock();
  
 // Sort.CockTailSort(Array.m_pData,Array.m_iArrayStart,Array.m_iArrayEnd);
  
  end = clock();
  
  printf("CockTailSort:%5d\n",(end - start));
  
  Array.DestroyArray();





  printf("\n");

  


  
  return 0;
}

template <typename SORTDATA>
inline void SORT<SORTDATA>::Swap(SORTDATA &a, SORTDATA &b)
{
  if (&a==&b)
  {
    return;
  }
  a ^= b ^= a ^= b;
}



template <typename SORTDATA>
void SORT<SORTDATA>::SelectSort(SORTDATA a[], int iStart, int iEnd)
{
  int i = 0;
  
  int j = 0;
  
  int Min = 0;
  
  for (i=iStart;i<iEnd;++i)
  {
    Min  =i;
    
    for (j=i+1;j<=iEnd;++j)
    {
      if (a[Min]>a[j])
      {
        Min = j;
      }
    }
    
    if (Min!=i)
    {
      Swap(a[i],a[Min]);
    }
  }
  
}




template <typename SORTDATA>
void SORT<SORTDATA>::InsertSort(SORTDATA a[],int iStart, int iEnd)
{
  int i = 0;

  int j = 0;

  SORTDATA temp ; 

  for (i=iStart+1;i<=iEnd;++i)
  {
    temp = a[i];
    
    for (j=i-1;j>=iStart && temp<a[j] ;--j)
    {
      a[j+1] = a[j] ;
    }
    
    a[j+1] = temp;
  }
}


template <typename SORTDATA>
void SORT<SORTDATA>::QuickSort_New(SORTDATA a[], int iStart, int iEnd) // 2013-1-11 学习大话数据结构之后 优化了算法
{
	if ((iEnd-iStart) >MAX_LENGTH_INSERT_SORT) // 优化一 当数组小的时候 使用插入排序最佳
	{
		int iPivot;
		while (iStart<iEnd)  // 优化二 使用循环  来代替递归  
		{
			iPivot = Partition(a,iStart,iEnd);

			QuickSort_New(a,iStart,iPivot-1);

			iStart = iPivot+1;
		}
	}
	else
		InsertSort(a,iStart,iEnd);
}

template <typename SORTDATA>
void SORT<SORTDATA>::QuickSort_Old(SORTDATA a[], int iStart, int iEnd)
{
  // 这是老套路的 使用两个函数实现的方法    假如有规定只允许我们使用一个函数
  if (iStart<iEnd)
  {
    int iMid = Partition(a,iStart,iEnd);

    QuickSort_Old(a,iStart,iMid-1);

    QuickSort_Old(a,iMid+1,iEnd);
  }

  // 那就这样实现了
  // 经过实践证明  下面单个函数实现的方法 不如上边两个函数实现更加高效  下面的方法消耗的时间是上面的三倍

  /*
  int iLow = iStart, iHigh = iEnd;

  SORTDATA temp = a[iLow];
  
  while (iLow<iHigh)
  {
    while (iLow<iHigh&& temp<=a[iHigh])
    {
      --iHigh;
    }
    Swap(a[iHigh],a[iLow]);
    
    while (iLow<iHigh && temp>=a[iLow])
    {
      ++iLow;
    }
    
    Swap(a[iLow],a[iHigh]);
  }

  a[iLow] =temp;

  if (iStart!=iLow)
  {
    QuickSort(a,iStart,iLow-1);
  }

  if (iEnd!=iHigh)
  {
    QuickSort(a,iHigh+1,iEnd);
  }

  */
}

template <typename SORTDATA>
int SORT<SORTDATA>::Partition(SORTDATA a[], int iStart, int iEnd)
{

	// 三路取中值   为了更好地得到 枢纽值
	int iMid = iStart + ((iEnd-iStart)>>1);
	if(a[iStart] > a[iEnd])
		Swap(a[iStart] , a[iEnd]);
	if(a[iMid] > a[iEnd])
		Swap(a[iMid] , a[iEnd]);
	if(a[iMid] > a[iStart])
		Swap(a[iMid] , a[iStart]); 

	SORTDATA temp = a[iStart];
  while (iStart<iEnd)
  {
		
    while (iStart<iEnd && temp<=a[iEnd])
    {
      --iEnd;
    }
    //Swap(a[iEnd],temp);  // 有的代码是 交换 Swap(a[iStart],a[iEnd]);   注意区别

		a[iStart] = a[iEnd]; // 优化  高效

    while (iStart<iEnd && temp>=a[iStart])
    {
      ++iStart;
    }

    //Swap(a[iStart],temp);

		a[iEnd] = a[iStart];
  }

	a[iStart] = temp;

  return iStart;
}



template <typename SORTDATA>
void SORT<SORTDATA>::Sift(SORTDATA a[], int iStart , int iEnd)
{
  int i = iStart , j = 2*i;

  while (j<=iEnd)  // 这里很重要  数组索引跟建立的堆是有关系的  因为通过索引找孩子
  {
    if (j<iEnd && a[j]<a[j+1]) // 比较左右孩子，j指向较大者
    {
      ++j;
    }

    if (a[i]>=a[j])
    {
      break;
    }

    else
    {
       Swap(a[i],a[j]);  
    }

    i = j, j = 2*i;
  }
}

template <typename SORTDATA>
void SORT<SORTDATA>::HeapSort(SORTDATA a[], int iStart,  int iEnd)
{
  int i = 0;

  for (i=iEnd>>1;i>=iStart;--i)
  {
    Sift(a,i,iEnd);
  }

  for (i=iEnd;i>iStart;--i)
  {
    Swap(a[iStart],a[i]);
    
    Sift(a,iStart,i-1);
  }
}



template <typename SORTDATA>
void SORT<SORTDATA>::BubbleSort(SORTDATA a[], int iStart, int iEnd)
{
  int i = 0;

  BOOL bExchange = TRUE; // 起泡排序  不是双for循环

  while (bExchange)
  {
    bExchange = FALSE;

    for (i=iStart;i<iEnd;++i)
    {
      
      if (a[i]>a[i+1])
      {
        bExchange = TRUE;
        Swap(a[i],a[i+1]);
      }
    }
  }
}


template <typename SORTDATA>
void SORT<SORTDATA>::CockTailSort(SORTDATA a[], int iStart, int iEnd)
{
  int i = 0;
  
  BOOL bExchange = TRUE;

  while (bExchange)
  {
    bExchange = FALSE;

    for (i=iStart ; i<iEnd;++i)
    {
      if (a[i]>a[i+1])
      {
        bExchange = TRUE;

        Swap(a[i],a[i+1]);
      }
    }
      --iEnd;

      for (i=iEnd;i>iStart;--i)
      {
        if (a[i]<a[i-1])
        {
          bExchange = TRUE;

          Swap(a[i],a[i-1]);
        }
      }

      ++iStart;
  }
}


template <typename SORTDATA>
void SORT<SORTDATA>::ShellSort(SORTDATA a[], int iStart, int iEnd)
{
  // 希尔排序主要是增量序列会不同 
int iGap, i, j, k = 1;

SORTDATA temp;

for (k=3;;k *= 3) // 的确是ht4=N/3+1,N/9+1,N/27+1,…,1 比  ht1=N/2,N/4,N/8,…,1； 更快
{
  if (iEnd/(k/3)==0 && iEnd/k==0) // 注意这里的判断不好做  做笔记 当数组是10000000
  {
    break;
  }
  iGap = iEnd/k + 1;
    for (i=iGap+iStart;i<=iEnd;++i)
    {

      temp = a[i];

      for (j=i-iGap;j>=iStart && temp<a[j];j-=iGap)
      {
        a[j+iGap] = a[j];
      }

      a[j+iGap] = temp;
    }
}

}


// 当100,0000 的时候

// ShellSort:  312
// HeapSort:  902


template <typename SORTDATA>
void SORT<SORTDATA>::Merge(SORTDATA a[], int iStart, int iMid , int iEnd)
{
  SORTDATA* p = (SORTDATA*)malloc(sizeof(SORTDATA)*(iEnd-iStart+1));

  assert(p!=NULL);

  int i = iStart , j = iMid+1 , k = 0;

  while(i<=iMid && j<=iEnd)
  {
    if (a[i]<a[j])
    {
      p[k++] = a[i++];
    }
    else
    {
      p[k++] = a[j++];
    }
  }

  while (i<=iMid)
  {
    p[k++] = a[i++];
  }

  while (j<=iEnd)
  {
    p[k++] = a[j++];
  }

  for (i=iStart;i<=iEnd;++i)
  {
    a[i] = p[i-iStart];
  }
  free(p);
}


template <typename SORTDATA>
void SORT<SORTDATA>::MergeSort(SORTDATA a[], int iStart, int iEnd)
{
  if (iStart<iEnd)
  {
    int iMid = (iStart+iEnd)>>1;  // 除2操作 都使用位移运算来代替

    MergeSort(a,iStart,iMid);

    MergeSort(a,iMid+1,iEnd);

    Merge(a,iStart,iMid,iEnd);
  }
}