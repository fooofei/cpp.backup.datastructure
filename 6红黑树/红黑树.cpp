#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>

//红黑树的性质 1节点是红色或者黑色  2根节点是黑色  3每个叶子节点是黑色  4每个红色节点的两个子节点都是黑色，从每个叶子节点
//到根的所有路径不能有两个连续的红色节点   5从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点

//算法导论 13章  看看就行了   不要求


#define     RBTREE_COLOR_RED    0
#define     RBTREE_COLOR_BLACK  1


typedef struct _RBTREENODE_ 
{
	_RBTREENODE_* pLeft;
	_RBTREENODE_* pRight;
	_RBTREENODE_* pParent;
	int iMagic;
	void* pData;
}RBTreeNode,*pRBTreeNode;


typedef struct _RBTREE_ 
{
	pRBTreeNode pRoot;
	UINT uNodeCount;
}RBTree,*pRBTree;





//函数指针
typedef void (*DESTROYFUNC)(void* pData ); 
void DestroyData(void* pData);

typedef int (COMPAREFUNC)(void* pDataA,void* pDataB);
int CompareData(void* pDataA,void* pDataB);  //自定义比较规则 我这里用的是int 型数据


pRBTree RBTreeCreate(); //树的创建
void* RBTreeNodeCreate(void* pData); //叶子的创建

void RBTreeDestroy(pRBTree pRBTreeTemp,DESTROYFUNC DestroyFunc);
void RBTreeNodeDestroy(pRBTreeNode pRBTreeNodeTemp,DESTROYFUNC DestroyFunc);

// 红黑树的左旋操作,旋转前A节点和它的右节点B均存在,旋转后A节点的右指针指向B节点的左节点，B节点的左指针指向A节点，
void RBTreeRotateLeft(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA);
//红黑树的右旋操作,旋转前A节点和它的左节点B均存在,旋转后A节点的左指针指向B节点的右节点，B节点的右指针指向A节点，
void RBTreeRotateRight(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA);


// 两次左旋和一次右旋操作合并到一个函数里
//如果A为基准节点,则B为A的左节点,C为B的右节点,先对C作左旋,再对B左旋,再对A进行右旋而成。
void RBTreeRotateLeftLeftRight(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeStartNode);

// 两次左旋和一次右旋操作合并到一个函数里
//如果A为基准节点,则B为A的右节点,C为B的左节点先对C作右旋,再对B右旋,再对A进行左旋而成。
void RBTreeRotateRightRightLeft(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeStartNode);


//删除
void RBTreeAdjustColorForDel(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeParent,pRBTreeNode pRBTreeNodeReplace);
int  RBTreeDelete(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc,DESTROYFUNC DestroyFunc);

//插入
int RBTreeInsert(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc);
int RBTreeInterInsert(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeNew,COMPAREFUNC CompareFunc);
void RBTreeAdjustColorForInsert(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA);


//查找
void* RBTreeFind(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc);

void main()
{

}


pRBTree RBTreeCreate()
{
	pRBTree pTreeTemp = NULL;

	pTreeTemp = (pRBTree)malloc(sizeof(RBTree));

	if (pTreeTemp!=NULL)
	{
		pTreeTemp->pRoot = NULL;

		pTreeTemp->uNodeCount = 0;
	}


	return pTreeTemp;
}


void* RBTreeNodeCreate(void* pData)
{
	pRBTreeNode pRBTreeNodeNew = NULL;

	pRBTreeNodeNew = (pRBTreeNode)malloc(sizeof(RBTreeNode));

	if (pRBTreeNodeNew!=NULL)
	{
		pRBTreeNodeNew->pLeft = pRBTreeNodeNew->pRight = NULL;

		pRBTreeNodeNew->iMagic = RBTREE_COLOR_RED;

		pRBTreeNodeNew->pData = pData;
	}


	return (void*)pRBTreeNodeNew;
}

void RBTreeNodeDestroy(pRBTreeNode pRBTreeNodeTemp,DESTROYFUNC DestroyFunc)
{
	if (pRBTreeNodeTemp!=NULL)
	{
		if (pRBTreeNodeTemp->pLeft!=NULL)
		{
			RBTreeNodeDestroy(pRBTreeNodeTemp->pLeft,DestroyFunc);
		}

		if (pRBTreeNodeTemp->pRight!=NULL)
		{
			RBTreeNodeDestroy(pRBTreeNodeTemp->pRight,DestroyFunc);
		}

		if (DestroyFunc!=NULL&&pRBTreeNodeTemp->pData!=NULL)
		{
			DestroyFunc(pRBTreeNodeTemp->pData);
		}


		free(pRBTreeNodeTemp);
	}
}


void RBTreeDestroy(pRBTree pRBTreeTemp,DESTROYFUNC DestroyFunc)
{
	if (pRBTreeTemp!=NULL)
	{
		RBTreeNodeDestroy(pRBTreeTemp->pRoot,DestroyFunc);

		free(pRBTreeTemp);
	}
}


void RBTreeRotateLeft(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA)
{
	pRBTreeNode pRBTreeNodeB = NULL;

	pRBTreeNodeB = pRBTreeNodeA->pRight;

	//将B节点的左节点变成A节点的右节点

	pRBTreeNodeA->pRight = pRBTreeNodeB->pLeft;

	if (pRBTreeNodeB->pLeft!=NULL)
	{
		pRBTreeNodeB->pLeft->pParent = pRBTreeNodeA;
	}


	//修改A节点的父指针和B节点的关系
	pRBTreeNodeB->pParent = pRBTreeNodeA->pParent;

	if (pRBTreeNodeA==pRBTreeTemp->pRoot)
	{
		pRBTreeTemp->pRoot = pRBTreeNodeB;
	}

	else if (pRBTreeNodeA==pRBTreeNodeA->pParent->pLeft)
	{
		pRBTreeNodeA->pParent->pLeft = pRBTreeNodeB;
	}

	else
	{
		pRBTreeNodeA->pParent->pRight = pRBTreeNodeB;
	}

	 //将A节点变成B节点的左节点

	pRBTreeNodeB->pLeft = pRBTreeNodeA;

	pRBTreeNodeA->pParent = pRBTreeNodeB;

}


void RBTreeRotateRight(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA)
{
	pRBTreeNode pRBTreeNodeB = NULL;

	pRBTreeNodeB = pRBTreeNodeA->pLeft;

	//将B节点的右节点变成A节点的左节点
	
	pRBTreeNodeA->pLeft = pRBTreeNodeB->pRight;

	if (pRBTreeNodeB->pRight!=NULL)
	{
		pRBTreeNodeB->pRight->pParent = pRBTreeNodeA;
	}

	//修改A节点的父指针和B节点的关系

	pRBTreeNodeB->pParent = pRBTreeNodeA->pParent;

	if (pRBTreeNodeA==pRBTreeTemp->pRoot)
	{
		pRBTreeTemp->pRoot = pRBTreeNodeB;
	}

	else if (pRBTreeNodeA==pRBTreeNodeA->pParent->pRight)
	{
		pRBTreeNodeA->pParent->pRight = pRBTreeNodeB;
	}

	else
	{
		pRBTreeNodeA->pParent->pLeft = pRBTreeNodeB;
	}

	 //将A节点变成B节点的右节点
	pRBTreeNodeB->pRight = pRBTreeNodeA;

	pRBTreeNodeA->pParent = pRBTreeNodeB;


}


int RBTreeInsert(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc)
{
	int iRet = 0;

	pRBTreeNode pRBTreeNodeTemp;

	pRBTreeNodeTemp = (pRBTreeNode)RBTreeNodeCreate(pData);

	if (pRBTreeNodeTemp!=NULL)
	{
		iRet = RBTreeInterInsert(pRBTreeTemp,pRBTreeNodeTemp,CompareFunc);
	}

	return iRet;
}



int RBTreeInterInsert(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeNew,COMPAREFUNC CompareFunc)
{

	pRBTreeNode pRBTreeNodeTemp = NULL;

	pRBTreeNode pRBTreeNodeParent = NULL;

	int iRet = 0;

	pRBTreeNodeTemp = pRBTreeTemp->pRoot;

	while (pRBTreeNodeTemp!=NULL)
	{
		pRBTreeNodeParent = pRBTreeNodeTemp;

		iRet = CompareFunc(pRBTreeNodeTemp->pData,pRBTreeNodeNew->pData);

		if (iRet<0)
		{
			pRBTreeNodeTemp = pRBTreeNodeTemp->pRight;
		}

		else
		{
			pRBTreeNodeTemp = pRBTreeNodeTemp->pLeft;
		}


	}

	if (pRBTreeNodeParent==NULL)
	{
		//树为空的情况

		pRBTreeTemp->pRoot = pRBTreeNodeNew;

		pRBTreeNodeNew->pParent = NULL;
	}

	else
	{
		if (iRet<0)
		{
			pRBTreeNodeParent->pRight = pRBTreeNodeNew;
		}

		else
		{
			pRBTreeNodeParent->pLeft = pRBTreeNodeNew;
		}

		pRBTreeNodeNew->pParent = pRBTreeNodeParent;
	}

	pRBTreeTemp->uNodeCount+=1;

	
    RBTreeAdjustColorForInsert(pRBTreeTemp,pRBTreeNodeNew);

	return 1;

}



void RBTreeAdjustColorForInsert(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA)
{
	pRBTreeNodeA->iMagic = RBTREE_COLOR_RED;

	while (pRBTreeNodeA!=pRBTreeTemp->pRoot&&pRBTreeNodeA->pParent->iMagic==RBTREE_COLOR_RED)
	{
		if (pRBTreeNodeA->pParent==pRBTreeNodeA->pParent->pParent->pLeft)
		{
			//父节点为祖父节点左节点的情况

			pRBTreeNode pRBTreeNodeTemp = pRBTreeNodeA->pParent->pParent->pRight;

			if (pRBTreeNodeTemp!=NULL&&pRBTreeNodeTemp->iMagic==RBTREE_COLOR_RED)
			{
				pRBTreeNodeA->pParent->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeTemp->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeA->pParent->pParent->iMagic = RBTREE_COLOR_RED;


				//由于祖父节点颜色被改变成了红色，因此祖父节点和它的父节点
                //有可能都是红色，这里需要继续循环来矫正祖父节点的颜色平衡情况 
                
				pRBTreeNodeA = pRBTreeNodeA->pParent->pParent;
			}

			else
			{
				if (pRBTreeNodeA==pRBTreeNodeA->pParent->pRight)
				{
					pRBTreeNodeA = pRBTreeNodeA->pParent;

					RBTreeRotateLeft(pRBTreeTemp,pRBTreeNodeA);
				}

				pRBTreeNodeA->pParent->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeA->pParent->pParent->iMagic = RBTREE_COLOR_RED;

				RBTreeRotateRight(pRBTreeTemp,pRBTreeNodeA->pParent->pParent);
			}


		}

		else
		{
			//父节点为祖父节点右节点的情况
			pRBTreeNode pRBTreeNodeTemp = pRBTreeNodeA->pParent->pParent->pLeft;


			if (pRBTreeNodeTemp!=NULL&&pRBTreeNodeTemp->iMagic==RBTREE_COLOR_RED)
			{
				pRBTreeNodeA->pParent->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeTemp->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeA->pParent->pParent->iMagic = RBTREE_COLOR_RED;


				pRBTreeNodeA = pRBTreeNodeA->pParent->pParent;


			}

			else
			{
				if (pRBTreeNodeA==pRBTreeNodeA->pParent->pLeft)
				{
					pRBTreeNodeA = pRBTreeNodeA->pParent;

					RBTreeRotateRight(pRBTreeTemp,pRBTreeNodeA);
				}

				pRBTreeNodeA->pParent->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeA->pParent->pParent->iMagic = RBTREE_COLOR_RED;

				RBTreeRotateLeft(pRBTreeTemp,pRBTreeNodeA->pParent->pParent);
			}

		}
	}

	pRBTreeTemp->pRoot->iMagic = RBTREE_COLOR_BLACK;
}



void RBTreeRotateLeftLeftRight(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeStartNode)
{
	pRBTreeNode pRBTreeNodeParent = NULL;

	pRBTreeNode pRBTreeNodeB = NULL;

	pRBTreeNode pRBTreeNodeC = NULL;
	
	pRBTreeNode pRBTreeNodeD = NULL;
	
	pRBTreeNodeParent = pRBTreeStartNode;

	pRBTreeNodeB = pRBTreeNodeParent->pLeft;

	pRBTreeNodeC = pRBTreeNodeParent->pRight;

	pRBTreeNodeD = pRBTreeNodeC->pRight;

	if (pRBTreeNodeParent->pParent==NULL)
	{

		pRBTreeTemp->pRoot = pRBTreeNodeD;
	}

	else if (pRBTreeNodeParent->pParent->pLeft == pRBTreeNodeParent)
	{
		pRBTreeNodeParent->pParent->pLeft = pRBTreeNodeD;
	}

	else
	{
		pRBTreeNodeParent->pParent->pRight = pRBTreeNodeD;
	}

	pRBTreeNodeD->pParent = pRBTreeNodeParent->pParent;

	pRBTreeNodeC->pRight = pRBTreeNodeD->pLeft;

	if (pRBTreeNodeD->pLeft!=NULL)
	{
		pRBTreeNodeD->pLeft->pParent = pRBTreeNodeC;
	}

	pRBTreeNodeParent->pLeft = pRBTreeNodeD->pRight;

	if (pRBTreeNodeD->pRight!=NULL)
	{

		pRBTreeNodeD->pRight->pParent = pRBTreeNodeParent;
	}

	pRBTreeNodeD->pLeft = pRBTreeNodeB;

	pRBTreeNodeB->pParent = pRBTreeNodeD;

	pRBTreeNodeD->pRight = pRBTreeNodeParent;

	pRBTreeNodeParent->pParent = pRBTreeNodeD;
}


void RBTreeRotateRightRightLeft(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeStartNode)
{
	pRBTreeNode pRBTreeNodeParent;
	pRBTreeNode pRBTreeNodeB = NULL;
	pRBTreeNode pRBTreeNodeC = NULL;
	pRBTreeNode pRBTreeNodeD = NULL;


	pRBTreeNodeParent = pRBTreeStartNode;

	pRBTreeNodeB = pRBTreeNodeParent->pRight;

	pRBTreeNodeC = pRBTreeNodeB->pLeft;

	pRBTreeNodeD = pRBTreeNodeC->pLeft;

	//使D节点成为A节点祖父节点的子节点,即节点替代祖父节点位置

	if (pRBTreeNodeParent->pParent==NULL)
	{
		pRBTreeTemp->pRoot = pRBTreeNodeD;
	}

	else if (pRBTreeNodeParent->pParent->pLeft==pRBTreeNodeParent)
	{
		pRBTreeNodeParent->pParent->pLeft = pRBTreeNodeD;
	}

	else
	{
		pRBTreeNodeParent->pParent->pRight = pRBTreeNodeD;
	}

	pRBTreeNodeD->pParent = pRBTreeNodeParent->pParent;


	//D节点的右节点变成C节点的左节点

	pRBTreeNodeC->pLeft = pRBTreeNodeD->pRight;

	if (pRBTreeNodeD->pRight!=NULL)
	{
		pRBTreeNodeD->pRight->pParent = pRBTreeNodeC;
	}

	 //D节点的左节点变成父节点的右节点

	pRBTreeNodeParent->pRight = pRBTreeNodeD->pLeft;

	if (pRBTreeNodeD->pLeft!=NULL)
	{
		pRBTreeNodeD->pLeft->pParent = pRBTreeNodeParent;
	}

	//B节点变成D节点的右节点
	pRBTreeNodeD->pRight = pRBTreeNodeB;

	pRBTreeNodeB->pParent = pRBTreeNodeD;

	//父节点变成D节点的左节点

	pRBTreeNodeD->pLeft = pRBTreeNodeParent;

	pRBTreeNodeParent->pParent = pRBTreeNodeD;
}


//看看就行了很复杂
void RBTreeAdjustColorForDel(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeParent,pRBTreeNode pRBTreeNodeReplace)
{
	pRBTreeNode  pRBTreeNodeA;                  // 需要调整平衡的节点 
    pRBTreeNode  pRBTreeNodeAParent;			  // A节点的父节点 
    pRBTreeNode  pRBTreeNodeB;            // pRBTreeNodeA的另一子节点 
    pRBTreeNode  pRBTreeNodeC;           // 临时变量用来记录B节点的一个子节点 


	pRBTreeNodeA = pRBTreeNodeReplace;
	
    pRBTreeNodeAParent = pRBTreeNodeParent;
	
	while (pRBTreeNodeA != pRBTreeTemp->pRoot 
            && (pRBTreeNodeA == NULL || pRBTreeNodeA->iMagic == RBTREE_COLOR_BLACK))
	{
		if (pRBTreeNodeA == pRBTreeNodeAParent->pLeft)   //左右型
		{
			pRBTreeNodeB = pRBTreeNodeAParent->pRight;

			if (pRBTreeNodeB->iMagic == RBTREE_COLOR_RED)
			{
				pRBTreeNodeC = pRBTreeNodeB->pLeft;

				if ((pRBTreeNodeC->pLeft == NULL 
                    || pRBTreeNodeC->pLeft->iMagic == RBTREE_COLOR_BLACK)
                    && (pRBTreeNodeC->pRight == NULL 
                    || pRBTreeNodeC->pRight->iMagic == RBTREE_COLOR_BLACK))
				{
					//C节点左右节点都是黑色的情况
					pRBTreeNodeC->iMagic = RBTREE_COLOR_RED;
                    pRBTreeNodeB->iMagic = RBTREE_COLOR_BLACK;
                    
					RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}

				else if (pRBTreeNodeC->pRight != NULL 
                    && pRBTreeNodeC->pRight->iMagic == RBTREE_COLOR_RED 
                    && ( pRBTreeNodeC->pLeft == NULL 
                    || pRBTreeNodeC->pLeft->iMagic == RBTREE_COLOR_BLACK))
				{
					//即C节点左节点为黑色，右节点为红色的情况
					pRBTreeNodeC->pRight->iMagic = RBTREE_COLOR_BLACK;
                    RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeB);
                    RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}

				else
				{
					//左红右黑 与 双红 的情况

					pRBTreeNodeC->pLeft->iMagic = RBTREE_COLOR_BLACK;
                    RBTreeRotateRightRightLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}
			}

			else
			{
				if ((pRBTreeNodeB->pLeft == NULL 
                    || pRBTreeNodeB->pLeft->iMagic == RBTREE_COLOR_BLACK)
                    && ( pRBTreeNodeB->pRight == NULL  
                    || pRBTreeNodeB->pRight->iMagic == RBTREE_COLOR_BLACK))
				{
					// B节点的左右子节点都是黑色的情况
					if (pRBTreeNodeAParent->iMagic == RBTREE_COLOR_BLACK )
					{
						 //如果A节点的父节点颜色为黑色的话,需要将B节点改成红色，
                         //然后将A节点的父节点变成A节点重新调整平衡。
                        
                        pRBTreeNodeB->iMagic = RBTREE_COLOR_RED;
                        pRBTreeNodeA = pRBTreeNodeAParent;
                        pRBTreeNodeAParent = pRBTreeNodeA->pParent;
                        
						continue;
					}

					else
                    {
                         // A节点的父节点为红色的情况,只需要将A节点的颜色
                         // 改成黑色,将B节点颜色改成红色即可达到平衡
                         
                        pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
                        pRBTreeNodeB->iMagic = RBTREE_COLOR_RED;
                    }
				}

				else if (pRBTreeNodeB->pRight != NULL 
                    && pRBTreeNodeB->pRight->iMagic == RBTREE_COLOR_RED
                    && (pRBTreeNodeB->pLeft == NULL 
                    || pRBTreeNodeB->pLeft->iMagic == RBTREE_COLOR_BLACK ))
				{
					//即B节点的左子节点为黑色，右子节点为红色的情况

					pRBTreeNodeB->iMagic = pRBTreeNodeAParent->iMagic;
                    pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
                    pRBTreeNodeB->pRight->iMagic = RBTREE_COLOR_BLACK;
                    RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}

				else
				{
					//B节点的左子节点红黑和都为红色的情况,需
                    //要先对B节点进行右旋再对A节点的父节点进行左旋即可达到平衡

					pRBTreeNodeB->pLeft->iMagic = pRBTreeNodeAParent->iMagic;
                    pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
                    RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeB);
                    RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}
			}
		}

		else               //右左性
		{
			 pRBTreeNodeB = pRBTreeNodeAParent->pLeft;

			 if (pRBTreeNodeB->iMagic == RBTREE_COLOR_RED)
			 {
				 pRBTreeNodeC = pRBTreeNodeB->pRight;

				 if ((pRBTreeNodeC->pLeft == NULL 
					 || pRBTreeNodeC->pLeft->iMagic == RBTREE_COLOR_BLACK)
					 && (pRBTreeNodeC->pRight == NULL 
                    || pRBTreeNodeC->pRight->iMagic == RBTREE_COLOR_BLACK))
				 {
					 
					 
					 pRBTreeNodeB->iMagic = RBTREE_COLOR_BLACK;
					 pRBTreeNodeC->iMagic = RBTREE_COLOR_RED;
                     RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeAParent);

				 }

				 else if(pRBTreeNodeC->pRight == NULL 
					 ||pRBTreeNodeC->pRight->iMagic == RBTREE_COLOR_BLACK)
				 {
				
					 pRBTreeNodeC->pLeft->iMagic = RBTREE_COLOR_BLACK;
					 RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent->pLeft);
					 RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeAParent);
				 }

				 else
				 {
					 pRBTreeNodeC->pRight->iMagic = RBTREE_COLOR_BLACK;
                     RBTreeRotateLeftLeftRight(pRBTreeTemp, pRBTreeNodeAParent);
				 }
			 }

			 else
			 {
				 if ((pRBTreeNodeB->pLeft == NULL 
					 || pRBTreeNodeB->pLeft->iMagic == RBTREE_COLOR_BLACK)
					 && ( pRBTreeNodeB->pRight == NULL  
                    || pRBTreeNodeB->pRight->iMagic == RBTREE_COLOR_BLACK ))
				 {
					 if (pRBTreeNodeAParent->iMagic == RBTREE_COLOR_BLACK )
					 {
						 pRBTreeNodeB->iMagic = RBTREE_COLOR_RED;
						 pRBTreeNodeA = pRBTreeNodeAParent;
						 pRBTreeNodeAParent = pRBTreeNodeA->pParent;
                         continue;
					 }

					 else
					 {
						 pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
                         pRBTreeNodeB->iMagic = RBTREE_COLOR_RED;
					 }
				 }

				 else if (pRBTreeNodeB->pLeft != NULL 
					 && pRBTreeNodeB->pLeft->iMagic == RBTREE_COLOR_RED
					 && (pRBTreeNodeB->pRight == NULL 
                    || pRBTreeNodeB->pRight->iMagic == RBTREE_COLOR_BLACK ))
				 {
					 pRBTreeNodeB->iMagic = pRBTreeNodeAParent->iMagic;
					 pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
					 pRBTreeNodeB->pLeft->iMagic = RBTREE_COLOR_BLACK;
                     RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeAParent);
				 }

				 else
				 {
					 pRBTreeNodeB->pRight->iMagic = pRBTreeNodeAParent->iMagic;
					 pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
					 RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeB);
                     RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeAParent);
				 }
			 }
		}

		break;
	}

	if (pRBTreeNodeA!=NULL)
	{
		pRBTreeNodeA->iMagic = RBTREE_COLOR_BLACK;
	}
}

int RBTreeDelete(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc,DESTROYFUNC DestroyFunc)
{
	pRBTreeNode pRBTreeNodeParent = NULL;

	pRBTreeNode pRBTreeNodeA = NULL;

	pRBTreeNode pRBTreeNodeAParent = NULL;

	int iRet = 0;

	pRBTreeNode pRBTreeNodeTravel = NULL;

	pRBTreeNode pRBTreeNodeDel = NULL;

	if (pRBTreeTemp == NULL ||pData == NULL ||CompareFunc == NULL )
    {
        return -1;
    }

	pRBTreeNodeTravel = pRBTreeTemp->pRoot;

	while (pRBTreeNodeTravel!=NULL)
	{
		pRBTreeNodeParent = pRBTreeNodeTravel;

		iRet = CompareFunc(pRBTreeNodeTravel->pData,pData);

		if (iRet<0)
		{
			pRBTreeNodeTravel = pRBTreeNodeTravel->pRight;
		}

		else if (iRet>0)
		{
			pRBTreeNodeTravel =  pRBTreeNodeTravel->pLeft;
		}

		else
		{
			break;
		}
	}

	if (pRBTreeNodeTravel==NULL)
	{
		return -1;  //没有该数据
	}

	pRBTreeNodeDel = pRBTreeNodeTravel;

	if (pRBTreeNodeTravel->pLeft != NULL && pRBTreeNodeTravel->pRight != NULL)
	{
		int iMagic;

		//pRBTreeNodeTravel有两个子节点的情况
		pRBTreeNodeDel = pRBTreeNodeDel->pLeft;  
		
		while (pRBTreeNodeDel->pRight!=0)
		{
			pRBTreeNodeDel = pRBTreeNodeDel->pRight;
		}

		pRBTreeNodeA = pRBTreeNodeDel->pLeft;

		pRBTreeNodeTravel->pRight->pParent = pRBTreeNodeDel; 
        pRBTreeNodeDel->pRight = pRBTreeNodeTravel->pRight;


		if (pRBTreeNodeDel != pRBTreeNodeTravel->pLeft)
		{
			pRBTreeNodeAParent = pRBTreeNodeDel->pParent;
            if (pRBTreeNodeA != NULL)
            {
                pRBTreeNodeA->pParent = pRBTreeNodeDel->pParent;
            }
            pRBTreeNodeDel->pParent->pRight = pRBTreeNodeTravel;
            pRBTreeNodeDel->pLeft = pRBTreeNodeTravel->pLeft;
            pRBTreeNodeTravel->pLeft->pParent = pRBTreeNodeDel;
		}

		else
		{
			 pRBTreeNodeAParent = pRBTreeNodeDel;  
		}

		if (pRBTreeTemp->pRoot == pRBTreeNodeTravel)
		{
			pRBTreeTemp->pRoot = pRBTreeNodeDel;
		}

		else if (pRBTreeNodeTravel->pParent->pLeft == pRBTreeNodeTravel)
		{
			  pRBTreeNodeTravel->pParent->pLeft = pRBTreeNodeDel;
		}

		else
		{
			pRBTreeNodeTravel->pParent->pRight = pRBTreeNodeDel;
		}

		pRBTreeNodeDel->pParent = pRBTreeNodeTravel->pParent;
		
        iMagic = pRBTreeNodeDel->iMagic;
        pRBTreeNodeDel->iMagic = pRBTreeNodeTravel->iMagic;
        pRBTreeNodeTravel->iMagic = iMagic;
		
        pRBTreeNodeDel = pRBTreeNodeTravel;
	}

	else
	{
		//处理最多只有一个子节点的情况

		if (pRBTreeNodeTravel->pLeft!=NULL)
		{
			pRBTreeNodeA = pRBTreeNodeTravel->pLeft;
		}

		else
		{
			pRBTreeNodeA = pRBTreeNodeTravel->pRight;
		}

		pRBTreeNodeAParent = pRBTreeNodeDel->pParent;

		if (pRBTreeNodeA!=NULL)
		{
			 pRBTreeNodeA->pParent = pRBTreeNodeDel->pParent;   
		}

		if (pRBTreeTemp->pRoot==pRBTreeNodeTravel)
		{
			pRBTreeTemp->pRoot = pRBTreeNodeA;
		}

		else
		{
			if (pRBTreeNodeTravel->pParent->pLeft == pRBTreeNodeTravel)
			{
				pRBTreeNodeTravel->pParent->pLeft = pRBTreeNodeA;
			}

			else
			{
				pRBTreeNodeTravel->pParent->pRight = pRBTreeNodeA;
			}
		}

	}

	if (pRBTreeNodeDel->iMagic != RBTREE_COLOR_RED)
	{
		RBTreeAdjustColorForDel(pRBTreeTemp, pRBTreeNodeAParent, pRBTreeNodeA);

        if (DestroyFunc != NULL )
        {
            DestroyFunc(pRBTreeNodeDel->pData);
        }
        free(pRBTreeNodeDel);

	}

    pRBTreeTemp->uNodeCount -= 1;
	
    return 1;

}




void* RBTreeFind(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc)
{
	pRBTreeNode pRBTreeNodeTemp = NULL;

	if (pRBTreeTemp==NULL||pData==NULL||CompareFunc==NULL)
	{
		return NULL;
	}

	pRBTreeNodeTemp = pRBTreeTemp->pRoot;

	while (pRBTreeNodeTemp!=NULL)
	{
		int iRet = CompareFunc(pRBTreeNodeTemp->pData,pData);


		if (iRet<0)
		{
			pRBTreeNodeTemp = pRBTreeNodeTemp->pRight;
		}

		else if (iRet>0)
		{
			pRBTreeNodeTemp = pRBTreeNodeTemp->pLeft;
		}

		else
		{
			return pRBTreeNodeTemp->pData;
		}
	}


	return NULL;
}



void DestroyData(void* pData)
{
	if (pData!=NULL)
	{
		free(pData);
	}
}


int CompareData(void* pDataA,void* pDataB)
{
	if (*((int*)pDataA)>*((int*)pDataB))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}