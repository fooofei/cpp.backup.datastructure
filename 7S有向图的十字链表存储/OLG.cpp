#include <STDIO.H>
#include <WINDOWS.H>

#define  MAX_VERTEX_NUM 20
#define  MAX_INFO 20

// datetime:2012-9-18
// author:

// 注意 ： 有向图中叫弧 Arc  
//		无向图中叫 边 Edge
//		弧尾-》 弧头
// 无向的时候  两个端点保存的信息是一致的
// 这是我自己写 程序 对严蔚敏的程序代码加以优化 改进 封装为类

// 改进说明：在插入顶点的时候增加校验，已有数据不能插入。插入弧情况也校验.
//            加入计算每一个顶点的入度 出度 (计算有向图的出度入度很方便)
#define  QUEUESIZESTEP 3 // 队列长度每一步加和
#define  QUEUEDATA int  // 每次使用 需要更改的数据类型
class QUEUE
{
protected:
  
  int m_nBase;
  int m_nTop;
  int m_nQueueLen;
  int m_nQueueMAX;
  QUEUEDATA* m_pData;
public:
  
  BOOL InitQueue();
  BOOL EnQueue(QUEUEDATA Data);
  BOOL DeQueue(QUEUEDATA &Data);
  BOOL QueueIsEmpty();
  int GetQueueLen();
  BOOL DestroyQueue();
};

struct ArcNode
{
  int TailVex;
  int HeadVex;
  ArcNode* HeadLink;
  ArcNode* TailLink;
  VOID* pInfor;
}; 

struct VexNode
{
  CHAR Data;
  BOOL bVisited;
  ArcNode* pFirstInArc;
  ArcNode* pFirstOutArc;
};


class OLG
{
private:
  
  VexNode m_VexList[MAX_VERTEX_NUM];

  int m_iVexNum;
  int m_iArcNum;
  BOOL m_bContainInfor;
public:
  int LocateVex(CHAR v);
  BOOL CreateDG();
  BOOL CreateDGFromFile(LPCTSTR lpszFile);

  CHAR GetVex(int v);
  ArcNode* GetArc(CHAR v, CHAR w);
  BOOL PutVex(CHAR v, CHAR value);
  int FirstAdjVex(CHAR v);
  int NextAdjVex(CHAR v,CHAR w);

  BOOL InsertVex(CHAR v);
  BOOL DeleteVex(CHAR v);

  BOOL InsertArc(CHAR v, CHAR w);
  BOOL DeleteArc(CHAR v, CHAR w);


  BOOL Display();

  BOOL MakeVexUnVisited();
  BOOL DFS(int iv);
  BOOL DFSTraverse();
  BOOL BFSTraverse();

  BOOL DestroyGraph();

  int OutDegree(CHAR v);
  int InDegree(CHAR v);

  int GetVexNum();
  int GetArcNum();
};


int main(int argc,char** argv)
{

  OLG G;

  if (G.CreateDGFromFile("1.txt"))
  {
    printf("打印：\n");
    
    if (!G.Display())
    {
      printf("Error Display\n");
    }


    int i = 0;

    for (i=0;i<G.GetVexNum();++i)
    {
      printf("顶点%c的入度：%d 出度:%d \n",G.GetVex(i),G.InDegree(G.GetVex(i)),G.OutDegree(G.GetVex(i)));
    }
    
    //   printf("深度优先遍历:\n");
    // 
    //   G.DFSTraverse();
    // 
    //   printf("广度优先遍历:\n");
    // 
    //   G.BFSTraverse();
    
     G.DestroyGraph();

     printf("\n");
  }
 

 
  return 0;
}


int OLG::GetVexNum()
{
  return m_iVexNum;
}
int OLG::GetArcNum()
{
  return m_iArcNum;
}
int OLG::LocateVex(CHAR v)
{
  int i  = 0;

  for (i=0;i<m_iVexNum;++i)
  {
    if (m_VexList[i].Data==v)
    {
      return i;
    }
  }

  return -1;
}
BOOL OLG::CreateDG()
{
  printf("请输入有向图的顶点数,弧数,弧是否含其它信息(是:1，否:0):\n");

  scanf("%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  while (m_iArcNum>(m_iVexNum-1)*m_iVexNum)
  {
    printf("弧数应<=%d,重新输入.\n",(m_iVexNum-1)*m_iVexNum);

    scanf("%d",&m_iArcNum);
  }
  int i = 0;

  CHAR v = 0;
  for (i=0;i<m_iVexNum;++i)
  {
    scanf(" %c",&v);

    if (LocateVex(v)!=-1)
    {
      printf("数据重复，重新输入.\n");

      --i;

      continue;
    }

    m_VexList[i].Data = v;

    m_VexList[i].pFirstInArc = m_VexList[i].pFirstOutArc = NULL;
  }

  printf("输入%d 条弧的弧尾、弧头:\n",m_iArcNum);

  int k = 0;

  CHAR a,b;
  int ia,ib;

  ArcNode* pNodeNew = NULL;
    
  for (k=0;k<m_iArcNum;++k)
  {
    printf("输入%d的弧尾、弧头：\n",k+1);

    scanf(" %c",&a);
    scanf(" %c",&b);

    ia = LocateVex(a);
    ib = LocateVex(b);

    if (-1==ia ||-1==ib || ia==ib || GetArc(a,b))
    {
      printf("数据错误，重新输入其他值.\n");

      --k;

      continue;
    }

    if (NULL==(pNodeNew = (ArcNode*)malloc(sizeof(ArcNode))))
    {
      exit(0);
    }

    memset(pNodeNew,0,sizeof(ArcNode));

    // 一气呵成的赋值
    pNodeNew->TailVex = ia;
    pNodeNew->HeadVex = ib;
    pNodeNew->TailLink = m_VexList[ia].pFirstOutArc;
    pNodeNew->HeadLink = m_VexList[ib].pFirstInArc;
    m_VexList[ia].pFirstOutArc = m_VexList[ib].pFirstInArc;

    if (m_bContainInfor)
    {
      printf("输入%c→%c的信息：",a,b);

      CHAR pszBuffer[MAX_INFO];

      memset(pszBuffer,0,MAX_INFO);

      scanf("%s",pszBuffer);

      int nBufferLen = strlen(pszBuffer);

      if (nBufferLen)
      {
        if (!( pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1))))
        {
          exit(0);
        }

        memset(pNodeNew->pInfor,0,sizeof(CHAR)*(nBufferLen+1));

        memcpy(pNodeNew->pInfor,pszBuffer,sizeof(CHAR)*nBufferLen);
      }
    }


  }


  return TRUE;
}
BOOL OLG::CreateDGFromFile(LPCTSTR lpszFile)
{
  FILE* fp = NULL;

  if (NULL==(fp=fopen(lpszFile,"r")))
  {
    return FALSE;
  }

    fscanf(fp,"%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  if (m_iArcNum>(m_iVexNum-1)*m_iVexNum)
  {
    exit(0);
  }
  int i = 0;

  CHAR v = 0;
  for (i=0;i<m_iVexNum;++i)
  {
    fscanf(fp,"%s",&v);

    if (LocateVex(v)!=-1)
    {
      --m_iArcNum;

      --i;

      continue;
    }

    m_VexList[i].Data = v;

    m_VexList[i].pFirstInArc = m_VexList[i].pFirstOutArc = NULL;
  }

  int k = 0;

  CHAR a,b;
  int ia,ib;

  ArcNode* pNodeNew = NULL;
    
  for (k=0;k<m_iArcNum;++k)
  {

    fscanf(fp,"%s",&a);
    fscanf(fp,"%s",&b);

    ia = LocateVex(a);
    ib = LocateVex(b);

    if (-1==ia ||-1==ib || ia==ib) // 别忘了判断弧
    {
      --m_iArcNum;

      --k;

      continue;
    }

    if (NULL==(pNodeNew = (ArcNode*)malloc(sizeof(ArcNode))))
    {
      exit(0);
    }

    memset(pNodeNew,0,sizeof(ArcNode));

    // 一气呵成的赋值
    pNodeNew->TailVex = ia;
    pNodeNew->HeadVex = ib;
    pNodeNew->TailLink = m_VexList[ia].pFirstOutArc;
    pNodeNew->HeadLink = m_VexList[ib].pFirstInArc;
    m_VexList[ia].pFirstOutArc = m_VexList[ib].pFirstInArc = pNodeNew;

    if (m_bContainInfor)
    {

      CHAR pszBuffer[MAX_INFO];

      memset(pszBuffer,0,MAX_INFO);

      fscanf(fp,"%s",pszBuffer);

      int nBufferLen = strlen(pszBuffer);

      if (nBufferLen)
      {
        if (!( pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1))))
        {
          exit(0);
        }

        memset(pNodeNew->pInfor,0,sizeof(CHAR)*(nBufferLen+1));

        memcpy(pNodeNew->pInfor,pszBuffer,sizeof(CHAR)*nBufferLen);
      }
    }


  }

  fclose(fp);

  return TRUE;
}

BOOL OLG::DestroyGraph()
{
   int i = 0;
   ArcNode* pNodeTemp = NULL;

   ArcNode* pNodePre = NULL;

   for (i=0;i<m_iVexNum;++i)
   {
     pNodeTemp = m_VexList[i].pFirstOutArc;

     while (pNodeTemp)
     {
       pNodePre = pNodeTemp;

       pNodeTemp = pNodeTemp->TailLink;

       if (pNodePre->pInfor)
       {
         free(pNodePre->pInfor);
       }

       free(pNodePre);
     }

   }

   m_iVexNum = 0;

   m_iArcNum = 0;

   return TRUE;
}
CHAR OLG::GetVex(int v)
{
  if (v<0||v>=m_iVexNum)
  {
    exit(0);
  }

  return m_VexList[v].Data;
}
BOOL OLG::PutVex(CHAR v, CHAR value)
{
  int i = LocateVex(v);

  if (i==-1)
  {
    return FALSE;
  }

  m_VexList[i].Data = value;

  return TRUE;
}
int OLG::FirstAdjVex(CHAR v) // 以出弧为出发点 然后寻找下一个弧的HeadVex
{
  int iv = LocateVex(v);

  if (iv==-1)
  {
    return -1;
  }

  ArcNode* pNodeTemp = m_VexList[iv].pFirstOutArc;

  if (pNodeTemp)
  {
    return pNodeTemp->HeadVex;
  }
  
   return -1;

}
int OLG::NextAdjVex(CHAR v,CHAR w)
{
  int iv = LocateVex(v);
  int iw = LocateVex(w);

  if (-1==iv||-1==iw||iw==iv)
  {
    return -1;
  }

  ArcNode* pNodeTemp = m_VexList[iv].pFirstOutArc;

  while (pNodeTemp&&pNodeTemp->HeadVex!=iw)
  {
    pNodeTemp = pNodeTemp->TailLink;
  }

  if (pNodeTemp&&pNodeTemp->TailLink)
  {
    return pNodeTemp->TailLink->HeadVex;
  }

  return -1;
}

BOOL OLG::InsertVex(CHAR v)
{
  if (m_iVexNum>=MAX_VERTEX_NUM || LocateVex(v)!=-1)
  {
    return FALSE;
  }

  m_VexList[m_iVexNum].Data = v;
  m_VexList[m_iVexNum].pFirstInArc = m_VexList[m_iVexNum].pFirstOutArc = NULL;

  ++m_iVexNum;

  return TRUE;
}
BOOL OLG::DeleteVex(CHAR v)
{
  // 一会改进   能不能直接使用DeleteArc就解决

  int iv = LocateVex(v);
  if (iv==-1)
  {
    return FALSE;
  }

  ArcNode * pNodePre = NULL;

  ArcNode* pNodeTemp = NULL;

  int i = 0;
// 以下删除顶点v的出弧
  for (i=0;i<m_iVexNum;++i)// 顶点v的出弧是其它顶点的入弧
  {
    if (i==iv)
    {
      continue;
    }

    pNodeTemp = m_VexList[i].pFirstInArc;

    while (pNodeTemp)
    {
      if (pNodeTemp->TailVex==iv&&pNodeTemp==m_VexList[i].pFirstInArc)// 待删结点为首结点 
      {
        m_VexList[i].pFirstInArc = pNodeTemp->HeadLink;

        break;
      }
      else if (pNodeTemp->TailVex!=iv) // 不是要删除的结点
      {
        pNodePre = pNodeTemp;

        pNodeTemp = pNodeTemp->HeadLink;
      }
      else // 找到了要删除的结点  而且不是首结点
      {
        pNodePre->HeadLink = pNodeTemp->HeadLink;

        break;
      }
    }
  }

  pNodeTemp = m_VexList[iv].pFirstOutArc;// 删除与顶点v有关的出弧

  while (pNodeTemp)
  {
    pNodePre = pNodeTemp->TailLink;

    if (pNodeTemp->pInfor)
    {
      free(pNodeTemp->pInfor);
    }

    free(pNodeTemp);

    --m_iArcNum;

    pNodeTemp = pNodePre;
  }



  // 以下删除顶点v的入弧


  for (i=0;i<m_iVexNum;++i)
  {
    if (i==iv)
    {
      continue;
    }

    pNodeTemp = m_VexList[i].pFirstOutArc;

    while (pNodeTemp)
    {
      if (pNodeTemp->HeadVex==iv&&pNodeTemp==m_VexList[i].pFirstOutArc)
      {
        m_VexList[i].pFirstOutArc = pNodeTemp->TailLink;

        break;
      }
      else if (pNodeTemp->HeadVex!=iv) // 没找到
      {
        pNodePre = pNodeTemp;

        pNodeTemp = pNodeTemp->TailLink;
      }
      else
      {
        pNodePre->TailLink = pNodeTemp->TailLink;

        break;
      }
    }
  }

  //  删除与顶点v有关的入弧

  pNodeTemp = m_VexList[iv].pFirstInArc;

  while (pNodeTemp)
  {
    pNodePre = pNodeTemp->HeadLink;

    if (pNodeTemp->pInfor)
    {
      free(pNodeTemp->pInfor);
    }

    free(pNodeTemp);

    --m_iArcNum;

    pNodeTemp = pNodePre;
  }

  // 顶点序列前移

  for (i = iv+1;i<m_iVexNum;++i)
  {
    m_VexList[i-1] = m_VexList[i];
  }

  --m_iVexNum;
  //结点序号>iv的要减1

  for (i=0;i<m_iVexNum;++i)
  {
    pNodeTemp = m_VexList[i].pFirstOutArc;// 处理出弧

    while (pNodeTemp)
    {
      if (pNodeTemp->HeadVex>iv)
      {
        --pNodeTemp->HeadVex;
      }

      if (pNodeTemp->TailVex>iv)
      {
        --pNodeTemp->TailVex;
      }

      pNodeTemp = pNodeTemp->TailLink;
    }
  }


  return TRUE;
}

BOOL OLG::InsertArc(CHAR v, CHAR w)
{
  int iv = LocateVex(v);
  int iw = LocateVex(w);

  if (-1==iv||-1==iw||iw==iv ||GetArc(v,w))
  {
    return FALSE;
  }
  CHAR pszBuffer[MAX_INFO];
  memset(pszBuffer,0,MAX_INFO);

  ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));

  if (!pNodeNew)
  {
    exit(0);
  }

  memset(pNodeNew,0,sizeof(ArcNode));

  pNodeNew->TailVex = iv;
  pNodeNew->HeadVex = iw;
  pNodeNew->TailLink = m_VexList[iv].pFirstOutArc;
  pNodeNew->HeadLink = m_VexList[iw].pFirstInArc;
  m_VexList[iv].pFirstOutArc = m_VexList[iw].pFirstInArc = pNodeNew;

  ++m_iArcNum;

  if (m_bContainInfor)
  {
    printf("输入%c→%c的信息:",v,w);

    scanf("%s",pszBuffer);
    if (!(pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(1+strlen(pszBuffer)))))
    {
      exit(0);
    }

    memset(pNodeNew->pInfor ,0,sizeof(CHAR)*(1+strlen(pszBuffer)));

    memcpy(pNodeNew->pInfor,pszBuffer,sizeof(CHAR)*strlen(pszBuffer));
  }

  return TRUE;
}
ArcNode* OLG::GetArc(CHAR v, CHAR w)
{
  int iv= LocateVex(v);
  int iw = LocateVex(w);
  
  if (-1==iv ||-1==iw ||iv==iw)
  {
    return NULL;
  }
  
  ArcNode* pNodeTemp = m_VexList[iv].pFirstOutArc;
  
  if (pNodeTemp&&pNodeTemp->HeadVex==iw)
  {
    return pNodeTemp;
  }
  else
  {
    while (pNodeTemp&&pNodeTemp->HeadVex!=iw)
    {
      
      pNodeTemp = pNodeTemp->TailLink;
    }
    
    if (pNodeTemp)
    {
      return pNodeTemp;
    }
  }
  
 return NULL;
}
BOOL OLG::DeleteArc(CHAR v, CHAR w)
{
  int iv= LocateVex(v);
  int iw = LocateVex(w);

  if (-1==iv ||-1==iw ||iv==iw)
  {
    return FALSE;
  }

  ArcNode* pNodeTemp = m_VexList[iv].pFirstOutArc;

  ArcNode* pNodePre = NULL;

  if (pNodeTemp&&pNodeTemp->HeadVex==iw)
  {
    m_VexList[iv].pFirstOutArc = pNodeTemp->TailLink;
  }
  else
  {
    while (pNodeTemp&&pNodeTemp->HeadVex!=iw)
    {
      pNodePre = pNodeTemp;

      pNodeTemp = pNodeTemp->TailLink;
    }

    if (pNodeTemp)
    {
      pNodePre->TailLink = pNodeTemp->TailLink;
    }
  }

  // 开始删除弧

  pNodeTemp = m_VexList[iw].pFirstInArc;

  if (pNodeTemp&&pNodeTemp->TailVex==iv)
  {
    m_VexList[iw].pFirstInArc = pNodeTemp->HeadLink;
  }

  else
  {
    while (pNodeTemp&&pNodeTemp->TailVex!=iv)
    {
      pNodePre = pNodeTemp;

      pNodeTemp = pNodeTemp->HeadLink;
    }

    if (pNodeTemp)
    {
      pNodePre->HeadLink = pNodeTemp->HeadLink;
    }
  }

  if (pNodeTemp->pInfor)
  {
    free(pNodeTemp->pInfor);
  }

  free(pNodeTemp);

  --m_iArcNum;

  return TRUE;
}


BOOL OLG::Display()
{
  printf("%d个顶点%d条弧的有向图.\n",m_iVexNum,m_iArcNum);

  int i = 0;

  ArcNode* pNodeTemp = NULL;

  for (i=0;i<m_iVexNum;++i)
  {
    printf("顶点%c:入度:",GetVex(i));

    pNodeTemp = m_VexList[i].pFirstInArc;

    if (!pNodeTemp)
    {
      printf("无 ");
    }

    while (pNodeTemp)
    {
      printf("%c→%c ",GetVex(pNodeTemp->TailVex),GetVex(i));

      if (pNodeTemp->pInfor)
      {
        printf("弧信息:%s  ",pNodeTemp->pInfor);
      }
      pNodeTemp = pNodeTemp->HeadLink;
    }

    printf("出度: ");

    pNodeTemp = m_VexList[i].pFirstOutArc;

    if (!pNodeTemp)
    {
      printf("无 ");
    }

    while (pNodeTemp)
    {
      printf("%c→%c ",GetVex(i),GetVex(pNodeTemp->HeadVex));

      if (pNodeTemp->pInfor)
      {
        printf("弧信息:%s  ",pNodeTemp->pInfor);
      }

      pNodeTemp = pNodeTemp->TailLink;
    }

    printf("\n");
  }

  return TRUE;
}

BOOL OLG::MakeVexUnVisited()
{
  int i = 0;
  for (i=0;i<m_iVexNum;++i)
  {
    m_VexList[i].bVisited = FALSE;
  }

  return TRUE;
}
BOOL OLG::DFS(int iv)
{
  if(iv<0||iv>=m_iVexNum)
  {
    return FALSE;
  }

  CHAR v = GetVex(iv);

  m_VexList[iv].bVisited = TRUE;

  printf("%c ",v);

  ArcNode* pNodeTemp = m_VexList[iv].pFirstOutArc;

  while (pNodeTemp&&m_VexList[pNodeTemp->HeadVex].bVisited)// 没到表尾且该弧的头顶点已被访问 
  {
    pNodeTemp = pNodeTemp->TailLink;
  }

  if (pNodeTemp&&!m_VexList[pNodeTemp->HeadVex].bVisited)
  {
    DFS(pNodeTemp->HeadVex);
  }
  return TRUE;
}
BOOL OLG::DFSTraverse()
{
  int i = 0;

  MakeVexUnVisited();

  for(i=0;i<m_iVexNum;++i)
  {
    if (!m_VexList[i].bVisited)
    {
      if (!DFS(i))
      {
        return FALSE;
      }
      
    }
  }

  printf("\n");
  return TRUE;
}
BOOL OLG::BFSTraverse()
{
  CHAR v  = 0;
  CHAR w = 0;

  MakeVexUnVisited();

  QUEUE Q;

  Q.InitQueue();


  int i = 0; int j = 0; int k = 0;

  for (i=0;i<m_iVexNum;++i)
  {
    if (!m_VexList[i].bVisited)
    {
      m_VexList[i].bVisited = TRUE;

      printf("%c ",GetVex(i));

      Q.EnQueue(i);

      while (!Q.QueueIsEmpty())
      {
        Q.DeQueue(j);

        for (k=FirstAdjVex(GetVex(j));k>=0;k=NextAdjVex(GetVex(j),GetVex(k)))
        {
          if (!m_VexList[k].bVisited)
          {
            m_VexList[k].bVisited = TRUE;

            printf("%c ",GetVex(k));

            Q.EnQueue(k);
          }
        }
      }
    }
  }
  Q.DestroyQueue();

  printf("\n");
  return TRUE;
}

int OLG::OutDegree(CHAR v)
{
  int iv = LocateVex(v);

  if (iv==-1)
  {
    return -1;
  }
  int iDegree = 0;

  ArcNode* pNodeTemp = m_VexList[iv].pFirstOutArc;

  while (pNodeTemp)
  {
    ++iDegree;

    pNodeTemp = pNodeTemp->TailLink;
  }

  return iDegree;

}
int OLG::InDegree(CHAR v)
{
  int iv = LocateVex(v);
  
  if (iv==-1)
  {
    return -1;
  }
  int iDegree = 0;
  
  ArcNode* pNodeTemp = m_VexList[iv].pFirstInArc;

  while (pNodeTemp)
  {
    ++iDegree;
    pNodeTemp = pNodeTemp->HeadLink;
  }
  
  return iDegree;
}

BOOL QUEUE::InitQueue()
{
  
  if (NULL==(m_pData = (QUEUEDATA*)malloc(sizeof(QUEUEDATA)*QUEUESIZESTEP)))
  {
    return FALSE;
  }
  
  memset(m_pData,0,sizeof(QUEUEDATA)*QUEUESIZESTEP);
  
  m_nTop = m_nBase = m_nQueueLen = 0;
  
  m_nQueueMAX = QUEUESIZESTEP;
  
  return TRUE;
}
BOOL QUEUE::EnQueue(QUEUEDATA Data)
{
  if (m_nTop==m_nQueueMAX-1)
  {
    
    if (NULL==(m_pData = (QUEUEDATA*)realloc(m_pData,sizeof(QUEUEDATA)*(m_nQueueMAX+QUEUESIZESTEP))))
    {
      return FALSE;
    }
    
    memset(&m_pData[m_nQueueMAX],0,sizeof(QUEUEDATA)*QUEUESIZESTEP);
    
    m_nQueueMAX += QUEUESIZESTEP;
  }
  
  m_pData[m_nTop++] = Data;
  
  ++m_nQueueLen;
  
  return TRUE;
}
BOOL QUEUE::DeQueue(QUEUEDATA &Data)
{
  if (QueueIsEmpty())
  {
    Data = *(QUEUEDATA*)0;  // 这里可能需要更改  
    
    return FALSE;
  }
  
  Data = m_pData[m_nBase++];
  
  --m_nQueueLen;
  
  return TRUE;
}
BOOL QUEUE::QueueIsEmpty()
{
  if (m_nBase==m_nTop)
  {
    return TRUE;
  }
  
  return FALSE;
}
int QUEUE::GetQueueLen()
{
  return m_nQueueLen;
}
BOOL QUEUE::DestroyQueue()
{
  if (NULL==m_pData)
  {
    return FALSE;
  }
  
  free(m_pData);
  
  m_pData = NULL;
  
  m_nTop = m_nBase = m_nQueueMAX = 0 ;
  
  m_nQueueLen = -1;
  
  return TRUE;
}
