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

  printf("�ṹ��WORDΪ%d���ֽ�.\n",sizeof(_WORD_));

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

  printf("��ʼ��֮��,�����ÿռ��Ϊ :\n");

  Print(pav);

  printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
  v[0] = AllocBoundTag(pav,300);

  printf("����300�ռ�֮��.\n");

  Print(pav);

  PrintUser(v);

  printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

  v[1] = AllocBoundTag(pav,450);

  printf("����450�ռ�֮��.\n");

  Print(pav);

  PrintUser(v);


  printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

  v[2] = AllocBoundTag(pav,242);

  printf("����242�ռ�֮��.\n");

  Print(pav);

  PrintUser(v);


  printf("����300�ռ�֮��.\n");
  Reclaim(pav,v[0]);
  Print(pav);
  
  PrintUser(v);

   printf("����450�ռ�֮��.\n");
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

// Reclaim�ǻ��������õ���˼
// p ��Ҫ���յ��ڴ�
void Reclaim(pSpace &pav,pSpace &p)
{
  pSpace pLowHead = (p-1)->a.UpLink; // p ������͵�ַ���ڵ��ڴ����ĵײ���ַ


  pSpace pHighHead = p+p->Size; // �ߵ�ַ���ڵ��ڴ�����ͷ����ַ

  int LowTag = pLowHead->iTag;

  int HighTag = pHighHead->iTag;

  if (!pav) // �޿���������
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
      printf("��Ĵ�С=%d ����׵�ַ=%#p.",pTemp->Size,pTail->a.UpLink);

      printf("���־=%d(0:���� 1:ռ��) �ڿ��׵�ַ=%#p.\n",pTemp->iTag,pTail+1);


      pTemp = pTemp->RightLink;

      pTail = FootLoc(pTemp);
      
    } while (pTemp!=p);
  }
  else
  {
    printf("���п��Ѿ�����.\n");
  }
}


void PrintUser(pSpace* p)
{
  int i = 0;

  for (i=0;i<MAX/e;++i)
  {
    if (p[i])
    {
      printf("��%d���׵�ַ=%#p.",i,p[i]);

      printf("��Ĵ�С=%d��ͷ��־=%d(0:���� 1:ռ��).",p[i]->Size,p[i]->iTag);

      printf("��β��־=%d.\n",(FootLoc(p[i]))->iTag);
    } 
  }
}