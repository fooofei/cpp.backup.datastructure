
// 参考别人的代码实现
// 2012-9-7
// author：
#include <STDIO.H>
#include <WINDOWS.H>

typedef enum{LINK,THREAD}PointerTag;

typedef struct _BITREENODE_
{
		int iData;
		_BITREENODE_* pLeft;
		_BITREENODE_* pRight;
		PointerTag LTag;
		PointerTag RTag;
}BiTreeNode,*pBiTreeNode;


BOOL CreateBiTree(pBiTreeNode &T);
BOOL PosThreading(pBiTreeNode T);
BOOL PosOrderThreading(pBiTreeNode &Thrt,pBiTreeNode T);
BOOL PosOrderTravelThr(pBiTreeNode Thr);
BOOL PosOrderTravel(pBiTreeNode T);// 与上面的作对比
pBiTreeNode PosPre(pBiTreeNode T);
pBiTreeNode g_pPre = NULL;
int main(int argc, char* argv[])
{

		pBiTreeNode pRoot = NULL;
		
		pBiTreeNode pThr = NULL;
		
		CreateBiTree(pRoot);
		
		PosOrderThreading(pThr,pRoot);

    printf("\n做对比\n");
    
    PosOrderTravel(pRoot);
		
		printf("\n后序遍历(输出)二叉线索树(后继 ):\n");
		
		PosOrderTravelThr(pThr);

    
		
		printf("\n");
		return 0;
}

BOOL CreateBiTree(pBiTreeNode &T)
{
		
		int iValue = 0;
		
		scanf(" %c",&iValue);
		
		if (iValue=='#')
		{
				T = NULL;
		}
		else
		{
				if (NULL==(T=(pBiTreeNode)malloc(sizeof(BiTreeNode))))
				{
						return false;
				}
				
				memset(T,0,sizeof(BiTreeNode));
				
				T->iData = iValue;
				
				CreateBiTree(T->pLeft);
				
				CreateBiTree(T->pRight);
		}
		
		return TRUE;
}// CreateBiTree

BOOL PosThreading(pBiTreeNode T)
{

		if (NULL != T)
		{
			PosThreading(T->pLeft);	
			PosThreading(T->pRight);
			
				if (!T->pLeft)
				{
						T->pLeft = g_pPre;
						
						T->LTag = THREAD;
				}
				
				if (!g_pPre->pRight)
				{
						g_pPre->pRight = T;
						
						g_pPre->RTag = THREAD;
				}
				g_pPre = T;
	
				return TRUE;
		}
		
		return FALSE;

}// PosThreading
BOOL PosOrderThreading(pBiTreeNode &Thrt,pBiTreeNode T)
{

		if (NULL==(Thrt = (pBiTreeNode)malloc(sizeof(BiTreeNode))))
		{
				return FALSE;
		}
		memset(Thrt,0,sizeof(BiTreeNode));

		Thrt->pRight = Thrt;
		
		Thrt->RTag = THREAD;
		
		Thrt->LTag = LINK;
		
		if(NULL == T)
		{
				Thrt->pLeft = Thrt;
				
				return FALSE;
		}
		
		g_pPre = Thrt;
		
		Thrt->pLeft = T;
		
		PosThreading(T);
		Thrt->pRight = g_pPre;

//     g_pPre->pRight = Thrt;
// 
//     g_pPre->RTag = THREAD;
		
		return TRUE;
}// PosOrderThreading

pBiTreeNode PosPre(pBiTreeNode T)// 找前驱
{
  if (!T)
  {
    return NULL;
  }

  if (T->RTag==LINK)
  {
    return T->pRight;
  }

  else
  {
    return T->pLeft;
  }

}// PosPre
BOOL PosOrderTravelThr(pBiTreeNode Thr) // 寻找直接前驱简单
{
  if (!Thr && !Thr->pRight)  // 这样打印 只能找前驱 因为后继找不到
  {
    return FALSE;
  }
	
  pBiTreeNode p = Thr->pRight;

  while (p!=Thr)
  {
    printf("%c ",p->iData);

    p = PosPre(p);
  }
		return TRUE;
}// PosOrderTravelThr

BOOL PosOrderTravel(pBiTreeNode T)
{
  if (NULL != T)
  {
    if (T->LTag==LINK)
    { 
      PosOrderTravel(T->pLeft);
    }

    if (T->RTag==LINK)
    {
      PosOrderTravel(T->pRight);
    }

    printf("%c ",T->iData);

    return TRUE;
  }

  return FALSE;
}// PosOrderTravel

// 寻找节点的直接前驱 
// 在后序线索二叉树中 若节点 RTag ==0 那么有右儿子  就是前驱
//   若RTag==1  LTag==0有左儿子 就是前驱  LTag==1 pLeft就是线索 也是前驱

// 寻找结点的直接后继
//  需要知道结点的双亲  不好找  所以这个算法缺陷很大 