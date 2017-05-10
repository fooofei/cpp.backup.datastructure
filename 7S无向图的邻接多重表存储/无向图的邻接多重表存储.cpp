#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX_VERTEX_NUM 20
#define MAX_INFOR 20

#define  QUEUESIZESTEP 3 // 队列长度每一步加和
#define  QUEUEDATA int  // 每次使用 需要更改的数据类型
typedef enum{unvisited,visited}VisitIf;

// 在邻接多重表中所有依附于同一顶点的边串联在
// 同一链表中 由于每条边依附于两个顶点 则每个边节点同时链接在
// 两个链表中

// 与邻接表的差别  同一条边在邻接表中用两个结点表示
// 在临界多重表中只有一个结点 
typedef struct EBox 
{
	VisitIf mark;
	int ivex;
	int jvex;
	EBox* iLink;
	EBox* jLink;
	char* pInfor;
}EBox;


typedef struct  
{
	char data;
	EBox* firstedge;
}VexBox;

typedef struct
{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum;
	int edgenum;
}AMLGraph;


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



int LocateVex(AMLGraph G,char u);
bool CreateGraph(AMLGraph* G);    /* 采用邻接多重表存储结构,构造无向图G */

char GetVex(AMLGraph G,int v);
bool PutVex(AMLGraph* G,char v,char value);

int FirstAdjVex(AMLGraph G,char v);

int NextAdjVex(AMLGraph G,char v,char w);

bool InsertVex(AMLGraph* G,char v);

bool DeleteArc(AMLGraph* G,char v,char w);

bool InsertArc(AMLGraph* G,char v,char w);

bool DeleteVex(AMLGraph* G,char v);

void MarkUnVisited(AMLGraph G);


void Display(AMLGraph G);


void DestroyGraph(AMLGraph* G);


void DFSTraverse(AMLGraph G);

void DFS(AMLGraph G,int v);

void BFSTraverse(AMLGraph G);

bool CreateGraphFromFile(AMLGraph* G,LPCTSTR lpszFile);

void Visit(char p)
{
	printf("%c ",p);
	
}

void (*VisitFunc)(char);  //全局函数指针 

bool visit[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */


void main()
{

  AMLGraph G;
  CreateGraphFromFile(&G,"1.txt");
 
  Display(G);


  
VisitFunc = Visit;
  DFSTraverse(G);
  BFSTraverse(G);

// a b c d e f g h
// a c b h d e g f

  DestroyGraph(&G);

  Display(G);


}

int LocateVex(AMLGraph G,char u)
{
	int i = 0;

	for (i=0;i<G.vexnum;i++)
	{
		if (G.adjmulist[i].data==u)
		{
			return i;
		}
	}

	return -1;
}

bool CreateGraph(AMLGraph* G)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int IncInfor = 0;

	char s[MAX_INFOR] = {0};

	char va,vb;

	EBox* p = NULL;

	printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1，否:0):\n");


	scanf("%d",&G->vexnum);

	scanf("%d",&G->edgenum);


//	scanf("%d",&IncInfor);

  IncInfor = 0;

	printf("请输入%d个顶点的值:\n",(*G).vexnum);

	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->adjmulist[i].data);

		G->adjmulist[i].firstedge = NULL;
	}

	printf("请顺序输入每条边的两个端点:\n");

	for (k=0;k<G->edgenum;k++)
	{
		scanf(" %c",&va);

		scanf(" %c",&vb);

		i = LocateVex(*G,va);
		j = LocateVex(*G,vb);

    if (i==-1||j==-1)
    {
      return false;
    }


		p = (EBox*)malloc(sizeof(EBox));


		p->mark = unvisited;

		p->ivex = i;

		p->jvex = j;

		p->pInfor = NULL;


		p->iLink = G->adjmulist[i].firstedge;

		G->adjmulist[i].firstedge = p;


		p->jLink = G->adjmulist[j].firstedge;

		G->adjmulist[j].firstedge = p;

		if (IncInfor)
		{
			 printf("请输入该弧的相关信息\n");


			 scanf("%s",s);

			 l = strlen(s);

			 if (l)
			 {
				 p->pInfor = (char*)malloc(sizeof(char)*(l+1));

				 strcpy(p->pInfor,s);


			 }
		}
	}


	return true;
}

bool CreateGraphFromFile(AMLGraph* G,LPCTSTR lpszFile)
{
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int IncInfor = 0;
  
  char s[MAX_INFOR] = {0};
  
  char va,vb;
  
  EBox* p = NULL;
  
  int Infor = 0;
  FILE* fp= fopen(lpszFile,"r");

  fscanf(fp,"%d",&G->vexnum);
  fscanf(fp,"%d",&G->edgenum);
  fscanf(fp,"%d",&Infor); // 为了对应格式一致
  
  for (i=0;i<G->vexnum;i++)
  {
    fscanf(fp,"%s",&G->adjmulist[i].data);
    
    G->adjmulist[i].firstedge = NULL;
  }
   

  
  for (k=0;k<G->edgenum;k++)
  {
    fscanf(fp,"%s%s",&va,&vb);
    
    i = LocateVex(*G,va);
    j = LocateVex(*G,vb);
    
    if (i==-1||j==-1)
    {
      return false;
    }
    
    
    p = (EBox*)malloc(sizeof(EBox));
    
    
    p->mark = unvisited;
    
    p->ivex = i;
    
    p->jvex = j;
    
    p->pInfor = NULL;
    
    
    p->iLink = G->adjmulist[i].firstedge;
    
    G->adjmulist[i].firstedge = p;
    
    
    p->jLink = G->adjmulist[j].firstedge;
    
    G->adjmulist[j].firstedge = p;
    
  }
  fclose(fp);
  
  return true;
}


char GetVex(AMLGraph G,int v)
{
	if (v>=G.vexnum||v<0)
	{
		exit(0);
	}

	return G.adjmulist[v].data;
}

bool PutVex(AMLGraph* G,char v,char value)
{
	int i = 0;

	i = LocateVex(*G,v);


	if (i<0)
	{
		return false;
	}

	G->adjmulist[i].data = value;


	return true;
}


int FirstAdjVex(AMLGraph G,char v)
{
  /* 初始条件: 有向图G存在,v是G中某个顶点 */
   /* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
	int i = 0;

	i = LocateVex(G,v);

	if (i<0)
	{
		return -1;
	}

	if (G.adjmulist[i].firstedge)
	{
		if (G.adjmulist[i].firstedge->ivex==i)
		{
			return G.adjmulist[i].firstedge->jvex;
		}

		else
		{
			return G.adjmulist[i].firstedge->ivex;   //   无向图的处理
		}



	}
		return -1;
	
}

/* 初始条件: 无向图G存在,v是G中某个顶点,w是v的邻接顶点 */
/* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。 */
   /*           若w是v的最后一个邻接点,则返回-1 */
int NextAdjVex(AMLGraph G,char v,char w)
{
  
	int i = 0;
	int j = 0;

	EBox* p = NULL;
	i = LocateVex(G,v);
	j = LocateVex(G,w);


	if (i<0||j<0)
	{
		return -1;
	}

  // 先沿着i的路径找到 两头是 i 和 j 的弧

	p = G.adjmulist[i].firstedge;

	while (p)
	{
		if (p->ivex==i&&p->jvex!=j)  // 不是邻接顶点w(情况1) 
		{

			p = p->iLink;
		}

		else if (p->jvex==i&&p->ivex!=j)  //不是邻接点  无向图 的另一种情况
		{
			p = p->jLink;
		}

		else
		{
			break;// 是邻接顶点w 
		}
  } // 找到了 


	if (p&&p->ivex==i&&p->jvex==j)  // 找到邻接顶点w(情况1)   
	{
		p = p->iLink;  

		if (p&&p->ivex==i) // 
		{
			return p->jvex;
		}

		else if (p&&p->jvex==i)
		{
			return p->ivex;
		}

	}


	if (p&&p->ivex==j&&p->jvex==i) // 找到邻接顶点w(情况2) 
	{
		p = p->jLink;

		if (p&&p->ivex==i)
		{
			return p->jvex;
		}

		else if (p&&p->jvex==i)
		{
			return p->ivex;
		}
	}


	return -1;

}

bool InsertVex(AMLGraph* G,char v)
{
	if (G->vexnum==MAX_VERTEX_NUM)
	{
		return false;
	}

	if (LocateVex(*G,v)>=0)   //节点存在
	{
		 return false;
	}



	G->adjmulist[G->vexnum].data = v;

	G->adjmulist[G->vexnum].firstedge = NULL;


	G->vexnum++;


	return true;
}


bool DeleteArc(AMLGraph* G,char v,char w) // 删弧
{
	int i = 0;

	int j = 0;

	EBox* p = NULL;

	EBox* q = NULL;


	i = LocateVex(*G,v);

	j = LocateVex(*G,w);


	if (i<0||j<0||i==j)
	{
		return false;
	}

	p = G->adjmulist[i].firstedge;

	if (p&&p->jvex==j)  // 第1条边即为待删除边(情况1)   yes
	{
		G->adjmulist[i].firstedge = p->iLink;
    // 这里有个疑问 我们是寻找一条以 i j  为端点的弧 可是 我们并没有判断两个 比如说这样
    // p->ivex==i && p->jvex==j 我们只用了 p->jvex==j  为什么呢  
    // 因为这是从 i 的边缘寻找的  必然与i 有关系  所以  我们只需要看跟j有没有关系就行了 
	}

	else if (p&&p->ivex==j) // 第1条边即为待删除边(情况2) 
	{
		G->adjmulist[i].firstedge = p->jLink;
	}

	else// 第1条边不是待删除边 
	{

		while(p)
		{
			if (p->ivex==i&&p->jvex!=j)// 不是待删除边
			{
				q = p;      // q is the p of pre node       yes

				p = p->iLink; // 找下一个邻接顶点
			}

			else if (p->jvex==i&&p->ivex!=j)
			{

				q = p;

				p = p->jLink;
			}

			else
			{
				break;// 是邻接顶点
			}

		}

		if (!p)// 如果没有找到  就返回了  所以下面的从反方向寻找不会说产生内存错误
		{
			return false;
		}

		if (p->ivex==i&&p->jvex==j) // 找到弧<v,w>(情况1)  yes
		{

			if (q->ivex==i) // the p of pre 
			{
				q->iLink = p->iLink;
			}

			else
			{
				q->jLink = p->iLink;
			}
		}

		else if (p->ivex==j&&p->jvex==i)// 找到弧<v,w>(情况2) 
		{
			if (q->ivex==i)
			{
				q->iLink = p->jLink;
			}

			else
			{
				q->jLink = p->jLink;
			}
		}
	}


	 // 以下由另一顶点起找待删除边且删除之

	p = G->adjmulist[j].firstedge;


	if (p->jvex==i )// (j,i)  yes  第一结点  
	{
		G->adjmulist[j].firstedge = p->iLink;

		if (p->pInfor)
		{
			free(p->pInfor);
		}

		free(p);
	}

	else if (p->ivex==i) // (i,j)  yes 第一结点
	{
		G->adjmulist[j].firstedge = p->jLink;

		if (p->pInfor)
		{
			free(p->pInfor);
		}

		free(p);
	}

	else// 第1条边不是待删除边
	{
		while (p)// 向后查找弧<v,w>
		{
			if (p->ivex==j&&p->jvex!=i)
			{
				q = p;

				p = p->iLink;
			}

			else if (p->jvex==j&&p->ivex!=i)
			{
				q = p;

				p = p->jLink;
			}

			else
			{
				break;
			}
		}

    if (!p) 
    {
      return false;
    }
		if (p->ivex==i&&p->jvex==j) //
		{
			if (q->ivex==j)
			{
				q->iLink = p->jLink;
			}

			else
			{
				q->jLink = p->jLink;
			}

			if (p->pInfor)
			{
				free(p->pInfor);
			}

			free(p);
		}
		
		else if (p->ivex==j&&p->jvex==i)
		{
			if (q->ivex==j)
			{
				q->iLink = p->iLink;
			}

			else
			{
				q->jLink = p->iLink;
			}

			if (p->pInfor)
			{
				free(p->pInfor);
			}

			free(p);

		}
	}

	G->edgenum--;

	return true;
}





bool InsertArc(AMLGraph* G,char v,char w) // 插弧
{
	int i = 0;
	int j = 0;
	int l = 0;

	int IncInfor = 0;


	char s[MAX_INFOR] = {0};


	EBox* p = NULL;


	i = LocateVex(*G,v);
	j = LocateVex(*G,w);


	if (i<0||j<0)
	{
		return false;
	}

	
  if (NULL==(p = (EBox*)malloc(sizeof(EBox))))
  {
    return false;
  }
 	p->mark = unvisited;

	p->ivex = i;

	p->jvex = j;

	p->pInfor = NULL;

	p->iLink = G->adjmulist[i].firstedge;

	G->adjmulist[i].firstedge = p;

	p->jLink = G->adjmulist[j].firstedge;


	G->adjmulist[j].firstedge = p;


//	printf("该边是否有相关信息(1:有 0:无):\n");


//	scanf("%d",&IncInfor);

  IncInfor = 0;

	if (IncInfor)
	{
		printf("请输入该边的相关信息\n");


		scanf("%s",s);

		l = strlen(s);

		if (l)
		{
			p->pInfor = (char*)malloc(sizeof(char)*(l+1));

			strcpy(p->pInfor,s);
		}
	}

	G->edgenum++;

	return true;
}



bool DeleteVex(AMLGraph* G,char v) // 删除点
{
	int i = 0;
	int j = 0;

	char w;
	EBox* p = NULL;

	i = LocateVex(*G,v);

	if (i<0)
	{
		return false;
	}

	for (j=0;j<G->vexnum;j++)
	{
		if (i==j)
		{
			continue;
		}

		w = GetVex(*G,j);

		DeleteArc(G,v,w);
	}

	// 排在顶点v后面的顶点的序号减1 

	for (j=i+1;j<G->vexnum;j++)
	{
		G->adjmulist[j-1] = G->adjmulist[j];
	}

	G->vexnum--;

	 // 修改顶点的序号 

	for (j=i;j<G->vexnum;++j)
	{
		p = G->adjmulist[j].firstedge;

		if (p)
		{
			if (p->ivex==j+1)
			{
				p->ivex--;

				p = p->iLink;
			}

			else
			{
				p->jvex--;

				p = p->jLink;
			}
		}


	}

	return true;
}


void DestroyGraph(AMLGraph* G)
{
	int i = 0;

	for (i=G->vexnum-1;i>=0;--i) // 在这里其实i 一直等于 vexnum-1
	{
		DeleteVex(G,G->adjmulist[i].data); // 删除顶点 之后 在删除顶点里面的函数有删除边  所以 不用管边
	}

  // 或者这样做   知道为什么上面的要倒着删除了吗  因为每次删除顶点之后 我们的vexnum也在变化啊 所以
  // 我们要递增着删除就不是那么好了
//   int iNum = G->vexnum ;
//   for (i=0;i<iNum;++i)
//   {
//     DeleteVex(G,G->adjmulist[G->vexnum-1].data);
//   }
}

void MarkUnVisited(AMLGraph G)
{
	int i = 0;

	EBox* p = NULL;
	for (i=0;i<G.vexnum;i++)
	{
		p = G.adjmulist[i].firstedge;

		while (p)
		{
	
			p->mark = unvisited;

			if (p->ivex==i)
			{
				p = p->iLink;
			}

			else
			{
				p = p->jLink;
			}
		}
	}
}


void Display(AMLGraph G)// 输出无向图的邻接多重表G 
{
	int i = 0;

	EBox* p = NULL;

	MarkUnVisited(G);

	printf("%d个顶点:\n",G.vexnum);


	for (i=0;i<G.vexnum;i++)
	{
		 printf("%c ",G.adjmulist[i].data);
	}

	printf("\n%d条边:\n",G.edgenum);


	for (i=0;i<G.vexnum;i++) // Bug  edgenum  改为 vexnum
	{
		p = G.adjmulist[i].firstedge;

		while (p)
		{
			if (p->ivex==i)// 边的i端与该顶点有关 
			{
			
				if (!p->mark)
				{
					printf("%c－%c ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);

					p->mark = visited;

					if (p->pInfor)
					{
						printf("相关信息%s\n",p->pInfor);
					}

				}


				p = p->iLink;
			}

			else // 边的j端与该顶点有关 
			{
				if (!p->mark)
				{
					printf("%c－%c ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);


					p->mark = visited;


					if (p->pInfor)
					{
						printf("相关信息%s\n",p->pInfor);
					}
				}

				p = p->jLink;
			}

		}

		printf("\n");
	}
}


void DFSTraverse(AMLGraph G)
{
	int v = 0;
	
	for (v=0;v<G.vexnum;++v)
	{
		visit[v] = false;
	}

	for (v=0;v<G.vexnum;++v)
	{
		if (!visit[v])
		{
			DFS(G,v);
		}

	
	}	
  printf("\n");
}


void DFS(AMLGraph G,int v)
{

	int j = 0;

	EBox* p = NULL;

	VisitFunc(G.adjmulist[v].data);

	visit[v] = true;

	p = G.adjmulist[v].firstedge;

	while (p)
	{
		j = p->ivex==v?p->jvex:p->ivex;

		if (!visit[j])
		{
			DFS(G,j);
		}

		p = p->ivex==v?p->iLink:p->jLink;
	}
}

/* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.6 */
/* 操作结果: 从第1个顶点起,按广度优先非递归遍历图G,并对每个顶点调用函数 */
/*           Visit一次且仅一次。一旦Visit()失败,则操作失败。 */
/*           使用辅助队列Q和访问标志数组visite */
void BFSTraverse(AMLGraph G)
{
  int v = 0;
  int u = 0;
  int w = 0;

  char u1;

  QUEUE Q;

  Q.InitQueue();

  for (v=0;v<G.vexnum;++v)
  {
    visit[v] = false;
  }

  for (v=0;v<G.vexnum;++v)
  {
    if (!visit[v])
    {
      visit[v] = true;

      VisitFunc(G.adjmulist[v].data);

      Q.EnQueue(v);

      while (!Q.QueueIsEmpty())
      {
        Q.DeQueue(u);

        u1 = GetVex(G,u);

        for (w = FirstAdjVex(G,u1);w>=0;w = NextAdjVex(G,u1,GetVex(G,w)))
        {
          if (!visit[w])
          {
            visit[w] = true;

            VisitFunc(G.adjmulist[w].data);

            Q.EnQueue(w);
          }
        }
      }
    }
  }

  printf("\n");
  Q.DestroyQueue();
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