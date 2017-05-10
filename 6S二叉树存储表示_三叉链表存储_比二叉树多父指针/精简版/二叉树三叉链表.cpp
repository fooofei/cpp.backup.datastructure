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

// ���д���
void CreateBiTree(PBTNODE &pRoot,PBTNODE pParent);
void CreateBiTreeFromFile(PBTNODE &pRoot,PBTNODE pParent , FILE* fp);


// �ݹ鴴��
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

// ���д�����������
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


// ����  ��Ϊ �ļ�
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


void PreOrderTraverse2(PBTNODE pRoot)// �Ƽ� ������������ �ü���
{
    if(pRoot == NULL )
        return;
    
    stack<PBTNODE> s;
    // ����ջ
    s.push(pRoot);
    
    // ѭ��ջ����
    while(!s.empty())
    {
        // ��ջ��Ҫ������������...Orz...
        // ȡ������ ���
        pRoot = s.top();
        s.pop();
        printf("%c ",pRoot->Data );
        
        // �����Һ��� �Һ�����ջ �������� ������ջ
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