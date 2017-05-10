#include <STDIO.H>
#include <WINDOWS.H>
#include <STDLIB.H>
#include <TIME.H>

#include "SRANDARRAY.H"

template <typename FINDDATATYPE>
// 统一规定  比如我们的数组是 a[4]  第0元素不存放值 那么 开始就是1  结束定为 iArrayEnd(该索引有值)
class SEARCH // 查找类 里面都是查找的函数
{
public:
  //  返回值是查找到的数据的索引  返回-1 表示没有找到  //前提是有序数组
  int InsertValueSearch(FINDDATATYPE *pArray,int iArrayStart, int iArrayEnd, FINDDATATYPE DataToFind);
                // 数组地址   //数组开始查找的索引    //数组结束索引    // 要搜索的值

  int BinSearch(FINDDATATYPE* pArray,int iArrayStart, int iArrayEnd, FINDDATATYPE DataToFind);
  // 参数同上


  int FibonacciSearch(FINDDATATYPE* pArray,int iArrayStart, int iArrayEnd, FINDDATATYPE DataToFind);
  BOOL QuickSort(FINDDATATYPE* pArray,int iStart, int iEnd); // 提供一个排序函数用来给哪些必须有序数组查找的函数做准备

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

  printf("输入数据查找:");

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



// 二分查找算法是将Low和High的权重固定设定为0.5，也就是二分，来对Mid值进行计算
// 因为这种固定的权重限制，使得二分查找算法存在很大的局限，任何数列都会在查找数列的最后一个元素时进行
// log2n+1 次比较  于是提出基于拉格朗日差值的动态预测查找算法

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

    CheckHigh = (DataToFind-pArray[High])*(High-Low)/(pArray[High]-pArray[Low]); // 很多人的算法中都没有这个判断  

    // 表示DataToFind < pArray[Low] // 第二个参数表示DataToFind>pArray[High]
      if (CheckLow<0||CheckHigh>0) // 我自己加的判断
      {
        return -1;
      }

      Mid = Low + CheckLow; // 有的算法是 Mid = Low + CheckLow +0.5 是向上取正

			// 其实就是比二分查找优化了 这个 
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
	// 必须是有序的
  QuickSort(pArray,iArrayStart,iArrayEnd);

  int Left = iArrayStart;

  int Right = iArrayEnd;

  int Mid = 0;

  while(Left<=Right)
  {
  //  Mid = (Left+Right)/2; // 为提高算法执行效率 采用位运算

    // Mid = (Left+Right)>>1; // 这样的话Left与right的值比较大的时候可能溢出
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







