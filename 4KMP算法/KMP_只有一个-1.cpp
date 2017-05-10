#include <STDIO.H>
#include <WINDOWS.H>


void Get_Next(const char* T,int next[])
{

  int j = 1;

  int k = 0;

  next[0] = 0;

  while (T[j]!='\0')
  {
    if (T[j]==T[k])
    {

      next[j] = k;

      ++j;

      ++k;
    }

    else if (T[j]!=T[0])
    {
      next[j] = k;

      ++j;

      k = 0;
    }
    else
    {
      next[j] = k;

      ++j;

      k = 1;
    }
  }// while
}

int KMP(const char *s, const char *t , int pos)
{
  int i = pos ;

  int j = 0;

  int nLen = strlen(t);

  int *next = (int*)malloc(sizeof(int)*nLen);

  Get_Next(t,next);

  while(s[i]!='\0' &&t[j]!='\0')
  {

    if (s[i]==t[j])
    {
      ++i;

      ++j;
    }

    else
    {
      ++i;

      j = next[j];
    }
  }// while


  free(next);

  if (t[j]=='\0')
  {
    return (i-j);
  }
  else
  {
    return -1;
  }
}


int main()
{
  char* text="bababCabCadcaabcaababcbaaaabaaacababcaabc";
    char*pattern="adCadCad";

    printf("%d ",KMP(text,pattern,0));
  return 0;
}