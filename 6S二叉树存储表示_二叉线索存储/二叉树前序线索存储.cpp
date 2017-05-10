
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
BOOL PreThreading(pBiTreeNode T);
BOOL PreOrderThreading(pBiTreeNode &Thrt,pBiTreeNode T);
BOOL PreOrderTravelThrPost(pBiTreeNode T);
BOOL PreOrderTraverse(pBiTreeNode T);// 作对比打印
pBiTreeNode g_pPre = NULL;


int main(int argc, char* argv[])
{

		pBiTreeNode pRoot = NULL;

		pBiTreeNode pThr = NULL;

		CreateBiTree(pRoot);

		PreOrderThreading(pThr,pRoot);

    printf("\n作对比\n");

    PreOrderTraverse(pRoot);

		printf("\n前序遍历(输出)二叉线索树(后继 ):\n");

		PreOrderTravelThrPost(pThr);

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

BOOL PreThreading(pBiTreeNode T)
{
		if (T)
		{
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

				if (T->LTag== LINK)
				{
						PreThreading(T->pLeft);
				}
				if (T->RTag==LINK)
				{
						PreThreading(T->pRight);
				}

      
//           PreThreading(T->pLeft);
//         
//       
//           PreThreading(T->pRight);
			

				return TRUE;
		}

		return FALSE;

}// PreThreading
BOOL PreOrderThreading(pBiTreeNode &Thrt,pBiTreeNode T)
{

		if (NULL==(Thrt = (pBiTreeNode)malloc(sizeof(BiTreeNode))))
		{
				return FALSE;
		}

		Thrt->pRight = Thrt;

		Thrt->RTag = THREAD;

		Thrt->LTag = LINK;

		if(!T)
		{
				Thrt->pLeft = Thrt;

				return FALSE;
		}

		g_pPre = Thrt;

		Thrt->pLeft = T;

		PreThreading(T);

		g_pPre->pRight = Thrt;

		g_pPre->RTag = THREAD;

		Thrt->pRight = g_pPre;

		return TRUE;
}// PreOrderThreading

BOOL PreOrderTravelThrPost(pBiTreeNode T)
{
		pBiTreeNode p = T->pLeft;

		while (p!=T) // 寻找结点的后继 比较简单  寻找结点的前驱很复杂
		{
				printf("%c ",p->iData);

				if (p->LTag==LINK)
				{
						p = p->pLeft;
				}

				else
				{
						p = p->pRight;
				}
		}

		return TRUE;

}// PreOrderTravelThrPost

BOOL PreOrderTraverse(pBiTreeNode T)
{
  if (T)
  {
    printf("%c ",T->iData);

    if (T->LTag==LINK)
    {
      PreOrderTraverse(T->pLeft);
    }
    if (T->RTag==LINK)
    {
      PreOrderTraverse(T->pRight);
    }

    return TRUE;
  }

  return FALSE;
}// PreOrderTraverse
// 123##4##56##7##
// 前序遍历(输出)二叉线索树(后继 ):
// 1 2 3 4 5 6 7
// Press any key to continue
