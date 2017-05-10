//********************************************************************
//    DEMO.CPP    文件注释
//    FileName   :    DEMO.CPP
//    Author     :    
//    CreateTime :    2013/5/12 11:36
//    Description:    融合了严蔚敏以及部分网络代码,你会看到部分函数严蔚敏没有涉及
//*********************************************************************
#include <STDIO.H>
#include <windows.h>
#include <QUEUE>
using namespace std;

typedef char  TElemType;
// 以 '#' 结尾
const TElemType Nil = '#';


typedef struct tagTNODE
{
    TElemType Data;
    struct tagTNODE* pFirst;
    struct tagTNODE* pNextSibling;
}TNODE,*PTNODE;


// 共16个函数
// 用到的数据结构 : 队列

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

// s 改为 e 因为有可能会修改pRoot的值 所以要传引用
void Assign(PTNODE &pRoot , TElemType s , TElemType e);

// pTNodeInsert 是 pRoot的某个结点
// 操作结果: 将pTNew 插到pTNodeInsert 的第i 个结点
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

    printf("深度%d.\n",GetDepth(pRoot));
    
    
    
    printf("%c.\n",GetParent(pRoot,'7'));
    
    
    PTNODE pTNodeTemp = GetPoint(pRoot,'2');
    printf("%c\n",GetValue(pTNodeTemp));
    
    
    
    PTNODE pTreeNew = NULL;
    printf("新树\n");

    fp = fopen("newtree.txt","r");
    if(fp == NULL)
        return 0;
    CreateTreeFromFile(pTreeNew,fp);
    fclose(fp);
    InsertTree(pRoot,pRoot,pTreeNew,1);
    
    printf("插入:");
    PreOrderTraverse(pRoot);
    printf("\n");
    
    printf("删除:");
    DeleteTree(pRoot,pRoot,1);
    printf("处理之后\n");
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
    //printf("%c ",pRoot->Data); // 第一句
    while ( !q.empty() )
    {
        pRoot = q.front();
        q.pop();
        // 这里有个问题  以前用三句相同的话与入队一起输出
        // 现在放在出队的时候输出  效果是一样的
        printf("%c ",pRoot->Data);
        if (pRoot->pFirst != NULL)
        {
            pRoot = pRoot->pFirst;
            //printf("%c ",pRoot->Data);// 第二句
            q.push(pRoot);

            while (pRoot->pNextSibling != NULL)
            {
                pRoot = pRoot->pNextSibling;
                //printf("%c ",pRoot->Data); // 第三句
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

// pTNodeInsert 是 pRoot的某个结点
// 操作结果: 将pTNew 插到pTNodeInsert 的第i 个结点
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


// s 改为 e 因为有可能会修改pRoot的值 所以要传引用
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

//s 是非叶子结点 返回他的左孩子  也就是大儿子
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

// s 是非根结点 返回其双亲
TElemType GetParent(PTNODE pRoot , TElemType s)
{
    // 是根节点
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
                // 大儿子入队
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

// 返回给定结点的指针
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

// 严蔚敏的 GetRoot 函数与之相同
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


    // 换一种方式理解
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

// 用到的数据结构 : 队列

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
        
        printf("输入%c的孩子:",pNodeNew->Data) ;
        
        scanf("%s" , szBuffer);
        
        szBufferLen = strlen(szBuffer);
        
        if(szBuffer[0] == Nil)
            continue;
        
        // 不为Nil
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
        
        //printf("输入%c的孩子:",pNodeNew->Data) ;
        
        fscanf(fp,"%s" , szBuffer);
        
        szBufferLen = strlen(szBuffer);
        
        if(szBuffer[0] == Nil)
            continue;
        
        // 不为Nil
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