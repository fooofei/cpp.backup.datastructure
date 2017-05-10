#include <iostream>
using namespace std;
#include "ListQueue.h"
#include "NodeType.h"

// 重点是得到树的深度
// 21 个  子函数 
void  CreateBiTree(pBTNode &pRoot);
void DestroyBiTree(pBTNode &pRoot);
bool BiTreeIsEmpty(pBTNode pRoot);
int BiTreeDepth(pBTNode pRoot);
TElemType GetRoot (pBTNode pRoot);
TElemType GetValue(pBTNode p);
void Assign(pBTNode p,TElemType value);/* 给p所指结点赋值为value */
void PreOrderTraverse(pBTNode pRoot);
void InOrderTraverse(pBTNode pRoot);
void PosOrderTraverse(pBTNode pRoot);
void LevelOrderTraverse(pBTNode pRoot);
//////////////////////////////////////////////////////////////////////////
TElemType GetParent(pBTNode pRoot,TElemType e);
pBTNode GetPoint(pBTNode pRoot,TElemType s);
TElemType GetLeft(pBTNode pRoot,TElemType e);
TElemType GetRight(pBTNode pRoot,TElemType e);

//////////////////////////////////////////////////////////////////////////
TElemType GetLeftSibling(pBTNode pRoot,TElemType e);
TElemType GetRightSibling(pBTNode pRoot,TElemType e);

//////////////////////////////////////////////////////////////////////////
void InsertChild(pBTNode pBTNodeTemp,bool LR,pBTNode pRootNew);
void DelChild(pBTNode pBTNodeTemp, bool LR);

//////////////////////////////////////////////////////////////////////////

// 对于第二个二叉树的问题，如果节点中不包含指向父节点的指针应该怎么计算？
// 算法思想：如果一个节点的左子树包含p，q中的一个节点，右子树包含另一个，则这个节
// 点就是p，q的最近公共祖先。

int NearestCommonAncestor(pBTNode pRoot,pBTNode a, pBTNode b,pBTNode &pParent);

int main ()
{
	pBTNode pRoot = NULL; //主树

	cout<<"构建主树"<<endl;
	CreateBiTree(pRoot);
	cout<<"主树前序遍历";
	PreOrderTraverse(pRoot);
	cout<<endl;
	cout<<"主树中序遍历";
	InOrderTraverse(pRoot);
	cout<<endl;
	cout<<"主树后序遍历";
	PosOrderTraverse(pRoot);
	cout<<endl;
	cout<<"层次";
	LevelOrderTraverse(pRoot);
	cout<<endl;
 	cout<<"主树的深度";
 	cout<<BiTreeDepth(pRoot)<<endl;

	cout<<endl;


	

//	cout<<GetLeftSibling(pRoot,'3')<<endl;

//	cout<<GetRightSibling(pRoot,'2')<<endl;




	cout<<endl;
	cout<<"主树前序遍历";
	PreOrderTraverse(pRoot);
	cout<<endl;
	cout<<"主树中序遍历";
	InOrderTraverse(pRoot);
	cout<<endl;
	cout<<"主树后序遍历";
	PosOrderTraverse(pRoot);
	cout<<endl;
	cout<<"层次";
	LevelOrderTraverse(pRoot);
	cout<<endl;
	DestroyBiTree(pRoot);
	return 0;
}


void  CreateBiTree(pBTNode &pRoot)
{
	TElemType c = 0;
	cin>>c;
	if(c==Nil)
	{
		pRoot = NULL;
	}
	else
	{
		pRoot = (pBTNode)malloc(sizeof(BTNode));
		if (pRoot==NULL)
		{
			return ;
		}

		pRoot->Data = c;

		CreateBiTree(pRoot->pLNext);

		CreateBiTree(pRoot->pRNext);
	}
}

void DestroyBiTree(pBTNode &pRoot)
{
	if(pRoot!=NULL)
	{
		DestroyBiTree(pRoot->pLNext);

		DestroyBiTree(pRoot->pRNext);

		free(pRoot);

		pRoot = NULL;
	}
}

bool BiTreeIsEmpty(pBTNode pRoot)
{
	if(pRoot==NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int BiTreeDepth(pBTNode pRoot)
{
	int i =0;
	int j = 0;

	if(pRoot==NULL)
	{
		return 0;
	}
	if(pRoot->pLNext!=NULL)
	{
		i = BiTreeDepth(pRoot->pLNext);
	}
	
	if(pRoot->pRNext!=NULL)
	{
		j = BiTreeDepth(pRoot->pRNext);
	}
	
	return i>j?i+1:j+1;
}

int NearestCommonAncestor(pBTNode pRoot,pBTNode a, pBTNode b,pBTNode &pParent)
{
	if (pRoot==NULL)
	{
		return 0;
	}

	if (pRoot==a||pRoot==b)
	{
		return 1;
	}

	int iLeft = NearestCommonAncestor(pRoot->pLNext,a,b,pParent);

	if (iLeft==2)
	{
		return 2;
	}

	int iRight = NearestCommonAncestor(pRoot->pRNext,a,b,pParent);

	if (iRight==2)
	{
		return 2;
	}

	if (iLeft+iRight==2)
	{
		pParent = pRoot;
	}

	return iLeft+ iRight;

}
TElemType GetRoot (pBTNode pRoot)
{/* 初始条件: 二叉树存在。操作结果: 返回根 */
	if(BiTreeIsEmpty(pRoot))
	{
		return Nil;
	}
	else
	{
		return pRoot->Data;
	}
}

TElemType GetValue(pBTNode p)
{/* 初始条件: 二叉树T存在，p指向T中某个结点 */
	if(p!=NULL)
	{
		return p->Data;
	}

	return Nil;
	
}

void Assign(pBTNode p,TElemType value)
{/* 给p所指结点赋值为value */
	p->Data = value;
}


void PreOrderTraverse(pBTNode pRoot)
{
	if(pRoot!=NULL)
	{
		cout<<pRoot->Data<<" ";
		PreOrderTraverse(pRoot->pLNext);
		PreOrderTraverse(pRoot->pRNext);
	}
}

void InOrderTraverse(pBTNode pRoot)
{
	if(pRoot!=NULL)
	{
		InOrderTraverse(pRoot->pLNext);
		
		cout<<pRoot->Data<<" ";

		InOrderTraverse(pRoot->pRNext);
	}
}

void PosOrderTraverse(pBTNode pRoot)
{
	if(pRoot!=NULL)
	{
		PosOrderTraverse(pRoot->pLNext);

		PosOrderTraverse(pRoot->pRNext);

		cout<<pRoot->Data<<" ";
	}


}

TElemType GetParent(pBTNode pRoot,TElemType e)
{/* 初始条件: 二叉树存在,e是某个结点 */
   /* 操作结果: 若e是非根结点,则返回它的双亲,否则返回＂空＂ */

	ListQueue Q;
	Q.InitListQueue();
	if(pRoot!=NULL)
	{
		pBTNode pBTNodeNew;

		Q.EnListQueue(pRoot);

		while(!Q.ListQueueIsEmpty())
		{
			Q.DeListQueue(pBTNodeNew);

			if((pBTNodeNew->pLNext!=NULL&&pBTNodeNew->pLNext->Data==e)||(pBTNodeNew->pRNext!=NULL&&pBTNodeNew->pRNext->Data==e))
			{/* 找到e(是其左或右孩子) *//* 返回e的双亲的值 */
				Q.DestroyListQueue();
				return pBTNodeNew->Data;
			}
			else/* 没找到e,则入队其左右孩子指针(如果非空) */
			{
				if(pBTNodeNew->pLNext!=NULL)
				{
					Q.EnListQueue(pBTNodeNew->pLNext);
				}
				if(pBTNodeNew->pRNext!=NULL)
				{
					Q.EnListQueue(pBTNodeNew->pRNext);
				}
			}
		}
	}
	Q.DestroyListQueue();
	return Nil;/* 树空或没找到e */

	
}

pBTNode GetPoint(pBTNode pRoot,TElemType s)
{/* 返回二叉树指向元素值为s的结点的指针。另加 */

	ListQueue Q;
	Q.InitListQueue();
	if(pRoot!=NULL)
	{
		pBTNode pBTNodeNew;

		Q.EnListQueue(pRoot);

		while(!Q.ListQueueIsEmpty())
		{
			Q.DeListQueue(pBTNodeNew);

			if(pBTNodeNew->Data==s)
			{/* 找到e(是其左或右孩子) *//* 返回e的双亲的值 */
				Q.DestroyListQueue();
				return pBTNodeNew;
			}
			/* 没找到e,则入队其左右孩子指针(如果非空) */
			
			if(pBTNodeNew->pLNext!=NULL)
			{
				Q.EnListQueue(pBTNodeNew->pLNext);
			}

			if(pBTNodeNew->pRNext=NULL)
			{
				Q.EnListQueue(pBTNodeNew->pRNext);
			}
			
		}
	}
	Q.DestroyListQueue();
	return NULL;/* 树空或没找到e */

	
}

TElemType GetLeft(pBTNode pRoot,TElemType e)
{
	pBTNode pBTNodeCur = NULL ;

	if(pRoot!=NULL)//非空树
	{
		pBTNodeCur = GetPoint(pRoot,e);

		if(pBTNodeCur !=NULL && pBTNodeCur->pLNext!=NULL)
		{
			return pBTNodeCur ->pLNext->Data;
		}
	}

	return Nil;
}

TElemType GetRight(pBTNode pRoot,TElemType e)
{
	pBTNode pBTNodeCur = NULL ;

	if(pRoot!=NULL)//非空树
	{
		pBTNodeCur = GetPoint(pRoot,e);

		if(pBTNodeCur !=NULL && pBTNodeCur->pRNext!=NULL)
		{
			return pBTNodeCur ->pRNext->Data;
		}
	}

	return Nil;
}

TElemType GetLeftSibling(pBTNode pRoot,TElemType e)
{
	TElemType TParent;
	pBTNode  pBTNodeNew = NULL;
	
	if(pRoot!=NULL)
	{
		TParent = GetParent(pRoot,e);

		pBTNodeNew = GetPoint(pRoot,TParent);

		if(pBTNodeNew!=NULL&& pBTNodeNew->pLNext!=NULL &&pBTNodeNew->pRNext!=NULL && pBTNodeNew->pRNext->Data == e)
		{
			return pBTNodeNew->pLNext ->Data;
		}
	}

	return Nil;
}


TElemType GetRightSibling(pBTNode pRoot,TElemType e)
{
	TElemType TParent;
	pBTNode  pBTNodeNew = NULL;
	
	if(pRoot!=NULL)
	{
		TParent = GetParent(pRoot,e);

		pBTNodeNew = GetPoint(pRoot,TParent);

		if(pBTNodeNew!=NULL &&pBTNodeNew->pLNext!=NULL &&pBTNodeNew->pRNext!=NULL && pBTNodeNew->pLNext->Data == e)
		{
			return pBTNodeNew->pRNext ->Data;
		}
	}

	return Nil;
}

void InsertChild(pBTNode pBTNodeTemp,bool LR,pBTNode pRootNew)
{
	/* 初始条件: 二叉树存在,p指向某个结点,LR为0或1,非空二叉树c与T */
   /*           不相交且右子树为空 */
   /* 操作结果: 根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点的 */
   /*           原有左或右子树则成为c的右子树 */
	if(pBTNodeTemp!=NULL)
	{
		if(LR==0)
		{
			pRootNew->pRNext = pBTNodeTemp->pLNext;

			pBTNodeTemp->pLNext = pRootNew;
		}

		else//LR ==1
		{
			pRootNew ->pRNext = pBTNodeTemp->pRNext;

			pBTNodeTemp->pRNext = pRootNew;
		}
	}
}



void DelChild(pBTNode pBTNodeTemp, bool LR)
{ /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1 */
   /* 操作结果: 根据LR为0或1,删除T中p所指结点的左或右子树 */
	if(pBTNodeTemp!=NULL)
	{
		if(LR==0)
		{
			DestroyBiTree(pBTNodeTemp->pLNext);
		}

		else
		{
			DestroyBiTree(pBTNodeTemp->pRNext);
		}
	}
}


void LevelOrderTraverse(pBTNode pRoot)
{
	if (pRoot!=NULL)
	{
		ListQueue Q;
		Q.InitListQueue();

		pBTNode pBTNodeNew = NULL;

		Q.EnListQueue(pRoot);

		while(!Q.ListQueueIsEmpty())
		{
			Q.DeListQueue(pBTNodeNew);

			cout<<pBTNodeNew->Data<<" ";

			if(pBTNodeNew->pLNext!=NULL)
			{
				Q.EnListQueue(pBTNodeNew->pLNext);
			}

			if(pBTNodeNew->pRNext!=NULL)
			{
				Q.EnListQueue(pBTNodeNew->pRNext);
			}
		}

		Q.DestroyListQueue();
	}
}


// 构建主树
// 123##4##56##7##
// 主树前序遍历1 2 3 4 5 6 7
// 主树中序遍历3 2 4 1 6 5 7
// 主树后序遍历3 4 2 6 7 5 1
// 层次1 2 5 3 4 6 7
// 主树的深度3
// 
// 
// 主树前序遍历1 2 3 4 5 6 7
// 主树中序遍历3 2 4 1 6 5 7
// 主树后序遍历3 4 2 6 7 5 1
// 层次1 2 5 3 4 6 7
// 请按任意键继续. . .