#include <STDIO.H>
#include <STDLIB.H>
#include <STRING>
void Get_Next(const char* T,int *next)
{
  int i = 0;

  int j = -1;

  next[0] = -1;

  while (T[i]!='\0')
  {
    if (j==-1 || T[j]==T[i])
    {
      ++j;

      ++i;

      if (T[j]!=T[i])
      {
        next[i] = j;
      }
      else
      {
        next[i] = next[j];
      }
    }

    else
    {
      j = next[j]; // 若字符不相同,则回溯
    }
  }
}

int Index_Kmp(char *s, char *t, int pos)
{
  int i = pos-1;

  int j = 0;

  int next[255] = {0};

  Get_Next(t,next);

  while(s[i]!='\0' && t[j]!='\0')
  {
    if (s[i]==t[j])
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

  if (t[j]=='\0')
  {
    return i-strlen(t) +1;
  }
  else
  {
    return -1;
  }
}
int main()
{
  char s[255];
  char t[255] = "abcab";
  int pos = 0,position = 0;

  int next[255] = {0};
  
  Get_Next(t,next);

  int i = 0;

  for (i=0;i<8;++i)
  {
    printf("%d ",next[i]);
  }

  printf("\n");

 // position = Index_Kmp(s,t,pos);
  if(position == -1)
    printf("子串未在主串的%d个位置之后出现\n",pos);
  else
		printf("子串在主串的第%d个位置出现:\n",position);

  return 0;
}