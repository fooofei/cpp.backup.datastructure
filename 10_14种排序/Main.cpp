#include<iostream>
#include<time.h>
using namespace std;
#define  MAX 4
/*
简单插入排序:
最差时间复杂度:O(n^2)
平均时间复杂度:O(n^2)
*/
void Insertion_Sort(int *a,int n)
{
	int i,j;
	for(i=2;i<=n;i++)
		if(a[i]<a[i-1])
		{
			a[0]=a[i];
			for(j=i-1;a[j]>a[0];j--)
				a[j+1]=a[j];
			a[j+1]=a[0];
		}
}
/*
折半插入排序:
最差时间复杂度:O(n^2)
平均时间复杂度:O(n^2)
*/
void Bin_Sort(int *a,int n)
{
	int i,j,low,mid,high;
	for(i=2;i<=n;i++)
		if(a[i]<a[i-1])
		{
			a[0]=a[i];
			low=1;
			high=i-1;
			while(low<=high)
			{
				mid=(low+high)/2;
				if(a[mid]>a[0])
					high=mid-1;
				else 
					low=mid+1;
			}
			for(j=i-1;j>high;j--)
				a[j+1]=a[j];
			a[high+1]=a[0];
		}
}
/*选择排序:
最差时间复杂度:O(n^2)
平均时间复杂度:O(n^2)
*/
void Selection_Sort(int *a,int n)
{
	int i,j,k;
	for(i=1;i<n;i++)
	{
		k=i;
		for(j=i+1;j<=n;j++)
			if(a[k]>a[j])
				k=j;
		if(k!=i)	
			swap(a[k],a[i]);
	}
}
/*快速排序
最差时间复杂度:O(n^2)
平均时间复杂度:O(nlogn)
*/
void Quick_Sort(int *a,int low,int high)
{
	int i=low,j=high;
	a[0]=a[low];
	while(low<high)
	{
		while(low<high && a[high]>=a[0])
			high--;
		swap(a[low],a[high]);
		while(low<high && a[low]<=a[0])
			low++;
		swap(a[low],a[high]);
	}
	a[low]=a[0];
	if(i!=low)
		Quick_Sort(a,i,low-1);
	if(j!=high)
		Quick_Sort(a,high+1,j);
}
/*冒泡排序
最差时间复杂度:O(n^2)
平均时间复杂度:O(n^2)
*/
void Bubble_Sort(int *a,int n)
{
	int i;
	bool change=true;
	while(change)
	{
		change=false;
		for(i=1;i<n;i++)
			if(a[i]>a[i+1])
			{
				change=true;
				swap(a[i],a[i+1]);
			}
	}
}
/*鸡尾酒排序(双向冒泡排序):
最差时间复杂度:O(n^2))
平均时间复杂度:O(n^2)
*/
void Cocktail_Sort(int *a,int n)
{
	int i;
	int left=1,right=n;
	bool change=true;
	while(change)
	{
		change=false;
		for(i=left;i<right;i++)
			if(a[i]>a[i+1])
			{
				change=true;
				swap(a[i],a[i+1]);
			}
			right--;
			for(i=right;i>left;i--)
				if(a[i]<a[i-1])
				{
					change=true;
					swap(a[i],a[i-1]);
				}
				left++;
	}
}
/*堆排序
最差时间复杂度:O(nlogn)
平均时间复杂度:O(nlogn)
*/
void Heap_Adjust(int *a,int low,int high)
{
	int i;
	a[0]=a[low];
	for(i=2*low;i<=high;i*=2)
	{
		if(i<high && a[i]<a[i+1])
			i++;
		if(a[0]>=a[i])
			break;
		else 
		{
			a[low]=a[i];
			low=i;
		}
		a[low]=a[0];
	}
}
void Heap_Sort(int *a,int n)
{
	int i;
	for(i=n/2;i>=1;i--)
		Heap_Adjust(a,i,n);
	for(i=n;i>=2;i--)
	{
		swap(a[1],a[i]);
		Heap_Adjust(a,1,i-1);
	}
}
/*
希尔排序
最差时间复杂度:O(n^2)
平均时间复杂度:O(n^1.3)
*/
void Shell_Sort(int *a,int n)
{
	int i,j;
	int gap=n/2;
	while(gap)
	{
		for(i=gap+1;i<=n;i++)
			if(a[i]<a[i-gap])
			{
				for(j=i-gap;j>0 && a[j]>a[0];j-=gap)
					a[j+gap]=a[j];
				a[j+gap]=a[0];
			}
			gap/=2;
	}
}
/*
计数排序:
最差时间复杂度:O(n+k)
平均时间复杂度:O(n+k)
*/
void Counting_Sort(int *a,int n)
{
	int i;
	int max=a[1];
	for(i=2;i<=n;i++)
	{
		if(max<a[i])
			max=a[i];
	}
	int *mark=new int[max+1];
	memset(mark,0,sizeof(int)*(max+1));
	for(i=1;i<=n;i++)
		mark[a[i]]++;
	for(i=1;i<=max;i++)
		mark[i]+=mark[i-1];
	int *p=new int[n+1];
	memset(p,0,sizeof(int)*(n+1));
	for(i=1;i<=n;i++)
	{
		p[mark[a[i]]]=a[i];
		mark[a[i]]--;
	}
	for(i=1;i<=n;i++)
		a[i]=p[i];
}
/*
鸽巢排序:
最差时间复杂度:O(n+N)
平均时间复杂度:O(n+N)
*/
void Pigeonhole_Sort(int *a,int n)
{
	int i,j,k=1;
	int max=a[1];
	for(i=2;i<=n;i++)
	{
		if(max<a[i])
			max=a[i];
	}
	int *mark=new int[max+1];
	memset(mark,0,sizeof(int)*(max+1));
	for(i=1;i<=n;i++)
		mark[a[i]]++;
	for(i=1;i<=max;i++)
		for(j=1;j<=mark[i];j++)
			a[k++]=i;
}
/*
归并排序:
最差时间复杂度:O(nlogn)
平均时间复杂度:O(nlogn)
*/
void Merge(int *a,int low,int mid,int high)
{
	int p,i=low,j=mid+1,k=low;
	int *temp=new int[high+1];
	memset(temp,0,sizeof(int)*(high+1));
	for(;i<=mid && j<=high;k++)
		if(a[i]<a[j])
			temp[k]=a[i++];
		else 
			temp[k]=a[j++];
	if(i<=mid)
		for(p=0;p<=mid-i;p++)
			temp[k+p]=a[i+p];
	if(j<=high)
		for(p=0;p<=high-j;p++)
			temp[k+p]=a[j+p];
	for(p=low;p<=high;p++)
		a[p]=temp[p];

	delete []temp;
}
void MSort(int *a,int low,int high)
{
	if(low<high)
	{
		int mid=(low+high)/2;
		MSort(a,low,mid);
		MSort(a,mid+1,high);
		Merge(a,low,mid,high);
	}
}
/*
梳排序:
最差时间复杂度:O(nlogn)
平均时间复杂度:O(nlogn)
*/
void Comb_Sort(int *a,int n)
{
	int i;
	int gap=n;
	while(gap/=1.3)
	{
		for(i=gap+1;i<=n;i++)
			if(a[i]<a[i-gap])
				swap(a[i],a[i-gap]);
	}
}
/*
奇偶排序(砖排序):
最差时间复杂度:O(n^2)
平均时间复杂度:O(n^2)
*/
void Odd_Even(int *a,int n)
{
	int i;
	bool change=true;
	while(change)
	{
		change=false;
		for(i=1;i<n;i+=2)
			if(a[i]>a[i+1])
			{
				change=true;
				swap(a[i],a[i+1]);
			}
			for(i=2;i<n;i+=2)
				if(a[i]>a[i+1])
				{
					change=true;
					swap(a[i],a[i+1]);
				}
	}
}
/*
地精排序(侏儒排序):
最差时间复杂度:O(n^2)
平均时间复杂度:O(n^2)
*/
void Gnome_Sort(int *a,int n)
{
	int i=0;
	while(i<n)
	{
		if(i<=0 || (i>=1 && a[i]<=a[i+1]))
			i++;
		else 
		{
			swap(a[i],a[i+1]);
			i--;
		}
	}
}
void Out(int *a,int n)
{
	int i;
	for(i=1;i<=n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
}
int main()
{
	srand((unsigned)time(NULL));
	int *p=new int[MAX];
	memset(p,0,sizeof(int)*MAX);
	for(int i=1;i<=MAX;i++)
	{
		p[i]=rand()%100;
	}
	Out(p,MAX);
	//Insertion_Sort(p,15);
	//Bin_Sort(p,15);
	//Selection_Sort(p,15);
	//Quick_Sort(p,1,15);
	//Bubble_Sort(p,15);
	//Cocktail_Sort(p,15);
	//Heap_Sort(p,15);
	//Shell_Sort(p,15);
	//Counting_Sort(p,15);
	//Pigeonhole_Sort(p,15);
	Comb_Sort(p,MAX);
	//Odd_Even(p,15);
	//MSort(p,1,15);
	//Gnome_Sort(p,MAX);
	Out(p,MAX);
}