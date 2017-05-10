#include <stdio.h>
#include <malloc.h>
#include <math.h>



//注意该程序用到二维指针，很难处理所以要小心，如果定义全局变量的话应该简单些。
#define  N  9
#define  LT(a,b) ((a)<(b))

//定义数据元素类型
typedef struct _ELEMENT_
{
	char KeyWord;
	int  i;

}Element,*pElement;


//静态查找表的顺序结构
typedef struct _SFTable_
{
	pElement pEle;//数据元素存储空间的基地址
    int nLength;  //表的长度

}SFTable,*pSFTable;

//树节点的结构体
typedef struct _NODE_
{
	Element Data;//节点中的数据
	_NODE_* pLeft;
	_NODE_* pRight; //左右两个孩子的指针

}Node,*pNode;

//函数声明
bool CreateSequance(pSFTable pSFT,int n);
void TravelSequance(SFTable SFT,void(*Function)(Element));
void Print(Element Ele);

void ElementSort(pSFTable pSFT);

//构造树的结构
void CreateTree(pNode *pTree,pSFTable pSFT);

void FindSW(int* Array,pSFTable pSFT);

void SecondOptimal(pNode *pTreeNode,pElement pEle,int* Array,int Low,int High);


//查找函数
bool SearchData(pNode *pTreeNode,char KeyWord);

//定义全局数组

Element g_Array[N] = {{'C',778},{'A',110},{'B',120},{'E',0},{'D',1},{'F',5},{'G',6},{'H',33},{'I',9}};

//定义一个一个全局的累计权值表
int g_sw[N+1];


int main()
{
	SFTable SFT;
    
	//定义一个节点的结构体
	pNode   pTreeNode = NULL;

	
	//创建一个含有n个数据元素的顺序查找表(数据来自全局数组)
	
	
	if (CreateSequance(&SFT,N))
	{
		//为了防止元素没有进行有效的排序我们还需要将全局数组中的数据进行按字符排序
		//如果全局数组中的数据是
		//Element g_Array[N] = {{'B',120},{'A',110},{'E',1},{'C',778},{'D',0},{'F',5},{'I',9},{'G',6},{'H',33}}
		//就要再次进行排序
		ElementSort(&SFT);


	}
	//打印函数

	TravelSequance(SFT,Print);

	printf("\n");


	//由有序表构建一个次优查找树

	CreateTree(&pTreeNode,&SFT);

	//查询函数

	printf("Input KeyWord\n");

	char KeyWord;

	scanf("%c",&KeyWord);
	bool i = SearchData(&pTreeNode,KeyWord);

	if (i==true)
	{
		printf("%c  is %d",KeyWord,pTreeNode->Data.i);

		printf("\n");
	}

	else
	{
		printf("No Found\n");
	}
		
}


bool CreateSequance(pSFTable pSFT,int n)
{
	//动态申请内存
	pSFT->pEle = (pElement)malloc(sizeof(Element)*10);

	if (pSFT->pEle==NULL)
	{
		return false;
	}

	//将全局数据中的数据拷贝到内存中并空出第一块内存

	int i = 1;
	for (i=1;i<=n;i++)
	{
		*(pSFT->pEle+i) = g_Array[i-1];   //因为结构体可以进行等号拷贝
	}

	pSFT->nLength = n;

	return true;

}

void TravelSequance(SFTable SFT,void(*Function)(Element))
{
	//定义一个数据类型的指针
	pElement pEle;

	pEle = ++SFT.pEle;

	int i = 1;
	for (i=1;i<=SFT.nLength;i++)
	{
		Function(*pEle);

		pEle++;
	}
}

void Print(Element Ele)
{
	printf("%c %d   ",Ele.KeyWord,Ele.i);
}

void ElementSort(pSFTable pSFT)
{
	//因为第一块内存是一个空值所以我们可以定义成那个交换的全局变量

	//我在这里就用一下选择排序
	int i;
	int j;
	int k;
	for (i=1;i<pSFT->nLength;i++)
	{
		k = i;
		//将要比较的那个值存入第一块内存块中
		pSFT->pEle[0] = pSFT->pEle[i];

		for (j = i+1;j<=pSFT->nLength;j++)
		{
			if (LT(pSFT->pEle[j].KeyWord,pSFT->pEle[0].KeyWord))
			{
				k = j;

				pSFT->pEle[0] = pSFT->pEle[j];
			}
		}

		if (k!=i)
		{
			pSFT->pEle[k] = pSFT->pEle[i];
			pSFT->pEle[i] = pSFT->pEle[0];
		}
		

	}
}

//构造树
void CreateTree(pNode *pTree,pSFTable pSFT)
{
	if (pSFT->nLength==0)
	{
		return;
	}

	else
	{
		//按照已经排好的有序表中的各个元素的值域求累计的权值表
		FindSW(g_sw,pSFT);

		SecondOptimal(&(*pTree),pSFT->pEle,g_sw,1,pSFT->nLength);

	}
}


void FindSW(int* Array,pSFTable pSFT)
{
     int i = 0;

	 //将数组的首元素预留出来
	 Array[0] = 0;
	 for (i=1;i<=pSFT->nLength;i++)
	 {
		 Array[i] = Array[i-1] + pSFT->pEle->i; 
	 }
}

void SecondOptimal(pNode *pTreeNode,pElement pEle,int* Array,int Low,int High)
{
	int i;
	int j;

	i = Low;
	int Min;  //选择最小值
	int dw;
	
	Min = abs(Array[High] - Array[Low]);
	dw  = Array[High] + Array[Low-1];

	//选择最小值然后根据该值申请节点构建树结构
	for (j=Low+1;j<=High;j++)
	{
		if (abs(dw-Array[j]-Array[j-1])<Min)
		{
			i = j;
			//改变Min值
			Min = abs(dw - Array[j] - Array[j-1]);
		}
	}


	//申请内存
	*pTreeNode = (pNode)malloc(sizeof(Node));

	if (*pTreeNode==NULL)
	{
		return;
	}

	//生成节点
	(*pTreeNode)->Data = pEle[i];

	//判断后进行递归
	if (i==Low)
	{
		(*pTreeNode)->pLeft = NULL;  //左节点就为空
	}

	else
	{
		SecondOptimal(&(*pTreeNode)->pLeft,pEle,Array,Low,i-1);
	}

	if (i==High)
	{
		(*pTreeNode)->pRight = NULL;  //右节点创建
	}

	else
	{
		SecondOptimal(&(*pTreeNode)->pRight, pEle,Array,i+1,High);
	}
	
}


bool SearchData(pNode *pTreeNode,char KeyWord)
{
	while (*pTreeNode)
	{
		if ((*pTreeNode)->Data.KeyWord==KeyWord)
		{
			return true;
		}
		else if ((*pTreeNode)->Data.KeyWord>KeyWord)
		{
			*pTreeNode = (*pTreeNode)->pLeft;
		}
		else
		{
			*pTreeNode = (*pTreeNode)->pRight;
		}
	}

	return false;
}