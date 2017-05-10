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

	// 朱战力老师是从第二步开始算比较次数的 
	// 我不认可他的看法 因为他的第一步预处理已经比较过很多次了
	// 第二步还利用了第一步比较的结果
	// 所以把第一步也应该加上
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

		// 匹配
		if (j==tLen)
		{
			printf("在主串的%d位置发现模式串.\n",Array[m]-tLen+1+1);
		}
	}
	printf("朱战力认为共比较了%d次.\n",v);
	printf("我认为共比较了%d次.\n",iTotal);

	return 0;
}



// 这个例子是ZZL算法的发明者朱战立老师使用的例子 
// char* S = "From automated teller machines and atomic clocks to mammograms and \
semiconductors,innumerable products and services rely in some way on technology,me\
asurement,and standards provided by the National Institute of Standards and Technology";
// char* T = "products and services";
// 在主串的95位置发现模式串.
// 共比较了23次.
// Press any key to continue
