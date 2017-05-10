#include <STDIO.H>
#include <WINDOWS.H>
#include <LIMITS.H>
typedef struct _BITREE_
{
  int Weight;
  _BITREE_* pLeft;
  _BITREE_* pRight;
}BiTree,*pBiTree;

typedef struct _HUFFMANTREE_
{
  int Weight;
  int Left;
  int Right;
  int Parent;
}HuffManTree,*pHuffManTree;

int g_nKey =1;
int g_nCount =0;
VOID CreateBiTree(pBiTree &pRoot)
{
  int Weight= 0;

  scanf(" %d",&Weight);

  if (Weight==0)
  {
    pRoot = NULL;
  }
  else
  {
    if (NULL==(pRoot=(pBiTree)malloc(sizeof(BiTree))))
    {
      return ;
    }

    memset(pRoot,0,sizeof(BiTree));
    
    pRoot->Weight = Weight;

    CreateBiTree(pRoot->pLeft);

    CreateBiTree(pRoot->pRight);

    g_nCount++;
  }

}// CreateBiTree


VOID  InitHuffManTree(pHuffManTree &pHuffManTreeTemp)
{
  int iNum = g_nCount*2-1;
  
  pHuffManTreeTemp = (pHuffManTree)malloc(sizeof(HuffManTree)*(iNum+1));
  // ע�� ���˿���˵Ҫ������iNum+1  ����g_nCount*2�Ͳ�-1��    �������ĺ��岻ͬ  �������ǻ�������д��


  memset(pHuffManTreeTemp,0,sizeof(HuffManTree)*(iNum+1));


}// InitHuffManTree
VOID CreateArray(pHuffManTree &pHuffManTreeTemp, pBiTree pRoot)
{
 
  if (!pRoot)
  {
    return ;
  }

  pHuffManTreeTemp[g_nKey++].Weight = pRoot->Weight;

  CreateArray(pHuffManTreeTemp,pRoot->pLeft);

  CreateArray(pHuffManTreeTemp,pRoot->pRight);
}// CreateArray

int GetNode(pHuffManTree& pHuffManTreeTemp,int iIndex)
{
  unsigned int nOver = UINT_MAX;

  int i =0;

  int Flag = 0;

  for (i=1;i<iIndex;++i)
  {
    if (pHuffManTreeTemp[i].Weight<nOver && pHuffManTreeTemp[i].Parent==0)
    {
      nOver = pHuffManTreeTemp[i].Weight;

      Flag = i;
    }
  }

  pHuffManTreeTemp[Flag].Parent = 1;
  return Flag;
}// GetNode


VOID CreateHuffManTree(pHuffManTree& pHuffManTreeTemp)
{
  int m =0;
  int n =0;

  for (int i=g_nCount+1;i<2*g_nCount;++i)
  {
    m = GetNode(pHuffManTreeTemp,i);// i Ҳ���ڱ仯�� ������εõ��Ľ�� �´�Ҳ����Ƚ�

    n = GetNode(pHuffManTreeTemp,i);

    pHuffManTreeTemp[m].Parent = pHuffManTreeTemp[n].Parent = i;

    pHuffManTreeTemp[i].Left = m;

    pHuffManTreeTemp[i].Right = n;

    pHuffManTreeTemp[i].Weight = pHuffManTreeTemp[m].Weight+pHuffManTreeTemp[n].Weight;
  }
}// CreateHuffManTree


VOID DestroyBiTree(pBiTree &pRoot)
{

  if (pRoot)
  {
    DestroyBiTree(pRoot->pLeft);

    DestroyBiTree(pRoot->pRight);

    free(pRoot);

    pRoot = NULL;
  }
}// DestroyBiTree

VOID DestroyHuffManTree(pHuffManTree& pHuffManTreeTemp)
{

  if (pHuffManTreeTemp)
  {
    free(pHuffManTreeTemp);

    pHuffManTreeTemp = NULL;
  }
}// DestroyHuffManTree


VOID HuffManCode(pHuffManTree &pHuffManTreeTemp)
{

  int nStart = 0;

  CHAR* p = (CHAR*)malloc(sizeof(CHAR)*g_nCount);

  memset(p,0,sizeof(CHAR)*g_nCount);

//  p[g_nCount-1] = '\0';

  int i =0;
  int n = 0;

  int Parent = 0;

  for (i=1;i<=g_nCount;++i)
  {
    nStart = g_nCount-1;

    n = i;
    
    Parent = pHuffManTreeTemp[i].Parent;

    while (Parent!=0)
    {
      if (pHuffManTreeTemp[Parent].Left==n)
      {
        p[--nStart] = '0';
      }
      else
      {
        p[--nStart] = '1';
      }

      n = Parent;

      Parent = pHuffManTreeTemp[Parent].Parent;
    }
    

    printf("%d �ı����� %s \n ",pHuffManTreeTemp[i].Weight,&p[nStart]);

  }

  free(p);
}// HuffManCode
int main(int argc, char* argv[])
{

  pBiTree pRoot = NULL;

  printf("������������0���� ��Ҫ�ظ� \n");
   CreateBiTree(pRoot);
  pHuffManTree pHuffManTreeTemp = NULL;
  InitHuffManTree(pHuffManTreeTemp);
  CreateArray(pHuffManTreeTemp,pRoot);


  for (int i=1;i<g_nKey;++i)
  {
    printf("%d ",pHuffManTreeTemp[i].Weight);
  }

  printf("\n");

  CreateHuffManTree(pHuffManTreeTemp);


  for (i =1;i<2*g_nCount;++i)
  {
    printf("%d ",pHuffManTreeTemp[i].Weight);
  }

  printf("\nCode\n");

  HuffManCode(pHuffManTreeTemp);
  DestroyBiTree(pRoot);
  DestroyHuffManTree(pHuffManTreeTemp);
  return 0;
}// main 
