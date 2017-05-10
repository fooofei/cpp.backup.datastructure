#include <stdio.h>
#include <malloc.h>
#include <windows.h>

#define  MAX 1
#define  HASHMAX 10

//设置偏移量
#define  Offset(m,s)      (BYTE)(&((m*)0)->s)

//创建存值域的结构体
typedef struct _DATA_
{
	char Name[20];
	int Age;
}Data,*pData;


//定义一个全局偏移量

UINT g_offset = 0;

//创建哈希表链表中的节点结构体

typedef struct _HASHLISTNODE_
{
	_HASHLISTNODE_* pNext;
	pData  pDt;
	
}HashListNode,*pHashListNode,**ppHashListNode;


//创建哈希链表的结构体在哈希表中最重要的一个值域就是索引表因为这是一个指针数组所以我们要定义一个二维指针

typedef struct _HASHLIST_
{
	ppHashListNode ppBuckets;
	int            nBucketCount;    //索引表的个数
	int            nNodeCount;        //节点的个数
	
}HashList,*pHashList;




//重定义函数的指针
typedef int (*HASHLISTFUNC)(int Key,int nBacketCount);




typedef int (*DATACMPFUNC)(char* pData1,char* pData2);



int HashInt(int Key,int nBacketCount);
int DataCmp(char* pData1,char* pData2);

//创建一个哈希表
pHashList CreateHashList();

//连接哈希表
void InsertNodeToHashList(pHashList pHashTemp,HASHLISTFUNC HashListFunc,int key, pData pDaTemp);

//查找函数
pHashListNode FindDataFromHashList(pHashList pHashTemp,DATACMPFUNC DataCmpFunc,HASHLISTFUNC HashListFunc,char* pData1,int Key);



void FreeHashList(pHashList &pHashListTemp);  // 我自己加上去的  

int main()
{
	int i = 0;
	int KeyWord = 0;
	char Name[20];
	int  Age;
	pData pNew = NULL;

	pHashList pHashNew = CreateHashList();

    //定义一个函数指针
	HASHLISTFUNC HashListFunc;
	
	for (i=0;i<MAX;i++)
	{
		printf("Input Name...Age\n");
		scanf("%s",Name);
		scanf("%d",&Age);

		//申请堆内存

		pNew = (pData)malloc(sizeof(Data));

		if(pNew==NULL)
		{
			return;
		}

		else
		{

			//函数的指针进行赋值
			HashListFunc = HashInt;
			

            //从缓冲区中将数据拷贝到堆上

			pNew->Age = Age;

			strcpy(pNew->Name,Name);

			printf("Input KeyWord\n");

			scanf("%d",&KeyWord);
			//连接哈希表
			InsertNodeToHashList(pHashNew,HashListFunc,KeyWord, pNew);

		}
	   
	}


	//定义一个查找函数的指针
	DATACMPFUNC DataCmpFunc = DataCmp;

	printf("Input KeyWord \n");
	scanf("%d",&KeyWord);

	printf("Input Name\n");

	scanf("%s",Name);

	pHashListNode pHashListNodeTemp;

	if (pHashListNodeTemp =  FindDataFromHashList(pHashNew,DataCmpFunc,HashListFunc,Name,KeyWord))
	{
		g_offset = Offset(Data,Age);
		printf("%s",pHashListNodeTemp->pDt);
		printf("%d",*((char*)(pHashListNodeTemp->pDt)+g_offset));
	}

   


	FreeHashList(pHashNew);



}


pHashList CreateHashList()

{
	//创建一个哈希表

	pHashList pHashListTemp = NULL;
	pHashListTemp = (pHashList)malloc(sizeof(HashList));

	if(pHashListTemp == NULL)
	{
		return NULL;
	}

	else
	{
		//初始化哈希表中索引表中的个数
		pHashListTemp->nBucketCount = HASHMAX;	//10
		
		//创建哈希表中的索引表
		//为了能够方便程序的控制我定义了一个宏为了确保索引表的个数

		pHashListTemp->ppBuckets = (ppHashListNode)malloc(sizeof(pHashListNode)*pHashListTemp->nBucketCount);


		if(pHashListTemp->ppBuckets == NULL)
		{
			
			//如果为空释放第一次申请的哈希表
			free(pHashListTemp);
			
			return NULL;
		}


		else
		{
			//初始化索引表中的值
			memset(pHashListTemp->ppBuckets,0,(pHashListTemp->nBucketCount)*sizeof(pHashListNode));

			pHashListTemp->nNodeCount  = 0;
		}
	}


	return pHashListTemp;
}

void InsertNodeToHashList(pHashList pHashTemp,HASHLISTFUNC HashListFunc,int key, pData pDaTemp)
{
	UINT uBucketIndex = 0;
	
	//首先判断
	if (pHashTemp==NULL||pDaTemp==NULL)
	{
		return;
	}

	else
	{
		//首先要申请节点的内存
		pHashListNode pHashListNodeTemp = (pHashListNode)malloc(sizeof(HashListNode));

		if (pHashListNodeTemp==NULL)
		{
			free(pHashTemp->ppBuckets);
			free(pHashTemp);
			free(pDaTemp);
			
			return;
		}

		else
		{
			//为节点进行连接赋值
			pHashListNodeTemp->pDt = pDaTemp;
			pHashListNodeTemp->pNext = NULL;


			//将节点插入到哈希表中

			//首先计算索引值
			uBucketIndex = HashListFunc(key,pHashTemp->nBucketCount);
			
			if (pHashTemp->ppBuckets[uBucketIndex]==NULL)
			{
				pHashTemp->ppBuckets[uBucketIndex] = pHashListNodeTemp;
			}

			else
			{
				//定一个临时的链表查找值
				pHashListNode pCheckTemp = pHashTemp->ppBuckets[uBucketIndex];

				while(pCheckTemp->pNext!=NULL)
				{
					pCheckTemp = pCheckTemp->pNext;
				}

				pCheckTemp->pNext = pHashListNodeTemp;
			}



			pHashTemp->nNodeCount+=1;
		}
	}

}

pHashListNode FindDataFromHashList(pHashList pHashTemp,DATACMPFUNC DataCmpFunc,HASHLISTFUNC HashListFunc,char* pData1,int Key)
{

	pHashListNode pHashListNodeTemp = NULL;

	if (pHashTemp==NULL||DataCmpFunc==NULL||HashListFunc==NULL)
	{
		return NULL;
	}

	//通过参数计算索引				//我觉得这么费劲的 传递函数首地址过来  是为了练习学生  因为实在是不值得

	UINT uIndex = HashListFunc(Key,pHashTemp->nBucketCount);


	pHashListNodeTemp = pHashTemp->ppBuckets[uIndex];

	while(pHashListNodeTemp!=NULL)
	{
		if (DataCmpFunc(pData1,pHashListNodeTemp->pDt->Name)==0)
		{
			return pHashListNodeTemp;
		}

		pHashListNodeTemp = pHashListNodeTemp->pNext;
	}


	printf("No Data\n");

	return NULL;
}


int HashInt(int Key,int nBacketCount)
{
	return ((UINT)Key%nBacketCount);
}



int DataCmp(char* pData1,char* pData2)
{
	int i = strcmp(pData1,pData2);

	if (i==0)
	{
		return 0;
	}

	return 1;
}


void FreeHashList(pHashList &pHashListTemp)
{
	if (pHashListTemp==NULL)
	{
		return;
	}
	int i =0;
	pHashListNode pHashListNodeTemp = NULL;

	for (i=0;i<pHashListTemp->nBucketCount;i++)
	{
		pHashListNodeTemp = pHashListTemp->ppBuckets[i];

		while (pHashListNodeTemp!=NULL)
		{
			pHashListTemp->ppBuckets[i] = pHashListTemp->ppBuckets[i]->pNext;
			free(pHashListNodeTemp);
			pHashListNodeTemp = pHashListTemp->ppBuckets[i];
		}
	}
	
	free(pHashListTemp);
	pHashListTemp =  NULL;
}