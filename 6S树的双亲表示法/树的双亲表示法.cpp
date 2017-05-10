// 树与森林的转换
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Queue.h"



typedef struct _BITREENODE_ 
{
	int a;
	int iParent;
}BiTreeNode,*pBiTreeNode;

typedef struct _DATA_ 
{
	BiTreeNode BiTreeNodeArray[MAX];
	int iCount;
}Data,*pData;





int GetRoot(Data DataTemp);
bool InitTree(pData pDataTemp);
bool TreeEmpty(pData pDataTemp);
int TreeDepth(pData pDataTemp);
bool CreateTree(pData pDataTemp);
int GetValue(Data DataTemp,int i);
int GetLeft(Data DataTemp,int e);
int GetRightSibling(Data DataTemp,int e);
void TravelTree(Data DataTemp);
bool Swap(int &a, int &b);
bool Swap(BiTreeNode& a, BiTreeNode& b);

/* 初始条件: 树T存在,p是T中某个结点,1≤i≤p所指结点的度 */
   /* 操作结果: 删除T中结点p的第i棵子树 */
bool DelChild(pData pDataTemp,int p,int e);


/* 初始条件: 树T存在,p是T中某个结点,1≤i≤p所指结点的度+1,非空树c与T不相交 */
/* 操作结果: 插入c为T中p结点的第i棵子树 */
bool InsertChild(pData pDataTemp,int p,int e,Data DataNew);


bool Assign(pData pDataTemp,int iCur,int iValue);

int iDeleted[MAX] = {0};  // DelChild 中用到

int main()
{
	Data DataTemp;

	Data DataNew;

	int iIndex = 0;


	InitTree(&DataTemp);

	InitTree(&DataNew);

	printf("Input Root\n");
	CreateTree(&DataTemp);
	TravelTree(DataTemp);

// 	printf("Node Count: %d\n",DataTemp.iCount);
// 
// 	printf("Tree Depth:%d\n",TreeDepth(&DataTemp));
// 
// 	printf("Tree Root:%c\n",GetRoot(DataTemp));

//	printf("Input Index To Get Value\n");
//	scanf("%d",&iIndex);
//	printf("Value:%c\n",GetValue(DataTemp,iIndex-1));


//	printf("Input Father To Get Left\n");
//	scanf(" %c",&iIndex);
//	printf("Left Value:%c\n",GetLeft(DataTemp,iIndex));


//	printf("Input Left Son To Get Right\n");
//	scanf(" %c",&iIndex);
//	printf("Right Value:%c\n",GetRightSibling(DataTemp,iIndex));


		printf("Input New Tree Root\n");
  	CreateTree(&DataNew);
		printf("插入第几个孩子\n");
		scanf("%d",&iIndex);
	  InsertChild(&DataTemp,'2',iIndex,DataNew);
  	TravelTree(DataTemp);

//	printf("Del\n");


//	DelChild(&DataTemp,'1',3);

//	TravelTree(DataTemp);

  	return 0;

}

bool InitTree(pData pDataTemp)
{
	pDataTemp->iCount = 0;

	int i = 0;
	for (i=0;i<MAX;i++)
	{
		pDataTemp->BiTreeNodeArray[i].a = 0;
		pDataTemp->BiTreeNodeArray[i].iParent = -1;

	}

	return true;
}

bool CreateTree(pData pDataTemp)
{
	Queue QueueTemp;

	InitQueue(&QueueTemp);


	char Array[MAX] = {0};

	int i = 1;

	QueueData ParentTemp = {0};

	QueueData ChildTemp = {0};

	scanf(" %c",&pDataTemp->BiTreeNodeArray[0].a);  //输入我们的Root


	if (pDataTemp->BiTreeNodeArray[0].a!=0)
	{
		pDataTemp->BiTreeNodeArray[0].iParent = -1;

		ParentTemp.a = pDataTemp->BiTreeNodeArray[0].a;

		ParentTemp.iIndex = 0;

		EnQueue(&QueueTemp,ParentTemp);


		while (i<MAX&&!QueueEmpty(&QueueTemp))
		{
			DeQueue(&QueueTemp,&ParentTemp);


			printf("按照长序输入节点%c的所有Child:  '#' break\n",ParentTemp.a);


			scanf("%s",Array);

			if (Array[0]!='#')
			{
				int iLen = strlen(Array);
				
				for (int j=0;j<iLen;j++)
				{
					pDataTemp->BiTreeNodeArray[i].a = Array[j];
					
					pDataTemp->BiTreeNodeArray[i].iParent = ParentTemp.iIndex;
					
					
					ChildTemp.a = Array[j];
					
					
					ChildTemp.iIndex = i;
					
					
					EnQueue(&QueueTemp,ChildTemp);	
					i++;
					
				}
			}
		
		}


		if (i>MAX)
		{
			printf("Overflow\n");

			return false;
		}

		else
		{
			pDataTemp->iCount = i;
		}
	}

	DestroyQueue(&QueueTemp);


	return true;
}


bool TreeEmpty(pData pDataTemp)
{
	if (pDataTemp->iCount)
	{
		return false;
	}

	else
	{
		return true;
	}
}


bool Assign(pData pDataTemp,int iCur,int iValue)
{
	int j = 0;

	for (j=0;j<(*pDataTemp).iCount;j++)
	{
		if ((*pDataTemp).BiTreeNodeArray[j].a==iCur)
		{
			(*pDataTemp).BiTreeNodeArray[j].a = iValue;
			
			return true;
		}
	}
	
	
	return false;
}

int TreeDepth(pData pDataTemp) // 这是一个树  而且是线性树 因为不存在链性树
{

	int i = 0;
	int iDepth = 0;

	int iMaxDepth = 0;
	int e = 0;
	for (i=0;i<pDataTemp->iCount;i++)
	{

		iDepth = 1;

		e = pDataTemp->BiTreeNodeArray[i].iParent;

		while (e!=-1)
		{
			e = pDataTemp->BiTreeNodeArray[e].iParent;

			iDepth++;
		}

		if (iMaxDepth<iDepth)
		{
			iMaxDepth = iDepth;
		}
	}
	return iMaxDepth;
}



int GetRoot(Data DataTemp)
{
		int i = 0;//直接返回 DataTemp.BireeNodeArray[0].a
		
		// 	for (i=0;i<DataTemp.iCount;i++)
		// 	{
		// 		if (DataTemp.BiTreeNodeArray[i].iParent<0)
		// 		{
		// 			return DataTemp.BiTreeNodeArray[i].a;
		// 		}
		// 	}
		
		if (DataTemp.BiTreeNodeArray[0].iParent==-1)
		{
				return DataTemp.BiTreeNodeArray[0].a;
		}


	return 0;
}


int GetValue(Data DataTemp,int i)
{
	if (i<DataTemp.iCount)
	{
		return DataTemp.BiTreeNodeArray[i].a;
	}

	return '#';
	
}


int GetLeft(Data DataTemp,int e)
{
	int i = 0;

	int j = 0;
	for (i=0;i<DataTemp.iCount;i++)
	{
		if (DataTemp.BiTreeNodeArray[i].a==e)
		{

			break;
		}
	}

	for (j=i+1;j<DataTemp.iCount;j++)
	{
		if (DataTemp.BiTreeNodeArray[j].iParent==i)
		{
			return DataTemp.BiTreeNodeArray[j].a;
		}
	}

	return 0;
}

int GetRightSibling(Data DataTemp,int e)
{
	int i = 0;

	for (i=0;i<DataTemp.iCount;i++)
	{
		if (DataTemp.BiTreeNodeArray[i].a==e)
		{
			break;
		}
	}

	if (DataTemp.BiTreeNodeArray[i+1].iParent==DataTemp.BiTreeNodeArray[i].iParent)
	{
		return DataTemp.BiTreeNodeArray[i+1].a;
	}

	return 0;
}


void TravelTree(Data DataTemp)
{
	int i = 0;
	for (i=0;i<DataTemp.iCount;i++)
	{


		printf("节点 %c",DataTemp.BiTreeNodeArray[i].a);

		if (DataTemp.BiTreeNodeArray[i].iParent>=0)
		{
			printf("        双亲 %c",DataTemp.BiTreeNodeArray[DataTemp.BiTreeNodeArray[i].iParent]);
		}


		printf("\n");
	}
}


bool InsertChild(pData pDataTemp,int p,int e,Data DataNew)
{

		// 遇到的问题：  比如 1的孩子是23 ，2的孩子是456 ，3没有孩子 插入2的第一个孩子  DataNew 为9 无子树 那么结果显示为在
//线性内存中 9插入到了 3的 前面 这是不对的   (我的代码已经解决)
		// 下面是哥抄的严蔚敏的代码 结果他只讲了插入的是第一个孩子的情况 下面的情况不说了 不负责任
		// 于是 代码不要  自己做
		/*
	int j = 0;

	int n = 0;

	int l = 0;

	int k = 0;

	bool bOk = true;
	
	if (!TreeEmpty(pDataTemp))
	{
		for (j=0;j<pDataTemp->iCount;j++)
		{
			if (pDataTemp->BiTreeNodeArray[j].a==p)
			{
				break;
			}
		}
		l = j + 1;   //第一棵子树  

		//如果 DataNew 不是p的第一棵子树

		if(e>1)
		{
			k = j+1;
			for (k=j+1;k<pDataTemp->iCount;k++)
			{

				if (pDataTemp->BiTreeNodeArray[k].iParent==j)
				{
					n++;

					if (n==e-1) 
					{
						break;
					}
				}
			}

			l = k+1;		
		}

		//向后移动我们的成员

		if (l<pDataTemp->iCount)
		{
			for (k=pDataTemp->iCount-1;k>=l;k--)
			{
				pDataTemp->BiTreeNodeArray[k+DataNew.iCount] = pDataTemp->BiTreeNodeArray[k];


				if (pDataTemp->BiTreeNodeArray[k].iParent>=l)
				{
					pDataTemp->BiTreeNodeArray[k+DataNew.iCount].iParent += DataNew.iCount;
				}
			}
		}


		//将新树插入

		for (k=0;k<DataNew.iCount;k++)
		{
			pDataTemp->BiTreeNodeArray[l+k].a = DataNew.BiTreeNodeArray[k].a;

			pDataTemp->BiTreeNodeArray[l+k].iParent = DataNew.BiTreeNodeArray[k].iParent+l;
		}


		pDataTemp->BiTreeNodeArray[l].iParent = j; // 其实在上面的for中我们已经赋值了 但总归是要赋回去的
																								//  绝对不能省略

		pDataTemp->iCount+=DataNew.iCount;
	

		return true;


	}

	else
	{
		return false;
	}

	*/


	int j = 0;

	int l = 0;

	int k = 0;

	int n = 0;
	
	if (!TreeEmpty(pDataTemp))
	{
		for (j=0;j<pDataTemp->iCount;j++)
		{
			if (pDataTemp->BiTreeNodeArray[j].a==p)		// j 是父节点的索引
			{
				break;
			}
		}
		
			for (l=j+1;l<pDataTemp->iCount;++l)
			{

				if (pDataTemp->BiTreeNodeArray[l].iParent==j)		// l 是孩子的索引
				{
					++n;

					if (n==e)
					{
						break;
					}
				}
			}


		//向后移动我们的成员

		if (l<pDataTemp->iCount)
		{
			for (k=pDataTemp->iCount-1;k>=l;k--)
			{
				pDataTemp->BiTreeNodeArray[k+DataNew.iCount] = pDataTemp->BiTreeNodeArray[k];


				if (pDataTemp->BiTreeNodeArray[k].iParent>=l)// 父亲的索引也在改变  所以要重新赋值
				{
					pDataTemp->BiTreeNodeArray[k+DataNew.iCount].iParent += DataNew.iCount;
				}
			}
		}


		//将新树插入

		for (k=0;k<DataNew.iCount;k++)
		{
			pDataTemp->BiTreeNodeArray[l+k].a = DataNew.BiTreeNodeArray[k].a;

			pDataTemp->BiTreeNodeArray[l+k].iParent = DataNew.BiTreeNodeArray[k].iParent+l;
		}


		pDataTemp->BiTreeNodeArray[l].iParent = j;

		pDataTemp->iCount+=DataNew.iCount;


		//////////////////////////////////////////////////////////////////////////
		//我自己增加一个函数改变结点位置 使结点层序排列

		int nFlag = 1;
		while(nFlag)
		{
				nFlag = 0;
				for (j =1;j<pDataTemp->iCount-1;j++)
				{
						if (pDataTemp->BiTreeNodeArray[j].iParent>pDataTemp->BiTreeNodeArray[j+1].iParent)
								
						{

								Swap(pDataTemp->BiTreeNodeArray[j],pDataTemp->BiTreeNodeArray[j+1]);
								
								nFlag = 1;
								
								for (k = j;k<pDataTemp->iCount;k++)
								{
										if (pDataTemp->BiTreeNodeArray[k].iParent==j) // 当我们交换两个数之后  他们后边的孩子的双亲的索引也要改变
										{
												pDataTemp->BiTreeNodeArray[k].iParent++;
										}
										
										else if (pDataTemp->BiTreeNodeArray[k].iParent==j+1)
										{
												pDataTemp->BiTreeNodeArray[k].iParent--;
										}
								}
								
						}
				}
		}
		
	

		return true;


	}

	else
	{
		return false;
	}

}// InsertChild


bool DelChild(pData pDataTemp,int p,int e)
{
		if (TreeEmpty(pDataTemp))
		{
				return false;
		}
	Queue QueueTemp;

	InitQueue(&QueueTemp);


	QueueData Family = {0};

	QueueData Family1 = {0};


	int j = 0;
	int k = 0;
	int n = 0;
	for (j=0;j<pDataTemp->iCount;j++)
	{
		if (pDataTemp->BiTreeNodeArray[j].a==p)
		{
			break;
		}
	}


	for (k=j+1;k<pDataTemp->iCount;k++)   //找子树
	{
		if (pDataTemp->BiTreeNodeArray[k].iParent==j)
		{
				n++;	
				if (n==e)
				{
						break;
				}
		}

	
	}// k  为  要删除的 p 的子树的索引 (iIndex)

	if (k<pDataTemp->iCount)
	{
		n = 0;

		Family.iIndex = k;


		iDeleted[k] = 1;


		n++;


		EnQueue(&QueueTemp,Family);

		while (!QueueEmpty(&QueueTemp))
		{
			DeQueue(&QueueTemp,&Family1);
			for (j=Family1.iIndex+1;j<pDataTemp->iCount;j++)
			{
				if (pDataTemp->BiTreeNodeArray[j].iParent==Family1.iIndex) //  我们先找到我们要删除哪个节点 置一个要删除的标志
				{
					Family.iIndex = j;

					iDeleted[j] = 1;

					n++;

					EnQueue(&QueueTemp,Family);
				}
			}
		}


		for (j=0;j<pDataTemp->iCount;j++)
		{
			if (iDeleted[j]==1)
			{
				for (k=j+1;k<=pDataTemp->iCount;k++)
				{
					iDeleted[k-1] = iDeleted[k];

					pDataTemp->BiTreeNodeArray[k-1] = pDataTemp->BiTreeNodeArray[k];


					if((pDataTemp->BiTreeNodeArray[k].iParent)>j)
					{
					   --pDataTemp->BiTreeNodeArray[k-1].iParent;
					}

				}

				j--;
			}
		
		}

		pDataTemp->iCount -= n;
	}

	DestroyQueue(&QueueTemp);

	return true;
}// DelChild
bool Swap(int &a, int &b)
{
		if (&a==&b)
		{
				return false;
		}
		a ^= b ^= a ^= b;

		return true;
}// Swap int

bool Swap(BiTreeNode& a, BiTreeNode& b)
{

		BiTreeNode c = a;
		a = b;
		b = c;

		return true;
}// Swap BiTreeNode