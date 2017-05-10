#include <STDIO.H>
#include <WINDOWS.H>
#include <STDLIB.H>
#include <TIME.H>

#include "SRANDARRAY.H"

template <typename FINDDATATYPE>
// ͳһ�涨  �������ǵ������� a[4]  ��0Ԫ�ز����ֵ ��ô ��ʼ����1  ������Ϊ iArrayEnd(��������ֵ)
class SEARCH // ������ ���涼�ǲ��ҵĺ���
{
public:
  //  ����ֵ�ǲ��ҵ������ݵ�����  ����-1 ��ʾû���ҵ�  //ǰ������������
  int InsertValueSearch(FINDDATATYPE *pArray,int iArrayStart, int iArrayEnd, FINDDATATYPE DataToFind);
                // �����ַ   //���鿪ʼ���ҵ�����    //�����������    // Ҫ������ֵ

  int BinSearch(FINDDATATYPE* pArray,int iArrayStart, int iArrayEnd, FINDDATATYPE DataToFind);
  // ����ͬ��


  int FibonacciSearch(FINDDATATYPE* pArray,int iArrayStart, int iArrayEnd, FINDDATATYPE DataToFind);
  BOOL QuickSort(FINDDATATYPE* pArray,int iStart, int iEnd); // �ṩһ����������������Щ��������������ҵĺ�����׼��

private:
  int Partition(FINDDATATYPE* pArray,int iStart, int iEnd);
  BOOL Swap(FINDDATATYPE &a, FINDDATATYPE &b);
};





int main(int argc, char** argv)
{

  SRANDARRAY<int> MyArray;

  int ArraySize = 6;

  MyArray.CreateArray(1,ArraySize);

  MyArray.DisplayArray();

  SEARCH<int> Find;

  printf("�������ݲ���:");

  int DataToFind = 0;

  scanf("%d",&DataToFind);

// int DataIndex = Find.InsertValueSearch(MyArray.m_pData,MyArray.m_iArrayStart,MyArray.m_iArrayEnd,DataToFind);


 //  int DataIndex = Find.BinSearch(MyArray.m_pData,MyArray.m_iArrayStart,MyArray.m_iArrayEnd,DataToFind);


   int DataIndex = Find.FibonacciSearch(MyArray.m_pData,MyArray.m_iArrayStart,MyArray.m_iArrayEnd,DataToFind);
  if (DataIndex==-1)
  {
    printf("No Data\n");
  }
  else
  {
    printf("the index of %d is %d\n",DataToFind,DataIndex);
  }

  return 0;
}



// ���ֲ����㷨�ǽ�Low��High��Ȩ�ع̶��趨Ϊ0.5��Ҳ���Ƕ��֣�����Midֵ���м���
// ��Ϊ���̶ֹ���Ȩ�����ƣ�ʹ�ö��ֲ����㷨���ںܴ�ľ��ޣ��κ����ж����ڲ������е����һ��Ԫ��ʱ����
// log2n+1 �αȽ�  ������������������ղ�ֵ�Ķ�̬Ԥ������㷨

template <typename FINDDATATYPE>
int SEARCH<FINDDATATYPE>::InsertValueSearch(FINDDATATYPE *pArray,int iArrayStart, int iArrayEnd, FINDDATATYPE DataToFind)
{
  int Mid = 0;

  int CheckLow = 0;

  int CheckHigh = 0;

  int Low = iArrayStart;

  int High = iArrayEnd;

  while (Low<=High)
  {
    CheckLow = (DataToFind-pArray[Low])*(High-Low)/(pArray[High]-pArray[Low]);

    CheckHigh = (DataToFind-pArray[High])*(High-Low)/(pArray[High]-pArray[Low]); // �ܶ��˵��㷨�ж�û������ж�  

    // ��ʾDataToFind < pArray[Low] // �ڶ���������ʾDataToFind>pArray[High]
      if (CheckLow<0||CheckHigh>0) // ���Լ��ӵ��ж�
      {
        return -1;
      }

      Mid = Low + CheckLow; // �е��㷨�� Mid = Low + CheckLow +0.5 ������ȡ��

			// ��ʵ���Ǳȶ��ֲ����Ż��� ��� 
			// Mid = Low + (High - Low)*(DataToFind - pArray[Low]) / (pArray[High] - pArray[Low]);
      if (DataToFind>pArray[Mid])
      {
        Low = Mid+1;
      }
      else if(DataToFind<pArray[Mid])
      {
        High = Mid-1;
      }
      else
      {
        return Mid;
      }
  }

  return -1;
}


template <typename FINDDATATYPE>
int SEARCH<FINDDATATYPE>::BinSearch(FINDDATATYPE* pArray,int iArrayStart, int iArrayEnd, FINDDATATYPE DataToFind)
{
	// �����������
  QuickSort(pArray,iArrayStart,iArrayEnd);

  int Left = iArrayStart;

  int Right = iArrayEnd;

  int Mid = 0;

  while(Left<=Right)
  {
  //  Mid = (Left+Right)/2; // Ϊ����㷨ִ��Ч�� ����λ����

    // Mid = (Left+Right)>>1; // �����Ļ�Left��right��ֵ�Ƚϴ��ʱ��������
		Mid = Left + ((Right-Left)>>1);

    if (Mid<iArrayStart||Mid>iArrayEnd)
    {
      return -1;
    }

    if (DataToFind<pArray[Mid])
    {
      Right = Mid-1;
    }

    else if (DataToFind>pArray[Mid])
    {
      Left = Mid+1;
    }
    else
    {
      return Mid;
    }

  }

  return -1;
}


template <typename FINDDATATYPE>
int SEARCH<FINDDATATYPE>::FibonacciSearch(FINDDATATYPE* pArray,int iArrayStart, int iArrayEnd, FINDDATATYPE DataToFind)
{
  QuickSort(pArray,iArrayStart,iArrayEnd);

  int Low= iArrayStart;

  int High = iArrayEnd;

  int Mid = 0;

  int k = 0;

  int *F = (int*)malloc(sizeof(int)*(iArrayEnd+1));

  int i = 0;

  F[0] = 1;

  F[1] = 1;

  for (i=2;i<=iArrayEnd;++i)
  {
    F[i] = F[i-2] + F[i-1] ; 
  }

  while (iArrayEnd>=F[k] - 1)
  {
    ++k;
  }

  for (i=iArrayEnd+1;i<F[k]-1;++i)
  {
    pArray[i] = pArray[High];
  }

  while(Low<=High)
  {
    Mid = Low + F[k-1] -1;

    if (pArray[Mid]>DataToFind)
    {
      High = Mid-1;

      --k;
    }

    else if (pArray[Mid]<DataToFind)
    {
      Low = Mid +1;
      k = k-2;
    }
    else 
    {
      if (Mid<=High)
      {
        free(F);
        return Mid;
      }
      else
      {
        free(F);
        return -1;
      }
    }
  }

  free(F);
  return -1;
}

template <typename FINDDATATYPE>
int SEARCH<FINDDATATYPE>::Partition(FINDDATATYPE* pArray,int iStart, int iEnd)
{
  while (iStart<iEnd)
  {
    FINDDATATYPE DataTemp = pArray[iStart];

    while (DataTemp<=pArray[iEnd] && iStart<iEnd)
    {
      --iEnd;
    }
    Swap(DataTemp,pArray[iEnd]);

    while (DataTemp>=pArray[iStart] && iStart<iEnd)
    {
      ++iStart;
    }

    Swap(DataTemp,pArray[iStart]);


  }

  return iStart; // Or iEnd
}


template <typename FINDDATATYPE>
BOOL SEARCH<FINDDATATYPE>::QuickSort(FINDDATATYPE* pArray,int iStart, int iEnd)
{
 
  if (iStart<iEnd)
  { 
    int Mid = Partition(pArray,iStart,iEnd);
  
    QuickSort(pArray,iStart,Mid-1);
  
    QuickSort(pArray,Mid+1,iEnd);

  }

  return TRUE;
}



template <typename FINDDATATYPE>
BOOL SEARCH<FINDDATATYPE>::Swap(FINDDATATYPE &a, FINDDATATYPE &b)
{
  if (&a==&b)
  {
    return FALSE;
  }

  a ^=b ^=a ^= b;

  return TRUE;
}







