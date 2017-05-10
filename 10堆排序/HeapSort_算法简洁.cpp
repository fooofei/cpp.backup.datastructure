#include <stdio.h>
#include <windows.h>


// 个数少的情况不适合

void Swap(int &a,int &b)
{
	a ^= b^= a^= b;
}


//
// 调整r[s] 使r[s..m] 成为一个大顶堆
//
void HeapAdjust(int r[], int  s ,int m)
{
	int temp,j;
	temp = r[s];

	// 这里的意思是要给temp 找个合适的位置 就是找个好娘家
	// 所以我们看到并没有每一步都交换
	for (j=2*s;j<=m;j*=2)
	{
		if(j<m && r[j]<r[j+1])
			++j;
		if(temp >=r[j])
			break; // 就不比较了
		r[s] = r[j];
		s =j;
	}

	r[s] = temp;
}

void HeapSort(int r[] , int m)
{
	int i;
	for(i=m/2;i>0;--i)
		HeapAdjust(r,i,m);

	for(i=m;i>1;--i)
	{
		Swap(r[1],r[i]);
		HeapAdjust(r,1,i-1);
	}
		
}
int main()
{

	int i;

	int a[] = {0,7,4,8,9,4,6,2};
	int count = sizeof(a)/sizeof(int);
	HeapSort(a,count-1);

	for (i=1;i<count;++i)
	{
		printf("%d ",a[i]);
	}
	return 0;
}