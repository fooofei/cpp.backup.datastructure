#include <stdio.h>
#include <windows.h>
#include <QUEUE>
#include <stack>
using namespace std;

typedef struct tagBTNODE
{
    char Data;
    struct tagBTNODE* pParent;
    struct tagBTNODE* pLNext;
    struct tagBTNODE* pRNext;
}BTNODE,*PBTNODE;


void DestroyTree(PBTNODE &pRoot);

// 队列创建
void CreateBiTree(PBTNODE &pRoot,PBTNODE pParent);
void CreateBiTreeFromFile(PBTNODE &pRoot,PBTNODE pParent , FILE* fp);


// 递归创建
void CreateBiTree2(PBTNODE &pRoot,PBTNODE pParent);
void CreateBiTreeFromFile2(PBTNODE &pRoot,PBTNODE pParent , FILE* fp);

void PreOrderTraverse2(PBTNODE pRoot);

int main()
{

    FILE* fp = fopen("tree.txt" , "r");
    PBTNODE pRoot = NULL;
    CreateBiTreeFromFile(pRoot , NULL,fp);
    fclose(fp);
    
    printf("PreOrderTraverse2:    ");
	PreOrderTraverse2(pRoot );

    DestroyTree(pRoot);

    printf("------------------------------------\n");
    fp = fopen("tree.txt" , "r");
    pRoot = NULL;
    CreateBiTreeFromFile(pRoot , NULL,fp);
    fclose(fp);
    
    printf("PreOrderTraverse2:    ");
    PreOrderTraverse2(pRoot );
    
    DestroyTree(pRoot);
    return 0;
}

// 队列创建三叉链表
void CreateBiTree(PBTNODE &pRoot,PBTNODE pParent)
{
    char Data = 0;
    scanf(" %c",&Data);

    if(Data == '#')
        pRoot = NULL;
    else
    {
        pRoot = (PBTNODE )malloc(sizeof(BTNODE));
        memset(pRoot , 0 , sizeof(BTNODE));
        pRoot->Data = Data;
        queue<PBTNODE> q;
        q.push(pRoot);

        PBTNODE pBTNodeTemp =NULL;
        while ( !q.empty() )
        {
            pBTNodeTemp = q.front();
            q.pop();
            
            scanf(" %c",&Data);
            if (Data !='#')
            {
                pBTNodeTemp->pLNext = (PBTNODE)malloc(sizeof(BTNODE));
                memset(pBTNodeTemp->pLNext,0,sizeof(BTNODE));
                pBTNodeTemp->pLNext->Data = Data;
                pBTNodeTemp->pLNext->pParent = pBTNodeTemp;
                q.push(pBTNodeTemp->pLNext);
            }   

            scanf(" %c",&Data);
            if (Data !='#')
            {
                pBTNodeTemp->pRNext = (PBTNODE)malloc(sizeof(BTNODE));
                memset(pBTNodeTemp->pRNext,0,sizeof(BTNODE));
                pBTNodeTemp->pRNext->Data = Data;
                pBTNodeTemp->pRNext->pParent = pBTNodeTemp;
                q.push(pBTNodeTemp->pRNext);
            }   
        }
    }
}


// 队列  改为 文件
void CreateBiTreeFromFile(PBTNODE &pRoot,PBTNODE pParent , FILE* fp)
{
    char Data = 0;
    fscanf(fp," %c",&Data);
    
    if(Data == '#')
        pRoot = NULL;
    else
    {
        pRoot = (PBTNODE )malloc(sizeof(BTNODE));
        memset(pRoot , 0 , sizeof(BTNODE));
        pRoot->Data = Data;
        queue<PBTNODE> q;
        q.push(pRoot);
        
        PBTNODE pBTNodeTemp =NULL;
        while ( !q.empty() )
        {
            pBTNodeTemp = q.front();
            q.pop();
            
            fscanf(fp," %c",&Data);
            if (Data !='#')
            {
                pBTNodeTemp->pLNext = (PBTNODE)malloc(sizeof(BTNODE));
                memset(pBTNodeTemp->pLNext,0,sizeof(BTNODE));
                pBTNodeTemp->pLNext->Data = Data;
                pBTNodeTemp->pLNext->pParent = pBTNodeTemp;
                q.push(pBTNodeTemp->pLNext);
            }   
            
            fscanf(fp," %c",&Data);
            if (Data !='#')
            {
                pBTNodeTemp->pRNext = (PBTNODE)malloc(sizeof(BTNODE));
                memset(pBTNodeTemp->pRNext,0,sizeof(BTNODE));
                pBTNodeTemp->pRNext->Data = Data;
                pBTNodeTemp->pRNext->pParent = pBTNodeTemp;
                q.push(pBTNodeTemp->pRNext);
            }   
        }
    }
}


void PreOrderTraverse2(PBTNODE pRoot)// 推荐 与层序遍历类似 好记忆
{
    if(pRoot == NULL )
        return;
    
    stack<PBTNODE> s;
    // 根入栈
    s.push(pRoot);
    
    // 循环栈不空
    while(!s.empty())
    {
        // 出栈需要调用两个函数...Orz...
        // 取出数据 输出
        pRoot = s.top();
        s.pop();
        printf("%c ",pRoot->Data );
        
        // 其有右孩子 右孩子入栈 其有左孩子 左孩子入栈
        if(pRoot->pRNext != NULL)
            s.push(pRoot->pRNext );
        if(pRoot->pLNext != NULL )
            s.push( pRoot->pLNext );
    }
    
    printf("\n");
}

void DestroyTree(PBTNODE &pRoot)
{
    if (pRoot != NULL)
    {
        DestroyTree(pRoot->pLNext );
        DestroyTree( pRoot->pRNext );
        free(pRoot );
        pRoot = NULL;
    }
}


void CreateBiTree2(PBTNODE &pRoot,PBTNODE pParent)
{
    char Data = 0;
    scanf(" %c",&Data);
    if(Data == '#')
        pRoot = NULL;
    else
    {
        pRoot = (PBTNODE)malloc(sizeof(BTNODE));
        memset(pRoot , 0, sizeof(BTNODE));
        pRoot->Data = Data;
        pRoot->pParent = pParent;
        CreateBiTree2(pRoot->pLNext , pRoot);
        CreateBiTree2(pRoot->pRNext , pRoot);

    }
}
void CreateBiTreeFromFile2(PBTNODE &pRoot,PBTNODE pParent , FILE** fp)
{
    char Data = 0;
    fscanf(*fp," %c",&Data);
    if(Data == '#')
        pRoot = NULL;
    else
    {
        pRoot = (PBTNODE)malloc(sizeof(BTNODE));
        memset(pRoot , 0, sizeof(BTNODE));
        pRoot->Data = Data;
        pRoot->pParent = pParent;
        CreateBiTree2(pRoot->pLNext , pRoot);
        CreateBiTree2(pRoot->pRNext , pRoot);
        
    }
}