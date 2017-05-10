#include <STDIO.H>

void Swap(int &a, int &b)
{
  if (&a==&b)
  {
    return;
  }

  a ^= b ^= a ^= b;
}

void HeapAdjust(int *a,int i,int size)  //������ 
{
  int lchild=2*i;       //i�����ӽڵ���� 
  int rchild=2*i+1;     //i���Һ��ӽڵ���� 
  int max=i;            //��ʱ���� 
  if(i<=size/2)          //���i����Ҷ�ڵ�Ͳ��ý��е��� 
  {
    if(lchild<=size&&a[lchild]>a[max])
    {
      max=lchild;
    }    
    if(rchild<=size&&a[rchild]>a[max])
    {
      max=rchild;
    }
    if(max!=i)
    {
      Swap(a[i],a[max]);
      HeapAdjust(a,max,size);    //�������֮����maxΪ���ڵ���������Ƕ� 
    }
  }        
}

void BuildHeap(int *a,int size)    //������ 
{
  int i;
  for(i=size/2;i>=1;i--)    //��Ҷ�ڵ�������ֵΪsize/2 
  {
    HeapAdjust(a,i,size);    
  }    
} 

void HeapSort(int *a,int size)    //������ 
{
  int i;
  BuildHeap(a,size);
  for(i=size;i>=1;i--)
  {
    //cout<<a[1]<<" ";
    Swap(a[1],a[i]);           //�����Ѷ������һ��Ԫ�أ���ÿ�ν�ʣ��Ԫ���е�����߷ŵ������ 
    //BuildHeap(a,i-1);        //������Ԫ�����½���Ϊ�󶥶� 
    HeapAdjust(a,1,i-1);      //���µ����Ѷ��ڵ��Ϊ�󶥶�
  }
} 


int main(void)
{

  int p[] = {0,7,8,5,6,4,3};

  int size = sizeof(p)/sizeof(int);
  
  int i = 0;

  for (i=1;i<size;++i)
  {
    printf("%d ",p[i]);
  }

  printf("\n");
 
  HeapSort(p,size-1);

  for (i=1;i<size;++i)
  {
    printf("%d ",p[i]);
  }

  printf("\n");
  return 0;
}