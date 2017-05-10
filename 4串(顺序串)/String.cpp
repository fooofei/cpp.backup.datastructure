#include <STDIO.H>
#include <WINDOWS.H>
#include <STDLIB.H>
#include <ASSERT.H>


// ˵����д������⺯������������ �����ַ������������⺯��strcpy �Լ�����Ϊstr_cpy

// �ַ������Ӻ���

// ���������realloc ���� �����Ǵ��������ַ�����ջ�ڴ��ʱ�� ���Ǿ��޷�realloc ��������������

// ���� �ع鵽���Ǻ�����Ŀ��  ������Ϊ����pszDest�ĺ������pszSource���Ҫ��֤pszDest֮���пռ���
// ����pszSource ��̬�����ڴ������Ѿ�ʧ�� ���� ����ֻ�ܼ�ϣ���� ���ν�����ʱ�� pszDest�Ѿ��пռ�������pszSource
// ���Ǵ˺���Ҳ�ͱ�ü��� ֱ����pszDest�����������
char*  str_cat(char* pszDest, const char* pszSource)
{
  assert(pszDest!=NULL && pszSource!=NULL); // �ں�����ڼ���βε���Ч��

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

// �ַ����ȽϺ���
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

// �ַ�������
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

  

  // �Ӵ��Ѷ� �������κα����󳤶��أ� ���½ⷨ  ���ǵݹ鿪����


 // return ('\0'!=*pszSource) ? (1+str_len(++pszSource)) : 0;
  

}

// ���Ӵ��������г��ֵ�λ��
char*  str_str( char *pszDest ,  char *pszSub) // ҪKMP�㷨
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

//�ַ�������
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