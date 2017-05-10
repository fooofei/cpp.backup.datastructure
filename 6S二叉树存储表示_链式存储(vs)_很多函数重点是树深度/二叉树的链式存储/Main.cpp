#include <iostream>
using namespace std;
#include "ListQueue.h"
#include "NodeType.h"

// �ص��ǵõ��������
// 21 ��  �Ӻ��� 
void  CreateBiTree(pBTNode &pRoot);
void DestroyBiTree(pBTNode &pRoot);
bool BiTreeIsEmpty(pBTNode pRoot);
int BiTreeDepth(pBTNode pRoot);
TElemType GetRoot (pBTNode pRoot);
TElemType GetValue(pBTNode p);
void Assign(pBTNode p,TElemType value);/* ��p��ָ��㸳ֵΪvalue */
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

// ���ڵڶ��������������⣬����ڵ��в�����ָ�򸸽ڵ��ָ��Ӧ����ô���㣿
// �㷨˼�룺���һ���ڵ������������p��q�е�һ���ڵ㣬������������һ�����������
// �����p��q������������ȡ�

int NearestCommonAncestor(pBTNode pRoot,pBTNode a, pBTNode b,pBTNode &pParent);

int main ()
{
	pBTNode pRoot = NULL; //����

	cout<<"��������"<<endl;
	CreateBiTree(pRoot);
	cout<<"����ǰ�����";
	PreOrderTraverse(pRoot);
	cout<<endl;
	cout<<"�����������";
	InOrderTraverse(pRoot);
	cout<<endl;
	cout<<"�����������";
	PosOrderTraverse(pRoot);
	cout<<endl;
	cout<<"���";
	LevelOrderTraverse(pRoot);
	cout<<endl;
 	cout<<"���������";
 	cout<<BiTreeDepth(pRoot)<<endl;

	cout<<endl;


	

//	cout<<GetLeftSibling(pRoot,'3')<<endl;

//	cout<<GetRightSibling(pRoot,'2')<<endl;




	cout<<endl;
	cout<<"����ǰ�����";
	PreOrderTraverse(pRoot);
	cout<<endl;
	cout<<"�����������";
	InOrderTraverse(pRoot);
	cout<<endl;
	cout<<"�����������";
	PosOrderTraverse(pRoot);
	cout<<endl;
	cout<<"���";
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
{/* ��ʼ����: ���������ڡ��������: ���ظ� */
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
{/* ��ʼ����: ������T���ڣ�pָ��T��ĳ����� */
	if(p!=NULL)
	{
		return p->Data;
	}

	return Nil;
	
}

void Assign(pBTNode p,TElemType value)
{/* ��p��ָ��㸳ֵΪvalue */
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
{/* ��ʼ����: ����������,e��ĳ����� */
   /* �������: ��e�ǷǸ����,�򷵻�����˫��,���򷵻أ��գ� */

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
			{/* �ҵ�e(��������Һ���) *//* ����e��˫�׵�ֵ */
				Q.DestroyListQueue();
				return pBTNodeNew->Data;
			}
			else/* û�ҵ�e,����������Һ���ָ��(����ǿ�) */
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
	return Nil;/* ���ջ�û�ҵ�e */

	
}

pBTNode GetPoint(pBTNode pRoot,TElemType s)
{/* ���ض�����ָ��Ԫ��ֵΪs�Ľ���ָ�롣��� */

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
			{/* �ҵ�e(��������Һ���) *//* ����e��˫�׵�ֵ */
				Q.DestroyListQueue();
				return pBTNodeNew;
			}
			/* û�ҵ�e,����������Һ���ָ��(����ǿ�) */
			
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
	return NULL;/* ���ջ�û�ҵ�e */

	
}

TElemType GetLeft(pBTNode pRoot,TElemType e)
{
	pBTNode pBTNodeCur = NULL ;

	if(pRoot!=NULL)//�ǿ���
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

	if(pRoot!=NULL)//�ǿ���
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
	/* ��ʼ����: ����������,pָ��ĳ�����,LRΪ0��1,�ǿն�����c��T */
   /*           ���ཻ��������Ϊ�� */
   /* �������: ����LRΪ0��1,����cΪT��p��ָ���������������p��ָ���� */
   /*           ԭ��������������Ϊc�������� */
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
{ /* ��ʼ����: ������T����,pָ��T��ĳ�����,LRΪ0��1 */
   /* �������: ����LRΪ0��1,ɾ��T��p��ָ������������� */
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


// ��������
// 123##4##56##7##
// ����ǰ�����1 2 3 4 5 6 7
// �����������3 2 4 1 6 5 7
// �����������3 4 2 6 7 5 1
// ���1 2 5 3 4 6 7
// ���������3
// 
// 
// ����ǰ�����1 2 3 4 5 6 7
// �����������3 2 4 1 6 5 7
// �����������3 4 2 6 7 5 1
// ���1 2 5 3 4 6 7
// �밴���������. . .