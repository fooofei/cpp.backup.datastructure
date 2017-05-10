#pragma once

// 2014_06_03	
#include <stdio.h>

class CStringFinder
{
	
public:
	static int kmp( const char *strSour, int sourLen,const char *strSub, int subLen,int pos);

	static int  BruteForce(const char* strSour,int sourLen ,const char* strSub , int subLen,
		int pos);
	
	/*
	 *	pfn : return true for go on find
	 *  pos : the position not index
	 */
	static int zzl(const char* strSour,int sourLen ,const char* strSub , int subLen,
		int pos,bool (*pfn)(int postion));

	static int zzl_better(const char* strSour,int sourLen ,const char* strSub , int subLen,
		int pos,bool (*pfn)(int postion));
	

	/*
	 *	Next数组中存在多个-1
	 */
private:
	static void inline getNext(const char* s,int slen ,int *next)
	{
	int i = 0;
	int j = -1;
	next[0] = -1;
	while (i<slen)
	{
		if (j==-1 || s[j]==s[i])
		{
			++j;
			++i;
			if (s[j]!=s[i])
				next[i] = j;
			else
				next[i] = next[j];
		}
			else
			{
				j = next[j]; // 若字符不相同,则回溯
			}
		}
	}

};

int  CStringFinder::kmp( const char *strSour, int sourLen,const char *strSub, int subLen,int pos)
{

	if (sourLen <=0|| subLen<=0 || pos<=0 || 
		pos>sourLen || (pos-1+subLen) >sourLen || strSub == NULL || strSour == NULL)
	{
		return -1;
	}
	int i = pos-1;
	int j = 0;

	// malloc 一下子也挺费时间的
	int *next = (int*)malloc((sourLen+1)*sizeof(int));
	getNext(strSour,sourLen,next);

	while(i<sourLen && j<subLen)
	{
		if (strSour[i]==strSub[j])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
			if (j==-1)
			{
				++j;
				++i;
			}
		}
	}
	free(next);

	if ( j== subLen)
	{
		return i- j +1;
	}
	return -1;
	
}


/*
 *  返回字串strDes 第一次在strSour中出现的位置
 *	pos  是起始位置 并不是索引
 */
int  CStringFinder::BruteForce(const char* strSour,int sourLen ,const char* strSub , int subLen,
			   int pos)
{
	if (sourLen <=0|| subLen<=0 || pos<=0 || 
		pos>sourLen || (pos-1+subLen) >sourLen || strSub == NULL || strSour == NULL)
	{
		return -1;
	}

	int i =pos-1;
	int j =0;
	while (i<sourLen && j<subLen)
	{
		if (strSour[i]==strSub[j])
		{
			
			i++;
			j++;
		}
		else
		{
			i = i-j+1;
			j =0;
		}
	}

	if (j==subLen)
	{
		return i-j+1;
	}
	return -1;
}

/*
 *	找出pos之后的所有字串位置(pos不是索引)
 *	pfn return true for go on
 */
int CStringFinder::zzl(const char* strSour,int sourLen ,const char* strSub , int subLen,
		int pos,bool (*pfn)(int postion))
{
	if (sourLen <=0|| subLen<=0 || pos<=0 || 
		pos>sourLen || (pos-1+subLen) >sourLen || strSub == NULL || strSour == NULL)
	{
		return -1;
	}

	int array_size = sourLen-subLen+1;
	int *array = (int*)malloc(sizeof(int)*array_size);
	int i , k , m , j;
	
	k=0;
	for (i=pos-1;i<array_size;++i)
	{
		if (strSour[i] == strSub[0])
		{
			array[k] = i;
			++k;
		}
	}

	for (m=0;m<k;++m)
	{
		for (j=1;j<subLen;++j)
		{
			if (strSour[array[m]+1] == strSub[j])
			{
				array[m]++;
			}else
			{
				break;
			}
		}
		if (j == subLen)
		{
			// If return false , will break.
			if(pfn != NULL && !pfn(array[m]-subLen+1+1))
				break;
		}
	}
	free(array);
	return -1;
}

/*
 *	找出pos之后的所有字串位置(pos不是索引)
 *	pfn return true for go on
 *	zzl的改进 最短匹配定理
 *	实际测试时间时,提高并不多
 */
int CStringFinder::zzl_better(const char* strSour,int sourLen ,const char* strSub , int subLen,
		int pos,bool (*pfn)(int postion))
{
	if (sourLen <=0|| subLen<=0 || pos<=0 || 
		pos>sourLen || (pos-1+subLen) >sourLen || strSub == NULL || strSour == NULL)
	{
		return -1;
	}

	int array_size = sourLen-subLen+1;
	int *array = (int*)malloc(sizeof(int)*array_size);
	int i , k , m , j , weight;
	

	char ch = strSub[0];

	weight = subLen;
	for (i=1;i<subLen;++i)
	{
		if (strSub[i] == ch)
		{
			weight = i;
			break;
		}
	}


	k=0;
	for (i=pos-1;i<=array_size;++i)
	{
		if (strSour[i] == strSub[0])
		{
			if (k ==0 || i-array[k]>=weight)
			{
				array[k] = i;
				++k;
			}
			else
				array[k-1] = i;
		}
	}

	for (m=0;m<k;++m)
	{
		for (j=1;j<subLen;++j)
		{
			if (strSour[array[m]+1] == strSub[j])
			{
				array[m]++;
			}else
			{
				break;
			}
		}
		if (j == subLen)
		{
			// If return false , will break.
			if(pfn != NULL && !pfn(array[m]-subLen+1+1))
				break;
		}
	}
	free(array);
	return -1;
}
