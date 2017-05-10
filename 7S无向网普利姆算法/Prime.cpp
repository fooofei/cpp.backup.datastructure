#include <STDIO.H>
#include <WINDOWS.H>
#include <LIMITS.H>

// ע�� �� ����ͼ�нл� Arc  
//		����ͼ�н� �� Edge
//		��β-�� ��ͷ
// �����ʱ��  �����˵㱣�����Ϣ��һ�µ�
// �������Լ�д ���� ����ε���ĳ����������Ż� �Ľ� ��װΪ��

// author:
// datatime:2012-9-15
#define  QUEUESIZESTEP 3 // ���г���ÿһ���Ӻ�
#define  QUEUEDATA int  // ÿ��ʹ�� ��Ҫ���ĵ���������
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


#define  MAX_VERTEX_NUM 20// ��󶥵����
#define  MAX_INFO	20	// ������Ϣ���ַ���
typedef enum{DG,DN,UDG,UDN}GraphKind;// ����ͼ,������,����ͼ,������
#define  VEXDATA CHAR

struct ArcCell // ������������
{
	int iAdj; // ͼ ����0 or 1  �� ����Ȩֵ ���� ����
	
	VOID* pInfor;
};

struct MiniSide
{
  VEXDATA AdjVex;
  int iLowCost;
};
class MG
{
protected:
	VEXDATA m_Vexs[MAX_VERTEX_NUM]; // ����
	BOOL	m_bVisited[MAX_VERTEX_NUM]; // �����Ƿ񱻷���
	ArcCell m_Arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int		m_iArcNum;
	int		m_iVexNum;
	GraphKind m_GraphKind;
	BOOL	m_bContainInfor;
public:
	
	int LocateVex(VEXDATA u);
	BOOL InitAdjMart(int iInvalidData); // ��ʼ���ڽӾ���  
	BOOL CreateUDN();
	BOOL CreateUDNFromFile(LPCTSTR lpszFile);
	BOOL DestroyGraph();
	VEXDATA GetVex(int iIndex);
	BOOL PutVex(VEXDATA v, VEXDATA value);

	int FirstAdjVex(VEXDATA v);
	int NextAdjVex(VEXDATA v,VEXDATA w);

	BOOL InsertVex(VEXDATA v);
	BOOL DeleteVex(VEXDATA v);

	BOOL InsertArc(VEXDATA v,VEXDATA w);
	BOOL DeleteArc(VEXDATA v,VEXDATA w);

	BOOL MakeUnVisited();
	BOOL DFS(int iIndex);
	BOOL DFSTraverse();

	BOOL BFSTraverse();

	BOOL Display();

  int GetVexDegree(VEXDATA v);
  int GetVexOutDegree(VEXDATA v);
  int GetVexInDegree(VEXDATA v);

  BOOL MiniSpanTree_PRIM(VEXDATA u); // ����С������  �������еĶ���  ��С��������Ψһ��
  int MiniNum(MiniSide* SZ);
};
int main(int argc, char* argv[])
{

  MG G;
  
  if (G.CreateUDNFromFile("UDN.txt"))
  {
    printf("��ӡ:\n");
    G.Display();
    
    printf("������ȱ���:\n");
    
    G.DFSTraverse();
    
    printf("������ȱ���:\n");
    
    G.BFSTraverse();
    
    printf("��С������\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(0));
    
    printf("��С������\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(1));
    
    printf("��С������\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(2));

    printf("��С������\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(3));

    printf("��С������\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(4));

    printf("��С������\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(5));
    G.DestroyGraph();
  }
  return 0;
}


int MG::LocateVex(VEXDATA u)
{
	int i =0;
	
	for (i=0;i<m_iVexNum;++i)
	{
		if (u==m_Vexs[i]) // ����ıȽ� �Ժ� �������͸��ĵ�ʱ�� ��Ҫ��������
		{
			return i;
		}
	}

	return -1;
}

BOOL MG::InitAdjMart(int iInvalidData)
{
	int i = 0;
	int j = 0;
	for (i=0;i<m_iVexNum;++i)
	{
		for (j=0;j<m_iVexNum;++j)
		{
			m_Arcs[i][j].iAdj = iInvalidData;

			m_Arcs[i][j].pInfor = NULL;
		}
	}

	return TRUE;

}



BOOL MG::CreateUDN()
{
	printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0):\n");

	scanf("%d",&m_iVexNum);

	scanf("%d",&m_iArcNum);

  while (m_iArcNum>m_iVexNum*(m_iVexNum-1)/2)
  {
    printf("�������Ӧ<=%d,����������.\n",m_iVexNum*(m_iVexNum-1)/2);
    
    scanf("%d",&m_iArcNum);
  }

	scanf("%d",&m_bContainInfor);

	printf("������%d�������ֵ:\n",m_iVexNum);

	int i =0;

  VEXDATA v;
  for (i=0;i<m_iVexNum;++i)  // ����¼�붥��Ҳ��Ҫ�Ľ�  ÿ��¼�붥�����Ƕ�У�� �Ƿ�������Ѿ�����
  {
    scanf(" %c",&v); // �������͸��� �������������Ҳ��Ҫ����
    
    if (LocateVex(v)!=-1) // ���Ǵ���
    {
      printf("�����Ѿ����ڣ���������ֵ.\n");
      
      --i;
      
      continue;
    }
    else
    {
      m_Vexs[i] = v;
    }
  }

	InitAdjMart(INT_MAX);

	int ia,ib;
	VEXDATA va,vb;
	int Weight= 0;

	for (i=0;i<m_iArcNum;++i)
	{
		printf("%d�ߵ������˵㡢Ȩֵ\n",i+1);

		scanf(" %c %c",&va,&vb);
		scanf("%d",&Weight);

		ia = LocateVex(va);
		ib = LocateVex(vb);

		if (ia==-1 || ib==-1 || ia==ib || m_Arcs[ia][ib].iAdj!=INT_MAX)
		{
      printf("����������������.\n");
      --i;
     
      continue;
    }
		
		m_Arcs[ia][ib].iAdj = m_Arcs[ib][ia].iAdj = Weight;

		if (m_bContainInfor)
		{
			CHAR pszBuffer[MAX_INFO];
			
			memset(pszBuffer,0,MAX_INFO);

			printf("����Ϣ:");
			
			scanf("%s",pszBuffer);
			
			int nBufferLen = strlen(pszBuffer);
			
			if (nBufferLen)
			{
				m_Arcs[ia][ib].pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1));
				
				memset(m_Arcs[ia][ib].pInfor,0,sizeof(CHAR)*(nBufferLen+1));
				
				memcpy(m_Arcs[ia][ib].pInfor,pszBuffer,sizeof(CHAR)*nBufferLen);
				
				m_Arcs[ib][ia].pInfor = m_Arcs[ia][ib].pInfor;
			}
		}


	}

	m_GraphKind = UDN;
	return TRUE;
}
BOOL MG::CreateUDNFromFile(LPCTSTR lpszFile)
{
	FILE* fp = NULL;

	if (NULL==(fp = fopen(lpszFile,"r")))
	{
		return FALSE;
	}
	
	fscanf(fp,"%d",&m_iVexNum);
	
	fscanf(fp,"%d",&m_iArcNum);

  if (m_iArcNum>m_iVexNum*(m_iVexNum-1)/2)
  {
    exit(0);
  }
	

	fscanf(fp,"%d",&m_bContainInfor);
	
	int i =0;
	
  VEXDATA v;
  for (i=0;i<m_iVexNum;++i)  // ����¼�붥��Ҳ��Ҫ�Ľ�  ÿ��¼�붥�����Ƕ�У�� �Ƿ�������Ѿ�����
  {
    fscanf(fp,"%s",&v); // �������͸��� �������������Ҳ��Ҫ����
    
    if (LocateVex(v)!=-1) // ���Ǵ���
    {
     
      --i;

      --m_iVexNum;
      
      continue;
    }
    else
    {
      m_Vexs[i] = v;
    }
  }
	
	InitAdjMart(INT_MAX);
	
	int ia,ib;
	VEXDATA va,vb;
	int Weight= 0;
	
	for (i=0;i<m_iArcNum;++i)
	{
		
		fscanf(fp,"%s%s",&va,&vb);
		fscanf(fp,"%d",&Weight);
		
		ia = LocateVex(va);
		ib = LocateVex(vb);
		
		if (ia==-1 || ib==-1 || ia==ib ||m_Arcs[ia][ib].iAdj!=INT_MAX)
		{
			--i;
      --m_iArcNum;
      continue;
		}
		
		m_Arcs[ia][ib].iAdj = m_Arcs[ib][ia].iAdj = Weight;
		
		if (m_bContainInfor)
		{
			CHAR pszBuffer[MAX_INFO];
			
			memset(pszBuffer,0,MAX_INFO);
			
			fscanf(fp,"%s",pszBuffer);
			
			int nBufferLen = strlen(pszBuffer);
			
			if (nBufferLen)
			{
				m_Arcs[ia][ib].pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1));
				
				memset(m_Arcs[ia][ib].pInfor,0,sizeof(CHAR)*(nBufferLen+1));
				
				memcpy(m_Arcs[ia][ib].pInfor,pszBuffer,sizeof(CHAR)*nBufferLen);
				
				m_Arcs[ib][ia].pInfor = m_Arcs[ia][ib].pInfor;
			}
		}
		
		
	}
	
	m_GraphKind = UDN;

	
	fclose(fp);
	return TRUE;
}




BOOL MG::DestroyGraph()
{
	int i = 0;
	int j = 0;

	for (i=0;i<m_iVexNum;++i)
	{
		for (j=0;j<m_iVexNum;++j)
		{
			// �Ҳ�֪������ôЩ�жϸ�ʲô �����ò��� ��ε������Ĵ����������
			// ��ʹû��·���Ļ� pInfor Ҳ�� NULL ����
			if ((m_GraphKind==DG&&m_Arcs[i][j].iAdj!=0)||
				(m_GraphKind==DN&&m_Arcs[i][j].iAdj!=INT_MAX)||
				(m_GraphKind==UDG&&m_Arcs[i][j].iAdj!=0)||
				(m_GraphKind==UDN&&m_Arcs[i][j].iAdj!=INT_MAX))
			{
				if (m_Arcs[i][j].pInfor)
				{
					free(m_Arcs[i][j].pInfor);
					
					if (m_GraphKind==DN||m_GraphKind==DG)// ����
					{
						m_Arcs[i][j].pInfor = NULL;
					}

					else // �����ʱ��  �����˵㱣�����Ϣ��һ�µ�
					{
						m_Arcs[i][j].pInfor = m_Arcs[j][i].pInfor= NULL;
					}

				}
			}
		}
	}

	return TRUE;
}
VEXDATA MG::GetVex(int iIndex)
{
	if (iIndex>=m_iVexNum||iIndex<0)
	{
		exit(0);
	}


	return m_Vexs[iIndex];

	
}
BOOL MG::PutVex(VEXDATA v, VEXDATA value)
{
	int iv = LocateVex(v);

	if (iv==-1)
	{
		return FALSE;
	}
	m_Vexs[iv] = value;

	return TRUE;
}

// ��ʼ����: ͼG����,v��G��ĳ������ 
// �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1 
int MG::FirstAdjVex(VEXDATA v)
{
	int iv= LocateVex(v);

	int iInvalidData = 0;

	if (iv==-1)
	{
		return FALSE;
	}

	if (m_GraphKind==DN||m_GraphKind==UDN)
	{
		iInvalidData = INT_MAX;
	}

	int i = 0;
	for (i=0;i<m_iVexNum;++i)
	{
		if (m_Arcs[iv][i].iAdj!=iInvalidData)
		{
			return i;
		}
	}

	return -1;
}
// ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ��� 
// �������: ����v��(�����w��)��һ���ڽӶ�������, 
//           ��w��v�����һ���ڽӶ���,�򷵻�-1 
int MG::NextAdjVex(VEXDATA v,VEXDATA w)
{
	int iv = LocateVex(v);

	int iw = LocateVex(w);

	if (iv==-1 || iw==-1 || iv==iw)
	{
		return -1;
	}

	int iInvalidData = 0;
	if (m_GraphKind==DN||m_GraphKind==UDN)
	{
		iInvalidData=  INT_MAX;
	}

	int i = 0;

	for (i = iw+1;i<m_iVexNum;++i)
	{
		if (m_Arcs[iv][i].iAdj!=iInvalidData)
		{
			return i;
		}
	}
	return -1;
}
// ��ʼ����: ͼG����,v��ͼG�ж�������ͬ���� 
// �������: ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��) 
BOOL MG::InsertVex(VEXDATA v)
{
	if (m_iVexNum>=MAX_VERTEX_NUM)
	{
		return FALSE;
	}
	m_Vexs[m_iVexNum] = v;

	int i = 0;

	// ���κζ��㶼û�л�
	for (i=0;i<=m_iVexNum;++i)
	{
		

		if (m_GraphKind==DN||m_GraphKind==UDN) // �� 
		{
			m_Arcs[m_iVexNum][i].iAdj = INT_MAX;
			m_Arcs[i][m_iVexNum].iAdj = INT_MAX;
		}
		else //  ͼ
		{
			m_Arcs[m_iVexNum][i].iAdj = 0;
			m_Arcs[i][m_iVexNum].iAdj = 0;
		}

		m_Arcs[m_iVexNum][i].pInfor = NULL;
		m_Arcs[i][m_iVexNum].pInfor = NULL;
	}

	++m_iVexNum;
	return TRUE;
}
BOOL MG::DeleteVex(VEXDATA v)
{
	int iv = LocateVex(v);

	if (iv==-1)
	{
		return FALSE;
	}

	int iInvalidData = 0;

	if (m_GraphKind==DN||m_GraphKind==UDN)
	{
		iInvalidData = INT_MAX;
	}

	// ����ļ����

	int i = 0;

	// ����ε���㷨�ĸĽ�
	for (i=0;i<m_iVexNum;++i) // ���Լ�������ɾ����ķ��� ���ֳɵ�ɾ�����ĺ��� Ϊʲô������
	{
		DeleteArc(v,GetVex(i));
	}

	for (i=0;i<m_iVexNum;++i)
	{
		DeleteArc(GetVex(i),v);
	}
// 	for (i=0;i<m_iVexNum;++i)
// 	{
// 		if (m_Arcs[i][iv].iAdj!=iInvalidData) // ע�����ﲻ��ʡ�� Ҫ�ж���û�л� �в�-1 û������жϾ��޷�-1
// 		{
// 			if (m_Arcs[i][iv].pInfor) // ���˵���  �뻡
// 			{
// 				free(m_Arcs[i][iv].pInfor);
// 
// 				m_Arcs[i][iv].pInfor = NULL;
// 			}
// 			
// 			m_Arcs[i][iv].iAdj=iInvalidData; // �Ҽӵ�
// 
// 			--m_iArcNum;
// 
// 		}
// 
// 	}
// 
// 	// ����� 
// 	if (m_GraphKind==DN||m_GraphKind==DG) 
// 	{
// 		for (i=0;i<m_iVexNum;++i)
// 		{
// 			if (m_Arcs[iv][i].iAdj!=iInvalidData) // ��������  ����
// 			{
// 				if (m_Arcs[iv][i].pInfor)
// 				{
// 					free(m_Arcs[iv][i].pInfor);
// 
// 					m_Arcs[iv][i].pInfor = NULL;
// 				}
// 				
// 				m_Arcs[iv][i].iAdj = iInvalidData;
// 
// 				--m_iArcNum;
// 			}
// 		}
// 	}


	//  �ַ�����ǰ��

	for (i=iv+1;i<m_iVexNum;++i)
	{
		m_Vexs[i-1] = m_Vexs[i];
	}

	// �ƶ�����


	int j = 0;

	for (i=0;i<m_iVexNum;++i)
	{
		for (j=iv;j<m_iVexNum;++j)
		{
			m_Arcs[i][j] = m_Arcs[i][j+1]; // �����ƶ�
		} 
	}

	for (i=0;i<m_iVexNum;++i)
	{
		for (j=iv;j<m_iVexNum;++j)
		{
			m_Arcs[j][i] = m_Arcs[j+1][i]; // �����ƶ�
		}
	}

	--m_iVexNum;
	return TRUE;
}

BOOL MG::InsertArc(VEXDATA v,VEXDATA w)
{
	int iv = LocateVex(v);

	int iw = LocateVex(w);

	if (iv==-1||iw==-1||iv==iw)
	{
		return FALSE;
	}

	++m_iArcNum;

	if (m_GraphKind==DN||m_GraphKind==UDN)
	{
		printf("����Ȩֵ");

		scanf("%d",&m_Arcs[iv][iw].iAdj);
	}

	if (m_bContainInfor)
	{
		printf("������Ϣ(<%d�ַ�)",MAX_INFO);

		TCHAR pszBuffer[MAX_INFO];

		memset(pszBuffer,0,MAX_INFO);

		scanf("%s",pszBuffer);

		int nBufferLen = strlen(pszBuffer);

		if (nBufferLen)
		{
			m_Arcs[iv][iw].pInfor = (PCHAR)malloc(sizeof(CHAR)*(nBufferLen+1));

			if (!m_Arcs[iv][iw].pInfor)
			{
				exit(0);
			}

			memset(m_Arcs[iv][iw].pInfor,0,sizeof(CHAR)*(nBufferLen+1));

			memcpy(m_Arcs[iv][iw].pInfor,pszBuffer,sizeof(CHAR)*nBufferLen);
		}
	}

	if (m_GraphKind==UDG||m_GraphKind==UDN) // ���� �Գ�
	{
		m_Arcs[iw][iv].iAdj= m_Arcs[iv][iw].iAdj;

		m_Arcs[iw][iv].pInfor = m_Arcs[iv][iw].pInfor;
	}

	return TRUE;
}
BOOL MG::DeleteArc(VEXDATA v,VEXDATA w) // Ҫ�ж���������ڲ����� ��ε���Ĵ���û���ж�
{										// ������ʹҪɾ���Ļ�������  ������ĿҲ���Լ�
	int iv = LocateVex(v);

	int iw = LocateVex(w);

	if (iw==-1 || iv==-1 || iw==iv)
	{
		return FALSE;
	}
	
	int iInvalidData = 0;

	if (m_GraphKind==DN || m_GraphKind==UDN)
	{
		iInvalidData = INT_MAX;
	}
	// ��һ���ж�
	if (m_Arcs[iv][iw].iAdj==iInvalidData) // ��Ч�ͷ���
	{
		return FALSE;
	}
	
	m_Arcs[iv][iw].iAdj = iInvalidData;

	if (m_Arcs[iv][iw].pInfor)
	{
		free(m_Arcs[iv][iw].pInfor);
		m_Arcs[iv][iw].pInfor = NULL;
	}

	if (m_GraphKind==UDG||m_GraphKind==UDN) // �������� �ԳƵ���Ҫ����  pInfor ָ��ͬһ���ڴ�
	{
		m_Arcs[iw][iv].pInfor = NULL;

		m_Arcs[iw][iv].iAdj = m_Arcs[iv][iw].iAdj;
	}

	--m_iArcNum;
	return TRUE;
}
BOOL MG::MakeUnVisited()
{
	int i = 0;

	for(i=0;i<m_iVexNum;++i)
	{
		m_bVisited[i] = FALSE;
	}

	return TRUE;
}
BOOL MG::DFS(int iIndex)
{
	m_bVisited[iIndex] = TRUE;

	VEXDATA v= GetVex(iIndex);
	printf("%c ",v);

	int i =0;

	for (i=FirstAdjVex(v);i>=0;i=NextAdjVex(v,GetVex(i)))
	{
		if (!m_bVisited[i])
		{
			DFS(i);
		}
	}


	return TRUE;
}
BOOL MG::DFSTraverse()
{
	MakeUnVisited();

	int i = 0;

	for (i=0;i<m_iVexNum;++i)
	{
		if (!m_bVisited[i])
		{
			DFS(i);
		}
	}

	printf("\n");
	return TRUE;
}

BOOL MG::BFSTraverse()
{
	MakeUnVisited();

	int i = 0;

	int j =0;

	int k = 0;

	VEXDATA jv;

	QUEUE Q;
	Q.InitQueue();

	for (i=0;i<m_iVexNum;++i)
	{
		if (!m_bVisited[i])
		{
			m_bVisited[i] = TRUE;

			printf("%c ",GetVex(i));

			Q.EnQueue(i);

			while (!Q.QueueIsEmpty())
			{
				Q.DeQueue(j);

				jv = GetVex(j);

				for (k=FirstAdjVex(jv);k>=0;k=NextAdjVex(jv,GetVex(k)))
				{
					if (!m_bVisited[k])
					{
						m_bVisited[k] = TRUE;

						printf("%c ",GetVex(k));

						Q.EnQueue(k);
					}
				}
			}
		}
	}

	printf("\n");
	Q.DestroyQueue();
	return TRUE;
}

BOOL MG::Display()
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

	printf("%d������%d��%s��%s",m_iVexNum,m_iArcNum,pszEdgeKind,pszGraphKind);

	printf("����ֱ�Ϊ��\n");

	int i =0;

	for (i=0;i<m_iVexNum;++i)
	{
		printf("Vexs[%d]=%c\n",i,GetVex(i));
	}

	int j = 0;

	printf("����Ϊ��\n");

	for (i=0;i<m_iVexNum;++i)
	{
		for (j=0;j<m_iVexNum;++j)
		{
			if (m_Arcs[i][j].iAdj==INT_MAX)
			{
				printf("%6s","��");
			}

			else
			{
				printf("%6d",m_Arcs[i][j].iAdj);
			}
		}

		printf("\n");
	}

	if (m_bContainInfor)
	{
		printf(" ��β  ��ͷ  ��%s��Ϣ:\n",pszEdgeKind);

		if (m_GraphKind==DG||m_GraphKind==DN)// ���� ���մ�
		{
			for (i=0;i<m_iVexNum;++i)
			{
				for (j=0;j<m_iVexNum;++j)
				{
					
					if (m_Arcs[i][j].pInfor)
					{
						printf("%5c %5c     %s\n",GetVex(i),GetVex(j),m_Arcs[i][j].pInfor);// ����%s Ϊ %c
					}
					
					
					
				}
			}
			
		}
		
		
		else// ���� �ǶԳƵ� ���� ���ܴ�ӡ�ظ�
		{
			for (i=0;i<m_iVexNum;++i)
			{
				for (j=i+1;j<m_iVexNum;++j) // Ϊʲô�� i+1 ��Ϊ a ��a û�л� ���ԶԽ��߾Ͳ�����
				{
					
					if (m_Arcs[i][j].pInfor)
					{
						printf("%5c %5c     %s\n",GetVex(i),GetVex(j),m_Arcs[i][j].pInfor);// ����%s Ϊ %c
					}
					
					
					
				}
			}
		}
	}

	return TRUE;
}

int MG::GetVexDegree(VEXDATA v)
{
  if (LocateVex(v)==-1)
  {
    return -1;
  }
  int iDegree = 0;
  
  int iv = LocateVex(v);

  if (m_GraphKind==DG||m_GraphKind==DN) // �������
  {
    iDegree = GetVexOutDegree(v)+GetVexInDegree(v);
  }
  else
  {
     int i =0;

     int iInvalidData = 0;

     if (m_GraphKind==UDN)
     {
       iInvalidData = INT_MAX;
     }
     for (i=0;i<m_iVexNum;++i)
     {
       if (m_Arcs[iv][i].iAdj!=iInvalidData)
       {
         ++iDegree;
       }
     }
  }
  return iDegree;
}
int MG::GetVexOutDegree(VEXDATA v)
{
  if (LocateVex(v)==-1 ||m_GraphKind==UDN||m_GraphKind==UDG)
  {
    return -1;
  }

  int iDegree = 0;

  int iInvalidData = 0;

  int iv=  LocateVex(v);


  if (m_GraphKind==DN)
  {
    iInvalidData = INT_MAX;
  }

  int i =0;

  for (i=0;i<m_iVexNum;++i)
  {
    if (m_Arcs[iv][i].iAdj!=iInvalidData)
    {
      ++iDegree;
    }
  }

  return iDegree;
}
int MG::GetVexInDegree(VEXDATA v)
{
  if (LocateVex(v)==-1 ||m_GraphKind==UDN||m_GraphKind==UDG)
  {
    return -1;
  }

  int iDegree = 0;

  int iInvalidData = 0;
  
  int iv=  LocateVex(v);
  
  
  if (m_GraphKind==DN)
  {
    iInvalidData = INT_MAX;
  }
  
  int i =0;
  
  for (i=0;i<m_iVexNum;++i)
  {
    if (m_Arcs[i][iv].iAdj!=iInvalidData)
    {
      ++iDegree;
    }
  }

  return iDegree;
}

BOOL MG::MiniSpanTree_PRIM(VEXDATA u)
{
  int iu = LocateVex(u);
  
  if (iu==-1)
  {
    return FALSE;
  }
  
  int SumWeight = 0;
  
  MiniSide CloseEdge[MAX_VERTEX_NUM];
  
  memset(CloseEdge,0,sizeof(MiniSide)*MAX_VERTEX_NUM);
  
  int i = 0;
  
  for (i=0;i<m_iVexNum;++i)
  {
    if (i!=iu)
    {
      CloseEdge[i].AdjVex = u;
      CloseEdge[i].iLowCost = m_Arcs[iu][i].iAdj;
    }
  }
  
  CloseEdge[iu].iLowCost = 0;
  
  int k = 0;
  
  int j = 0;
  
  printf("��С��������������Ҫ�ĸ���������:\n");
  
  for (i=1;i<m_iVexNum;++i)
  {
    k = MiniNum(CloseEdge);
    
    printf("(%c,%c) ",CloseEdge[k].AdjVex,GetVex(k));
    
    SumWeight += m_Arcs[LocateVex(CloseEdge[k].AdjVex)][k].iAdj;
    
    CloseEdge[k].iLowCost = 0;
    
    for (j=0;j<m_iVexNum;++j)
    {
      if (m_Arcs[k][j].iAdj<CloseEdge[j].iLowCost)
      {
        CloseEdge[j].AdjVex = m_Vexs[k];
        
        CloseEdge[j].iLowCost = m_Arcs[k][j].iAdj;
      }
    }
  }
  
  printf("��·����:%d\n",SumWeight);
  
}
int MG::MiniNum(MiniSide* SZ)
{
  int i = 0;
  while (!SZ[i].iLowCost)
  {
    ++i;
  }

  int Min = SZ[i].iLowCost;

  int k = i;

  int j = 0;

  for (j=i+1;j<m_iVexNum;++j)
  {
    if (SZ[j].iLowCost >0)
    {
      if (Min>SZ[j].iLowCost)
      {
        Min = SZ[j].iLowCost;

        k = j;
      }
    }
  }

 return k;
}






// ����  
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