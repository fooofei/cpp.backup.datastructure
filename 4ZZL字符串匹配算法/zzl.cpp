#include <stdio.h>
#include <WINDOWS.H>
#include <MALLOC.H>

int main()
{

char* S = "From automated teller machines and atomic clocks to mammograms and \
semiconductors,innumerable products and services rely in some way on technology,me\
asurement,and standards provided by the National Institute of Standards and Technology";
	char* T = "products and services";

	int k,i,v,m,j;

	int iTotal = 0;

	int sLen = strlen(S);
	int tLen = strlen(T);

	int *Array = (int*)malloc(sizeof(int)*(sLen-tLen));
	memset(Array,0,sizeof(int)*(sLen-tLen));
	k =0;
	for (i=0;i<sLen-tLen;i++)
	{
		iTotal++;
		if (S[i] == T[0])
		{
			Array[k] = i;
			k++;
		}
	}

	// ��ս����ʦ�Ǵӵڶ�����ʼ��Ƚϴ����� 
	// �Ҳ��Ͽ����Ŀ��� ��Ϊ���ĵ�һ��Ԥ�����Ѿ��ȽϹ��ܶ����
	// �ڶ����������˵�һ���ȽϵĽ��
	// ���԰ѵ�һ��ҲӦ�ü���
	v= 0;
	for (m=0;m<k;m++)
	{
		for (j=1;j<tLen;++j)
		{
			iTotal++;
			v++;
			if (S[Array[m]+1] == T[j])
				Array[m]++;
			
			else
				break;
	
		}

		// ƥ��
		if (j==tLen)
		{
			printf("��������%dλ�÷���ģʽ��.\n",Array[m]-tLen+1+1);
		}
	}
	printf("��ս����Ϊ���Ƚ���%d��.\n",v);
	printf("����Ϊ���Ƚ���%d��.\n",iTotal);

	return 0;
}



// ���������ZZL�㷨�ķ�������ս����ʦʹ�õ����� 
// char* S = "From automated teller machines and atomic clocks to mammograms and \
semiconductors,innumerable products and services rely in some way on technology,me\
asurement,and standards provided by the National Institute of Standards and Technology";
// char* T = "products and services";
// ��������95λ�÷���ģʽ��.
// ���Ƚ���23��.
// Press any key to continue
