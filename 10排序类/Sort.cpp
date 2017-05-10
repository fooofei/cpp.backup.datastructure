#include <STDIO.H>
#include <ASSERT.H>
#include <MATH.H>
#include "SRANDARRAY.H"

// �����ԱȲ���  �ҵõ��Ľ����� ����Ҫ���� ��������  ϣ������ ������ 


#define MAX_LENGTH_INSERT_SORT 7 // ����50  ����������ʹ�ò����������ֵ

template <typename SORTDATA>
class SORT
{
public:
  void SelectSort(SORTDATA a[], int iStart, int iEnd);

  void InsertSort(SORTDATA a[], int iStart, int iEnd);

  void QuickSort_Old(SORTDATA a[], int iStart, int iEnd);
	void QuickSort_New(SORTDATA a[], int iStart, int iEnd); // 2013-1-11 ѧϰ�����ݽṹ֮�� �Ż����㷨

  void HeapSort(SORTDATA a[], int iStart,  int iEnd);

  void BubbleSort(SORTDATA a[], int iStart, int iEnd);

  void CockTailSort(SORTDATA a[], int iStart, int iEnd);// ��β������(˫��ð������)

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

	
  // ���ֲ��� Ӧ�ò�׼   

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

  Array.CreateArray(1,N);  // һ�����ʱ�� ϣ�������ǿ��Ե�  ��������ͻ�ջ���
  
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
void SORT<SORTDATA>::QuickSort_New(SORTDATA a[], int iStart, int iEnd) // 2013-1-11 ѧϰ�����ݽṹ֮�� �Ż����㷨
{
	if ((iEnd-iStart) >MAX_LENGTH_INSERT_SORT) // �Ż�һ ������С��ʱ�� ʹ�ò����������
	{
		int iPivot;
		while (iStart<iEnd)  // �Ż��� ʹ��ѭ��  ������ݹ�  
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
  // ��������·�� ʹ����������ʵ�ֵķ���    �����й涨ֻ��������ʹ��һ������
  if (iStart<iEnd)
  {
    int iMid = Partition(a,iStart,iEnd);

    QuickSort_Old(a,iStart,iMid-1);

    QuickSort_Old(a,iMid+1,iEnd);
  }

  // �Ǿ�����ʵ����
  // ����ʵ��֤��  ���浥������ʵ�ֵķ��� �����ϱ���������ʵ�ָ��Ӹ�Ч  ����ķ������ĵ�ʱ�������������

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

	// ��·ȡ��ֵ   Ϊ�˸��õصõ� ��Ŧֵ
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
    //Swap(a[iEnd],temp);  // �еĴ����� ���� Swap(a[iStart],a[iEnd]);   ע������

		a[iStart] = a[iEnd]; // �Ż�  ��Ч

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

  while (j<=iEnd)  // �������Ҫ  ���������������Ķ����й�ϵ��  ��Ϊͨ�������Һ���
  {
    if (j<iEnd && a[j]<a[j+1]) // �Ƚ����Һ��ӣ�jָ��ϴ���
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

  BOOL bExchange = TRUE; // ��������  ����˫forѭ��

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
  // ϣ��������Ҫ���������л᲻ͬ 
int iGap, i, j, k = 1;

SORTDATA temp;

for (k=3;;k *= 3) // ��ȷ��ht4=N/3+1,N/9+1,N/27+1,��,1 ��  ht1=N/2,N/4,N/8,��,1�� ����
{
  if (iEnd/(k/3)==0 && iEnd/k==0) // ע��������жϲ�����  ���ʼ� ��������10000000
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


// ��100,0000 ��ʱ��

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
    int iMid = (iStart+iEnd)>>1;  // ��2���� ��ʹ��λ������������

    MergeSort(a,iStart,iMid);

    MergeSort(a,iMid+1,iEnd);

    Merge(a,iStart,iMid,iEnd);
  }
}