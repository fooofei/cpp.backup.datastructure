#include <STDIO.H>
#include <WINDOWS.H>
#include <LIMITS.H>

// 注意 ： 有向图中叫弧 Arc  
//		无向图中叫 边 Edge
//		弧尾-》 弧头
// 无向的时候  两个端点保存的信息是一致的
// 这是我自己写 程序 对严蔚敏的程序代码加以优化 改进 封装为类

// author:
// datatime:2012-9-15
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


#define  MAX_VERTEX_NUM 20// 最大顶点个数
#define  MAX_INFO	20	// 输入信息的字符数
typedef enum{DG,DN,UDG,UDN}GraphKind;// 有向图,有向网,无向图,无向网
#define  VEXDATA CHAR

struct ArcCell // 矩阵数据类型
{
	int iAdj; // 图 就是0 or 1  网 就是权值 或者 无穷
	
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
	VEXDATA m_Vexs[MAX_VERTEX_NUM]; // 顶点
	BOOL	m_bVisited[MAX_VERTEX_NUM]; // 顶点是否被访问
	ArcCell m_Arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int		m_iArcNum;
	int		m_iVexNum;
	GraphKind m_GraphKind;
	BOOL	m_bContainInfor;
public:
	
	int LocateVex(VEXDATA u);
	BOOL InitAdjMart(int iInvalidData); // 初始化邻接矩阵  
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

  BOOL MiniSpanTree_PRIM(VEXDATA u); // 求最小生成树  经过所有的顶点  最小生成树是唯一的
  int MiniNum(MiniSide* SZ);
};
int main(int argc, char* argv[])
{

  MG G;
  
  if (G.CreateUDNFromFile("UDN.txt"))
  {
    printf("打印:\n");
    G.Display();
    
    printf("深度优先遍历:\n");
    
    G.DFSTraverse();
    
    printf("广度优先遍历:\n");
    
    G.BFSTraverse();
    
    printf("最小生成树\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(0));
    
    printf("最小生成树\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(1));
    
    printf("最小生成树\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(2));

    printf("最小生成树\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(3));

    printf("最小生成树\n");
    
    G.MiniSpanTree_PRIM(G.GetVex(4));

    printf("最小生成树\n");
    
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
		if (u==m_Vexs[i]) // 这里的比较 以后 数据类型更改的时候 需要更改这里
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
	printf("请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0):\n");

	scanf("%d",&m_iVexNum);

	scanf("%d",&m_iArcNum);

  while (m_iArcNum>m_iVexNum*(m_iVexNum-1)/2)
  {
    printf("输入边数应<=%d,请重新输入.\n",m_iVexNum*(m_iVexNum-1)/2);
    
    scanf("%d",&m_iArcNum);
  }

	scanf("%d",&m_bContainInfor);

	printf("请输入%d个顶点的值:\n",m_iVexNum);

	int i =0;

  VEXDATA v;
  for (i=0;i<m_iVexNum;++i)  // 这里录入顶点也需要改进  每次录入顶点我们都校验 是否该数据已经存在
  {
    scanf(" %c",&v); // 数据类型更改 这里的输入数据也需要更改
    
    if (LocateVex(v)!=-1) // 就是存在
    {
      printf("数据已经存在，输入其他值.\n");
      
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
		printf("%d边的两个端点、权值\n",i+1);

		scanf(" %c %c",&va,&vb);
		scanf("%d",&Weight);

		ia = LocateVex(va);
		ib = LocateVex(vb);

		if (ia==-1 || ib==-1 || ia==ib || m_Arcs[ia][ib].iAdj!=INT_MAX)
		{
      printf("输入有误，重新输入.\n");
      --i;
     
      continue;
    }
		
		m_Arcs[ia][ib].iAdj = m_Arcs[ib][ia].iAdj = Weight;

		if (m_bContainInfor)
		{
			CHAR pszBuffer[MAX_INFO];
			
			memset(pszBuffer,0,MAX_INFO);

			printf("边信息:");
			
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
  for (i=0;i<m_iVexNum;++i)  // 这里录入顶点也需要改进  每次录入顶点我们都校验 是否该数据已经存在
  {
    fscanf(fp,"%s",&v); // 数据类型更改 这里的输入数据也需要更改
    
    if (LocateVex(v)!=-1) // 就是存在
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
			// 我不知道做这么些判断干什么 根本用不到 严蔚敏上面的代码就是这样
			// 即使没有路径的话 pInfor 也是 NULL 的嘛
			if ((m_GraphKind==DG&&m_Arcs[i][j].iAdj!=0)||
				(m_GraphKind==DN&&m_Arcs[i][j].iAdj!=INT_MAX)||
				(m_GraphKind==UDG&&m_Arcs[i][j].iAdj!=0)||
				(m_GraphKind==UDN&&m_Arcs[i][j].iAdj!=INT_MAX))
			{
				if (m_Arcs[i][j].pInfor)
				{
					free(m_Arcs[i][j].pInfor);
					
					if (m_GraphKind==DN||m_GraphKind==DG)// 有向
					{
						m_Arcs[i][j].pInfor = NULL;
					}

					else // 无向的时候  两个端点保存的信息是一致的
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

// 初始条件: 图G存在,v是G中某个顶点 
// 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 
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
// 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 
// 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号, 
//           若w是v的最后一个邻接顶点,则返回-1 
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
// 初始条件: 图G存在,v和图G中顶点有相同特征 
// 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) 
BOOL MG::InsertVex(VEXDATA v)
{
	if (m_iVexNum>=MAX_VERTEX_NUM)
	{
		return FALSE;
	}
	m_Vexs[m_iVexNum] = v;

	int i = 0;

	// 到任何顶点都没有弧
	for (i=0;i<=m_iVexNum;++i)
	{
		

		if (m_GraphKind==DN||m_GraphKind==UDN) // 网 
		{
			m_Arcs[m_iVexNum][i].iAdj = INT_MAX;
			m_Arcs[i][m_iVexNum].iAdj = INT_MAX;
		}
		else //  图
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

	// 有向的加情况

	int i = 0;

	// 对严蔚敏算法的改进
	for (i=0;i<m_iVexNum;++i) // 我自己更换的删除点的方法 有现成的删除弧的函数 为什么不用呢
	{
		DeleteArc(v,GetVex(i));
	}

	for (i=0;i<m_iVexNum;++i)
	{
		DeleteArc(GetVex(i),v);
	}
// 	for (i=0;i<m_iVexNum;++i)
// 	{
// 		if (m_Arcs[i][iv].iAdj!=iInvalidData) // 注意这里不能省略 要判断有没有弧 有才-1 没有这个判断就无法-1
// 		{
// 			if (m_Arcs[i][iv].pInfor) // 别人到它  入弧
// 			{
// 				free(m_Arcs[i][iv].pInfor);
// 
// 				m_Arcs[i][iv].pInfor = NULL;
// 			}
// 			
// 			m_Arcs[i][iv].iAdj=iInvalidData; // 我加的
// 
// 			--m_iArcNum;
// 
// 		}
// 
// 	}
// 
// 	// 有向的 
// 	if (m_GraphKind==DN||m_GraphKind==DG) 
// 	{
// 		for (i=0;i<m_iVexNum;++i)
// 		{
// 			if (m_Arcs[iv][i].iAdj!=iInvalidData) // 它到别人  出弧
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


	//  字符数组前移

	for (i=iv+1;i<m_iVexNum;++i)
	{
		m_Vexs[i-1] = m_Vexs[i];
	}

	// 移动矩阵


	int j = 0;

	for (i=0;i<m_iVexNum;++i)
	{
		for (j=iv;j<m_iVexNum;++j)
		{
			m_Arcs[i][j] = m_Arcs[i][j+1]; // 纵向移动
		} 
	}

	for (i=0;i<m_iVexNum;++i)
	{
		for (j=iv;j<m_iVexNum;++j)
		{
			m_Arcs[j][i] = m_Arcs[j+1][i]; // 横向移动
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
		printf("输入权值");

		scanf("%d",&m_Arcs[iv][iw].iAdj);
	}

	if (m_bContainInfor)
	{
		printf("输入信息(<%d字符)",MAX_INFO);

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

	if (m_GraphKind==UDG||m_GraphKind==UDN) // 无向 对称
	{
		m_Arcs[iw][iv].iAdj= m_Arcs[iv][iw].iAdj;

		m_Arcs[iw][iv].pInfor = m_Arcs[iv][iw].pInfor;
	}

	return TRUE;
}
BOOL MG::DeleteArc(VEXDATA v,VEXDATA w) // 要判断这个弧存在不存在 严蔚敏的代码没有判断
{										// 这样即使要删除的弧不存在  弧的数目也会自减
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
	// 加一个判断
	if (m_Arcs[iv][iw].iAdj==iInvalidData) // 无效就返回
	{
		return FALSE;
	}
	
	m_Arcs[iv][iw].iAdj = iInvalidData;

	if (m_Arcs[iv][iw].pInfor)
	{
		free(m_Arcs[iv][iw].pInfor);
		m_Arcs[iv][iw].pInfor = NULL;
	}

	if (m_GraphKind==UDG||m_GraphKind==UDN) // 对于无向 对称的需要重置  pInfor 指向同一块内存
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
			strcpy(pszGraphKind,"有向图");
			strcpy(pszEdgeKind,"弧");
			break;
		}
	case DN:
		{
			strcpy(pszGraphKind,"有向网");
			strcpy(pszEdgeKind,"弧");
			break;
		}

	case UDG:
		{
			strcpy(pszGraphKind,"无向图");
			strcpy(pszEdgeKind,"边");
			break;
		}
	case UDN:
		{
			strcpy(pszGraphKind,"无向网");

			strcpy(pszEdgeKind,"边");
			break;
		}
	}

	printf("%d个顶点%d条%s的%s",m_iVexNum,m_iArcNum,pszEdgeKind,pszGraphKind);

	printf("顶点分别为：\n");

	int i =0;

	for (i=0;i<m_iVexNum;++i)
	{
		printf("Vexs[%d]=%c\n",i,GetVex(i));
	}

	int j = 0;

	printf("矩阵为：\n");

	for (i=0;i<m_iVexNum;++i)
	{
		for (j=0;j<m_iVexNum;++j)
		{
			if (m_Arcs[i][j].iAdj==INT_MAX)
			{
				printf("%6s","∞");
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
		printf(" 弧尾  弧头  该%s信息:\n",pszEdgeKind);

		if (m_GraphKind==DG||m_GraphKind==DN)// 有向 就照打
		{
			for (i=0;i<m_iVexNum;++i)
			{
				for (j=0;j<m_iVexNum;++j)
				{
					
					if (m_Arcs[i][j].pInfor)
					{
						printf("%5c %5c     %s\n",GetVex(i),GetVex(j),m_Arcs[i][j].pInfor);// 更改%s 为 %c
					}
					
					
					
				}
			}
			
		}
		
		
		else// 无向 是对称的 所以 不能打印重复
		{
			for (i=0;i<m_iVexNum;++i)
			{
				for (j=i+1;j<m_iVexNum;++j) // 为什么是 i+1 因为 a 到a 没有弧 所以对角线就不考虑
				{
					
					if (m_Arcs[i][j].pInfor)
					{
						printf("%5c %5c     %s\n",GetVex(i),GetVex(j),m_Arcs[i][j].pInfor);// 更改%s 为 %c
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

  if (m_GraphKind==DG||m_GraphKind==DN) // 有向最简单
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
  
  printf("最小代价生成树的需要的各边依次是:\n");
  
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
  
  printf("总路径是:%d\n",SumWeight);
  
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






// 队列  
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