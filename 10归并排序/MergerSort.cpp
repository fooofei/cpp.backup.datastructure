#include <stdio.h>


//000 11
void MergerSort(int *Array,int ArrayStart,int *Array1,int ArrayStart1,int ArrayEnd1,int *Array2,int Array2Start,int ArrayEnd2)
{
	//������ʱ����
	int ArrayTemp[8]={0};

	//
	int k = 0;//���������±�
	int i = ArrayStart1;      //0
	int j = Array2Start;      //1

	//��whileֻ������������Ĵ洢              // i      //j
	while(i<=ArrayEnd1&&j<=ArrayEnd2)          //19, 2  ,15,1,          Temp[0] = 19
	{                                                                  //Temp[1] = 15 
       if (Array1[i]<Array2[j])
       {
			ArrayTemp[k] = Array1[i];
			k++;
			i++;
       }
	   else
	   {
			ArrayTemp[k] = Array2[j];
			k++;
			j++;
	   }
          
	}
    
	//���һ�����Ĵ洢
	while (i<=ArrayEnd1)
	{
		ArrayTemp[k] = Array1[i];
		k++;
		i++;
	}

	while(j<=ArrayEnd2)
	{
		ArrayTemp[k] = Array2[j];
		k++;
		j++;
	}


	//����ʱ�����е�������Ԫ�����и�ֵ

	for (int h=0;h<k;h++)
	{
		Array[ArrayStart+h] = ArrayTemp[h];
	}
}
void Merger(int *Array,int Left,int Right)
{
	int nHalf;
	if (Left<Right)
	{                                        //  0  1   2 3    4  5  6  7
 		nHalf = (Left + Right)/2;            //  19 15 2 1  ,   30,22,11,0

		//��ֽ�
		Merger(Array,Left,nHalf);

		Merger(Array,nHalf+1,Right);

		MergerSort(Array,Left,Array,Left,nHalf,Array,nHalf+1,Right);
	}




}

void main()
{
	int a[8] = {2,19,15,1,22,30,0,11};

	int i = 0;
	for (i=0;i<8;i++)
	{
		printf("%d  ",a[i]);
	}

	Merger(a,0,7);

    printf("\n");
	for (i=0;i<8;i++)
	{
		printf("%d  ",a[i]);
	}

	
}