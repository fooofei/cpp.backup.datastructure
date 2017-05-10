#include <STDIO.H>
#include <windows.h>
#include <QUEUE>



typedef struct tagBTNODE
{
    int Data;
    int index;  // 要比原来的结构多一个索引的项目
    struct tagBTNODE* pLNext;
    struct tagBTNODE* pRNext;
}BTNODE,*PBTNODE;

// 默认从数组的 索引1 开始存入二叉树
void CreateBiTree(PBTNODE& pRoot , int* piArray , int iArraySize)
{

    std::queue<PBTNODE> q;
    pRoot = (PBTNODE)malloc(sizeof(BTNODE));
    memset(pRoot , 0, sizeof(BTNODE) );
    pRoot->Data =piArray[1];
    pRoot->index = 1;
    q.push(pRoot);

    PBTNODE pNodeTemp = NULL;
    while ( !q.empty() )
    {
        pNodeTemp = q.front();
        q.pop();

        if ( pNodeTemp->index * 2 < iArraySize )
        {
            pNodeTemp->pLNext = (PBTNODE) malloc( sizeof (BTNODE));
            memset(pNodeTemp->pLNext , 0, sizeof(BTNODE) );

            pNodeTemp->pLNext->Data = piArray[pNodeTemp->index*2] ;
            pNodeTemp->pLNext->index = pNodeTemp->index*2;

            q.push(pNodeTemp->pLNext);
        }

        if ( pNodeTemp->index * 2 + 1< iArraySize )
        {
            pNodeTemp->pRNext = (PBTNODE) malloc( sizeof (BTNODE));
            memset(pNodeTemp->pRNext , 0, sizeof(BTNODE) );
            
            pNodeTemp->pRNext->Data = piArray[pNodeTemp->index*2+1] ;
            pNodeTemp->pRNext->index = pNodeTemp->index*2+1;
            
            q.push(pNodeTemp->pRNext);
        }

    }
    
}


void PreOrderTraverse( PBTNODE pRoot )
{
    if (pRoot != NULL)
    {
        printf("%d ",pRoot->Data );
        PreOrderTraverse(pRoot->pLNext);
        PreOrderTraverse(pRoot->pRNext);
    }
}


void DestroyBiTree(PBTNODE &pRoot)
{
    if (pRoot != NULL)
    {
        DestroyBiTree(pRoot->pLNext);
        DestroyBiTree(pRoot->pRNext);
        free(pRoot);
        pRoot = NULL;
    }
}
int main()
{

    int iArray[] = {0,1,2,3,4,5,6,7};
    int iArraySize = sizeof(iArray)/(sizeof(iArray[0])) ;

    PBTNODE pRoot = NULL;
    CreateBiTree(pRoot, iArray , iArraySize );
    PreOrderTraverse(pRoot);
    DestroyBiTree(pRoot);
    return 0;
}

/*1  2  4  5  3  6  7  Press any key to continue*/