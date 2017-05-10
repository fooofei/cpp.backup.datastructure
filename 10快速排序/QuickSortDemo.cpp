#ifndef QUICKSORT_H
#define QUICKSORT_H
template<class T> void QuickSort(T *a,int len)
{
	QSort(a,0,len-1);
}
template<class T> void QSort(T *a,int low,int high) //���������㷨    ע�������ΪUINT ������ѭ�� 
{
	if(low < high)
	{
		int pivot = Partition(a,low,high); //��a[low].......a[high]һ��Ϊ��,�������ֵ
		QSort(a,low,pivot-1); //��ǰһ���������
		QSort(a,pivot+1,high); //����һ���������
	}
}
template<class T> int Partition(T *a,int low,int high)
{
	int pivotkey = a[low]; //ѡ�������еĵ�һ��Ԫ��Ϊ����ֵ
	while(low < high)  //�����е����˺��м�ɨ���������
	{
		while(low < high && a[high] >= pivotkey) 
			high--;
		Swap(a,low,high); //������ֵ
		while(low < high && a[low] <= pivotkey)
			low++;
		Swap(a,low,high);
	}
	return low; //������������λ��
}
template<class T> void Swap(T *a,int low,int high) //��������λ�õ�Ԫ��
{
	T temp = a[low];
	a[low] = a[high];
	a[high] = temp;
}
#endif //QUICKSORT_H

#include <stdio.h>
int main()
{
	//int a[] = {20,87,12,67,23,10,17,66,81,24,13};
	int a[] = {1,4,2,3};
	int len = sizeof(a) / sizeof(*a);
	QuickSort(a,len);
	printf("����������Ϊ:\n");
	for(int i = 0;i < len;++i)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}