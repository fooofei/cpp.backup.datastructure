#include <iostream.h>
#include <windows.h>
#include <malloc.h>
#include <stdio.h>


#define MAXKEYLEN 16 

typedef enum{LEAF,BRANCH}NodeKind; 

typedef struct _KEYTYPE_
{
	char szKey[MAXKEYLEN]; 
	int iNUM; 
}KeyType,pKeyType; 

typedef struct _RECORD_
{
	KeyType key; 
	int iOthers; 
}Record,*pRecord; 


typedef struct _DLTNODE_ 
{
	char cKey;
	struct _DLTNODE_* pNext; // 指向兄弟结点的指针 
	NodeKind kind;
	union
	{
		pRecord pRecordTemp; 
		struct _DLTNODE_* pChildFirst; // 分支结点的孩子链指针 
	}a;
}DLTNode,*pDLTNode,**ppDLTNode;

INT InitDSTable(ppDLTNode ppDLTNodeTemp);
void DestroyDSTable(ppDLTNode ppDLTNodeTemp);
pRecord SearchDLTree(pDLTNode pDLTNodeTemp,KeyType K);
void InsertDSTable(ppDLTNode ppDLTNodeTemp,pRecord r);

void main()
{

}


INT InitDSTable(ppDLTNode ppDLTNodeTemp)
{ 
	*ppDLTNodeTemp=NULL;
	
	return 1;
}



void DestroyDSTable(ppDLTNode ppDLTNodeTemp)
{
	if(*ppDLTNodeTemp) 
	{
		if((*ppDLTNodeTemp)->kind==BRANCH&&(*ppDLTNodeTemp)->a.pChildFirst)
		{
			DestroyDSTable(&(*ppDLTNodeTemp)->a.pChildFirst); // 销毁孩子子树 
		}
		if((*ppDLTNodeTemp)->pNext) // 有兄弟 
		{
			DestroyDSTable(&(*ppDLTNodeTemp)->pNext); // 销毁兄弟子树 
		}
		
		free(*ppDLTNodeTemp); // 释放根结点 
		
		*ppDLTNodeTemp = NULL; 
	}
 }


pRecord SearchDLTree(pDLTNode pDLTNodeTemp,KeyType K)
{ 
	pDLTNode p = NULL;
	int i = 0;
	
	if(pDLTNodeTemp)
	{
		p = pDLTNodeTemp;
		i = 0;
		
		while(p&&i<K.iNUM)
		{
			while(p&&p->cKey!=K.szKey[i]) // 查找关键字的第i位 
			{
				p=p->pNext;
			}
			
			if(p&&i<K.iNUM) // 准备查找下一位 
			{
				p=p->a.pChildFirst;
			}
			i++;
		} 

		if(!p)
		{
			return NULL;
		}
		else
		{
			return p->a.pRecordTemp;
		}
	}
	else
	{
		return NULL; // 树空 
	}
 }



void InsertDSTable(ppDLTNode ppDLTNodeTemp,pRecord r)
{ 

	pDLTNode p = NULL;
	pDLTNode q = NULL;
	pDLTNode pDLTNodeNew = NULL;
	int i = 0;
	
	KeyType K=r->key;
	
	if(!*ppDLTNodeTemp&&K.iNUM) // 空树且关键字符串非空 
	{
		*ppDLTNodeTemp = pDLTNodeNew = (pDLTNode)malloc(sizeof(DLTNode));
	
		for(;i<K.iNUM;i++) // 插入分支结点 
		{
			if(p)
			{
				p->a.pChildFirst = pDLTNodeNew;
			}
			pDLTNodeNew->pNext = NULL;
			pDLTNodeNew->cKey = K.szKey[i];
			pDLTNodeNew->kind = BRANCH;
			
			p = pDLTNodeNew;
			pDLTNodeNew = (pDLTNode)malloc(sizeof(DLTNode));
		}
	 
		p->a.pChildFirst = pDLTNodeNew; // 插入叶子结点 
		
		pDLTNodeNew->pNext = NULL;
		
		pDLTNodeNew->cKey = '0';
		
		pDLTNodeNew->kind=LEAF;
		
		pDLTNodeNew->a.pRecordTemp = r;
	}
	else /* 非空树 */
	{
		p=*ppDLTNodeTemp; 
	
		while(p&&i<K.iNUM)
		{
			while(p&&p->cKey<K.szKey[i]) // 沿兄弟结点查找 
			{
				q = p;
				p = p->pNext;
			}
			if(p&&p->cKey==K.szKey[i])   // 找到与K.ch[i]相符的结点 
			{
				q = p;
				p = p->a.pChildFirst; // p指向将与K.ch[i+1]比较的结点 
				
				++i;
			}
			else /* 没找到,插入关键字 */
			{
				pDLTNodeNew = (pDLTNode)malloc(sizeof(DLTNode));
				
				if(q->a.pChildFirst==p)
				{
					q->a.pChildFirst = pDLTNodeNew; // 在长子的位置插入
				}
				
				
				else 
				{
					q->pNext=pDLTNodeNew;          // 在兄弟的位置插入
				}
				pDLTNodeNew->pNext = p;
				pDLTNodeNew->cKey = K.szKey[i];
				pDLTNodeNew->kind = BRANCH;
				
				p = pDLTNodeNew;
				
				pDLTNodeNew=(pDLTNode)malloc(sizeof(DLTNode));
				i++;
			
				for(;i<K.iNUM;i++) // 插入分支结点 
				{
					p->a.pChildFirst = pDLTNodeNew;
					pDLTNodeNew->pNext = NULL;
					pDLTNodeNew->cKey = K.szKey[i];
					pDLTNodeNew->kind = BRANCH;
					p = pDLTNodeNew;
					
					pDLTNodeNew=(pDLTNode)malloc(sizeof(DLTNode));
				}
				p->a.pChildFirst = pDLTNodeNew; // 插入叶子结点 
				pDLTNodeNew->pNext = NULL;
				pDLTNodeNew->cKey = '0';
				pDLTNodeNew->kind = LEAF;
				pDLTNodeNew->a.pRecordTemp = r;
			}
		}
	}
 }