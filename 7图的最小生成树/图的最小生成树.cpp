#include <stdio.h>
#include <windows.h>


#define MAX 6

typedef struct tagNODE{
    int iFrom;
    int iTo;
    bool bFlag;
    int iValue;
    tagNODE* pNext;
}NODE,*PNODE;

PNODE g_pHead = NULL;
PNODE g_pTail = NULL;


void InsertList(int iFrom , int iTo , int iValue);
void FreeList();
void MinTree();
PNODE FindMinCost();

int main()
{
    int iData[10][3] = {{1,2,6},{1,6,12},{1,5,10},{2,3,3},{2,4,5},{2,6,8},{3,4,7},{4,6,11},{4,5,9},{5,6,16}};
    
    PNODE pNodeNew = NULL;

    int i = 0, j = 1;

    for (i=0;i<10;++i)
    {
        for (j=1;j<=MAX ; ++ j)
        {
            if (iData[i][0] == j)
            {
                InsertList(iData[i][0],iData[i][1],iData[i][2]);
            }
        }
    }


    // 输出
    PNODE pNodeTemp = g_pHead;

    printf("打印图\n");
    while (pNodeTemp !=NULL)
    {
        printf("Start Pos:%d    End Pos:%d     ival:%d\n",pNodeTemp->iFrom,pNodeTemp->iTo,pNodeTemp->iValue);
        
        pNodeTemp = pNodeTemp->pNext;
	}


    printf("\n最小生成树\n");
    MinTree();
    
	FreeList();

    return 0;
}

void InsertList(int iFrom , int iTo , int iValue)
{
    if (g_pHead == NULL)
    {
        g_pHead = (PNODE)malloc(sizeof(NODE));
        g_pHead->iFrom = iFrom;
        g_pHead->iTo = iTo;
        g_pHead->iValue = iValue;
        g_pHead->bFlag = false;
        g_pHead->pNext = NULL;
        g_pTail = g_pHead;
    }
    else
    {
        g_pTail->pNext = (PNODE)malloc(sizeof(NODE));
        g_pTail = g_pTail->pNext;
        g_pTail->iFrom = iFrom;
        g_pTail->iTo = iTo;
        g_pTail->iValue = iValue;
        g_pTail->bFlag = false;
        g_pTail->pNext = NULL;
    }
}

void FreeList()
{
    PNODE pNodeTemp = g_pHead;
    while (pNodeTemp != NULL)
    {
        g_pHead = g_pHead->pNext;
        free(pNodeTemp);
        pNodeTemp = g_pHead;
    }

    g_pHead  = g_pTail = NULL;
}
void MinTree()
{
    PNODE pNodeTemp = g_pHead ;
    PNODE pNodeFind = NULL;

    int iResult = 0;
    int iArray[MAX+1] = {0};

    while (pNodeTemp != NULL)
    {
        pNodeFind = FindMinCost();
        iArray[pNodeFind->iFrom]++;
        iArray[pNodeFind->iTo]++;
        
        if (iArray[pNodeFind->iFrom] > 1 
            && iArray[pNodeFind->iTo] > 1)
        {
            iArray[pNodeFind->iFrom]--;
            iArray[pNodeFind->iTo]--;
            iResult = 1;
        }
        else
            iResult = 0;

        if(iResult == 0)
            printf("Start Pos:%d    End Pos:%d     ival:%d\n",
            pNodeFind->iFrom,pNodeFind->iTo,pNodeFind->iValue);
        pNodeTemp = pNodeTemp->pNext;
    }
}
PNODE FindMinCost()
{
    int iMinValue = 100;

    PNODE pNodeTemp = g_pHead;

    PNODE pNodePre = NULL;

    while(pNodeTemp != NULL)
    {
        if (pNodeTemp->iValue < iMinValue && !pNodeTemp->bFlag)
        {
            iMinValue = pNodeTemp->iValue;
            pNodePre = pNodeTemp;
        }
        pNodeTemp = pNodeTemp->pNext;
    }

    pNodePre->bFlag = true;

    return pNodePre;
}