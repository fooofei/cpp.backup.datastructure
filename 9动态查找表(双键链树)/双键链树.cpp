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
	struct _DLTNODE_* pNext; // ָ���ֵܽ���ָ�� 
	NodeKind kind;
	union
	{
		pRecord pRecordTemp; 
		struct _DLTNODE_* pChildFirst; // ��֧���ĺ�����ָ�� 
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
			DestroyDSTable(&(*ppDLTNodeTemp)->a.pChildFirst); // ���ٺ������� 
		}
		if((*ppDLTNodeTemp)->pNext) // ���ֵ� 
		{
			DestroyDSTable(&(*ppDLTNodeTemp)->pNext); // �����ֵ����� 
		}
		
		free(*ppDLTNodeTemp); // �ͷŸ���� 
		
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
			while(p&&p->cKey!=K.szKey[i]) // ���ҹؼ��ֵĵ�iλ 
			{
				p=p->pNext;
			}
			
			if(p&&i<K.iNUM) // ׼��������һλ 
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
		return NULL; // ���� 
	}
 }



void InsertDSTable(ppDLTNode ppDLTNodeTemp,pRecord r)
{ 

	pDLTNode p = NULL;
	pDLTNode q = NULL;
	pDLTNode pDLTNodeNew = NULL;
	int i = 0;
	
	KeyType K=r->key;
	
	if(!*ppDLTNodeTemp&&K.iNUM) // �����ҹؼ��ַ����ǿ� 
	{
		*ppDLTNodeTemp = pDLTNodeNew = (pDLTNode)malloc(sizeof(DLTNode));
	
		for(;i<K.iNUM;i++) // �����֧��� 
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
	 
		p->a.pChildFirst = pDLTNodeNew; // ����Ҷ�ӽ�� 
		
		pDLTNodeNew->pNext = NULL;
		
		pDLTNodeNew->cKey = '0';
		
		pDLTNodeNew->kind=LEAF;
		
		pDLTNodeNew->a.pRecordTemp = r;
	}
	else /* �ǿ��� */
	{
		p=*ppDLTNodeTemp; 
	
		while(p&&i<K.iNUM)
		{
			while(p&&p->cKey<K.szKey[i]) // ���ֵܽ����� 
			{
				q = p;
				p = p->pNext;
			}
			if(p&&p->cKey==K.szKey[i])   // �ҵ���K.ch[i]����Ľ�� 
			{
				q = p;
				p = p->a.pChildFirst; // pָ����K.ch[i+1]�ȽϵĽ�� 
				
				++i;
			}
			else /* û�ҵ�,����ؼ��� */
			{
				pDLTNodeNew = (pDLTNode)malloc(sizeof(DLTNode));
				
				if(q->a.pChildFirst==p)
				{
					q->a.pChildFirst = pDLTNodeNew; // �ڳ��ӵ�λ�ò���
				}
				
				
				else 
				{
					q->pNext=pDLTNodeNew;          // ���ֵܵ�λ�ò���
				}
				pDLTNodeNew->pNext = p;
				pDLTNodeNew->cKey = K.szKey[i];
				pDLTNodeNew->kind = BRANCH;
				
				p = pDLTNodeNew;
				
				pDLTNodeNew=(pDLTNode)malloc(sizeof(DLTNode));
				i++;
			
				for(;i<K.iNUM;i++) // �����֧��� 
				{
					p->a.pChildFirst = pDLTNodeNew;
					pDLTNodeNew->pNext = NULL;
					pDLTNodeNew->cKey = K.szKey[i];
					pDLTNodeNew->kind = BRANCH;
					p = pDLTNodeNew;
					
					pDLTNodeNew=(pDLTNode)malloc(sizeof(DLTNode));
				}
				p->a.pChildFirst = pDLTNodeNew; // ����Ҷ�ӽ�� 
				pDLTNodeNew->pNext = NULL;
				pDLTNodeNew->cKey = '0';
				pDLTNodeNew->kind = LEAF;
				pDLTNodeNew->a.pRecordTemp = r;
			}
		}
	}
 }