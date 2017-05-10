//这是一个解释：二叉树的打印是没有按照输入的次序的  为了有次序 就与 队列  栈 相结合 实现有序打印 
//也可这样理解  用栈 打印 跟不用栈打印是一样的   这个程序就是这个意思 
#include <iostream>
using namespace std;


typedef struct _BTNODE_
{
	char c;
	_BTNODE_*pLNext;
	_BTNODE_*pRNext;

}BTNode,*pBTNode;

typedef struct  _STACKNODE_ 
{
	BTNode NodeTemp;  //这里没有定义 pBTNode pBTNodeTemp 的好处就是 当我们使用了栈的中序遍历 我们还可以使用后序遍历      
						//	假如使用pBTNode pBTNodeTemp 之后  我们就无法使用其他的遍历了 因为遍历的时候会改变节点的孩子
	_STACKNODE_* pNext;
}StackNode,*pStackNode;

void CreateBinNode(pBTNode& pBinNew);

void PopStack(BTNode &NodeTemp);
void PushStack(BTNode NodeTemp);
void FreeBTNode(pBTNode &pTemp);


void PreTravel(pBTNode pTemp);
void PrePrint(pBTNode pNodeTemp);

void ProPrint(pBTNode pNodeNew);
void PosTravel(pBTNode pNodeNew);


void MidTravel(pBTNode pNodeNew);
void MidPrint(pBTNode pNodeNew);
pStackNode pHead = NULL;


int main()
{
	pBTNode pRoot = NULL;
	cout<<"请输入，构建二叉树"<<endl;
	CreateBinNode(pRoot);


	cout<<"二叉树递归前序遍历 ";
	PreTravel(pRoot);//遍历在前边 不然二叉树被破坏   无法遍历
	cout<<endl;
	cout<<"非递归链栈前序遍历 ";
	PrePrint(pRoot);
	cout<<endl;
	
	
	cout<<"二叉树递归中序遍历 ";
	MidTravel(pRoot);
	cout<<endl;
	cout<<"非递归链栈中序遍历 ";
	MidPrint(pRoot);
	cout<<endl;
	
	
	cout<<"二叉树递归后序遍历 ";
	PosTravel(pRoot);
	cout<<endl;
	cout<<"非递归链栈后序遍历 ";
	ProPrint(pRoot);
	cout<<endl;
	
	

	

	FreeBTNode(pRoot);

}




void  CreateBinNode(pBTNode& pBinNew)
{
	char a = 0;
	cin>>a;

	if (a=='#')
	{
		pBinNew =  NULL;
	}

	else
	{
		pBinNew = new BTNode;

		pBinNew->c = a;

		pBinNew->pLNext  =NULL;

		pBinNew ->pRNext = NULL;
		CreateBinNode(pBinNew->pLNext);
		CreateBinNode(pBinNew->pRNext);
		
	}
}

void FreeBTNode(pBTNode &pTemp)
{
// 	if (pTemp)
// 	{	
// 		if (pTemp->pLNext!=NULL&&pTemp->pRNext==NULL)
// 		{
// 			FreeBTNode(pTemp->pLNext);
// 		}
// 		if (pTemp->pLNext ==NULL&&pTemp->pRNext!= NULL)
// 		{
// 			FreeBTNode(pTemp->pRNext);
// 		}
// 		if (pTemp->pLNext!=NULL && pTemp->pRNext !=NULL)
// 		{
// 			FreeBTNode(pTemp->pLNext);
// 			FreeBTNode(pTemp->pRNext);
// 		}
// 		if (pTemp->pLNext ==NULL && pTemp->pRNext==NULL)
// 		{
// 			free(pTemp);
// 			
// 			pTemp = NULL;
// 		}
// 	}



	//更简洁的方法

	if (pTemp)
	{
		FreeBTNode(pTemp->pLNext);
		
		FreeBTNode(pTemp->pRNext);
	

		free(pTemp);

		pTemp = NULL;
	}
}


void PushStack(BTNode NodeTemp)
{
	pStackNode p = new StackNode ;
	
	p->NodeTemp = NodeTemp;
	
	p->pNext = NULL;
		
	p->pNext = pHead;
	
	pHead = p;
	
}

void PopStack(BTNode &NodeTemp)
{
	NodeTemp= pHead->NodeTemp;

	pStackNode p = pHead ;

	pHead = pHead->pNext ;

	delete p;
}


//栈 前序遍历
void PrePrint(pBTNode pNodeTemp)
{
	if (pNodeTemp!=NULL)
	{
		PushStack(*pNodeTemp);
	}

	

	BTNode NodeNew;
	while (pHead!=NULL)
	{
		PopStack(NodeNew);
		cout<<NodeNew.c<<" ";
		
		if (NodeNew.pRNext!=NULL)
		{
			
			PushStack(*(NodeNew.pRNext));
		
		}

		if (NodeNew.pLNext!=NULL)
		{
		
			PushStack(*(NodeNew.pLNext));
			
		}
	}
}
//二叉树前序
void PreTravel(pBTNode pTemp)
{
	if (pTemp!=NULL)
	{
		cout<<pTemp->c<<" ";
		PreTravel(pTemp->pLNext);
		PreTravel(pTemp->pRNext);
	}
}
//栈 中序  自己做的  真TMD  不容易
void MidPrint(pBTNode pNodeNew)
{
	if (pNodeNew!=NULL)
	{
		PushStack(*pNodeNew);
	}
	

	BTNode NodeTemp ;

	pBTNode pLNode = NULL;
	while(pHead!=NULL)
	{
		PopStack(NodeTemp);

		pLNode = NodeTemp.pLNext;
		if(pLNode==NULL)
		{
			cout<<NodeTemp.c<<" ";
		}
		else
		{
		
			NodeTemp.pLNext = NULL;

			if(NodeTemp.pRNext!=NULL)
			{
				PushStack(*(NodeTemp.pRNext));
			}
			PushStack(NodeTemp);

			PushStack(*(pLNode));
			
		}
	}
}
//二叉树中序
void MidTravel(pBTNode pNodeNew)
{
	if(pNodeNew!=NULL)
	{
		MidTravel(pNodeNew->pLNext);
		cout<<pNodeNew->c<<" ";

		MidTravel(pNodeNew ->pRNext);
	}
}

//栈 后序遍历
void ProPrint(pBTNode pNodeNew)
{
	if(pNodeNew!=NULL)
	{
		PushStack(*pNodeNew);
	}
	

	BTNode NodeTemp ;

	pBTNode pRNode ,pLNode;

	while(pHead!=NULL)
	{
		PopStack(NodeTemp);

		pRNode = NodeTemp.pRNext;
		pLNode = NodeTemp.pLNext;
		if(pRNode==NULL&&pLNode==NULL)
		{
			cout<<NodeTemp.c<<" ";
		}


		else
		{
			NodeTemp.pRNext = NULL;

			NodeTemp.pLNext = NULL;

			PushStack(NodeTemp);

		
			if(pRNode != NULL)
			{
				PushStack(*pRNode);
			}
			if(pLNode!=NULL)
			{
				PushStack(*pLNode);
			}
			
			
		
		}
	}
}

//二叉树后续

void PosTravel(pBTNode pNodeNew)
{
	if(pNodeNew != NULL)
	{
		PosTravel(pNodeNew->pLNext);

		PosTravel(pNodeNew->pRNext);

		cout<<pNodeNew->c<<" ";
	}
}



// 测试用例  123##4##56##7##
// 
// 请输入，构建二叉树
// 123##4##56##7##
// 二叉树递归前序遍历 1 2 3 4 5 6 7
// 非递归链栈前序遍历 1 2 3 4 5 6 7
// 二叉树递归中序遍历 3 2 4 1 6 5 7
// 非递归链栈中序遍历 3 2 4 1 6 5 7
// 二叉树递归后序遍历 3 4 2 6 7 5 1
// 非递归链栈后序遍历 3 4 2 6 7 5 1
// Press any key to continue