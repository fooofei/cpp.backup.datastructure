#include <STDIO.H>
#include <MEMORY.H>
#include <MALLOC.H>


typedef struct _WORD_
{
  union
  {
    _WORD_* LeftLink;
    _WORD_* UpLink;
  }a;

  int iTag;
  int Size;
  _WORD_* RightLink;
}Head,Foot,*pSpace;


#define  MAX 1000
#define  e 10

#define FootLoc(p)   (p)+(p)->Size -1

pSpace AllocBoundTag(pSpace &pav, int n);
void Reclaim(pSpace &pav,pSpace &p);
void PrintUser(pSpace *p);
void Print(pSpace p);

int main(int argc, char** argv)
{

  pSpace pav = NULL;
  pSpace p  = NULL;

  pSpace pHead = NULL;

  pSpace v[MAX/e] = {NULL};

  printf("结构体WORD为%d个字节.\n",sizeof(_WORD_));

  pHead = p = (pSpace)malloc(sizeof(Head)*(MAX+2));

  memset(p,0,sizeof(Head)*(MAX+2));

  p->iTag = 1;

  pav = p+1;

  pav->RightLink = pav->a.LeftLink = pav;

  pav->iTag = 0;

  pav->Size = MAX;

  p = FootLoc(pav);


  p->a.UpLink = pav;
  p->iTag = 0;


  (p+1)->iTag = 1;

  printf("初始化之后,可利用空间表为 :\n");

  Print(pav);

  printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
  v[0] = AllocBoundTag(pav,300);

  printf("申请300空间之后.\n");

  Print(pav);

  PrintUser(v);

  printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

  v[1] = AllocBoundTag(pav,450);

  printf("申请450空间之后.\n");

  Print(pav);

  PrintUser(v);


  printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

  v[2] = AllocBoundTag(pav,242);

  printf("申请242空间之后.\n");

  Print(pav);

  PrintUser(v);


  printf("回收300空间之后.\n");
  Reclaim(pav,v[0]);
  Print(pav);
  
  PrintUser(v);

   printf("回收450空间之后.\n");
  Reclaim(pav,v[1]);

  Print(pav);
  
  PrintUser(v);

  free(pHead);

  int n = 0;
  return 0;
}


pSpace AllocBoundTag(pSpace &pav, int n)
{
  pSpace pTemp = pav;

  while (pTemp&&pTemp->Size<n&&pTemp->RightLink!=pav)
  {
    pTemp = pTemp->RightLink;
  }


  if (!pTemp||pTemp->Size<n)
  {
    return NULL;
  }

  pav = pTemp->RightLink;

  if (pTemp->Size-n<=e)
  {
    if (pav==pTemp)
    {
      pav=NULL;
    }
    else
    {
      pav->a.LeftLink = pTemp->a.LeftLink;

      pTemp->a.LeftLink->RightLink = pav;
    }

    pTemp->iTag =(FootLoc(pTemp))->iTag = 1;
  }
  else
  {


    (FootLoc(pTemp))->iTag = 1;

    pTemp->Size -= n;

    (FootLoc(pTemp))->iTag = 0;

    (FootLoc(pTemp))->a.UpLink = pTemp;

    pTemp = (FootLoc(pTemp))+1;

    pTemp->iTag = 1;

    pTemp->Size = n;

  }

  return pTemp;

}

// Reclaim是回收再利用的意思
// p 是要回收的内存
void Reclaim(pSpace &pav,pSpace &p)
{
  pSpace pLowHead = (p-1)->a.UpLink; // p 是与其低地址紧邻的内存区的底部地址


  pSpace pHighHead = p+p->Size; // 高地址紧邻的内存区的头部地址

  int LowTag = pLowHead->iTag;

  int HighTag = pHighHead->iTag;

  if (!pav) // 无空闲链表了
  {
    pav = p->a.LeftLink = p->RightLink = p;

    p->iTag = 0;

    (FootLoc(p))->a.UpLink = p;

    (FootLoc(p))->iTag = 0;
  }
  else
  {
    if (LowTag==1 && HighTag == 1)
    {
      p->iTag = 0;

      (FootLoc(p))->a.UpLink = p;

      (FootLoc(p))->iTag = 0;

      pav->a.LeftLink->RightLink = p;

      p->a.LeftLink = pav->a.LeftLink;

      p->RightLink = pav;

      pav->a.LeftLink = p;

      pav = p;

    }

    else if (LowTag==1 && HighTag==0)
    {
      p->iTag = 0;

      p->a.LeftLink = pHighHead->a.LeftLink;

      p->a.LeftLink->RightLink = p;

      p->RightLink = pHighHead->RightLink;

      p->RightLink->a.LeftLink = p;

      p->Size += pHighHead->Size;


      (FootLoc(pHighHead))->a.UpLink = p;

      if (pav==pHighHead)
      {
        pav = p;
      }
    }

    else if (LowTag==0 && HighTag==1)
    {
      pLowHead->Size += p->Size;

      (FootLoc(p))->a.UpLink = pLowHead;

      (FootLoc(p))->iTag = 0;
    }
    else
    {
      pLowHead->Size += p->Size + pHighHead->Size;
      pHighHead->a.LeftLink->RightLink = pHighHead->RightLink;

      pHighHead->RightLink->a.LeftLink = pHighHead->a.LeftLink;

      (FootLoc(pHighHead))->a.UpLink = pLowHead;

      if (pav==pHighHead)
      {
        pav = pLowHead;
      }
    }
  }

  p = NULL;
}

void Print(pSpace p)
{
  pSpace pTemp = NULL;

  pSpace pTail=  NULL;

  if (p)
  {
    pTemp = p ;

    pTail = FootLoc(pTemp);

    do 
    {
      printf("块的大小=%d 块的首地址=%#p.",pTemp->Size,pTail->a.UpLink);

      printf("块标志=%d(0:空闲 1:占用) 邻块首地址=%#p.\n",pTemp->iTag,pTail+1);


      pTemp = pTemp->RightLink;

      pTail = FootLoc(pTemp);
      
    } while (pTemp!=p);
  }
  else
  {
    printf("空闲块已经用完.\n");
  }
}


void PrintUser(pSpace* p)
{
  int i = 0;

  for (i=0;i<MAX/e;++i)
  {
    if (p[i])
    {
      printf("块%d的首地址=%#p.",i,p[i]);

      printf("块的大小=%d块头标志=%d(0:空闲 1:占用).",p[i]->Size,p[i]->iTag);

      printf("块尾标志=%d.\n",(FootLoc(p[i]))->iTag);
    } 
  }
}