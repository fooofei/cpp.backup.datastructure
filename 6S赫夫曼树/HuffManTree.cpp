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
  // 注意 有人可能说要在这里iNum+1  不如g_nCount*2就不-1了    这里代表的含义不同  所以我们还是这样写吧


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
    m = GetNode(pHuffManTreeTemp,i);// i 也是在变化的 所以这次得到的结果 下次也参与比较

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
int main(int argc, char* argv[])
{

  pBiTree pRoot = NULL;

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
  DestroyBiTree(pRoot);
  DestroyHuffManTree(pHuffManTreeTemp);
  return 0;
}// main 


// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 0
// 1 2 3 4 5 6 7 8 9
// 1 2 3 4 5 6 7 8 9 3 6 9 12 15 18 27 45 Press any key to continue