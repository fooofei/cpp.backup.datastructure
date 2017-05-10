#include <STDIO.H>
#include <WINDOWS.H>

// ע�� �� ����ͼ�нл� Arc  
//		����ͼ�н� �� Edge
//		��β-�� ��ͷ
// �����ʱ��  �����˵㱣�����Ϣ��һ�µ�
// �������Լ�д ���� ����ε���ĳ����������Ż� �Ľ� ��װΪ��

#define  MAX_VERTEX_NUM 20
#define  MAX_INFO   20
#define  QUEUESIZESTEP 3 // ���г���ÿһ���Ӻ�
#define  QUEUEDATA int  // ÿ��ʹ�� ��Ҫ���ĵ���������
typedef enum{DG,DN,UDG,UDN}GraphKind; // ����ͼ ������  ����ͼ ������
struct ArcNode
{
  int iAdjVex; // ������һ���˵������
  int iWeight; // ��������һ��Ȩֵ
  ArcNode* pNextArc;
  VOID* pInfor;
};

struct VexNode
{
  CHAR Data;
  BOOL	bVisit;// ÿһ�����㶼��һ��
  ArcNode* pFirstArc;
};

class ALG
{
protected:
  VexNode m_Vertices[MAX_VERTEX_NUM];  
  int     m_iVexNum;
  int     m_iArcNum;
  GraphKind m_GraphKind;
  BOOL    m_bContainInfor;
public:

  int     LocateVex(CHAR u);
  ArcNode* GetArc(CHAR v,CHAR w); // �Լ����ӵĺ���  �õ�������֮��Ļ� Ŀ����Ϊ�������뻡��ʱ�����ж�
  BOOL    CreateGraph();
  BOOL CreateDG();
  BOOL CreateDGFromFile(LPCTSTR lpszFile);
  BOOL CreateDN();
  BOOL CreateDNFromFile(LPCTSTR lpszFile);
  BOOL CreateUDG();
  BOOL CreateUDGFromFile(LPCTSTR lpszFile);
  BOOL CreateUDN();
  BOOL CreateUDNFromFile(LPCTSTR lpszFile);
  BOOL    DestroyGraph();
  CHAR    GetVex(int v);
  BOOL    PutVex(CHAR v, CHAR value);
  int     FirstAdjVex(CHAR v);
  int     NextAdjVex(CHAR v,CHAR w);
  BOOL    InsertVex(CHAR v);
  BOOL    DeleteVex(CHAR v);
  BOOL    InsertArc(CHAR v,CHAR w);
  BOOL    DeleteArc(CHAR v,CHAR w);
  BOOL    DFS(int v);
  BOOL    DFSTraverse();
  BOOL    BFSTraverse();
  BOOL    Display();

  int     GetVexDegree(CHAR v); // ������ͼ������ͼ�еõ�����v �Ķ�
  int     GetVexOutDegree(CHAR v); // ������ͼ�еõ�����
  int     GetVexInDegree(CHAR v);// ������ͼ�еõ����
};


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


int main(int argc, char* argv)
{

  ALG G;

  G.CreateDGFromFile("2.txt");

  printf("��ӡ��\n");
  G.Display();

  printf("������ȱ���\n");
  G.BFSTraverse();

  printf("������ȱ���\n");
  G.DFSTraverse();

  printf("����:%d ���:%d ��:%d \n",G.GetVexOutDegree(G.GetVex(1)),G.GetVexInDegree(G.GetVex(1)),G.GetVexDegree(G.GetVex(1)));
  G.DestroyGraph();
  
  return 0;
}


int     ALG::LocateVex(CHAR u)
{
    int i = 0;

    for (i=0;i<m_iVexNum;++i)
    {
      if (m_Vertices[i].Data==u)
      {
        return i;
      }
    }

    return -1;
}
BOOL    ALG::CreateGraph()
{
  printf("����ͼ����(0:����ͼ 1:������ 2:����ͼ 3:������)\n");

  scanf("%d",&m_GraphKind);

  switch(m_GraphKind)
  {
  case DG:
    {

      return CreateDG();
    }
  case DN:
    {
      return CreateDN();
    }
  case UDG:
    {
      return CreateUDG();
    }
  case UDN:
    {
      return CreateUDN();
    }
  }
 
  // ������ε�����Ϸ�����  ���Լ��Ż�����
//   printf("���붥����Ŀ������Ŀ\n");
//   
//   scanf("%d",&m_iVexNum);
//   scanf("%d",&m_iArcNum);
// 
//   printf("��������%d����\n",m_iVexNum);
// 
//   int i = 0;
// 
//   for (i=0;i<m_iVexNum;++i)
//   {
//     scanf(" %c",&m_Vertices[i].Data);
// 
//     m_Vertices[i].pFirstArc = NULL;
//   }
// 
//   if (m_GraphKind==UDN || m_GraphKind== DN)
//   {
//     printf("���뻡��Ȩֵ����β����ͷ\n");
//   }
//   else
//   {
//     printf("���뻡�Ļ�β����ͷ\n");
//   }
// 
//   int k = 0 , j =0;
// 
//   int Weight = 0;
// 
//   CHAR a,b;
//   for (k=0;k<m_iArcNum;++k)
//   {
//     if (m_GraphKind==UDN || m_GraphKind==DN)
//     {
//       printf("%d��Ȩֵ����β����ͷ\n",k+1);
// 
//       scanf("%d",&Weight);
//       scanf(" %c",&a);
//       scanf(" %c",&b);
//     }
//     else
//     {
//       printf("%d�Ļ�β����ͷ\n",k+1);
//       scanf(" %c",&a);
//       scanf(" %c",&b);
//     }
// 
//     i = LocateVex(a);
//     j = LocateVex(b);
// 
//     if (i==-1 || j==-1 ||j==i)
//     {
//       printf("�������,��������\n");
// 
//       --k;
//       continue;
//     }
// 
//     ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));
// 
//     if (!pNodeNew)
//     {
//       printf("Error Memory\n");
//       exit(0);
//     }
// 
//     memset(pNodeNew,0,sizeof(ArcNode));
// 
//     pNodeNew->iAdjVex = j;
// 
//     if (m_GraphKind==UDN || m_GraphKind==DN)
//     {
//       pNodeNew->iWeight = Weight;
//     }
// 
//     printf("�Ƿ�����Ϣ(0:���� 1:����)\n");
// 
//     scanf("%d",&m_bContainInfor);
// 
//     if (m_bContainInfor)
//     {
//       printf("��������Ϣ\n");
// 
//       CHAR pszBuffer[20]; // ��ֻ������20 �ֽ�
// 
//       memset(pszBuffer,0,20);
// 
//       scanf("%s",pszBuffer);
// 
//       int nLen = strlen(pszBuffer);
// 
//       if (nLen)
//       {
//         pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nLen+1));
// 
//         if (!pNodeNew->pInfor)
//         {
//           printf("Error Memory\n");
// 
//           exit(0);
//         }
// 
//         memset(pNodeNew->pInfor,0,sizeof(CHAR)*(nLen+1));
// 
//         memcpy(pNodeNew->pInfor,pszBuffer,nLen);
//       }
//     }
//     else
//     {
//       pNodeNew->pInfor =NULL;
//     }
// 
//     pNodeNew->pNextArc = m_Vertices[i].pFirstArc;
// 
//     m_Vertices[i].pFirstArc = pNodeNew;
//     
//     // ����ͼ����,�����ڶ�������
// 
//     if(m_GraphKind==UDN ||m_GraphKind==UDG)
//     {
//       pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));
// 
//       if (!pNodeNew)
//       {
//         printf("Error Memory\n");
// 
//         exit(0);
//       }
// 
//       memset(pNodeNew,0,sizeof(pNodeNew));
// 
//       pNodeNew->iAdjVex = i;
// 
//       if (m_GraphKind==UDN) // �� ��Ȩֵ
//       {
//         pNodeNew->iWeight = Weight;
//       }
// 
//       pNodeNew->pNextArc = m_Vertices[j].pFirstArc;
// 
//       m_Vertices[j].pFirstArc = pNodeNew;
//     }
//     
//   } 
//
// return TRUE;
}

BOOL ALG::CreateDG() // ����ͼ
{
    m_GraphKind = DG;
  printf("��������ͼ�Ķ�����Ŀ������Ŀ�����Ƿ�����Ϣ(0:�� 1:��)\n");

  scanf("%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  while(m_iArcNum>m_iVexNum*(m_iVexNum-1))
  {
    printf("���뻡��Ӧ<=%d,��������.\n",m_iVexNum*(m_iVexNum-1));

    scanf("%d",&m_iArcNum);
  }

  printf("��������%d������\n",m_iVexNum);

  int i = 0;

  CHAR v;
  for (i=0;i<m_iVexNum;++i) // Ҫ���жϵ� ��Ȼ �������� Ҳ��֪�������Ƿ��Ѿ�����
  {
    scanf(" %c",&v);

    if (LocateVex(v)!=-1)
    {
      printf("�Ѿ����ڸ�����,��������.\n");
      --i;
      continue;
    }
    else
    {
      m_Vertices[i].Data = v;
      
      m_Vertices[i].pFirstArc = NULL;
    }
    
  }

  CHAR a,b;

  int k = 0;

  int ia,ib;

  for (k=0;k<m_iArcNum;++k) // ����ж�һ�����Ƿ������ �������� ��������ܶ� 
  {
    printf("����%d�Ļ�β����ͷ\n",k+1);

    scanf(" %c %c",&a,&b);

    ia = LocateVex(a);

    ib = LocateVex(b);

    if (ia==-1 ||ib==-1 ||ia==ib ||GetArc(a,b))
    {
      printf("����������������\n");

      --k;

      continue;
    }

    ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));

    if (!pNodeNew)
    {
      printf("Error Memory\n");

      exit(0);
    }


    memset(pNodeNew,0,sizeof(ArcNode));

    pNodeNew->iAdjVex = ib;
   
    if (m_bContainInfor)
    {
      printf("��������Ϣ\n");

      CHAR pszBuffer[MAX_INFO];

      memset(pszBuffer,0,MAX_INFO);

      scanf("%s",pszBuffer);

      int nBufferLen = strlen(pszBuffer);

      if (nBufferLen)
      {
        pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1));

        if (!pNodeNew->pInfor)
        {
          printf("Error Memory\n");

          exit(0);
        }

        memset(pNodeNew->pInfor,0,sizeof(CHAR)*(nBufferLen+1));

        memcpy(pNodeNew->pInfor,pszBuffer,sizeof(CHAR)*nBufferLen);
      }
    }
 

    pNodeNew->pNextArc = m_Vertices[ia].pFirstArc;
    
    m_Vertices[ia].pFirstArc = pNodeNew;
  }
  

  return TRUE;
}
BOOL ALG::CreateDGFromFile(LPCTSTR lpszFile)
{
    m_GraphKind = DG;
  FILE* fp = NULL;

  if (NULL==(fp = fopen(lpszFile,"r")))
  {
    return FALSE;
  }
  
  fscanf(fp,"%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  if(m_iArcNum>m_iVexNum*(m_iVexNum-1))
  {
    exit(0);
  }
  
  int i = 0;
  
  CHAR v;
  for (i=0;i<m_iVexNum;++i) // Ҫ���жϵ� ��Ȼ �������� Ҳ��֪�������Ƿ��Ѿ�����
  {
    fscanf(fp,"%s",&v);
    
    if (LocateVex(v)!=-1)
    {
      --m_iVexNum;
      --i;
      continue;
    }
    else
    {
      m_Vertices[i].Data = v;
      
      m_Vertices[i].pFirstArc = NULL;
    }
    
  }
  CHAR a,b;
  
  int k = 0;
  
  int ia,ib;
  
  for (k=0;k<m_iArcNum;++k)
  {
    
    fscanf(fp,"%s%s",&a,&b);
    
    ia = LocateVex(a);
    
    ib = LocateVex(b);
    
    if (ia==-1 ||ib==-1 ||ia==ib  ||GetArc(a,b))
    {
      --k;

      --m_iArcNum; // �������� ���� �� �Ҿ���Ӧ��-1
      
      continue;
    }
    
    ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));
    
    if (!pNodeNew)
    {
      
      exit(0);
    }
    
    
    memset(pNodeNew,0,sizeof(ArcNode));
    
    pNodeNew->iAdjVex = ib;
    
    if (m_bContainInfor)
    {
      
      CHAR pszBuffer[MAX_INFO];
      
      memset(pszBuffer,0,MAX_INFO);
      
      fscanf(fp,"%s",pszBuffer);
      
      int nBufferLen = strlen(pszBuffer);
      
      if (nBufferLen)
      {
        pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1));
        
        if (!pNodeNew->pInfor)
        {
          
          exit(0);
        }
        
        memset(pNodeNew->pInfor,0,sizeof(CHAR)*(nBufferLen+1));
        
        memcpy(pNodeNew->pInfor,pszBuffer,sizeof(CHAR)*nBufferLen);
      }
    }
    pNodeNew->pNextArc = m_Vertices[ia].pFirstArc;
    
    m_Vertices[ia].pFirstArc = pNodeNew;
  }
  
  fclose(fp);

  return TRUE;
}
BOOL ALG::CreateDN() // ������
{

    m_GraphKind = DN;
  printf("�����������Ķ�����Ŀ������Ŀ�����Ƿ�����Ϣ(0:�� 1:��)\n");

  scanf("%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  while(m_iArcNum>m_iVexNum*(m_iVexNum-1))
  {
    printf("���뻡��Ӧ<=%d,��������.\n",m_iVexNum*(m_iVexNum-1));
    
    scanf("%d",&m_iArcNum);
  }

  printf("��������%d������\n",m_iVexNum);

  int i =0;
  CHAR v;
  for (i=0;i<m_iVexNum;++i) // Ҫ���жϵ� ��Ȼ �������� Ҳ��֪�������Ƿ��Ѿ�����
  {
    scanf(" %c",&v);
    
    if (LocateVex(v)!=-1)
    {
      printf("�Ѿ����ڸ�����,��������.\n");
      --i;
      continue;
    }
    else
    {
      m_Vertices[i].Data = v;
      
      m_Vertices[i].pFirstArc = NULL;
    }
    
  }
  int Weight = 0;

  CHAR a,b;

  int ia,ib;

  int k =0;

  for (k=0;k<m_iArcNum;++k)
  {
    printf("���뻡β����ͷ��Ȩֵ:\n");

    scanf(" %c %c%d",&a,&b,&Weight);

    ia = LocateVex(a);

    ib = LocateVex(b);

    if (-1==ia ||-1==ib || ia==ib  ||GetArc(a,b))
    {
      printf("��������,����������\n");

      --k;

      continue;
    }
  
    ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));

    if (!pNodeNew)
    {
      exit(0);
    }

    memset(pNodeNew,0,sizeof(ArcNode));

    pNodeNew->iAdjVex = ib;

    pNodeNew->iWeight = Weight;

    pNodeNew->pNextArc = m_Vertices[ia].pFirstArc;

    m_Vertices[ia].pFirstArc = pNodeNew;

    if (m_bContainInfor)
    {
      CHAR pszBuffer[MAX_INFO];

      memset(pszBuffer,0,MAX_INFO);

      printf("������û���Ϣ:");

      scanf("%s",pszBuffer);

      int nBufferLen = strlen(pszBuffer);

      if (nBufferLen)
      {
        pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1));

        if (!pNodeNew->pInfor)
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
BOOL ALG::CreateDNFromFile(LPCTSTR lpszFile)
{
   m_GraphKind = DN;
  FILE* fp = NULL;

  if ((NULL==(fp = fopen(lpszFile,"r"))))
  {
    return FALSE;
  }

  
  fscanf(fp,"%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  if(m_iArcNum>m_iVexNum*(m_iVexNum-1))
  {
    exit(0);
  }
  
  int i =0;
  CHAR v;
  for (i=0;i<m_iVexNum;++i) // Ҫ���жϵ� ��Ȼ �������� Ҳ��֪�������Ƿ��Ѿ�����
  {
    fscanf(fp,"%s",&v);
    
    if (LocateVex(v)!=-1)
    {
      --m_iVexNum;
      --i;
      continue;
    }
    else
    {
      m_Vertices[i].Data = v;
      
      m_Vertices[i].pFirstArc = NULL;
    }
    
  }

  
  int Weight = 0;
  
  CHAR a,b;
  
  int ia,ib;
  
  int k =0;
  
  for (k=0;k<m_iArcNum;++k)
  {
   
    fscanf(fp,"%s%s%d",&a,&b,&Weight);
    
    ia = LocateVex(a);
    
    ib = LocateVex(b);
    
    if (-1==ia ||-1==ib || ia==ib  ||GetArc(a,b))
    {
      
      --k;

      --m_iArcNum; // ��������  ���ǵĻ���-1  ��Ȼ ���еĻ���Ŀ�ͶԲ�����
      
      continue;
    }
    
    ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));
    
    if (!pNodeNew)
    {
      exit(0);
    }
    
    memset(pNodeNew,0,sizeof(ArcNode));
    
    pNodeNew->iAdjVex = ib;
    
    pNodeNew->iWeight = Weight;
    
    pNodeNew->pNextArc = m_Vertices[ia].pFirstArc;
    
    m_Vertices[ia].pFirstArc = pNodeNew;
    
    if (m_bContainInfor)
    {
      CHAR pszBuffer[MAX_INFO];
      
      memset(pszBuffer,0,MAX_INFO);
      
      fscanf(fp,"%s",pszBuffer);
      
      int nBufferLen = strlen(pszBuffer);
      
      if (nBufferLen)
      {
        pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1));
        
        if (!pNodeNew->pInfor)
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
BOOL ALG::CreateUDG()
{
  m_GraphKind = UDG;
  printf("��������ͼ�Ķ�����Ŀ������Ŀ�����Ƿ�����Ϣ(0:��1:��)\n");

  scanf("%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  while(m_iArcNum>m_iVexNum*(m_iVexNum-1)/2)
  {
    printf("�������Ӧ<=%d,��������.\n",m_iVexNum*(m_iVexNum-1)/2);
    
    scanf("%d",&m_iArcNum);
  }

  int i =0;

  printf("����%d���㣺\n",m_iVexNum);

  CHAR v;
  for (i=0;i<m_iVexNum;++i) // Ҫ���жϵ� ��Ȼ �������� Ҳ��֪�������Ƿ��Ѿ�����
  {
    scanf(" %c",&v);
    
    if (LocateVex(v)!=-1)
    {
      printf("�Ѿ����ڸ�����,��������.\n");
      --i;
      continue;
    }
    else
    {
      m_Vertices[i].Data = v;
      
      m_Vertices[i].pFirstArc = NULL;
    }
    
  }

  int k =0;

  CHAR a,b;
  int ia,ib;

  for (k=0;k<m_iArcNum;++k)
  {
    printf("����%d�ߵ������˵�\n",k+1);

    scanf(" %c %c",&a,&b);

    ia = LocateVex(a);
    ib = LocateVex(b);

    if (-1==ia ||-1==ib || ia==ib  ||GetArc(a,b)) //�����жϱߴ��ڲ�����
    {
      printf("����������������\n");

      --k;

      continue;
    }

    ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));

    if (!pNodeNew)
    {
      exit(0);
    }

    memset(pNodeNew,0,sizeof(ArcNode));

    pNodeNew->iAdjVex = ib;

    pNodeNew->pNextArc = m_Vertices[ia].pFirstArc ;

    m_Vertices[ia].pFirstArc = pNodeNew;

    if (m_bContainInfor)
    {
      printf("�����뻡����Ϣ:");

      CHAR pszBuffer[MAX_INFO];

      memset(pszBuffer,0,MAX_INFO);

      scanf("%s",pszBuffer);

      int nBufferLen = strlen(pszBuffer);

      if (nBufferLen)
      {
        pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen)+1);

        if (!pNodeNew->pInfor)
        {
          exit(0);
        }
        memset(pNodeNew->pInfor,0,sizeof(CHAR)*(nBufferLen+1));

        memcpy(pNodeNew->pInfor,pszBuffer,sizeof(CHAR)*nBufferLen);
      }
    }

    // ���ɵڶ������
    
    pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));
    
    if (!pNodeNew)
    {
      exit(0);
    }
    
    memset(pNodeNew,0,sizeof(ArcNode));
    
    pNodeNew->iAdjVex = ia;
    
    pNodeNew->pInfor = m_Vertices[ia].pFirstArc->pInfor;// ��Ҫ����Ҫ��
    
    pNodeNew->pNextArc = m_Vertices[ib].pFirstArc;
    
    m_Vertices[ib].pFirstArc = pNodeNew;

  }

  return TRUE;
}
BOOL ALG::CreateUDGFromFile(LPCTSTR lpszFile)
{
   m_GraphKind = UDG;
  FILE* fp = NULL;

  if (NULL==(fp = fopen(lpszFile,"r")))
  {
    return FALSE;
  }

  fscanf(fp,"%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  if(m_iArcNum>m_iVexNum*(m_iVexNum-1)/2)
  {
    exit(0);
  }

  
  int i =0;
  
  CHAR v;
  for (i=0;i<m_iVexNum;++i) // Ҫ���жϵ� ��Ȼ �������� Ҳ��֪�������Ƿ��Ѿ�����
  {
    fscanf(fp,"%s",&v);
    
    if (LocateVex(v)!=-1)
    {
      --m_iVexNum;
      --i;
      continue;
    }
    else
    {
      m_Vertices[i].Data = v;
      
      m_Vertices[i].pFirstArc = NULL;
    }
    
  }
  int k =0;
  
  CHAR a,b;
  int ia,ib;
  
  for (k=0;k<m_iArcNum;++k)
  {
   
    fscanf(fp,"%s%S",&a,&b);
    
    ia = LocateVex(a);
    ib = LocateVex(b);
    
    if (-1==ia ||-1==ib || ia==ib ||GetArc(a,b))
    {
  
      --k;

      --m_iArcNum; // ͬ�� ͬ��
      
      continue;
    }
    
    ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));
    
    if (!pNodeNew)
    {
      exit(0);
    }
    
    memset(pNodeNew,0,sizeof(ArcNode));
    
    pNodeNew->iAdjVex = ib;
    
    pNodeNew->pNextArc = m_Vertices[ia].pFirstArc ;
    
    m_Vertices[ia].pFirstArc = pNodeNew;
    
    if (m_bContainInfor)
    {
     
      CHAR pszBuffer[MAX_INFO];
      
      memset(pszBuffer,0,MAX_INFO);
      
      fscanf(fp,"%s",pszBuffer);
      
      int nBufferLen = strlen(pszBuffer);
      
      if (nBufferLen)
      {
        pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen)+1);
        
        if (!pNodeNew->pInfor)
        {
          exit(0);
        }
        memset(pNodeNew->pInfor,0,sizeof(CHAR)*(nBufferLen+1));
        
        memcpy(pNodeNew->pInfor,pszBuffer,sizeof(CHAR)*nBufferLen);
      }
    }

    // ���ɵڶ������
    
    pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));
    
    if (!pNodeNew)
    {
      exit(0);
    }
    
    memset(pNodeNew,0,sizeof(ArcNode));
    
    pNodeNew->iAdjVex = ia;
    
    pNodeNew->pInfor = m_Vertices[ia].pFirstArc->pInfor;// ��Ҫ����Ҫ��
    
    pNodeNew->pNextArc = m_Vertices[ib].pFirstArc;
    
    m_Vertices[ib].pFirstArc = pNodeNew;

  }
  fclose(fp);

 
  return TRUE;
}
BOOL ALG::CreateUDN()
{
 m_GraphKind = UDN;
  printf("�������������Ķ�����Ŀ������Ŀ�����Ƿ�����Ϣ(0:��1:��)\n");

  scanf("%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  while(m_iArcNum>m_iVexNum*(m_iVexNum-1)/2)
  {
    printf("�������Ӧ<=%d,��������.\n",m_iVexNum*(m_iVexNum-1)/2);
    
    scanf("%d",&m_iArcNum);
  }


  int i =0 ;

  printf("����%d���㣺\n",m_iVexNum);

  CHAR v;
  for (i=0;i<m_iVexNum;++i) // Ҫ���жϵ� ��Ȼ �������� Ҳ��֪�������Ƿ��Ѿ�����
  {
    scanf(" %c",&v);
    
    if (LocateVex(v)!=-1)
    {
      printf("�Ѿ����ڸ�����,��������.\n");
      --i;
      continue;
    }
    else
    {
      m_Vertices[i].Data = v;
      
      m_Vertices[i].pFirstArc = NULL;
    }
    
  }

  CHAR a,b;

  int ia,ib;

  int k = 0;

  int Weight = 0;

  for (k=0;k<m_iArcNum;++k)
  {
    printf("����%d�ߵ������˵㡢Ȩֵ\n",k+1);

    scanf(" %c %c%d",&a,&b,&Weight);

    ia = LocateVex(a);
    ib = LocateVex(b);

    if (-1==ia ||-1==ib ||ia==-ib  ||GetArc(a,b))
    {
      printf("���������������.\n");
      --k;
      continue;
    }

    ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));

    if (!pNodeNew)
    {
      exit(0);
    }
    memset(pNodeNew,0,sizeof(ArcNode));

    pNodeNew->iAdjVex = ib;
    pNodeNew->iWeight = Weight;
    pNodeNew->pNextArc = m_Vertices[ia].pFirstArc;
    m_Vertices[ia].pFirstArc = pNodeNew;

    if (m_bContainInfor)
    {
      printf("��������Ϣ:");

      CHAR pszBuffer[MAX_INFO];

      memset(pszBuffer,0,MAX_INFO);

      scanf("%s",pszBuffer);

      int nBufferLen = strlen(pszBuffer);

      if (nBufferLen)
      {
        pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1));

        if (!pNodeNew->pInfor)
        {
          exit(0);
        }

        memset(pNodeNew->pInfor,0,sizeof(CHAR)*(nBufferLen+1));

        memcpy(pNodeNew,pszBuffer,sizeof(CHAR)*nBufferLen);
      }
    }

    // ���ɵڶ������

    pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));

    if (!pNodeNew)
    {
      exit(0);
    }

    memset(pNodeNew,0,sizeof(ArcNode));

    pNodeNew->iAdjVex = ia;

    pNodeNew->iWeight = Weight; 

    pNodeNew->pInfor = m_Vertices[ia].pFirstArc->pInfor;// ��Ҫ����Ҫ��

    pNodeNew->pNextArc = m_Vertices[ib].pFirstArc;

    m_Vertices[ib].pFirstArc = pNodeNew;

    
  }

 
  return TRUE;
}
BOOL ALG::CreateUDNFromFile(LPCTSTR lpszFile)
{
  m_GraphKind = UDN;
  FILE* fp = NULL;

  if (NULL==(fp=fopen(lpszFile,"r")))
  {
    return FALSE;
  }

  fscanf(fp,"%d%d%d",&m_iVexNum,&m_iArcNum,&m_bContainInfor);

  if(m_iArcNum>m_iVexNum*(m_iVexNum-1)/2)
  {
    exit(0);
  }

  
  int i =0 ;
  
  for (i=0;i<m_iVexNum;++i)
  {
    fscanf(fp,"%s",&m_Vertices[i].Data);
    
    m_Vertices[i].pFirstArc = NULL;
  }
  
  CHAR a,b;
  
  int ia,ib;
  
  int k = 0;
  
  int Weight = 0;
  
  for (k=0;k<m_iArcNum;++k)
  {
   
    fscanf(fp,"%s%s%d",&a,&b,&Weight);
    
    ia = LocateVex(a);
    ib = LocateVex(b);
    
    if (-1==ia ||-1==ib ||ia==-ib  ||GetArc(a,b))
    {
      --k;
      --m_iArcNum;
      
      continue;
    }
    
    ArcNode* pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));
    
    if (!pNodeNew)
    {
      exit(0);
    }
    memset(pNodeNew,0,sizeof(ArcNode));
    
    pNodeNew->iAdjVex = ib;
    pNodeNew->iWeight = Weight;
    pNodeNew->pNextArc = m_Vertices[ia].pFirstArc;
    m_Vertices[ia].pFirstArc = pNodeNew;
    
    if (m_bContainInfor)
    {
    
      CHAR pszBuffer[MAX_INFO];
      
      memset(pszBuffer,0,MAX_INFO);
      
      fscanf(fp,"%s",pszBuffer);
      
      int nBufferLen = strlen(pszBuffer);
      
      if (nBufferLen)
      {
        pNodeNew->pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1));
        
        if (!pNodeNew->pInfor)
        {
          exit(0);
        }
        
        memset(pNodeNew->pInfor,0,sizeof(CHAR)*(nBufferLen+1));
        
        memcpy(pNodeNew,pszBuffer,sizeof(CHAR)*nBufferLen);
      }
    }
    
    // ���ɵڶ������
    
    pNodeNew = (ArcNode*)malloc(sizeof(ArcNode));
    
    if (!pNodeNew)
    {
      exit(0);
    }
    
    memset(pNodeNew,0,sizeof(ArcNode));
    
    pNodeNew->iAdjVex = ia;
    
    pNodeNew->iWeight = Weight; 
    
    pNodeNew->pInfor = m_Vertices[ia].pFirstArc->pInfor;// ��Ҫ����Ҫ��
    
    pNodeNew->pNextArc = m_Vertices[ib].pFirstArc;
    
    m_Vertices[ib].pFirstArc = pNodeNew;
    
    
  }

  return TRUE;
}
BOOL    ALG::DestroyGraph()
{
  int i =0;

  ArcNode* pNodeTemp = NULL;

  ArcNode* pPre = NULL;

  for (i=0;i<m_iVexNum;++i)
  {
    pPre = m_Vertices[i].pFirstArc;

    while (pPre)
    {
      pNodeTemp = pPre->pNextArc;

      if (pPre->pInfor)
      {
        free(pPre->pInfor);
      }

      free(pPre);

      pPre = pNodeTemp;
    }
  }

  return TRUE;
}
CHAR    ALG::GetVex(int v)
{
  if (v<0||v>=m_iVexNum)
  {
    exit(0);
  }

  return m_Vertices[v].Data;
}
BOOL    ALG::PutVex(CHAR v, CHAR value)
{
  int iv = LocateVex(v);

  if (iv==-1)
  {
    return FALSE;
  }

  m_Vertices[iv].Data = value;

  return TRUE;
}
int     ALG::FirstAdjVex(CHAR v)
{
  int iv = LocateVex(v);

  if (iv==-1)
  {
    return -1;
  }

  ArcNode* pNodeTemp = m_Vertices[iv].pFirstArc;

  if (pNodeTemp)
  {
    return pNodeTemp->iAdjVex;
  }

  return -1;
}
int     ALG::NextAdjVex(CHAR v,CHAR w)
{
  int iv = LocateVex(v);

  int iw = LocateVex(w);

  if (iv==-1 ||iw==-1 || iw==iv)
  {
    return -1;
  }

  ArcNode* pNodeTemp = m_Vertices[iv].pFirstArc;

  while (pNodeTemp&&pNodeTemp->iAdjVex!=iw)
  {
    pNodeTemp = pNodeTemp->pNextArc;
  }

  if (!pNodeTemp ||!pNodeTemp->pNextArc)
  {
    return -1;
  }
  
  return pNodeTemp->pNextArc->iAdjVex;
}
BOOL    ALG::InsertVex(CHAR v)
{
  if (m_iVexNum>=MAX_VERTEX_NUM)
  {
    return FALSE;
  }

  m_Vertices[m_iVexNum].Data = v;

  m_Vertices[m_iVexNum].pFirstArc = NULL;

  ++m_iVexNum;

  return TRUE;
}
BOOL    ALG::DeleteVex(CHAR v)
{
  int iv = LocateVex(v);

  if (iv==-1)
  {
    return FALSE;
  }

  ArcNode* pNodePre= NULL;
  ArcNode* pNodeTemp = m_Vertices[iv].pFirstArc;

  while (pNodeTemp)
  {
    pNodePre = pNodeTemp;

    pNodeTemp = pNodeTemp->pNextArc;

    if (pNodeTemp->pInfor)
    {
      free(pNodeTemp->pInfor);
    }

    free(pNodePre);

    --m_iArcNum;
  }

  --m_iVexNum;

  int i = 0;

  for (i=iv+1;i<m_iVexNum;++i) //  ע�����ﲻ��ʹ��i=iv     ��������Ļ� ����� ��ֵ��Ҫ�� m_Vertices[i] = m_Vertices[i+1];  ���ǲ��Ե� i+1 �Ѿ���������Ľ�����  
  {
    m_Vertices[i-1] = m_Vertices[i]; // ����ǰ��
  }

  for(i=0;i<m_iVexNum;++i)
  {
    pNodeTemp = m_Vertices[i].pFirstArc;

    while (pNodeTemp)
    {
      if (pNodeTemp->iAdjVex==iv)
      {
        if (pNodeTemp==m_Vertices[i].pFirstArc)
        {
          m_Vertices[i].pFirstArc = pNodeTemp->pNextArc;

          if (pNodeTemp->pInfor)
          {
            free(pNodeTemp->pInfor);
          }

          free(pNodeTemp);

          pNodeTemp = m_Vertices[i].pFirstArc;

          if (m_GraphKind==DN||m_GraphKind==DG)
          {
            --m_iArcNum;
          }
        }
        else
        {
          pNodePre->pNextArc = pNodeTemp->pNextArc;

          if (pNodeTemp->pInfor)
          {
            free(pNodeTemp->pInfor);
          }
          
          free(pNodeTemp);

           pNodeTemp  = pNodePre->pNextArc;

           if (m_GraphKind==DN||m_GraphKind==DG)
           {
             --m_iArcNum;
          }

        }
      }

      else
      {
        if (pNodeTemp->iAdjVex>iv)
        {
          --pNodeTemp->iAdjVex;
        }

        pNodePre = pNodeTemp;

        pNodeTemp = pNodeTemp->pNextArc;
      }
    }
    
  }

  return TRUE;
}
BOOL    ALG::InsertArc(CHAR v,CHAR w)
{
	int iv = LocateVex(v);
	
	int iw = LocateVex(w);

	if (iv==iw||iv==-1||iw==-1)
	{
		return FALSE;
	}

	++m_iArcNum;

	int Weight =0;
	if (m_GraphKind==DN||m_GraphKind==UDN)
	{
		printf("������%c��%cȨֵ",v,w);

		scanf("%d",&Weight);
	}

	ArcNode* pNodeTemp = (ArcNode*)malloc(sizeof(ArcNode));

	if (!pNodeTemp)
	{
		exit(0);
	}

	memset(pNodeTemp,0,sizeof(ArcNode));

	pNodeTemp->iAdjVex = iw;

	if (m_GraphKind==DN||m_GraphKind==UDN)
	{
		pNodeTemp->iWeight = Weight;
	}

	pNodeTemp->pNextArc = m_Vertices[iv].pFirstArc;

	m_Vertices[iv].pFirstArc = pNodeTemp;

	if (m_GraphKind==UDN||m_GraphKind==UDG)
	{
		pNodeTemp = (ArcNode*)malloc(sizeof(ArcNode));

		if (!pNodeTemp)
		{
			exit(0);
		}
		memset(pNodeTemp,0,sizeof(ArcNode));

		pNodeTemp->iAdjVex = iw;

		if (m_GraphKind==UDN)
		{
			pNodeTemp->iWeight = Weight;
		}

		pNodeTemp->pNextArc = m_Vertices[iw].pFirstArc;

		m_Vertices[iw].pFirstArc = pNodeTemp;
	}

  return TRUE;

}

ArcNode* ALG::GetArc(CHAR v,CHAR w)
{
  int iv= LocateVex(v);
  int iw = LocateVex(w);
  
  if (iv==-1||iw==-1||iv==iw)
  {
    return NULL;
	}

  ArcNode* pNodeTemp = m_Vertices[iv].pFirstArc;

  while (pNodeTemp&&pNodeTemp->iAdjVex!=iw)
  {
    pNodeTemp = pNodeTemp->pNextArc;
  }

  if (pNodeTemp&&pNodeTemp->iAdjVex==iw)
  {
    return pNodeTemp;
  }


  if (m_GraphKind==UDN||m_GraphKind==UDG)
  {
    pNodeTemp = m_Vertices[iw].pFirstArc;

    while (pNodeTemp&&pNodeTemp->iAdjVex!=iv)
    {
      pNodeTemp = pNodeTemp->pNextArc;
    }

    if (pNodeTemp&&pNodeTemp->iAdjVex==iv)
    {
      return pNodeTemp;
    }
  }

  return NULL;
}
BOOL    ALG::DeleteArc(CHAR v,CHAR w)
{
	int iv= LocateVex(v);
	int iw = LocateVex(w);

	if (iv==-1||iw==-1||iv==iw)
	{
		return FALSE;
	}

	ArcNode* pNodePre =NULL;
	ArcNode* pNodeTemp = m_Vertices[iv].pFirstArc;
	
	while (pNodeTemp&&pNodeTemp->iAdjVex!=iw)// ��������ָ֮�����Ǵ�ɾ����
	{
		pNodePre = pNodeTemp;

		pNodeTemp = pNodePre->pNextArc;
	}

	if (pNodeTemp&&pNodeTemp->iAdjVex==iw)// �ҵ���<v,w>
	{
		if (pNodeTemp==m_Vertices[iv].pFirstArc)// ��ָ�ǵ�1����
		{
			m_Vertices[iv].pFirstArc = pNodeTemp->pNextArc;
		}

		else
		{
			pNodePre->pNextArc = pNodeTemp->pNextArc;
		}
		if (pNodeTemp->pInfor)
		{
			free(pNodeTemp->pInfor);
		}

		free(pNodeTemp);

		--m_iArcNum;
	}
	
	// ����   ɾ���Գƻ�

	if (m_GraphKind==UDN||m_GraphKind==UDG)
	{
		pNodeTemp = m_Vertices[iw].pFirstArc;

		while (pNodeTemp&&pNodeTemp->iAdjVex!=iv)// p��������ָ֮�����Ǵ�ɾ����<w,v>
		{
			pNodePre = pNodeTemp;

			pNodeTemp = pNodePre->pNextArc;
		}

		if (pNodeTemp&&pNodeTemp->iAdjVex==iv)
		{
			if (pNodeTemp==m_Vertices[iw].pFirstArc)
			{
				m_Vertices[iw].pFirstArc = pNodeTemp;
			}
			else
			{
				pNodePre->pNextArc = pNodePre->pNextArc;
			}

			if (pNodeTemp->pInfor)
			{
				free(pNodeTemp->pInfor);	
			}

			free(pNodeTemp);
		}
	}

  return TRUE;
}
BOOL    ALG::DFS(int v)
{
	printf("%c ",m_Vertices[v].Data);
	
	m_Vertices[v].bVisit = TRUE;

	int i = 0;
	for (i=FirstAdjVex(GetVex(v));i>=0;i = NextAdjVex(GetVex(v),GetVex(i)))
	{
		if (!m_Vertices[i].bVisit)
		{
			DFS(i);
		}
	}

  return TRUE;
}
BOOL    ALG::DFSTraverse()
{
	int i =0;
	for (i=0;i<m_iVexNum;++i)
	{
		m_Vertices[i].bVisit = FALSE; // MakeUnVisited
	}

	for (i=0;i<m_iVexNum;++i)
	{
		if (!m_Vertices[i].bVisit)
		{
			DFS(i);
		}
	}

	printf("\n");

  return TRUE;
}
BOOL    ALG::BFSTraverse()
{
	int i = 0 ;
	for (i=0;i<m_iVexNum;++i)
	{
		m_Vertices[i].bVisit =FALSE;// MakeUnVisited
	}

	QUEUE Q;

	Q.InitQueue();
	int j = 0;
	int k = 0;
	for (i=0;i<m_iVexNum;++i)
	{
		if (!m_Vertices[i].bVisit)
		{
			m_Vertices[i].bVisit = TRUE;

			printf("%c ",GetVex(i));

			if (!Q.EnQueue(i))
			{
        return FALSE;
			}

			while (!Q.QueueIsEmpty())
			{
			
        if(!	Q.DeQueue(j))
        {
          return FALSE;
        }

				for (k=FirstAdjVex(GetVex(j));k>=0;k=NextAdjVex(GetVex(j),GetVex(k)))
				{
					if (!m_Vertices[k].bVisit)
					{
						m_Vertices[k].bVisit = TRUE;

						printf("%c ",GetVex(k));
						
            if (!Q.EnQueue(k))
            {
              return FALSE;
            }
					}
				}
			}
		}
	}


	Q.DestroyQueue();

  printf("\n");

  return TRUE;
}
BOOL    ALG::Display()
{
  CHAR pszGraphKind[7] = {0};
  CHAR pszEdgeKind[3] = {0};
  switch(m_GraphKind)
  {
  case DG:
    {
      strcpy(pszGraphKind,"����ͼ");
      strcpy(pszEdgeKind,"��");
       break;
    }

  case DN:
    {
      strcpy(pszGraphKind,"������");

      strcpy(pszEdgeKind,"��");

      break;
    }

  case UDG:
    {
      strcpy(pszGraphKind,"����ͼ");
      strcpy(pszEdgeKind,"��");
      break;
    }

  case UDN:
    {
      strcpy(pszGraphKind,"������");
      strcpy(pszEdgeKind,"��");
      break;
    }
  }


  printf("��ͼ��%d������%d��%s��%s\n",m_iVexNum,m_iArcNum,pszEdgeKind,pszGraphKind);

  printf("���%d������: ",m_iVexNum);
  int i =0;
  for (i=0;i<m_iVexNum;++i)
  {
    printf("%c ",GetVex(i));
  }

  printf("\n���%d����\n",m_iArcNum);

  ArcNode* pNodeTemp = NULL;

  for (i=0;i<m_iVexNum;++i)
  { 
    pNodeTemp = m_Vertices[i].pFirstArc;

    while (pNodeTemp)
    {
      if (m_GraphKind==DG||m_GraphKind==DN) // �������
      {
        printf("%c��%c ",GetVex(i),GetVex(pNodeTemp->iAdjVex));
        
        if ( m_GraphKind==DN) // ���Ļ� һ����Ȩֵ ��������Ϣ
        {
          printf("Ȩֵ:%d ",pNodeTemp->iWeight);
        }
        
        if (pNodeTemp->pInfor)
        {
          printf("������Ϣ:%s\n",pNodeTemp->pInfor);
        }
      }


      if (m_GraphKind==UDN || m_GraphKind==UDG) // ����
      {
        if (i<pNodeTemp->iAdjVex)
        {
          printf("%c--%c ",GetVex(i),GetVex(pNodeTemp->iAdjVex));
        }
        if (m_GraphKind==UDN)
        {
          printf("Ȩֵ :%d ",pNodeTemp->iWeight);
        }

        if (pNodeTemp->pInfor)
        {
          printf("������Ϣ:%s\n",pNodeTemp->pInfor);
        }
      }

      pNodeTemp = pNodeTemp->pNextArc;
    }
  }

  printf("\n");

  return TRUE;
}

int     ALG::GetVexDegree(CHAR v)
{
  if (LocateVex(v)==-1)
  {
    return -1;
  }

  int iv = LocateVex(v);

  int iDegree = 0;
  if (m_GraphKind==UDN||m_GraphKind==UDG)
  {
    

    ArcNode* pNodeTemp = m_Vertices[iv].pFirstArc;

    while (pNodeTemp)
    {
      pNodeTemp = pNodeTemp->pNextArc;

      ++iDegree;
    }
  }

  else // ����ͼ
  {
      iDegree = GetVexOutDegree(v)+GetVexInDegree(v);
  }

  return iDegree;
}

int     ALG::GetVexOutDegree(CHAR v) // ������ͼ�еõ�����
{
  if ((m_GraphKind!=DG &&m_GraphKind!=DN )|| LocateVex(v)==-1)
  {
    return -1;
  }
  int iDegree = 0;
  int iv= LocateVex(v);

  ArcNode* pNodeTemp = m_Vertices[iv].pFirstArc;

  while (pNodeTemp)  // ����ǳ���
  {
    pNodeTemp = pNodeTemp->pNextArc;

    ++iDegree;  
  }

  return iDegree;
}
int     ALG::GetVexInDegree(CHAR v)// ������ͼ�еõ����
{
  if ((m_GraphKind!=DG&&m_GraphKind!=DN )|| LocateVex(v)==-1)
  {
    return -1;
  }
  int iDegree = 0;

  int i= 0;

  int iv = LocateVex(v);

  ArcNode* pNodeTemp = NULL;

  for (i=0;i<m_iVexNum;++i)
  {
      pNodeTemp = m_Vertices[i].pFirstArc;

      while (pNodeTemp)
      {
        if (pNodeTemp->iAdjVex==iv)
        {
          ++iDegree;
        }
        pNodeTemp = pNodeTemp->pNextArc;


      }
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
		Data = *(QUEUEDATA*)0;  // ���������Ҫ����  
		
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