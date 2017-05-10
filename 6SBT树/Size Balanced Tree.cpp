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


// Nil哨兵结点，用来代替NULL表示空，可以极大地简化NULL判断
SBTNode Nil={0,0,&Nil,&Nil};

// 插入操作，注意可以这里使用leftBalance和rightBalance,省略maintain操作
BOOL Insert(pSBTNode &pNodeTemp,SBTDATA Data);

// 删除pRoot为根的树中，第一个含Data的结点 返回被删除的结点的指针第一个含x的结点
pSBTNode Delete (pSBTNode& pRoot,SBTDATA Data);

int GetDepth(pSBTNode pRoot);

// 中序遍历，方便调试用的
VOID InOrder(pSBTNode pRoot);

// 左平衡操作，用于平衡LL型和LR型
VOID LeftBalance(pSBTNode &pRoot);

// 右平衡操作，用于平衡RR型和RL型
VOID RightBalance(pSBTNode &pRoot);

// 左旋操作，两个平衡树基本操作之一
VOID L_Rotate(pSBTNode &pRoot);

// 右旋操作，两个平衡树基本操作之一
VOID R_Rotate(pSBTNode &pRoot);

// 返回Data如果插入pRoot树，排在第多少的位置,Data可以目前还不在pRoot中
int Rank(pSBTNode pRoot, SBTDATA Data);

pSBTNode Search(pSBTNode pRoot,SBTDATA Data);

// 返回第k大的结点,返回最小值Select(pRoot,1)即可
pSBTNode Select(pSBTNode pRoot,int K);

// 释放内存
VOID DestroySBT(pSBTNode &pRoot);

// 使用位运算高效交换两个数值
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

  printf("插入%d个数据使用了%d ms.\n",N,end-start);

  printf("左树的大小:%d 右树的大小:%d.\n",pRoot->Left->Size,pRoot->Right->Size);

  printf("树的高度%d.左树的高度:%d 右树的高度:%d.\n",GetDepth(pRoot),GetDepth(pRoot->Left),GetDepth(pRoot->Right));

  printf("15的等级是%d.\n",Rank(pRoot,15));

  printf("根是:%d.\n",pRoot->Data);

  printf("中序遍历.\n");
  
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

// 删除操作，也是最难正确实现的操作了，但其实一般题目中很少用，
// 如果直接假设int x在树中是存在的，那么将简单很多，但这并不十分合理
// 删除的总体是思路是这样的：
// 
// 如果比当前结点值小，到左树上面去删除
// 如果比当前结点值大，到右树上面去删除
// 如果等于当前结点值，那么应该删除本结点，但直接删除可能会破坏树的结构
// 如果左子树为空，返回右子树
// 如果右子树为空，返回左子树
// 如果左右子树都不为空，应该找到其中序前驱，或者后继来替换这个结点
// 
// 在不考虑size域的情况下，自此应该可以写出递归版本的删除了
// 但考虑size域呢，如果假设int x一定存在，那么只需要沿路径size--就可以
// 但如果还可能int x不存在呢，能直接沿路size--吗？这是不可以的
// 那么只有先尝试递归向下删除，查看删除结果，再判断是否size--，那么一些
// 简洁的写法不得不变的略复杂一下
// 
// 如果不需要Delete操作，那么数组静态实现是更好的选择，因为简单很多

// 删除pRoot为根的树中，第一个含Data的结点 返回被删除的结点的指针
pSBTNode Delete (pSBTNode& pRoot,SBTDATA Data)
{
  // 空树不需要删除
  if (pRoot==&Nil)
  {
    return &Nil;
  }

  pSBTNode p = &Nil;// 记录被删除的结点，并返回

  // 应该到左子树上寻找删除结点
  if (Data<pRoot->Data)
  {
    p = Delete(pRoot->Left,Data);
  }
  // 应该到右子树上寻找删除结点
  else if (Data>pRoot->Data)
  {
    p = Delete(pRoot->Right,Data);
  }

  // 删除本结点
  else
  {
    // 如果左右子树都不为空
    if (pRoot->Left!=&Nil && pRoot->Right!=&Nil)
    {
      // 找到中序的前驱，左子树的最右结点
      pSBTNode f= pRoot;

      p = f->Left;

      while (p->Right!=&Nil)
      {
        f= p;
        p = p->Right;
      }

      // p为用来替换根的结点，f是其父结点
      if (p==f->Right)
      {
        f->Right = p->Left;
      }
      else// p== f->Left
      {
        f->Left = p->Left;
      }
      
      // pRoot和p互换数据

      Swap(pRoot->Data,p->Data);
    }

    // 如果左子树为空(右子树空 或者 不空)
    else if (pRoot->Left==&Nil)
    {
      p = pRoot;

      pRoot = pRoot->Right;
    }
    else // 如果右子树为空(左子树一定不空)
    {
      p = pRoot;

      pRoot = pRoot->Left;
    }
  }

  // 调整大小,删除后pRoot可能是Nil
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

// 中序遍历，方便调试用的
VOID InOrder(pSBTNode pRoot)
{
  if (pRoot!=&Nil)
  {
    InOrder(pRoot->Left);

    printf("值:%4d,大小:%4d ",pRoot->Data,pRoot->Size);

    InOrder(pRoot->Right);
  }
}

// 左平衡操作，用于平衡LL型和LR型
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

// 右平衡操作，用于平衡RR型和RL型
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

// 左旋操作，两个平衡树基本操作之一
VOID L_Rotate(pSBTNode &pRoot)
{
  // 交接
  pSBTNode p = pRoot->Right;

  pRoot->Right = p->Left;

  p->Left = pRoot;

  // 调整
  p->Size = pRoot->Size;

  pRoot->Size = pRoot->Left->Size +pRoot->Right->Size +1;

  pRoot = p;

}
// 右旋操作，两个平衡树基本操作之一
VOID R_Rotate(pSBTNode &pRoot)
{
  // 交接
  pSBTNode p = pRoot->Left;

  pRoot->Left = p->Right;

  p->Right = pRoot;

  // 调整

  p->Size = pRoot->Size;

  pRoot->Size = pRoot->Left->Size + pRoot->Right->Size +1;

  pRoot = p;
}

// 返回Data如果插入pRoot树，排在第多少的位置,Data可以目前还不在pRoot中
int Rank(pSBTNode pRoot, SBTDATA Data)
{
  // 空树，插入即是最大
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

// 返回第k大的结点,返回最小值Select(pRoot,1)即可
pSBTNode Select(pSBTNode pRoot,int K)
{
  if (pRoot==&Nil || K>pRoot->Size)
  {
    return &Nil;
  }

  // OffSet表示比根大多少个位置
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

