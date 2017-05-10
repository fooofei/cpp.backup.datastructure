#include "SRANDARRAY.H"
#include <stdio.h>
#include <windows.h>
#include <STDLIB.H>
#include <TIME.H>



int com(const void *a,const void *b)
{
  return (*(int*)a-*(int*)b);
} 
int main(int argc, char *argv[])
{
  SRANDARRAY<int> A;

  const int N = 100000;

   clock_t start, end;

  while (true)
  {
    A.Create(0,N-1);

    srand(time(NULL));
    
  start = clock();

    
    qsort(A.m_pData,A.GetSize(),sizeof(int),com);
    
    end = clock();
    
  printf("qsort:%5d\n",(end - start));


   A.Destroy();
   Sleep(1000);
  }
 

  return 0;
}