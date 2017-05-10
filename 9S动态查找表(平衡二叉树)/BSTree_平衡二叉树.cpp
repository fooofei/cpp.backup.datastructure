#include <iostream>
#include <STDIO.H>
#include <WINDOWS.H>
using namespace std;
#define LH 1
#define EH 0
#define RH -1

// 平衡二叉树多用于查找数据，所以平衡二叉树又是颗二叉排序树。

typedef struct _BSTREE_
{
	int bf;

	int Data;

	_BSTREE_* pLNext;
	_BSTREE_* pRNext;
}BSTree,*pBSTree;

void L_Rotate(pBSTree &pBSTreeTemp);
void R_Rotate(pBSTree &pBSTreeTemp);
void DestroyBSTree(pBSTree &pBSTreeTemp);
void RightBalance(pBSTree &pBSTreeTemp);
void LeftBalance(pBSTree &pBSTreeTemp);
BOOL InsertAVL(pBSTree &pBSTreeTemp,int Data,BOOL &bTaller);
void TraverseBSTree(pBSTree pBSTreeTemp);
pBSTree GetPoint(pBSTree pBSTreeTemp,int Data);

int main(int argc, char** argv)
{
  BOOL bTaller;

  pBSTree pRoot = NULL;

  int p[] = {13,24,37,90,53};
  int Size =sizeof(p)/sizeof(int);

  int i = 0;

  for (i=0;i<Size;++i)
  {
    InsertAVL(pRoot,p[i],bTaller);
  }

  TraverseBSTree(pRoot);

  DestroyBSTree(pRoot);
  return 0;
}




pBSTree GetPoint(pBSTree pBSTreeTemp,int Data)
{

  while (pBSTreeTemp)
  {
    if (pBSTreeTemp->Data==Data)
    {
      return pBSTreeTemp;
    }

    else if (pBSTreeTemp->Data>Data)
    {
      pBSTreeTemp = pBSTreeTemp->pLNext;
    }
    else 
    {
      pBSTreeTemp = pBSTreeTemp->pRNext;
    }
  }

  return NULL;
}


BOOL InsertAVL(pBSTree &pBSTreeTemp,int Data,BOOL &bTaller)
{
  if (!pBSTreeTemp)
  {
   
    if (NULL==( pBSTreeTemp = (pBSTree)malloc(sizeof(BSTree))))
    {
      exit(0);
    }

    memset(pBSTreeTemp,0,sizeof(BSTree));

    pBSTreeTemp->Data = Data;

    bTaller = TRUE;

    return TRUE;
  }

  if (pBSTreeTemp->Data==Data)
  {
    bTaller = FALSE;

    return FALSE;
  }

  if (pBSTreeTemp->Data>Data)
  {
    if (!InsertAVL(pBSTreeTemp->pLNext,Data,bTaller))
    {
      return FALSE;
    }

    if (bTaller)
    {
      switch(pBSTreeTemp->bf)
      {
      case LH:
        {
          LeftBalance(pBSTreeTemp);

          bTaller = FALSE;

          break;
        }
      case EH:
        {
          pBSTreeTemp->bf = LH;
          
          bTaller = TRUE;

          break;
        } 

      case RH:
        {
          pBSTreeTemp->bf = EH;

          bTaller = FALSE;
        }
      }
    }
  }

  else // pBSTreeTemp->Data < Data
  {
    if (!InsertAVL(pBSTreeTemp->pRNext,Data,bTaller))
    {
      return FALSE;
    }

    if (bTaller)
    {
      switch(pBSTreeTemp->bf)
      {
      case LH:
        {
          pBSTreeTemp->bf = EH;

          bTaller = FALSE;
          break;
        }
      case EH:
        {
          pBSTreeTemp->bf = RH;
          bTaller = TRUE;
          break;
        }
      case RH:
        {
          RightBalance(pBSTreeTemp);

          bTaller = FALSE;
          break;
        }
      }
    }
  }

  return TRUE;

}

void TraverseBSTree(pBSTree pBSTreeTemp)
{
  if (pBSTreeTemp)
  {
    TraverseBSTree(pBSTreeTemp->pLNext);

    printf("%d ",pBSTreeTemp->Data);

    TraverseBSTree(pBSTreeTemp->pRNext);
  }
}

void L_Rotate(pBSTree &pBSTreeTemp) // 围绕 pBSTreeTemp 左旋 在图中就是 80
{
	/*
 绕某元素左旋转  
                                 80										                  90  
                                 /  \             左旋               /      \
                               60    90          ---- ->			     80       120
                                    /  \                          /  \       /
                                  85   120						         60     85   100
                                        /
                                      100     
                               a)  BST树                              b ) AVL树

	分析一下：在插入数据100之前，a图的B ST树只有80节点的平衡因子是-1(左高-右高)，但整棵树还是平衡的。加入100之后，80节点的平衡因子就成为了-2，此时平衡被破坏。需要左旋转成b 图。
     当树中节点X的右孩子的右孩子上插入新元素，且平衡因子从-1变成-2后，就需要绕节点X进行左旋转。   
							   */
	pBSTree pBSTreeCur = NULL;

	pBSTreeCur = pBSTreeTemp->pRNext;

	pBSTreeTemp->pRNext = pBSTreeCur->pLNext;

	pBSTreeCur->pLNext = pBSTreeTemp;

	pBSTreeTemp = pBSTreeCur;
}

void R_Rotate(pBSTree &pBSTreeTemp) // 围绕 pBSTreeTemp 右旋 在图中就是 100
{
	/*绕某元素右旋转  
                                 100									                     85
                                 /  \               右旋                /       \
                              85     120         ------ ->		  		  60        100  
                              /  \                                      \      /   \
                            60   90									                  	 80  90		120
                              \
                              80
                             a) B ST树                                b) AVL树
     当树中节点X的左孩子的左孩子上插入新元素，且平衡因子从1变成2后，就需要绕节点X进行右旋转。
	 */
	pBSTree pBSTreeCur = NULL;

	pBSTreeCur = pBSTreeTemp->pLNext;

	pBSTreeTemp->pLNext = pBSTreeCur ->pRNext;

	pBSTreeCur->pRNext = pBSTreeTemp;

	pBSTreeTemp = pBSTreeCur ;
}

void DestroyBSTree(pBSTree &pBSTreeTemp)
{
	if(pBSTreeTemp!=NULL)
	{
		DestroyBSTree(pBSTreeTemp->pLNext);

		DestroyBSTree(pBSTreeTemp->pRNext);

		delete pBSTreeTemp;

		pBSTreeTemp = NULL;
	}
}


void LeftBalance(pBSTree &pBSTreeTemp)
{
	pBSTree p = NULL;
	p = pBSTreeTemp->pLNext;

	pBSTree q= NULL;

	switch(p->bf)
	{
	case LH:/* 新结点插入在*T的左孩子的左子树上，要作单右旋处理 */
		{
			pBSTreeTemp->bf = p->bf = EH;

			R_Rotate(pBSTreeTemp);
			break;
		}
	case RH:/* 新结点插入在*T的左孩子的右子树上，要作双旋处理 */
		{
			q = p->pRNext;

			switch(q->bf)
			{
			case LH:
				{
					pBSTreeTemp->bf = RH;

					p->bf = EH;
					break;
				}
			case EH:
				{
					pBSTreeTemp->bf = p->bf = EH;

					break;
				}

			case RH:
				{
					pBSTreeTemp->bf = EH;
					
					p->bf  =  LH;


					break;
				}
			
			}

			q->bf = EH;

			L_Rotate(pBSTreeTemp->pLNext);

			R_Rotate(pBSTreeTemp);

			break;
		}

	}
}

void RightBalance(pBSTree &pBSTreeTemp)
{
	pBSTree p = NULL;

	p = pBSTreeTemp->pRNext;

	pBSTree q = NULL;

	switch(p->bf)
	{
	case RH:
		{
			pBSTreeTemp->bf = p->bf = EH;
			L_Rotate(pBSTreeTemp);
			break;
		}
	case LH:
		{
			q = p->pLNext;
			switch(q->bf)
			{
			case LH:
				{
					pBSTreeTemp->bf = EH;

					p->bf = RH;

					break;
				}
			case  EH:
				{
					pBSTreeTemp->bf = LH;

					p->bf = EH;

					break;
				}
			case RH:
				{
						pBSTreeTemp->bf = p->bf = EH;

						break;
				}

			}

			q->bf  = EH;

			R_Rotate(pBSTreeTemp->pRNext);

			L_Rotate(pBSTreeTemp);

			break;
		}



	}
}




/*

平衡二叉树的操作
 
1. 查找操作
       平衡二叉树的查找基本与二叉查找树相同。
 
2. 插入操作
       在平衡二叉树中插入结点与二叉查找树最大的不同在于要随时保证插入后整棵二叉树是平衡的。那么调整不平衡树的基本方法就是： 旋转 。 下面我们归纳一下平衡旋转的4中情况
1) 绕某元素左旋转  从最下边数    80 是不平衡的 围绕80旋转
                                 80                                    90  
                                 /  \             左旋               /    \
     RR                         60  90          ---- ->             80     120
                                    /  \                           /  \     /
                                  85 120                          60  85 100
                                        /
                                      100     
                               a)  BST树                              b ) AVL树
     分析一下：在插入数据100之前，a图的B ST树只有80节点的平衡因子是-1(左高-右高)，但整棵树还是平衡的。加入100之后，80节点的平衡因子就成为了-2，此时平衡被破坏。需要左旋转成b 图。
     当树中节点X的右孩子的右孩子上插入新元素，且平衡因子从-1变成-2后，就需要绕节点X进行左旋转。
 
2) 绕某元素右旋转  
                                100                                    85
     LL                          /  \               右旋              /    \
                              85  120         ------ ->              60    100  
                              /  \                                   \      /   \
                            60 90                                      80  90 120
                              \
                              80
                             a) B ST树                                b) AVL树
     当树中节点X的左孩子的左孩子上插入新元素，且平衡因子从1变成2后，就需要绕节点X进行右旋转。
 
3) 绕某元素的左子节点左旋转，接着再绕该元素自己右旋转。 此情况下就是左旋与右旋 的结合，具体操作时可以分 解成这两种操作，只是围绕点不一样而已。
                                                      
                              100                             100                                90
                             /  \             左旋            /  \              右旋           /    \
    LR                    80   120       ------>             90  120        ------>            80   100  
                          / \                                /                                /  \      \
                         60 90                               80                              60  85    120
                            /                               / \
                          85                               60 85 
      当树中节点X的左孩子的右孩子上插入新元素，且 平衡因子从1变成2后，就需要 先绕X的左子节点Y左旋转，接着再绕X右旋转

4) 绕某元素的右子节点右旋转，接着再绕该元素自己左旋转。 此情况下就是 右旋与左旋 的结合，具体操作时可以分解 成这两种操作，只是围绕点不一样而已 。
 
                                80                               80                                       85  
                               /   \             右 旋          /  \                 左 旋               /   \     
                             60   100      ------>              60 85            ------->               80  100
   RL                              /  \                              \                                 /   /   \       
                                  85  120                            100                             60    90 120
                                   \                                 /  \
                                   90                               90  120
       当树中节点X的右孩子的左孩子上插入新元素，且 平衡因子从-1变成-2后，就需要 先绕X的右子节点Y右旋转，接着再绕X左旋转

	   */