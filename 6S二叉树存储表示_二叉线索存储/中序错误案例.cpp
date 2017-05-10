// Error
// 我误以为是双向循环链表  特此记录我的错误
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

bool InOrderTravel(pBiTreeNode T);

pBiTreeNode g_pPre = NULL;

int main()
{
	pBiTreeNode H,T;

	CreateBiTree(&T);

	InOrderThreading(&H,T);

	printf("中序遍历(输出)二叉线索树:\n");
	InOrderTravel(H); /* 中序遍历(输出)二叉线索树 */
  
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
}



void InThreading(pBiTreeNode p)
{
	if (p)
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
}

										// 是最上边的空结点
bool InOrderThreading(ppBiTreeNode Thrt,pBiTreeNode T)
{
	if (NULL==(*Thrt = (pBiTreeNode)malloc(sizeof(BiTreeNode))))
	{
		return false;
	}
	memset(*Thrt,0,sizeof(BiTreeNode));
	(*Thrt)->LTag = LINK;

	(*Thrt)->RTag = THREAD; // 把自己放进去了

	(*Thrt)->pRight = *Thrt;   //右指针回指 

	if (!T) // 树空 
	{
		(*Thrt)->pLeft = *Thrt;

		return false;
	}

		(*Thrt)->pLeft = T;

		g_pPre = *Thrt;

		InThreading(T);

		g_pPre->pRight = *Thrt;

		g_pPre->RTag = THREAD; //最后一个结点线索化

	//	(*Thrt)->pRight = g_pPre; // 做更改 更改为双向循环链表

		pBiTreeNode pTemp = (*Thrt)->pLeft;

		while (pTemp->pLeft!=(*Thrt))
		{
				pTemp = pTemp->pLeft;
		}

		(*Thrt)->pRight  = pTemp;
		return true;

		// 并不是双向循环链表  错误案例
		
// 						1
// 								5
// 							6   
}


bool InOrderTravel(pBiTreeNode T)
{
	pBiTreeNode p = T->pRight;

	while (p!=T)
	{
			printf("%d ",p->iData);

			p = p->pRight;
	}
	return true;
}