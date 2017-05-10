#include <stdio.h>
#include <windows.h>


// �����ٵ�������ʺ�

void Swap(int &a,int &b)
{
	a ^= b^= a^= b;
}


//
// ����r[s] ʹr[s..m] ��Ϊһ���󶥶�
//
void HeapAdjust(int r[], int  s ,int m)
{
	int temp,j;
	temp = r[s];

	// �������˼��Ҫ��temp �Ҹ����ʵ�λ�� �����Ҹ������
	// �������ǿ�����û��ÿһ��������
	for (j=2*s;j<=m;j*=2)
	{
		if(j<m && r[j]<r[j+1])
			++j;
		if(temp >=r[j])
			break; // �Ͳ��Ƚ���
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