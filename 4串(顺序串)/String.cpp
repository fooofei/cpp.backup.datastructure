#include <STDIO.H>
#include <WINDOWS.H>
#include <STDLIB.H>
#include <ASSERT.H>


// 说明自写函数与库函数命名区别是 例如字符串拷贝函数库函数strcpy 自己命名为str_cpy

// 字符串连接函数

// 曾经想过用realloc 但是 当我们传进来的字符串是栈内存的时候 我们就无法realloc 于是陷入了死区

// 于是 回归到我们函数的目的  我们是为了在pszDest的后边连接pszSource这就要保证pszDest之后有空间来
// 容纳pszSource 动态申请内存我们已经失败 于是 我们只能寄希望于 传参进来的时候 pszDest已经有空间来容纳pszSource
// 于是此函数也就变得简单了 直接在pszDest后边续就行了
char*  str_cat(char* pszDest, const char* pszSource)
{
  assert(pszDest!=NULL && pszSource!=NULL); // 在函数入口检测形参的有效性

  char * p = pszDest;

  while (*pszDest!='\0')
  {
    ++pszDest;
  }
 
  while (*pszSource!='\0')
  {
    *pszDest++ = *pszSource++;
  }

  *pszDest = '\0';

  return p;

}

// 字符串比较函数
int _cdecl str_cmp(const char* pszDest, const char* pszSource) 
{

  assert(pszDest!=NULL && pszSource!=NULL);

  int ret = 0;

  while (!(ret = *pszDest - *pszSource) && *pszDest)
  {
    ++pszDest;

    ++pszSource;
  }

  if (ret<0)
  {
    return -1;
  }
  else if (ret>0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// 字符串长度
int _cdecl str_len(const char* pszSource)
{

  assert(pszSource!=NULL);

  
  int nLen = 0;

  while (*pszSource!='\0')
  {
    ++pszSource;
    
    ++nLen;
  }

  return nLen;

  

  // 加大难度 不适用任何变量求长度呢？ 如下解法  但是递归开销大


 // return ('\0'!=*pszSource) ? (1+str_len(++pszSource)) : 0;
  

}

// 求子串在主串中出现的位置
char*  str_str( char *pszDest ,  char *pszSub) // 要KMP算法
{
  assert(pszSub!=NULL && pszDest!=NULL);

  char *p = NULL;
  
  char *q = NULL; 

  
  while (*pszDest !='\0')
  {

    p = pszDest;
    
    q = pszSub; 
    
    while (*q!='\0')
    {
      if (*p==*q)
      {
        ++p;
        ++q;
      }
      else
      {
        break;
      }
    }

    if (*q=='\0')
    {

      return pszDest;
    }

    ++pszDest;

  }

  return NULL;
}

//字符串拷贝
char*  str_cpy(char *strDest,const char *strSource)
{

	if(strDest == strSource) {return strDest;}

	assert((strDest != NULL) && (strSource != NULL));

	char* address = strDest;

	while((*strDest++ = *strSource) != '\0');

	return address;

}

bool isdigit(char ch)
{
  return ('0'<=ch && ch<='9');
}


int StrToInt(const char* strSource)
{
  unsigned int iCur = 0, iMax = 0;
	
  int sign  = 0;
	
  assert(strSource!=NULL);
	
  while (*strSource==' ')
  {
    ++strSource;
  }
	
  sign = 1;
	
  iMax = ~(1<<8*sizeof(int)-1);
	
  if ('+'==*strSource)
  {
    ++strSource;
  }
	
  else if ('-'==*strSource)
  {
    ++strSource;
		
    sign = -1;
		
    iMax = -iMax; // 
  }
	
  if (!isdigit(*strSource))
  {
    return 0;
  }
	
	
	
	
  for (iCur=0;isdigit(*strSource) && iCur<=iMax ;strSource++)
  {
    iCur = iCur*10 + *strSource - '0';
  }
	
  if (iCur<=iMax)
  {
    return (int)(sign*iCur);
  }
  else
  {
    return 0;
  }
}

int main()
{

  char a[] = "HelloWord";

  char c[10] = {0};
  

  char *p = str_cpy(c,a);

  if (p!=NULL)
  {
    printf("p=%s,c=%s, nLen = %d.\n",p,c,str_len(c));
  }
  

  return 0;
}