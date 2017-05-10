#include <iostream>
using namespace std;



void MergerSort(int a[],int aStart,int b[] ,int bStart,int bEnd,int c[],int cStart, int cEnd)
{
	int k = 0;

	int i = bStart;
	int j = cStart;

	while(i<=bEnd&&j<=cEnd)
	{
		if(b[i]<c[j])
		{
			a[aStart+k] = b[i];
			k++;
			i++;
		}

		else
		{
			a[aStart+k]  = c[j];

			j++;

			k++;
		}
	}
	while(i<=bEnd)
	{
		a[aStart+k]  = b[i];
		k++;
		i++;
	}

	while(j<=cEnd)
	{
		a[aStart+k]  = c[j];

		j++;

		k++;
	}


}



void Merger(int a[], int Left, int Right)
{

	if(Left<Right)
	{
		int nHalf = (Left+Right)/2;

		Merger(a,Left,nHalf);

		Merger(a,nHalf+1,Right);

		MergerSort(a,Left,a,Left,nHalf,a,nHalf+1,Right);
	}
	
}


void main()
{
	int n = 5;

	int i = 0;
	int a[] = {3,5,7,9,6};

	for(i = 0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;

	Merger(a,0,n-1);

	for(i = 0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;


}