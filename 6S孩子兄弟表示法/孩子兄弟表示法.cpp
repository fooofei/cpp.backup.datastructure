//********************************************************************
//    DEMO.CPP    �ļ�ע��
//    FileName   :    DEMO.CPP
//    Author     :    
//    CreateTime :    2013/5/12 11:36
//    Description:    �ں�����ε���Լ������������,��ῴ�����ֺ�����ε��û���漰
//*********************************************************************
#include <STDIO.H>
#include <windows.h>
#include <QUEUE>
using namespace std;

typedef char  TElemType;
// �� '#' ��β
const TElemType Nil = '#';


typedef struct tagTNODE
{
    TElemType Data;
    struct tagTNODE* pFirst;
    struct tagTNODE* pNextSibling;
}TNODE,*PTNODE;


// ��16������
// �õ������ݽṹ : ����

void CreateTree(PTNODE &pRoot);
void CreateTreeFromFile(PTNODE &pRoot , FILE* fp);

void DestroyTree(PTNODE pRoot);

void PreOrderTraverse(PTNODE pRoot);
void PosOrderTraverse(PTNODE pRoot);
void LevelOrderTraverse(PTNODE pRoot);

bool IsTreeEmpty(PTNODE pRoot)  ;

int GetDepth(PTNODE pRoot);

TElemType GetValue(PTNODE pNodeTemp);

PTNODE GetPoint(PTNODE pRoot , TElemType s);

TElemType GetParent(PTNODE pRoot , TElemType s);

TElemType GetLeftChild(PTNODE pRoot , TElemType s);

TElemType GetRightSibling(PTNODE pRoot , TElemType s);

// s ��Ϊ e ��Ϊ�п��ܻ��޸�pRoot��ֵ ����Ҫ������
void Assign(PTNODE &pRoot , TElemType s , TElemType e);

// pTNodeInsert �� pRoot��ĳ�����
// �������: ��pTNew �嵽pTNodeInsert �ĵ�i �����
void InsertTree(PTNODE pRoot , PTNODE pTNodeInsert ,
                PTNODE pTNew , unsigned int i);

void DeleteTree(PTNODE pRoot , PTNODE pTDelete,unsigned int i);
int main()
{

  
    PTNODE pRoot = NULL;
    FILE* fp = fopen("tree.txt","r");
    if(fp == NULL)
        return 0;
    CreateTreeFromFile(pRoot,fp);
    fclose(fp);
    
    printf("PreOrderTraverse:");
    PreOrderTraverse(pRoot);
    printf("\n");
    
    printf("PosOrderTraverse:");
    PosOrderTraverse(pRoot);
    printf("\n");
    
    printf("LevelOrderTraverse:");
    LevelOrderTraverse(pRoot);
    printf("\n");

    printf("���%d.\n",GetDepth(pRoot));
    
    
    
    printf("%c.\n",GetParent(pRoot,'7'));
    
    
    PTNODE pTNodeTemp = GetPoint(pRoot,'2');
    printf("%c\n",GetValue(pTNodeTemp));
    
    
    
    PTNODE pTreeNew = NULL;
    printf("����\n");

    fp = fopen("newtree.txt","r");
    if(fp == NULL)
        return 0;
    CreateTreeFromFile(pTreeNew,fp);
    fclose(fp);
    InsertTree(pRoot,pRoot,pTreeNew,1);
    
    printf("����:");
    PreOrderTraverse(pRoot);
    printf("\n");
    
    printf("ɾ��:");
    DeleteTree(pRoot,pRoot,1);
    printf("����֮��\n");
    PreOrderTraverse(pRoot);
    printf("\n");
	DestroyTree(pRoot);
    return 0;
}

void LevelOrderTraverse(PTNODE pRoot)
{
    if (pRoot == NULL)
        return;

    queue<PTNODE> q;
    q.push(pRoot);
    //printf("%c ",pRoot->Data); // ��һ��
    while ( !q.empty() )
    {
        pRoot = q.front();
        q.pop();
        // �����и�����  ��ǰ��������ͬ�Ļ������һ�����
        // ���ڷ��ڳ��ӵ�ʱ�����  Ч����һ����
        printf("%c ",pRoot->Data);
        if (pRoot->pFirst != NULL)
        {
            pRoot = pRoot->pFirst;
            //printf("%c ",pRoot->Data);// �ڶ���
            q.push(pRoot);

            while (pRoot->pNextSibling != NULL)
            {
                pRoot = pRoot->pNextSibling;
                //printf("%c ",pRoot->Data); // ������
                q.push(pRoot);
            }
        }
    }   
}

void PosOrderTraverse(PTNODE pRoot)
{
    if (pRoot != NULL)
    {
        PTNODE pTNodeTemp = NULL;
        if (pRoot->pFirst != NULL)
        {
            PosOrderTraverse(pRoot->pFirst );
            pTNodeTemp = pRoot->pFirst->pNextSibling;
            while (pTNodeTemp != NULL)
            {
                PosOrderTraverse(pTNodeTemp);
                pTNodeTemp = pTNodeTemp->pNextSibling;
            }
        }
        printf("%c ",pRoot->Data);
    }
}


void DeleteTree(PTNODE pRoot , PTNODE pTDelete,unsigned int i)
{
    PTNODE pTPre = NULL;

    if (pRoot != NULL)
    {
        if (i == 1 )
        {
            pTPre = pTDelete->pFirst;
            pTDelete->pFirst = pTDelete->pFirst->pNextSibling;
            pTPre->pNextSibling = NULL ;
            DestroyTree(pTPre);
        }
        else
        {
            pTDelete = pTDelete->pFirst;
            
            unsigned int j = 2;
            
            while (pTDelete != NULL && j<i)
            {
                pTDelete = pTDelete->pNextSibling;
                j++;
            }
            
            if (j == i)
            {
               pTPre = pTDelete->pNextSibling;
               pTDelete->pNextSibling = pTDelete->pNextSibling->pNextSibling;
               pTPre->pNextSibling = NULL ;
               DestroyTree(pTPre);
            }
        }
    }
}

// pTNodeInsert �� pRoot��ĳ�����
// �������: ��pTNew �嵽pTNodeInsert �ĵ�i �����
void InsertTree(PTNODE pRoot , PTNODE pTNodeInsert ,
                PTNODE pTNew , unsigned int i)
{
    if (pRoot != NULL)
    {
        if (i == 1)
        {
            pTNew->pNextSibling = pTNodeInsert->pFirst;
            pTNodeInsert->pFirst = pTNew;
        }
        else
        {
            pTNodeInsert = pTNodeInsert->pNextSibling;

            unsigned int j = 2;
            
            while (pTNodeInsert != NULL && j<i)
            {
                pTNodeInsert = pTNodeInsert->pNextSibling;
                j++;
            }

            if (j == i)
            {
                pTNew->pNextSibling = pTNodeInsert->pNextSibling;
                pTNodeInsert->pNextSibling = pTNew;
            }
        }
    }
}


// s ��Ϊ e ��Ϊ�п��ܻ��޸�pRoot��ֵ ����Ҫ������
void Assign(PTNODE &pRoot , TElemType s , TElemType e)
{
    if(pRoot != NULL)
    {
        pRoot = GetPoint(pRoot,s);
        if(pRoot != NULL)
            pRoot->Data = e;
    }
}

TElemType GetRightSibling(PTNODE pRoot , TElemType s)
{
    if(pRoot != NULL)
    {
        pRoot = GetPoint(pRoot , s);
        if( pRoot != NULL && pRoot->pNextSibling != NULL)
            return (pRoot->pNextSibling->Data);
    }
    return Nil;
}

//s �Ƿ�Ҷ�ӽ�� ������������  Ҳ���Ǵ����
TElemType GetLeftChild(PTNODE pRoot , TElemType s)
{
    if(pRoot != NULL)
    {
        pRoot = GetPoint(pRoot,s);
        if(pRoot != NULL && pRoot->pFirst != NULL)
            return (pRoot->pFirst->Data);
    }
    return Nil;
}

// s �ǷǸ���� ������˫��
TElemType GetParent(PTNODE pRoot , TElemType s)
{
    // �Ǹ��ڵ�
    if(GetValue(pRoot) == s)
        return Nil;

    if (pRoot != NULL)
    {
        queue<PTNODE> q;
        PTNODE pNodeParent = NULL ;
        q.push(pRoot);
        while ( !q.empty() )
        {
            pRoot = q.front();
            q.pop();
            
            if (pRoot->pFirst != NULL )
            {
                if(pRoot->pFirst->Data == s)
                    return (pRoot->Data);
                pNodeParent = pRoot;
                pRoot  = pRoot->pFirst;
                // ��������
                q.push(pRoot);

                while (pRoot->pNextSibling != NULL)
                {
                    pRoot = pRoot->pNextSibling;
                    if(pRoot->Data ==s )
                        return (pNodeParent->Data);

                    q.push(pRoot);
                }

            }
        }
        
    }

    return Nil;
}

// ���ظ�������ָ��
PTNODE GetPoint(PTNODE pRoot , TElemType s)
{
    if(pRoot != NULL)
    {
        queue<PTNODE> q;
        q.push( pRoot );

        while ( !q.empty() )
        {
            pRoot = q.front();
            q.pop();

            if( pRoot->Data == s)
                return pRoot;
            if( pRoot->pFirst != NULL)
                q.push(pRoot->pFirst);
            if(pRoot->pNextSibling != NULL)
                q.push( pRoot->pNextSibling );

        }
    }

    return NULL;
}

// ��ε���� GetRoot ������֮��ͬ
TElemType GetValue(PTNODE pNodeTemp)
{
    if(pNodeTemp != NULL)
        return (pNodeTemp->Data);
    return Nil;
}

int GetDepth(PTNODE pRoot)
{
    /*
    int iDepth = 0;
    int i = 0;
    int iMaxDepth = 0;

    PTNODE pNodeTemp = NULL;
    if (pRoot != NULL)
    {
        if (pRoot->pFirst != NULL)
        {
            pNodeTemp = pRoot->pFirst;
            while (pNodeTemp != NULL)
            {
                iDepth = GetDepth(pNodeTemp);
                if(iDepth > iMaxDepth)
                    iMaxDepth = iDepth;
                pNodeTemp = pNodeTemp->pNextSibling;
            }
            return (iMaxDepth + 1);
        }
        return 1;
    }

    return 0;*/


    // ��һ�ַ�ʽ���
    int iDepth = 0;
    int iMaxDepth = 0;
    if(pRoot == NULL)
        return 0;
    if(pRoot->pFirst == NULL)
        return 1;

    PTNODE pTNodeTemp = pRoot;

    for (pTNodeTemp= pTNodeTemp->pFirst;pTNodeTemp !=NULL ; 
    pTNodeTemp = pTNodeTemp->pNextSibling)
    {
        iDepth = GetDepth(pTNodeTemp);
        if(iDepth > iMaxDepth )
            iMaxDepth = iDepth;
    }

    return (++ iMaxDepth);
}


bool IsTreeEmpty(PTNODE pRoot) 
{
    return (pRoot == NULL);
}

void PreOrderTraverse(PTNODE pRoot)
{
    if (pRoot != NULL )
    {
        printf("%c ",pRoot->Data);
        PreOrderTraverse(pRoot->pFirst);
        PreOrderTraverse(pRoot->pNextSibling);
    }
}

void DestroyTree(PTNODE pRoot)
{
    if(pRoot != NULL)
    {
        DestroyTree(pRoot->pFirst);
        DestroyTree(pRoot->pNextSibling);

        free(pRoot);
        pRoot = NULL;
    }
}

// �õ������ݽṹ : ����

void CreateTree(PTNODE &pRoot)
{
    char szBuffer[20] = {0};
    scanf(" %c" , &szBuffer[0]);
    
    if (szBuffer[0] == Nil)
        return ;
    pRoot = (PTNODE)malloc(sizeof(TNODE));
    memset(pRoot , 0 , sizeof(TNODE));
    
    pRoot->Data = szBuffer[0];
    
    PTNODE pNodeNew = NULL;
    size_t szBufferLen = 0;
    int i;
    queue<PTNODE> q;
    
    q.push(pRoot);
    
    while (!q.empty())
    {
        pNodeNew = q.front();
        q.pop();
        
        printf("����%c�ĺ���:",pNodeNew->Data) ;
        
        scanf("%s" , szBuffer);
        
        szBufferLen = strlen(szBuffer);
        
        if(szBuffer[0] == Nil)
            continue;
        
        // ��ΪNil
        pNodeNew->pFirst = (PTNODE)malloc(sizeof(TNODE));
        memset(pNodeNew->pFirst , 0, sizeof(TNODE));
        pNodeNew->pFirst->Data = szBuffer[0];
        q.push(pNodeNew->pFirst);
        
        pNodeNew = pNodeNew->pFirst;
        for (i=1 ; i<szBufferLen ; ++ i)
        {
            pNodeNew->pNextSibling = (PTNODE)malloc(sizeof(TNODE));
            pNodeNew = pNodeNew->pNextSibling;
            memset(pNodeNew , 0, sizeof(TNODE));
            pNodeNew->Data = szBuffer[i];
            
            q.push(pNodeNew);
        }
        
    }
    
}


void CreateTreeFromFile(PTNODE &pRoot , FILE* fp)
{
    char szBuffer[20] = {0};
    fscanf(fp," %c" , &szBuffer[0]);
    
    if (szBuffer[0] == Nil)
        return ;
    pRoot = (PTNODE)malloc(sizeof(TNODE));
    memset(pRoot , 0 , sizeof(TNODE));
    
    pRoot->Data = szBuffer[0];
    
    PTNODE pNodeNew = NULL;
    size_t szBufferLen = 0;
    int i;
    queue<PTNODE> q;
    
    q.push(pRoot);
    
    while (!q.empty())
    {
        pNodeNew = q.front();
        q.pop();
        
        //printf("����%c�ĺ���:",pNodeNew->Data) ;
        
        fscanf(fp,"%s" , szBuffer);
        
        szBufferLen = strlen(szBuffer);
        
        if(szBuffer[0] == Nil)
            continue;
        
        // ��ΪNil
        pNodeNew->pFirst = (PTNODE)malloc(sizeof(TNODE));
        memset(pNodeNew->pFirst , 0, sizeof(TNODE));
        pNodeNew->pFirst->Data = szBuffer[0];
        q.push(pNodeNew->pFirst);
        
        pNodeNew = pNodeNew->pFirst;
        for (i=1 ; i<szBufferLen ; ++ i)
        {
            pNodeNew->pNextSibling = (PTNODE)malloc(sizeof(TNODE));
            pNodeNew = pNodeNew->pNextSibling;
            memset(pNodeNew , 0, sizeof(TNODE));
            pNodeNew->Data = szBuffer[i];
            
            q.push(pNodeNew);
        }
        
    }
    
}