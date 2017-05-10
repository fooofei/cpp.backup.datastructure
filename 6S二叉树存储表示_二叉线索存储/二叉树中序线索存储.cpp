// 称为循环树  主要用在动态查找
#include <STDIO.H>
#include <WINDOWS.H>

typedef enum{LINK,THREAD}PointerTag; // LINK 代表人家本来就有孩子 THREAD 表示没有左右孩子等待被线索


typedef struct _BiTreeNode_
{
	int iData;
	_BiTreeNode_* pLeft;
	_BiTreeNode_* pRight;
	PointerTag RTag;
	PointerTag LTag;
}BiTreeNode,*pBiTreeNode,**ppBiTreeNode;



bool CreateBiTree(ppBiTreeNode T);

void InThreading(pBiTreeNode p);

bool InOrderThreading(ppBiTreeNode Thrt,pBiTreeNode T);

bool InOrderTravelThrPost(pBiTreeNode T);  // 这是严蔚敏中带的遍历 方法 是通过后继

bool InOrderTravelThrPre(pBiTreeNode T);// 中序遍历线索二叉树，通过前驱(我自己加上)

pBiTreeNode InOrderNext(pBiTreeNode T);// 我自己加的 查找后继

pBiTreeNode InOrderPre(pBiTreeNode T); // 查找前驱

pBiTreeNode g_pPre = NULL;

int main()
{
	pBiTreeNode H,T;

	CreateBiTree(&T);

	InOrderThreading(&H,T);

	printf("中序遍历(输出)二叉线索树(后继 ):\n");
	InOrderTravelThrPost(H); /* 中序遍历(输出)二叉线索树 */
	printf("\n");

	printf("%d ",H->pRight->iData);
  
	printf("\n");
}


bool CreateBiTree(ppBiTreeNode T)
{
	int iValue = 0;

	scanf("%d",&iValue);


	if (iValue==-1)
	{
		*T = NULL;
	}

	else
	{
			if (NULL==(*T = (pBiTreeNode)malloc(sizeof(BiTreeNode))))
			{
					return false;
			}
			
			memset(*T,0,sizeof(BiTreeNode));
			(*T)->iData = iValue;
			
		//	(*T)->LTag = LINK;  // 因为 Link 就是 0  我们初始化的就是0 所以不用赋值 不信就看内存
		//	(*T)->RTag = LINK;
			CreateBiTree(&(*T)->pLeft);
			
			// 	if ((*T)->pLeft)
			// 	{
			// 		(*T)->LTag = LINK;
			// 	}
			
			CreateBiTree(&(*T)->pRight);
			
			// 	if ((*T)->pRight)
			// 	{
			// 		(*T)->RTag = LINK;
			// 	}
			
	}
	
	return true;
}// CreateBiTree



void InThreading(pBiTreeNode p)
{
	if (NULL != p)
	{

		InThreading(p->pLeft); 
		
		if (!p->pLeft) // 为空才进去 
		{
			p->LTag = THREAD;

			p->pLeft = g_pPre;
		}

		if (!g_pPre->pRight)
		{
			g_pPre->RTag = THREAD;

			g_pPre->pRight = p;
		}

		g_pPre = p;

		InThreading(p->pRight);
	}
}// InThreading

										// 是最上边的空结点
bool InOrderThreading(ppBiTreeNode Thrt,pBiTreeNode T)
{
	if (NULL==(*Thrt = (pBiTreeNode)malloc(sizeof(BiTreeNode))))
	{
		return false;
	}
	// 新加的节点（头节点），树中没有这个点 
	// 中序线索化出的链表的第一个节点的前驱（左孩子指针）指向这个 头节点， 
	// 同时链表最后一个节点的后继（右孩子指针）也指向这个 头结点， 
  // 而这个 头结点的 左孩子指针 指向二叉树的根节点，右孩子指针 指向中序线索化链表的最后一个节点 
	memset(*Thrt,0,sizeof(BiTreeNode));
	(*Thrt)->LTag = LINK;

	(*Thrt)->RTag = THREAD; // 把自己放进去了

	(*Thrt)->pRight = *Thrt;   //右指针回指 

	if (NULL == T) // 树空 
	{
		(*Thrt)->pLeft = *Thrt;

		return false;
	}


		(*Thrt)->pLeft = T;

		g_pPre = *Thrt;

		InThreading(T);

		g_pPre->pRight = *Thrt;

		g_pPre->RTag = THREAD; //最后一个结点线索化

		(*Thrt)->pRight = g_pPre;

		return true;

}// InOrderThreading


bool InOrderTravelThrPost(pBiTreeNode T) // 中序遍历线索二叉树，通过后继
{
	pBiTreeNode p = T->pLeft;;

	// ReadMe 
// 	要在中序线索二叉树上查找结点*p的中序后继结点，要分两种情况：
// 	① 若结点*p的rtag域值为1，则表明p->rchild为右线索，它直接指向结点*p的中序后继结点；
// 　② 若结点*p的rtag域值为0，则表明p->rchild指向右孩子结点，结点*p的中序后继结点必
// 		是其右子树第一个中序遍历到的结点，因此从结点*p的右孩子开始，沿左指针链向下查找，
// 		直到找到一个没有左孩子(即ltag为1)的结点为止,该结点是结点*p的右子树中"最左下"的结点，它就是结点*p的中序后继结点。
	while (p!=T)
	{
		while (p->LTag==LINK) // 严重注意 这顺序不能反过来
		{
				p = p->pLeft;
		}
			
		printf("%d ",p->iData);

		while(p->RTag==THREAD&&p->pRight!=T)
		{
			p = p->pRight;

			printf("%d ",p->iData);
		}

		p = p->pRight;
	}


	return true;
}// InOrderTravelThrPost

bool InOrderTravelThrPre(pBiTreeNode T)// 中序遍历线索二叉树，通过前驱 (课外补充) 
{// 打印顺序刚好跟上面的后继方法相反   因为是前驱

		pBiTreeNode p = T->pLeft;

		while (p!=T)
		{
				while (p->RTag==LINK)
				{
						p = p->pRight;
				}

				printf("%d ",p->iData);

				while (p->LTag==THREAD && p->pLeft !=T)
				{
						p = p->pLeft;
						printf("%d ",p->iData);
				}

				p = p->pLeft;
		}
		return true;
}// InOrderTravelThrPre


// 线索二叉树是用来 查找前驱和后继的 
pBiTreeNode InOrderNext(pBiTreeNode T)
{
		if (T==NULL)
		{
				return NULL;
		}
		if (T->RTag==THREAD)
		{
				return T->pRight;
		}

		// 未被线索化

		pBiTreeNode p = T->pRight;

		while(p->LTag==LINK)
		{
				p = p->pLeft;
		}

		return p;
}// InOrderNext

pBiTreeNode InOrderPre(pBiTreeNode T)
{
		if (T==NULL)
		{
				return NULL;
		}

		if (T->LTag==THREAD)
		{
				return T->pLeft;
		}

		pBiTreeNode p = T->pLeft;

		while(p->RTag==LINK)
		{
				p = p->pRight;
		}

		return p;
}// InOrderPre



// 1
// 2
// 3
// -1
// -1
// 4
// -1
// -1
// 5
// 6
// -1
// -1
// 7
// -1
// -1
// 中序遍历(输出)二叉线索树(后继 ):
// 3 2 4 1 6 5 7
// 7
// Press any key to continue