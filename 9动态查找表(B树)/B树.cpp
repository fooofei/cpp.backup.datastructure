#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>


//严蔚敏数据结构 257 页有图

#define MAX  3

typedef struct _RECORD_
{
	int  others; 
	char ckey; 
	
}Record,*pRecord;  




typedef struct _BTNODE_
{
	int iNodeCount;              //节点个数 
	_BTNODE_* pParent;          /* 指向双亲结点 */
	struct Node     
	{
		char ckey; 
		struct _BTNODE_ *ptr;   /* 子树指针向量 */
		pRecord pRecordTemp; 
	}node[MAX+1]; 

}BTNode,*pBTNode,**ppBTNode; 


typedef struct _RESULT_
{
	pBTNode pBTNodeTemp;                 /* 指向找到的结点 */
	int i;                               /* 在结点中的关键字序号 */
	int tag;                             /* 1:查找成功，O:查找失败 */
}Result,*pResult;


typedef void(*MyPrint)(BTNode,int);


INT InitDSTable(ppBTNode ppBTNodeTemp);
void DestroyDSTable(ppBTNode ppBTNodeTemp);

Result SearchBTree(pBTNode pBTNodeTemp, char KeyWord);
int Search(pBTNode pBTNodeTemp, char KeyWord);
void Insert(ppBTNode ppBTNodeTemp,int i,pRecord p,pBTNode pBTNodeNew);
void NewRoot(ppBTNode ppBTNodeTmp,pRecord p,pBTNode pBTNodeNew);
void InsertBTree(ppBTNode ppBTNodeTemp,pRecord p,pBTNode pBTNodeCurrent,int i);
void split(ppBTNode ppBTNodeCurrent,ppBTNode ppBTNodeNew);

void TraverseDSTable(pBTNode pBTNodeTemp,void(*MyPrint)(BTNode,int));
void print(BTNode BTNodeTemp,int i);
int main()
{


	Record r[15]={{24,'1'},{45,'2'},{53,'3'},{12,'4'},{37,'5'},{50,'6'},{61,'7'},{90,'8'},{100,'9'},{70,'A'},
	{3,'B'},{30,'C'},{26,'D'},{85,'E'},{3,'F'}}; 
	
	pBTNode pBTNodeTemp = NULL;


	
	Result s = {0};
	
	int i = 0;
	
	InitDSTable(&pBTNodeTemp);

	for(i=0;i<15;i++)
	{
		s = SearchBTree(pBTNodeTemp,r[i].ckey);
	
		if(!s.tag)
		{
			InsertBTree(&pBTNodeTemp,&r[i],s.pBTNodeTemp,s.i);
		}
	}
 	printf("按关键字的顺序遍历B_树:\n");
 
	TraverseDSTable(pBTNodeTemp,print);
 	
	printf("\n请输入待查找记录的关键字: ");
 	
	scanf("%c",&i);

	s = SearchBTree(pBTNodeTemp,i);
 	if(s.tag)
	{
		print(*(s.pBTNodeTemp),s.i);
	}

   DestroyDSTable(&pBTNodeTemp);
}


int InitDSTable(ppBTNode ppBTNodeTemp)
{ 
	*ppBTNodeTemp = NULL;
	return 1;
}


void DestroyDSTable(ppBTNode ppBTNodeTemp)
{ 
	int i = 0;
	if(*ppBTNodeTemp) 
	{
		for(i=0;i<=(*ppBTNodeTemp)->iNodeCount;i++)
		{
			DestroyDSTable(&(*ppBTNodeTemp)->node[i].ptr); 
		}
		free(*ppBTNodeTemp); 
		
		*ppBTNodeTemp=NULL;
	}
}

int Search(pBTNode pBTNodeTemp, char KeyWord)
{ 
	int i = 0;
	int j = 0;
	for(j=1;j<=pBTNodeTemp->iNodeCount;j++)
	{
		if(pBTNodeTemp->node[j].ckey<=KeyWord)
		{
			i = j;
		}
	}
		return i;
 }


 Result SearchBTree(pBTNode pBTNodeTemp, char KeyWord)
 {

	 Result ResultTemp = {0};

	 bool bOk = false;

	 pBTNode p = pBTNodeTemp;
	 pBTNode q = NULL;

	 int i = 0;
	 while (p&&!bOk)
	 {

		 i = Search(p,KeyWord); 

		 if(i>0&&p->node[i].ckey==KeyWord)
		 {
			bOk = TRUE;
		 }

		 else
		 {
			q = p;

			p = p->node[i].ptr;
		 }
	 }

	 ResultTemp.i = i;

	 if (bOk)
	 {
		 ResultTemp.tag = 1;
		 ResultTemp.pBTNodeTemp = p;
	 }

	 else
	 {
		 ResultTemp.tag = 0;
		 ResultTemp.pBTNodeTemp = q;
	 }



	 return ResultTemp;

 }


 void InsertBTree(ppBTNode ppBTNodeTemp,pRecord p,pBTNode pBTNodeCurrent,int i)
 {
	 bool bOk = false;

	 pBTNode pBTNodeNew = NULL;

	 pRecord rx = p;

	 while (pBTNodeCurrent&&!bOk)
	 {
		 

		 Insert(&pBTNodeCurrent,i,rx,pBTNodeNew);
		 

		 if (pBTNodeCurrent->iNodeCount<MAX)
		 {
			
			
			 bOk = true;
		 }

		 else
		 {
			 int s = (MAX+1)/2;
			
			 rx = pBTNodeCurrent->node[s].pRecordTemp;
			
			 split(&pBTNodeCurrent,&pBTNodeNew); 
			 
			 pBTNodeCurrent = pBTNodeCurrent->pParent;
			 
			 if(pBTNodeCurrent)
			 {
				 i = Search(pBTNodeCurrent,rx->ckey); /* 在双亲结点*q中查找rx->key的插入位置 */
			 }
			 
			
		 }
	 }

	 if (!bOk)
	 {
		 NewRoot(ppBTNodeTemp,rx,pBTNodeNew);
	 }
 }


 void Insert(ppBTNode ppBTNodeTemp,int i,pRecord p,pBTNode pBTNodeNew)
 {
	 int j;

	 for (j=(*ppBTNodeTemp)->iNodeCount;j>i;j--)
	 {
		 (*ppBTNodeTemp)->node[j+1] = (*ppBTNodeTemp)->node[j];
	 }

	 (*ppBTNodeTemp)->node[i+1].ckey = p->ckey;

	 (*ppBTNodeTemp)->node[i+1].ptr = pBTNodeNew;

	 (*ppBTNodeTemp)->node[i+1].pRecordTemp = p;

	 (*ppBTNodeTemp)->iNodeCount++;
 }


 void NewRoot(ppBTNode ppBTNodeTmp,pRecord p,pBTNode pBTNodeNew)
 { 
	 pBTNode pBTNodeTemp;
	 pBTNodeTemp = (pBTNode)malloc(sizeof(BTNode));

	 pBTNodeTemp->node[0].ptr=*ppBTNodeTmp;
	 
	 *ppBTNodeTmp = pBTNodeTemp;
	 
	 if((*ppBTNodeTmp)->node[0].ptr)
	 {
		 (*ppBTNodeTmp)->node[0].ptr->pParent=*ppBTNodeTmp;
	 }
	 (*ppBTNodeTmp)->pParent = NULL;
	 (*ppBTNodeTmp)->iNodeCount = 1;
	 (*ppBTNodeTmp)->node[1].ckey = p->ckey;
	 (*ppBTNodeTmp)->node[1].pRecordTemp = p;
	 (*ppBTNodeTmp)->node[1].ptr = pBTNodeNew;
	 if((*ppBTNodeTmp)->node[1].ptr)
	 {
		 (*ppBTNodeTmp)->node[1].ptr->pParent=*ppBTNodeTmp;
	 }
 }



 void split(ppBTNode ppBTNodeCurrent,ppBTNode ppBTNodeNew)
 { 
	 
	 
	 /* 将结点ppBTNodeCurrent分裂成两个结点，前一半保留，后一半移入新生结点ppBTNodeNew */

	 int i = 0;
	 
	 int s = (MAX+1)/2;
	
	 *ppBTNodeNew=(pBTNode)malloc(sizeof(BTNode));                 //生成新结点ppBTNodeNew
	 
	 (*ppBTNodeNew)->node[0].ptr=(*ppBTNodeCurrent)->node[s].ptr;  // 后一半移入ppBTNodeNew 

	 for(i=s+1;i<=MAX;i++)
	 {
		 (*ppBTNodeNew)->node[i-s]=(*ppBTNodeCurrent)->node[i];
		 if((*ppBTNodeNew)->node[i-s].ptr)
		 {
			 (*ppBTNodeNew)->node[i-s].ptr->pParent=*ppBTNodeNew;
		 }
	 }
	 (*ppBTNodeNew)->iNodeCount = MAX-s;
	 (*ppBTNodeNew)->pParent = (*ppBTNodeCurrent)->pParent;
	 (*ppBTNodeCurrent)->iNodeCount = s-1; 
 }

 void TraverseDSTable(pBTNode pBTNodeTemp,void(*MyPrint)(BTNode,int))
 {
	 int i =0;

	 if(pBTNodeTemp) 
	 {
		 if(pBTNodeTemp->node[0].ptr) 
		 {
			 TraverseDSTable(pBTNodeTemp->node[0].ptr,MyPrint);
		 }
		 
		 for(i=1;i<=pBTNodeTemp->iNodeCount;i++)
		 {
			 MyPrint(*pBTNodeTemp,i);
			 if(pBTNodeTemp->node[i].ptr) 
			 {
				 TraverseDSTable(pBTNodeTemp->node[i].ptr,MyPrint);
			 }


		 }

		 printf("\n");
	 }
 }



 void print(BTNode BTNodeTemp,int i)
 {
	 printf("%c,%d    ",BTNodeTemp.node[i].ckey,BTNodeTemp.node[i].pRecordTemp->others);
 }