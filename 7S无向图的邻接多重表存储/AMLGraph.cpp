#include <STDIO.H>
#include <WINDOWS.H>

#define  MAX_VERTEX_NUM 20
#define  MAX_INFO 20 
#define  VEXDATA TCHAR
#define  QUEUESIZESTEP 3 // ���г���ÿһ���Ӻ�
#define  QUEUEDATA int  // ÿ��ʹ�� ��Ҫ���ĵ���������

// ���ڽӶ��ر�������������ͬһ����ıߴ�����
// ͬһ������ ����ÿ������������������ ��ÿ���߽ڵ�ͬʱ������
// ����������

// ���ڽӱ�Ĳ��  ͬһ�������ڽӱ�������������ʾ
// ���ٽ���ر���ֻ��һ����� 

VOID InputData(VEXDATA* pData);
VOID OutPutData(VEXDATA Data);
VOID OutPutData(VEXDATA Data1,VEXDATA Data2);
struct EdgeBox
{
  BOOL bVisitMark;
  int iVex;
  int jVex;
  EdgeBox* iLink;
  EdgeBox* jLink;
  VOID* pszInfor;
};

struct VexBox
{
  VEXDATA Data;
  BOOL bVisited;
  EdgeBox* FirstEdge;
};

class AMLGraph
{
protected:
  VexBox m_AdjMulist[MAX_VERTEX_NUM];
  int m_VexNum;
  int m_EdgeNum;
  BOOL m_bContainInfor;
public:
  int LocateVex(VEXDATA u);
  EdgeBox* GetArc(VEXDATA e,VEXDATA w);
  BOOL CreateGraph();
  BOOL CreateGraphFromFile(LPCTSTR lpszFileName);
  VEXDATA GetVex(int iIndex);
  BOOL PutVex(VEXDATA e, VEXDATA vValue);
  int FirstAdjVex(VEXDATA e);
  int NextAdjVex(VEXDATA e,VEXDATA w);

  BOOL InsertVex(VEXDATA NewData);
  BOOL DeleteVex(VEXDATA e);

  BOOL InsertArc(VEXDATA e,VEXDATA w);
  BOOL DeleteArc(VEXDATA e,VEXDATA w);
  BOOL MakeUnVisited();
  BOOL Display();
  BOOL DestroyGraph();

  VOID DFS(int iIndex);
  VOID DFSTraverse();

  VOID BFSTraverse();

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


int main(int argc, char* argv[])
{

  AMLGraph G;
//  G.CreateGraphFromFile("1.txt");

  G.CreateGraph();

  printf("��ӡ:\n");
  G.Display();

  printf("������ȱ���:\n");

  G.DFSTraverse();

  printf("������ȱ���:\n");
  G.BFSTraverse();

  G.DestroyGraph();

  G.Display();

  return 0;
}




int  AMLGraph::LocateVex(VEXDATA u)
{
  for (int i=0;i<m_VexNum;++i)
  {
    if (m_AdjMulist[i].Data==u) // ����������������� ����ıȽ�Ҳ����Ҫ���ĵ�
    {
      return i;
    }
  }

  return -1;
}


BOOL AMLGraph::CreateGraph()
{
  printf("��������ͼ�Ķ��������������Լ��Ƿ��и�����Ϣ\n");

  scanf("%d",&m_VexNum); // ����Ӧ����һ���ж�   �����������֮��Ĺ�ϵ  

  scanf("%d",&m_EdgeNum);

  while (m_EdgeNum>(m_VexNum*(m_VexNum-1))/2)
  {
    printf("�������Ӧ��<=%d,�����������.\n",(m_VexNum*(m_VexNum-1))/2);

    scanf("%d",&m_EdgeNum);
  }

  scanf("%d",&m_bContainInfor);


  printf("����%d�������ֵ\n",m_VexNum);

  int i= 0;

  VEXDATA v;

  for (i=0;i<m_VexNum;++i)
  {
    InputData(&v);

    if (LocateVex(v)!=-1)
    {
      printf("�����ظ�������������.\n");
      --i;
      continue;
    }

    
    m_AdjMulist[i].Data = v;

    m_AdjMulist[i].FirstEdge = NULL;
  }

  int k = 0;

  int j =0;

  printf("����ÿ���ߵ���������\n");

  VEXDATA va,vb;

  for (k=0;k<m_EdgeNum;++k)
  {
    InputData(&va);
    InputData(&vb);

    i = LocateVex(va);

    j = LocateVex(vb);

    if (i==-1||j==-1 || i==j || GetArc(va,vb))
    {
      printf("���������������.\n");

      --k;
      continue;
    }

    EdgeBox*  p = NULL;

    if (NULL==(p = (EdgeBox*)malloc(sizeof(EdgeBox))))
    {
      return FALSE;
    }
    
    p->bVisitMark = FALSE;
    p->iVex = i;
    p->jVex = j;
    p->pszInfor = NULL;

    p->iLink = m_AdjMulist[i].FirstEdge;
    m_AdjMulist[i].FirstEdge = p;

    p->jLink = m_AdjMulist[j].FirstEdge;
    m_AdjMulist[j].FirstEdge = p;

    TCHAR pszBuffer[1024];
    memset(pszBuffer,0,1024);

    if (m_bContainInfor)
    {
      printf("����û�������Ϣ\n");

      scanf("%s",pszBuffer);

      int nBufferLen =  strlen(pszBuffer);

      if (nBufferLen)
      {
        if (NULL==(p->pszInfor = (PTCHAR)malloc(sizeof(TCHAR)*(nBufferLen+1))))
        {
          return FALSE;
        }
		memset(p->pszInfor,0,sizeof(TCHAR)*(nBufferLen+1));

        memcpy(p->pszInfor,pszBuffer,nBufferLen);
        
      }
    }
  }

  return TRUE;
}
BOOL AMLGraph::CreateGraphFromFile(LPCTSTR lpszFileName)
{

  FILE* fp = NULL;

  if (NULL==(fp = fopen(lpszFileName,"r")))
  {
    return FALSE;
  }

  
  fscanf(fp,"%d%d%d",&m_VexNum,&m_EdgeNum,&m_bContainInfor);
  
  int i= 0;
  
  for (i=0;i<m_VexNum;++i) // ���붥��ֵ
  {
    fscanf(fp,"%s",&m_AdjMulist[i].Data);
    
    m_AdjMulist[i].FirstEdge = NULL;
  }
  
  int k = 0;
  
  int j =0;
  
  VEXDATA va,vb;
  
  for (k=0;k<m_EdgeNum;++k)
  {
  
    fscanf(fp,"%s%s",&va,&vb);
    
    i = LocateVex(va);
    
    j = LocateVex(vb);
    
    if (i==-1||j==-1)
    {
      return FALSE;
    }
    
    EdgeBox*  p = NULL;
    
    if (NULL==(p = (EdgeBox*)malloc(sizeof(EdgeBox))))
    {
      return FALSE;
    }
    
    p->bVisitMark = FALSE;
    p->iVex = i;
    p->jVex = j;
    p->pszInfor = NULL;
    
    p->iLink = m_AdjMulist[i].FirstEdge;
    m_AdjMulist[i].FirstEdge = p;
    
    p->jLink = m_AdjMulist[j].FirstEdge;
    m_AdjMulist[j].FirstEdge = p; 
    if (m_bContainInfor)
    {
		TCHAR pszBuffer[1024];
		memset(pszBuffer,0,1024);
		fscanf(fp,"%s",pszBuffer);
		
		int nBufferLen =  strlen(pszBuffer);
		
		if (nBufferLen)
		{
			if (NULL==(p->pszInfor = (PTCHAR)malloc(sizeof(TCHAR)*(nBufferLen+1))))
			{
				return FALSE;
			}
			memcpy(p->pszInfor,pszBuffer,nBufferLen);
			
		}
    }
  }

  fclose(fp);
  return TRUE;
}
VEXDATA AMLGraph::GetVex(int iIndex)
{
  if (iIndex>=m_VexNum||iIndex<0)
  {
    printf("Error GetVex\n");

    exit(0);
  }

  return m_AdjMulist[iIndex].Data;
}
BOOL AMLGraph::PutVex(VEXDATA e, VEXDATA vValue)
{
  int iIndex = 0;

  if ((iIndex=LocateVex(e))==-1)
  {
    return FALSE;
  }
  
  m_AdjMulist[iIndex].Data = vValue;

  return TRUE;
  
}
int AMLGraph::FirstAdjVex(VEXDATA e)
{
// ��ʼ����: ����ͼG����,v��G��ĳ������ 
// �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1 

  int iIndex = 0;

  if((iIndex=LocateVex(e))==-1)
  {
    return -1;
  }

  if (m_AdjMulist[iIndex].FirstEdge)
  {
    if (m_AdjMulist[iIndex].FirstEdge->iVex==iIndex)
    {
      return m_AdjMulist[iIndex].FirstEdge->jVex;
    }
    else
    {
      return m_AdjMulist[iIndex].FirstEdge->iVex;
    }
  }

  return -1;
}
// ��ʼ����: ����ͼG����,v��G��ĳ������,w��v���ڽӶ��� 
// �������: ����v��(�����w��)��һ���ڽӶ������š� 
//           ��w��v�����һ���ڽӵ�,�򷵻�-1 
int AMLGraph::NextAdjVex(VEXDATA e,VEXDATA w)
{
  int i = LocateVex(e);
  int j = LocateVex(w);

  if (i==-1||j==-1||i==j)
  {
    return -1;
  }

  // ������i��·���ҵ� ��ͷ�� i �� j �Ļ�
  EdgeBox* p = m_AdjMulist[i].FirstEdge;

  while (p)
  {
    if (p->iVex==i&&p->jVex!=j)
    {
      p = p->iLink;
    }
    else if (p->jVex==i&&p->iVex!=j)
    {
      p = p->jLink;
    }
    else// ���ڽӶ���w 
    {
       break;
    }
  }// ������ �ҵ� ���߸ɴ�û��
  
  if (p&&p->iVex==i&&p->jVex==j)
  {
    p = p->iLink;
    if (p&&p->iVex==i)
    {
      return p->jVex; // ע�� ���ص�������
    }
    else if (p&&p->jVex==i)
    {
      return p->iVex;
    }
  }


  if (p&&p->iVex==j&&p->jVex==i)
  {
    p = p->jLink;

    if (p&&p->iVex==i)
    {
      return p->jVex;
    }
    else if (p&&p->jVex==i)
    {
      return p->iVex;
    }
  }

  return -1;
}

BOOL AMLGraph::InsertVex(VEXDATA NewData)
{
  if (m_VexNum==MAX_VERTEX_NUM)
  {
    return FALSE;
  }

  if (LocateVex(NewData)!=-1)
  {
    return FALSE; // �����Ѿ�����  ���� ���ܴ�����������
  }

  m_AdjMulist[m_VexNum].Data = NewData;

  m_AdjMulist[m_VexNum].FirstEdge = NULL;

  ++m_VexNum;

  return TRUE;
}
BOOL AMLGraph::DeleteVex(VEXDATA e)
{
  int ie = LocateVex(e);

  if (ie==-1)
  {
    return FALSE;
  }

  int i =0;
  
  VEXDATA w ;
  for (i=0;i<m_VexNum;++i)
  {
    if (ie==i)
    {
      continue;
    }
    
    w = GetVex(i);

    DeleteArc(e,w);
  }

  // ����ǰ��
  for (i=ie+1;i<m_VexNum;++i)
  {
    m_AdjMulist[i-1] = m_AdjMulist[i];
  }

  --m_VexNum;

   EdgeBox* p = NULL;

  for (i=ie;i<m_VexNum;++i)
  {
    p  = m_AdjMulist[i].FirstEdge;

    if (p) // while???
    {
      if (p->iVex==i+1)
      {
        --p->iVex;

        p = p->iLink;
      }
      else
      {
        --p->jVex;

        p = p->jLink;
      }
    }
  }


  return TRUE;
}

BOOL AMLGraph::InsertArc(VEXDATA e,VEXDATA w)
{
  int ie = LocateVex(e);
  int iw = LocateVex(w);

  if (ie==-1 || iw == -1 ||ie==iw)
  {
    return FALSE;
  }

  EdgeBox* p = NULL;

  if (NULL==(p=(EdgeBox*)malloc(sizeof(EdgeBox))))
  {
    return FALSE;
  }

  p->bVisitMark = FALSE;
  p->iVex = ie;
  p->jVex = iw;

  p->pszInfor  = NULL;

  p->iLink = m_AdjMulist[ie].FirstEdge;

  m_AdjMulist[ie].FirstEdge  = p;

  p->jLink = m_AdjMulist[iw].FirstEdge;

  m_AdjMulist[iw].FirstEdge = p;

  int Infor = 0;

  printf("����ñߵ������Ϣ\n");

  scanf("%d",&Infor);

  TCHAR pszBuffer[1024];

  memset(pszBuffer,0,1024);

  if (Infor)
  {
    scanf("%s",pszBuffer);

    int nBufferLen = strlen(pszBuffer);

    if (nBufferLen)
    {
      if (NULL==(p->pszInfor=(TCHAR*)malloc(sizeof(TCHAR)*(nBufferLen+1))))
      {
        return FALSE;
      }

      memcpy(p->pszInfor,pszBuffer,nBufferLen);
    }
  }

  return TRUE;
}
EdgeBox* AMLGraph::GetArc(VEXDATA e,VEXDATA w)
{
   int ie = LocateVex(e);
  int iw = LocateVex(w);

  if (iw==-1 || ie==-1 || iw==ie)
  {
    return NULL;
  }

  EdgeBox* p = m_AdjMulist[ie].FirstEdge;

  if ((p&&p->jVex==iw)||(p&&p->iVex==iw))// ��1���߼�Ϊ��ɾ����
  {
    return p;
		  // �����и����� ������Ѱ��һ���� i j  Ϊ�˵�Ļ� ���� ���ǲ�û���ж����� ����˵����
    // p->ivex==ie && p->jvex==iw ����ֻ���� p->jvex==iw  Ϊʲô��  
    // ��Ϊ���Ǵ� i �ı�ԵѰ�ҵ�  ��Ȼ��i �й�ϵ  ����  ����ֻ��Ҫ����iw��û�й�ϵ������ 
  }
  else
  {
     while (p)
     {
       if (p->iVex==ie && p->jVex!=iw)
       {

         p = p->iLink;
       }
       else if (p->jVex==ie &&p->iVex!=iw)
       {

         p = p->jLink;
       }
       else
       {
         break;
       }
     }

     if (p) //  �������������   p->iVex==ie&& p->jVex==iw  Or p->jVex==ie&&p->iVex==iw Or p==NULL 
     {
       return p; // ΪNULL�����ܷ���   ֻ�����ҵ��˲ŷ���   
     }
  }
	// ����һ������Ѱ�һ�  
  p = m_AdjMulist[iw].FirstEdge;

  if (p&&(p->jVex==ie || p->iVex==ie))
  {
    return p;

  }

  else
  {
    while (p)
    {
      if (p->iVex==iw && p->jVex!=ie) //  ����� != Ҳ���н����� 
      {

        p = p->iLink;
      }
      else if (p->jVex==iw && p->iVex!=ie)
      {

        p = p->jLink;
      }
      else
      {
        break;
      }
    }

		// ��ǰ�� p ����Ҫɾ���Ļ� 
    // ����һ�����ҵ��� ��Ϊ���ϱߵ�ʱ���Ѿ��ҵ��� �����Ҳ��� �ͻ� return FALSE

    if (p) // ����ͬ��
    {
      return p;
    }

  }
  return NULL;
}
BOOL AMLGraph::DeleteArc(VEXDATA e,VEXDATA w)
{
  int ie = LocateVex(e);
  int iw = LocateVex(w);

  if (iw==-1 || ie==-1 || iw==ie)
  {
    return FALSE;
  }

  EdgeBox* p = m_AdjMulist[ie].FirstEdge;

  EdgeBox* pre = NULL;

  if (p&&p->jVex==iw)// ��1���߼�Ϊ��ɾ����
  {
    m_AdjMulist[ie].FirstEdge = p->iLink;
		  // �����и����� ������Ѱ��һ���� i j  Ϊ�˵�Ļ� ���� ���ǲ�û���ж����� ����˵����
    // p->ivex==ie && p->jvex==iw ����ֻ���� p->jvex==iw  Ϊʲô��  
    // ��Ϊ���Ǵ� i �ı�ԵѰ�ҵ�  ��Ȼ��i �й�ϵ  ����  ����ֻ��Ҫ����iw��û�й�ϵ������ 
  }
  else if (p&&p->iVex==iw)
  {
    m_AdjMulist[ie].FirstEdge = p->jLink;
  }
  else
  {
     while (p)
     {
       if (p->iVex==ie && p->jVex!=iw)
       {
         pre = p;

         p = p->iLink;
       }
       else if (p->jVex==ie &&p->iVex!=iw)
       {
         pre = p;

         p = p->jLink;
       }

       else
       {
         break; // �ҵ���
       }
     }

     if (!p)
     {
       return FALSE;
     }

     if (p->iVex==ie && p->jVex==iw)
     {
       if (pre->iVex == ie)
       {
         pre->iLink = p->iLink;
       }
       else
       {
         pre->jLink = p->iLink;
       }
     }
     else if (p->iVex==iw && p->jVex==ie)
     {
       if (pre->iVex==ie)
       {
         pre->iLink = p->jLink;
       }
       else
       {
         pre->jLink = p->jLink;
       }
     }
  }

	// ����һ������Ѱ�һ�  ���� free
  p = m_AdjMulist[iw].FirstEdge;

  if (p->jVex==ie)
  {
    m_AdjMulist[iw].FirstEdge = p->iLink; // ָ���Լ�����һ����� // ��������p->iVex==iw ������iLink

    if (p->pszInfor)
    {
      free(p->pszInfor);
    }

    free(p);

  }
  else if (p->iVex==ie)
  {
    m_AdjMulist[iw].FirstEdge = p->jLink;

    if (p->pszInfor)
    {
      free(p->pszInfor);
    }

    free(p);
  }

  else
  {
    while (p)
    {
      if (p->iVex==iw && p->jVex!=ie) //  ����� != Ҳ���н����� 
      {
        pre= p;

        p = p->iLink;
      }
      else if (p->jVex==iw && p->iVex!=ie)
      {
        pre = p;

        p = p->jLink;
      }
      else
      {
        break;
      }
    }

		// ��ǰ�� p ����Ҫɾ���Ļ� 
    // ����һ�����ҵ��� ��Ϊ���ϱߵ�ʱ���Ѿ��ҵ��� �����Ҳ��� �ͻ� return FALSE

    if (p->iVex==ie &&p->jVex==iw)
    {
      if (pre->iVex==iw) // �ж��ĸ���iw ���������  ���Լ�Ϊ���� �����ǵ�����
      {
        pre->iLink = p->jLink;
      }
      else
      {
        pre->jLink = p->jLink;
      }
      if (p->pszInfor)
      {
        free(p->pszInfor);
      }

      free(p); // ���� p=NULL  ��Ϊ����ɾ����һ��������������Ľ��
    }
    else if (p->iVex==iw && p->jVex==ie)
    {
      if (pre->iVex==iw)
      {
        pre->iLink = p->iLink; 
      }
      else 
      {
        pre->jLink = p->iLink;
      } 

      if (p->pszInfor)
      {
        free(p->pszInfor);
      }

      free(p);

      p =NULL;
    }

  }


  --m_EdgeNum;
  return TRUE;
}
BOOL AMLGraph::MakeUnVisited()
{
  int i = 0;

  EdgeBox* p = NULL;
  for (i=0;i<m_VexNum;++i)
  {
    p = m_AdjMulist[i].FirstEdge;

    while (p)
    {
      p->bVisitMark = FALSE;

      if (p->iVex==i)
      {
        p = p->iLink;
      }
      else
      {
        p = p->jLink;
      }
    }
  }

  return TRUE;
}
BOOL AMLGraph::Display()
{
  MakeUnVisited();

  printf("���㣺%d\n",m_VexNum);

  int i = 0;

  for (i=0;i<m_VexNum;++i)
  {
    OutPutData(m_AdjMulist[i].Data);
  }
 

  printf("\n����%d\n",m_EdgeNum);

  EdgeBox* p = NULL;

	// �ȴ�ӡ���� �ٴ�ӡ�뻡
  for (i=0;i<m_VexNum;++i)
  {
    p = m_AdjMulist[i].FirstEdge;

    while (p)
    {
      if (p->iVex==i)// �ߵ�i����ö����й�  �Ҿ��þ��ǳ���
      {
        if (!p->bVisitMark)
        { 
          OutPutData(m_AdjMulist[i].Data,m_AdjMulist[p->jVex].Data);
          
          p->bVisitMark = TRUE;
          
          if (p->pszInfor)
          {
            printf("Infor:%s\n",p->pszInfor);
          }
        
        }
       
        p = p->iLink;
      }

      else// �ߵ�j����ö����й�  Ӧ�����뻡
      {
        if (!p->bVisitMark)  // jLink �������Լ������������ 
        {
          OutPutData(m_AdjMulist[p->iVex].Data,m_AdjMulist[i].Data);

          p->bVisitMark = TRUE;

          if (p->pszInfor)
          {
            printf("Infor:%s\n",p->pszInfor);
          }
        }

        p = p->jLink;
      } 
    }
    printf("\n");
  }
  return TRUE;
}
BOOL AMLGraph::DestroyGraph()
{
  int i = 0;
  for (i=m_VexNum-1;i>=0;--i)
  {
    if (!DeleteVex(m_AdjMulist[i].Data))
    {
      printf("Error DestroyGraph\n");
      return FALSE;
    }   
  }

  return TRUE;
}

VOID AMLGraph::DFS(int iIndex)
{
  OutPutData(m_AdjMulist[iIndex].Data);

  m_AdjMulist[iIndex].bVisited = TRUE;

  EdgeBox* p = m_AdjMulist[iIndex].FirstEdge;

  int i = 0;

  while (p)
  {
    i = (p->iVex==iIndex?p->jVex:p->iVex);
    
    if (!m_AdjMulist[i].bVisited)
    {
      DFS(i);
    }

    p = (p->iVex==iIndex?p->iLink:p->jLink);
  }
}
VOID AMLGraph::DFSTraverse()
{
  int i = 0;

  for (i=0;i<m_VexNum;++i)
  {
    m_AdjMulist[i].bVisited = FALSE;
  }

  for (i=0;i<m_VexNum;++i)
  {
    if (!m_AdjMulist[i].bVisited)
    {
      DFS(i);
    }
  }

  printf("\n");
}

VOID AMLGraph::BFSTraverse()
{
  int i =0 ;

  for (i=0;i<m_VexNum;++i)
  {
    m_AdjMulist[i].bVisited = FALSE;
  }

  QUEUE Q;

  int j = 0,iw;

  VEXDATA vj,vw;

  Q.InitQueue();

  for (i=0;i<m_VexNum;++i)
  {
    if (!m_AdjMulist[i].bVisited)
    {
      m_AdjMulist[i].bVisited = TRUE;

      OutPutData(m_AdjMulist[i].Data);

      Q.EnQueue(i);

      while (!Q.QueueIsEmpty())
      {
        Q.DeQueue(j);
        
        vj = GetVex(j);

        for (iw = FirstAdjVex(vj);iw>=0;iw = NextAdjVex(vj,GetVex(iw)))
        {
          if (!m_AdjMulist[iw].bVisited)
          {
            m_AdjMulist[iw].bVisited = TRUE;

            OutPutData(m_AdjMulist[iw].Data);

            Q.EnQueue(iw);
          }
        }
      }
    }
  }


  Q.DestroyQueue();

  printf("\n");
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
// ���ڶ����������Ͳ�ͬ  �������������ⲿ�����ṩ
VOID InputData(VEXDATA* pData)
{
  scanf(" %c",pData);
}
VOID OutPutData(VEXDATA Data)
{
  printf(" %c",Data);
}
VOID OutPutData(VEXDATA Data1,VEXDATA Data2)
{
  printf("%c--%c ",Data1,Data2);
}