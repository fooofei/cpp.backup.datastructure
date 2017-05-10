#include <STDIO.H>
#include <WINDOWS.H>
#include <TIME.H>

#define  SBTDATA CHAR

typedef struct _SBTNODE_
{
  SBTDATA Data;
  int Size;
  _SBTNODE_* Left;
  _SBTNODE_* Right;
}SBTNode,*pSBTNode;


// Nil�ڱ���㣬��������NULL��ʾ�գ����Լ���ؼ�NULL�ж�
SBTNode Nil={0,0,&Nil,&Nil};

// ���������ע���������ʹ��leftBalance��rightBalance,ʡ��maintain����
BOOL Insert(pSBTNode &pNodeTemp,SBTDATA Data);

// ɾ��pRootΪ�������У���һ����Data�Ľ�� ���ر�ɾ���Ľ���ָ���һ����x�Ľ��
pSBTNode Delete (pSBTNode& pRoot,SBTDATA Data);

int GetDepth(pSBTNode pRoot);

// �����������������õ�
VOID InOrder(pSBTNode pRoot);

// ��ƽ�����������ƽ��LL�ͺ�LR��
VOID LeftBalance(pSBTNode &pRoot);

// ��ƽ�����������ƽ��RR�ͺ�RL��
VOID RightBalance(pSBTNode &pRoot);

// ��������������ƽ������������֮һ
VOID L_Rotate(pSBTNode &pRoot);

// ��������������ƽ������������֮һ
VOID R_Rotate(pSBTNode &pRoot);

// ����Data�������pRoot�������ڵڶ��ٵ�λ��,Data����Ŀǰ������pRoot��
int Rank(pSBTNode pRoot, SBTDATA Data);

pSBTNode Search(pSBTNode pRoot,SBTDATA Data);

// ���ص�k��Ľ��,������СֵSelect(pRoot,1)����
pSBTNode Select(pSBTNode pRoot,int K);

// �ͷ��ڴ�
VOID DestroySBT(pSBTNode &pRoot);

// ʹ��λ�����Ч����������ֵ
BOOL  Swap(SBTDATA &a,SBTDATA &b);


#define  N 10
int main(int argc,char** argv)
{

  pSBTNode pRoot= &Nil;

  pSBTNode pDelete = &Nil;

  clock_t start = clock();

  int i = 0;

  for (i=0;i<N;++i)
  {
    Insert(pRoot,i+1);
  }

  clock_t end = clock();

  printf("����%d������ʹ����%d ms.\n",N,end-start);

  printf("�����Ĵ�С:%d �����Ĵ�С:%d.\n",pRoot->Left->Size,pRoot->Right->Size);

  printf("���ĸ߶�%d.�����ĸ߶�:%d �����ĸ߶�:%d.\n",GetDepth(pRoot),GetDepth(pRoot->Left),GetDepth(pRoot->Right));

  printf("15�ĵȼ���%d.\n",Rank(pRoot,15));

  printf("����:%d.\n",pRoot->Data);

  printf("�������.\n");
  
  InOrder(pRoot), printf("\n");

  DestroySBT(pRoot);
  return 0;
}

BOOL Insert(pSBTNode &pNodeTemp,SBTDATA Data)
{
  if (pNodeTemp==&Nil)
  {
    pSBTNode pNew = (pSBTNode)malloc(sizeof(SBTNode));

    if (!pNew)
    {
      exit(0);
    }

    pNew->Data = Data;
    pNew->Size = 1;
    pNew->Left = &Nil;
    pNew->Right =&Nil;
    pNodeTemp = pNew;
  }
  else
  {
    if (Data<pNodeTemp->Data)
    {
      ++pNodeTemp->Size;

      Insert(pNodeTemp->Left,Data);
      
      LeftBalance(pNodeTemp);
      
    }
    else
    {
      ++pNodeTemp->Size;

      Insert(pNodeTemp->Right,Data);

      RightBalance(pNodeTemp);
    }
  }

  return TRUE;
}

// ɾ��������Ҳ��������ȷʵ�ֵĲ����ˣ�����ʵһ����Ŀ�к����ã�
// ���ֱ�Ӽ���int x�������Ǵ��ڵģ���ô���򵥺ܶ࣬���Ⲣ��ʮ�ֺ���
// ɾ����������˼·�������ģ�
// 
// ����ȵ�ǰ���ֵС������������ȥɾ��
// ����ȵ�ǰ���ֵ�󣬵���������ȥɾ��
// ������ڵ�ǰ���ֵ����ôӦ��ɾ������㣬��ֱ��ɾ�����ܻ��ƻ����Ľṹ
// ���������Ϊ�գ�����������
// ���������Ϊ�գ�����������
// ���������������Ϊ�գ�Ӧ���ҵ�������ǰ�������ߺ�����滻������
// 
// �ڲ�����size�������£��Դ�Ӧ�ÿ���д���ݹ�汾��ɾ����
// ������size���أ��������int xһ�����ڣ���ôֻ��Ҫ��·��size--�Ϳ���
// �����������int x�������أ���ֱ����·size--�����ǲ����Ե�
// ��ôֻ���ȳ��Եݹ�����ɾ�����鿴ɾ����������ж��Ƿ�size--����ôһЩ
// ����д�����ò�����Ը���һ��
// 
// �������ҪDelete��������ô���龲̬ʵ���Ǹ��õ�ѡ����Ϊ�򵥺ܶ�

// ɾ��pRootΪ�������У���һ����Data�Ľ�� ���ر�ɾ���Ľ���ָ��
pSBTNode Delete (pSBTNode& pRoot,SBTDATA Data)
{
  // ��������Ҫɾ��
  if (pRoot==&Nil)
  {
    return &Nil;
  }

  pSBTNode p = &Nil;// ��¼��ɾ���Ľ�㣬������

  // Ӧ�õ���������Ѱ��ɾ�����
  if (Data<pRoot->Data)
  {
    p = Delete(pRoot->Left,Data);
  }
  // Ӧ�õ���������Ѱ��ɾ�����
  else if (Data>pRoot->Data)
  {
    p = Delete(pRoot->Right,Data);
  }

  // ɾ�������
  else
  {
    // ���������������Ϊ��
    if (pRoot->Left!=&Nil && pRoot->Right!=&Nil)
    {
      // �ҵ������ǰ���������������ҽ��
      pSBTNode f= pRoot;

      p = f->Left;

      while (p->Right!=&Nil)
      {
        f= p;
        p = p->Right;
      }

      // pΪ�����滻���Ľ�㣬f���丸���
      if (p==f->Right)
      {
        f->Right = p->Left;
      }
      else// p== f->Left
      {
        f->Left = p->Left;
      }
      
      // pRoot��p��������

      Swap(pRoot->Data,p->Data);
    }

    // ���������Ϊ��(�������� ���� ����)
    else if (pRoot->Left==&Nil)
    {
      p = pRoot;

      pRoot = pRoot->Right;
    }
    else // ���������Ϊ��(������һ������)
    {
      p = pRoot;

      pRoot = pRoot->Left;
    }
  }

  // ������С,ɾ����pRoot������Nil
  if (pRoot!=&Nil)
  {
    pRoot->Size = pRoot->Left->Size + pRoot->Right->Size +1;
  }

  return p;
}

int GetDepth(pSBTNode pRoot)
{
   if (pRoot==&Nil)
   {
     return 0;
   }

   return (GetDepth(pRoot->Left)>=GetDepth(pRoot->Right)?
     GetDepth(pRoot->Left)+1:GetDepth(pRoot->Right)+1);
}

// �����������������õ�
VOID InOrder(pSBTNode pRoot)
{
  if (pRoot!=&Nil)
  {
    InOrder(pRoot->Left);

    printf("ֵ:%4d,��С:%4d ",pRoot->Data,pRoot->Size);

    InOrder(pRoot->Right);
  }
}

// ��ƽ�����������ƽ��LL�ͺ�LR��
VOID LeftBalance(pSBTNode &pRoot)
{
  if (pRoot->Left->Left->Size >pRoot->Right->Size)
  {
    R_Rotate(pRoot);
  }
  else if (pRoot->Left->Right->Size > pRoot->Right->Size)
  {
    L_Rotate(pRoot->Left), R_Rotate(pRoot);
  }
}

// ��ƽ�����������ƽ��RR�ͺ�RL��
VOID RightBalance(pSBTNode &pRoot)
{
  if (pRoot->Right->Right->Size > pRoot->Left->Size)
  {
    L_Rotate(pRoot);
  }
  else if (pRoot->Right->Left->Size > pRoot->Left->Size)
  {
    R_Rotate(pRoot->Right), L_Rotate(pRoot);
  }
}

// ��������������ƽ������������֮һ
VOID L_Rotate(pSBTNode &pRoot)
{
  // ����
  pSBTNode p = pRoot->Right;

  pRoot->Right = p->Left;

  p->Left = pRoot;

  // ����
  p->Size = pRoot->Size;

  pRoot->Size = pRoot->Left->Size +pRoot->Right->Size +1;

  pRoot = p;

}
// ��������������ƽ������������֮һ
VOID R_Rotate(pSBTNode &pRoot)
{
  // ����
  pSBTNode p = pRoot->Left;

  pRoot->Left = p->Right;

  p->Right = pRoot;

  // ����

  p->Size = pRoot->Size;

  pRoot->Size = pRoot->Left->Size + pRoot->Right->Size +1;

  pRoot = p;
}

// ����Data�������pRoot�������ڵڶ��ٵ�λ��,Data����Ŀǰ������pRoot��
int Rank(pSBTNode pRoot, SBTDATA Data)
{
  // ���������뼴�����
   if (pRoot==&Nil)
   {
     return 1;
   }

   if (Data<pRoot->Data)
   {
     return Rank(pRoot->Left,Data);
   }
   else if (Data>pRoot->Data)
   {
     return Rank(pRoot->Right,Data)+pRoot->Left->Size+1;
   }
   else // Data == pRoot->Data
   {
      return pRoot->Left->Size+1;
   }
}

pSBTNode Search(pSBTNode pRoot,SBTDATA Data)
{
    if (pRoot==&Nil || pRoot->Data==Data)
    {
      return pRoot;
    }
//    else
    
  return  Search(Data<pRoot->Data?pRoot->Left:pRoot->Right,Data);
    
}

// ���ص�k��Ľ��,������СֵSelect(pRoot,1)����
pSBTNode Select(pSBTNode pRoot,int K)
{
  if (pRoot==&Nil || K>pRoot->Size)
  {
    return &Nil;
  }

  // OffSet��ʾ�ȸ�����ٸ�λ��
  int OffSet = K - pRoot->Size -1;
  if (OffSet==0)
  {
    return pRoot;
  }
  else if (OffSet<0)
  {
    return Select(pRoot->Left,K);
  }
  else // OffSet >0
  {
    return Select(pRoot->Right,OffSet);
  }
}

VOID DestroySBT(pSBTNode &pRoot)
{
  if (pRoot!=&Nil)
  {
    DestroySBT(pRoot->Left);

    DestroySBT(pRoot->Right);

    free(pRoot);

    pRoot = NULL;
  }
}


BOOL  Swap(SBTDATA &a,SBTDATA &b)
{
  if (&a==&b)
  {
    return FALSE;
  }

  a ^= b ^= a ^= b;

  return TRUE;
}

