#include <stdio.h>
#include <iostream>
using namespace std;


size_t plus(const char* a, size_t sa, 
		  const char* b ,size_t sb, 
		  char* sum ,size_t s_sum)
{
	if (s_sum <max(sa,sb)+1)
	{
		return -1;
	}
	


	memset(sum,0,s_sum);
	size_t i;
	for (i=0;i<sa;++i)
	{
		sum[i] += a[sa-i-1] -48 ; //���������  �Ӹ�λ��ʼ��
	}

	for (i=0;i<sb;++i)
	{
		sum[i] += b[sb-i-1] - 48;
	}

	size_t sum_size = max(sa,sb);

	for (i=0;i<sum_size;++i)
	{
		sum[i+1] += sum[i]/10;
		sum[i] = sum[i]%10;
	}

	if (sum[sum_size] != 0) // û�н�λ �͵�λ�������������е����λ��
	{
		sum_size++;
	}

	for (i=0;i<sum_size;++i)
	{
		sum[i] += 48;
	}
	_strrev(sum);

	return sum_size;
}



int main()
{

	const int BUFFER_SIZE = 20;
	int i = 0;
	int j = 0;
	int count = 0;

	char  a[BUFFER_SIZE] = {0}; // ����ʹ�� char �������Ҫ ��Ϊһ��Ҫʹ��gets ���� �������ǵĴ���
	char b[BUFFER_SIZE] = {0};
	char sum[BUFFER_SIZE] = {0};
	
	while (1)
	{
		gets_s(a,BUFFER_SIZE);
		gets_s(b,BUFFER_SIZE);
		plus(a,strlen(a),b,strlen(b),sum,BUFFER_SIZE);

		printf("%s\n\n",sum);
	}
	return 0;
}
