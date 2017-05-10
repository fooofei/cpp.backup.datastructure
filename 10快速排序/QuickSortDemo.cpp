#ifndef QUICKSORT_H
#define QUICKSORT_H
template<class T> void QuickSort(T *a,int len)
{
	QSort(a,0,len-1);
}
template<class T> void QSort(T *a,int low,int high) //快速排序算法    注意这里改为UINT 会有死循环 
{
	if(low < high)
	{
		int pivot = Partition(a,low,high); //将a[low].......a[high]一分为二,算出枢轴值
		QSort(a,low,pivot-1); //将前一半快速排序
		QSort(a,pivot+1,high); //将后一半快速排序
	}
}
template<class T> int Partition(T *a,int low,int high)
{
	int pivotkey = a[low]; //选待排序列的第一个元素为枢轴值
	while(low < high)  //从序列的两端后中间扫描进行排序
	{
		while(low < high && a[high] >= pivotkey) 
			high--;
		Swap(a,low,high); //交换两值
		while(low < high && a[low] <= pivotkey)
			low++;
		Swap(a,low,high);
	}
	return low; //返回区轴所在位置
}
template<class T> void Swap(T *a,int low,int high) //交换两个位置的元素
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
	printf("排序后的序列为:\n");
	for(int i = 0;i < len;++i)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}