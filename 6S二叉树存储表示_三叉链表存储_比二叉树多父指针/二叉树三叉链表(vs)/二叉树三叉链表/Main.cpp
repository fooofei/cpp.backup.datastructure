#include <iostream>
using namespace std;
#include "ListQueue.h"
#include "NodeType.h"



// 20 个子函数

void  CreateBiTree(pBTNode &pRoot);
void Create(pBTNode &pRoot);//CreateBiTree 调用
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

void main()
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
// 
// 	pBTNode pBTNodeNew = NULL;
// 	cout<<"构建子树"<<endl;
// 	CreateBiTree(pBTNodeNew);
// 
// 	InsertChild(pRoot,1,pBTNodeNew);


	DelChild(pRoot,1);

	

//	cout<<GetLeftSibling(pRoot,'3')<<endl;

//	cout<<GetRightSibling(pRoot,'2')<<endl;

// 	cout<<GetRight(pRoot,'1')<<endl;
// 
// 	cout<<GetLeft(pRoot,'1')<<endl;
// 
// 	cout<<GetParent(pRoot,'2')<<endl;
// 
// 	cout<<GetLeft(pRoot,'3')<<endl;

	




	cout<<"经过一系列处理"<<endl;
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
}

void Create(pBTNode &pRoot)
{
	TElemType c = 0;
	cin>>c;

	if(c==Nil)
	{
		pRoot = NULL;
	}
	else
	{
		pRoot=  new BTNode ;

		pRoot->Data = c;

		CreateBiTree(pRoot->pLNext);

		CreateBiTree(pRoot->pRNext);
	}
}


void CreateBiTree(pBTNode &pRoot)
{
	ListQueue Q;

	Q.InitListQueue();

	pBTNode pBTNodeNew = NULL;


	Create(pRoot);

	if(pRoot!=NULL)
	{
		pRoot->pParent = NULL;

		Q.EnListQueue(pRoot);
		while(!Q.ListQueueIsEmpty())
		{
			Q.DeListQueue(pBTNodeNew);

			if(pBTNodeNew->pLNext!=NULL)
			{
				pBTNodeNew->pLNext->pParent = pBTNodeNew;
				Q.EnListQueue(pBTNodeNew->pLNext);
			}

			if(pBTNodeNew->pRNext!=NULL)
			{
				pBTNodeNew->pRNext->pParent = pBTNodeNew;
				Q.EnListQueue(pBTNodeNew->pRNext);
			}
		}
	}
	Q.DestroyListQueue();
}

void DestroyBiTree(pBTNode &pRoot)
{
	if(pRoot!=NULL)
	{
		DestroyBiTree(pRoot->pLNext);
		DestroyBiTree(pRoot->pRNext);

		delete pRoot;

		pRoot = NULL;
	}
}

bool BiTreeIsEmpty(pBTNode pRoot)
{
	if(pRoot == NULL)
	{
		return true;
	}
	
	return false;
}


int BiTreeDepth(pBTNode pRoot)
{
	int i = 0;
	int j = 0;

	if(pRoot == NULL)
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
	
	if(i<j)
	{
		return j+1;
	}
	else
	{
		return i+1;
	}
	
}

TElemType GetRoot(pBTNode pRoot)
{
	if(BiTreeIsEmpty(pRoot))
	{
		return Nil;
	}
	return pRoot->Data;
}

TElemType GetValue(pBTNode p)
{
	if(p!=NULL)
	{
		return p->Data;
	}
	return Nil;
}

void Assign(pBTNode p,TElemType value)
{
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

TElemType GetParent(pBTNode pRoot, TElemType e)
{
	pBTNode pBTNodeNew = NULL;

	if(pRoot!=NULL)
	{
		pBTNodeNew = GetPoint(pRoot,e);

		if(pBTNodeNew!=NULL&&pBTNodeNew!=pRoot)
		{
			return pBTNodeNew->pParent->Data;
		}
	}

	return Nil;
}

pBTNode GetPoint(pBTNode pRoot,TElemType s)
{
	ListQueue Q;
	Q.InitListQueue();
	if(pRoot!=NULL)
	{
		pBTNode pBTNodeNew = NULL;
		Q.EnListQueue(pRoot);
		while(!Q.ListQueueIsEmpty())
		{
			Q.DeListQueue(pBTNodeNew);

			if(pBTNodeNew->Data==s)
			{
				return pBTNodeNew;
			}
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

	Q.DestroyListQueue();
	return NULL;
}


TElemType GetLeft(pBTNode pRoot,TElemType e)
{
//得到左孩子
	pBTNode pBTNodeCur = NULL;

	if(pRoot!=NULL)
	{
		pBTNodeCur = GetPoint(pRoot,e);

		if(pBTNodeCur != NULL && pBTNodeCur ->pLNext!=NULL)
		{
			return pBTNodeCur->pLNext->Data;
		}
	}

	return Nil;
}


TElemType GetRight(pBTNode pRoot,TElemType e)
{
	pBTNode pBTNodeCur = NULL;

	if(pRoot!=NULL)
	{
		pBTNodeCur = GetPoint(pRoot,e);

		if(pRoot!=NULL && pRoot->pRNext!=NULL)
		{
			return pBTNodeCur->pRNext->Data;
		}
	}

	return Nil;
}

TElemType GetLeftSibling(pBTNode pRoot,TElemType e)
{
	pBTNode pBTNodeNew = NULL;

	if(pRoot!=NULL)
	{
		pBTNodeNew = GetPoint(pRoot,e);

		if(pBTNodeNew!=NULL&&pBTNodeNew!=pRoot&&pBTNodeNew->pParent->pLNext!=NULL)
		{
			return pBTNodeNew->pParent->pLNext->Data;
		}
	}

	return Nil;

}

TElemType GetRightSibling(pBTNode pRoot,TElemType e)
{
	pBTNode pBTNodeNew = NULL;

	if(pRoot!=NULL)
	{
		pBTNodeNew = GetPoint(pRoot,e);

		if(pBTNodeNew!=NULL && pBTNodeNew!=pRoot && pBTNodeNew->pParent->pRNext!=NULL)
		{
			return pBTNodeNew->pParent->pRNext->Data;
		}
	}

	return Nil;
}

void InsertChild(pBTNode pBTNodeTemp,bool LR,pBTNode pRootNew)
/* 初始条件: 二叉树存在,p指向某个结点,LR为0或1,非空二叉树c与T */
   /*           不相交且右子树为空 */
   /* 操作结果: 根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点的 */
   /*           原有左或右子树则成为c的右子树 */
{
	if(pBTNodeTemp!=NULL)
	{
		if(LR==0)
		{
			if(pBTNodeTemp->pLNext!=NULL)
			{
				pRootNew->pRNext = pBTNodeTemp->pLNext;

				pBTNodeTemp->pLNext->pParent = pRootNew;
			}
			

			pBTNodeTemp->pLNext = pRootNew;

			pRootNew->pParent = pBTNodeTemp;
		}

		if(LR==1)
		{
			if(pBTNodeTemp->pRNext!=NULL)
			{
				pRootNew->pRNext = pBTNodeTemp->pRNext;

			
				pBTNodeTemp->pRNext->pParent = pRootNew ;

			}
			
			pBTNodeTemp->pRNext = pRootNew;

			pRootNew->pParent = pBTNodeTemp;
		}
	}
}


void DelChild(pBTNode pBTNodeTemp,bool LR)
{
	if(pBTNodeTemp!= NULL)
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
		if(pRoot !=NULL)
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