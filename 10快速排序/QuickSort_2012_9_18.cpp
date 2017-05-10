
// datetime:2012-9-18 
// author： 

// Declare:仅凭记忆写出 写之前没有看笔记 能写出来 说明算法已经记住了 我感到高兴
#include <STDIO.H>

void Swap(int &a, int &b)
{
  if (&a==&b)
  {
    return;
  }

  a ^= b^= a^= b;
}

int Partion(int* p,int Start, int End)
{
  while (Start<End)
  {
     p[0] = p[Start];
     
     while (p[0]<=p[End] && Start<End)
     {
        --End;
     }

     Swap(p[0],p[End]);

     while (p[0]>=p[Start] && Start<End)
     {
       ++Start;
     }

     Swap(p[0],p[Start]);
  }

  return Start;
}

void QuickSort(int *p,int Start, int End)
{
  

  if(Start<End)
  {
      int Mid = Partion(p,Start,End);
      QuickSort(p,Start,Mid-1);
      QuickSort(p,Mid+1,End);
  }
}

int main(int argc, char** argv)
{



  int p[]={20,87,12,67,23,10,17,66,81,24,13};

  int nLen = sizeof(p)/(sizeof(int));
  int i = 0;

  QuickSort(p,1,nLen-1);
  for (i=1;i<nLen;++i)
  {
    printf("%d ",p[i]);
  }

  printf("\n");
  return 0;
}