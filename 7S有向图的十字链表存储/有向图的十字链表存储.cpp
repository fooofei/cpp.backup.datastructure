#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <windows.h>


#define MAX_VERTEX_NUM 20
#define MAX_INFOR 20


typedef struct ArcBox
{
	int tailvex;  /* 该弧的尾和头顶点的位置 */
	int headvex;

	ArcBox* hlink;
	ArcBox* tlink;

	char* pInfor;
}ArcBox,*pArcBox;

typedef struct  
{
	char data;
	ArcBox* firstin;
	ArcBox* firstout;
}VexNode;


typedef struct
{
	VexNode xlist[MAX_VERTEX_NUM];

	int vexnum;
	int arcnum;
}OLGraph;



int LocateVex(OLGraph G,char u);

bool CreateDG(OLGraph* G);

void DestroyGraph(OLGraph* G);

char GetVex(OLGraph G,int v);

bool PutVex(OLGraph* G,char v,char value);

int FirstAdjVex(OLGraph G,char v);

int NextAdjVex(OLGraph G,char v,char w);

void InsertVex(OLGraph* G,char v);

bool DeleteVex(OLGraph* G,char v);

bool InsertArc(OLGraph* G,char v,char w);

bool DeleteArc(OLGraph* G,char v,char w);

void Display(OLGraph G);

void Visit(char p)
{
	printf("%c ",p);
	
}

void DFSTravel(OLGraph* G,void (*Visit)(char));

void DFS(OLGraph G,int v);



#define MAXQSIZE 20 
typedef struct _SQQUEUE_
{
	int* pBase; 
	int iFront;	
	int iRear;
}SqQueue,*pSqQueue;


bool InitQueue(pSqQueue Q);
bool DestroyQueue(pSqQueue Q);
bool DeQueue(pSqQueue Q,int* e);
bool EnQueue(pSqQueue Q, int e);
bool QueueEmpty(SqQueue Q);

void (*VisitFunc)(char);  //全局函数指针 

bool visited[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */

void main()
{

}


int LocateVex(OLGraph G,char u)
{
	int i = 0;

	for (i=0;i<G.vexnum;i++)
	{
		if (G.xlist[i].data==u)
		{
			return i;
		}
	}


	return -1;
}


bool CreateDG(OLGraph* G)
{
	int i = 0;
	int j = 0;

	int k = 0;

	int IncInfor = 0;
	
	char str[MAX_INFOR] = {0};


	pArcBox p = NULL;

	char v1,v2;

	printf("请输入有向图的顶点数,弧数,弧是否含其它信息(是:1，否:0):\n");

	scanf("%d",&G->vexnum);

	scanf("%d",&G->arcnum);

	scanf("%d",&IncInfor);


	printf("请输入%d个顶点的值:\n",(*G).vexnum);

	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&(G->xlist[i].data));

		G->xlist[i].firstin = G->xlist[i].firstout = NULL;
	}

	printf("请输入%d条弧的弧尾和弧头\n",(*G).arcnum);



	for (k=0;k<G->arcnum;k++) // 弧尾->弧头
	{
		printf("弧尾\n");

		scanf(" %c",&v1);

		printf("弧头\n");

		scanf(" %c",&v2);

		i = LocateVex(*G,v1);

		j = LocateVex(*G,v2);

		p = (pArcBox)malloc(sizeof(ArcBox));

		p->headvex = j;

		p->tailvex = i;// 弧尾->弧头

		p->hlink = G->xlist[j].firstin;

		p->tlink = G->xlist[i].firstout;


		G->xlist[j].firstin = G->xlist[i].firstout = p;


		if (IncInfor)
		{
			printf("请输入该弧的相关信息\n");
     
			scanf("%s",str);

			p->pInfor = (char*)malloc(sizeof(char)*(strlen(str)+1));


			strcpy(p->pInfor,str);
		}

		else
		{
			p->pInfor = NULL;
		}
	
	}

	

		return true;
}


void DestroyGraph(OLGraph* G)
{
	int j = 0;

	pArcBox p = NULL;

	pArcBox q = NULL;

	for (j=0;j<G->vexnum;j++)
	{
		p = G->xlist[j].firstout;// 仅处理出弧

		while (p)
		{
			q = p;

			p = p->tlink;

			if (q->pInfor)
			{
				free(q->pInfor);
			}

			free(q);
		}
	}

	G->arcnum = 0;

	G->vexnum = 0;
}


char GetVex(OLGraph G,int v)
{
	if (v>=G.vexnum||v<0)
	{
		exit(0);
	}

	return G.xlist[v].data;
}


bool PutVex(OLGraph* G,char v,char value)
{
	int i = 0;

	i = LocateVex(*G,v);

	if (i<0)
	{
		return false;
	}

	G->xlist[i].data = value;

	return true;
}


int FirstAdjVex(OLGraph G,char v)
{
	int i = 0;

	pArcBox p = NULL;

	i = LocateVex(G,v);

	p = G.xlist[i].firstout;

	if (p)
	{
		return p->headvex;
	}

	else
	{
		return -1;
	}
}

int NextAdjVex(OLGraph G,char v,char w)
{
	int i = 0;
	int j = 0;

	pArcBox p = NULL;

	i = LocateVex(G,v);

	j = LocateVex(G,w);

	p = G.xlist[i].firstout;

	while (p&&p->headvex!=j)
	{
		p = p->tlink;
	}

	if (p)
	{
		p = p->tlink;
	}

	if (p)
	{
		return p->headvex;
	}

	return -1;
}


void InsertVex(OLGraph* G,char v)
{
  if (G->vexnum==MAX_VERTEX_NUM)
  {
    return;
  }
	G->xlist[G->vexnum].data = v;

	G->xlist[G->vexnum].firstin = G->xlist[G->vexnum].firstout = NULL;

	G->vexnum++;
}

bool DeleteVex(OLGraph* G,char v)
{
	int j = 0;

	int k = 0;


	pArcBox p = NULL;

	pArcBox q = NULL;

	k = LocateVex(*G,v);

	if (k<0)
	{
		return false;
	}

	  // 以下删除顶点v的出弧 
	for (j=0;j<G->vexnum;j++) // 顶点v的出弧是其它顶点的入弧 
	{
		if (j==k)
		{
			continue;
		}

		// 在其它顶点的入弧链表中删除顶点v的出弧 

		p = G->xlist[j].firstin;

		while(p)
		{
			if (p->tailvex==k&&p==G->xlist[j].firstin)
			{
				G->xlist[j].firstin = p->hlink;

				break;
			}

			else if (p->tailvex!=k)
			{
				q = p;

				p = p->hlink;

			}

			else  /* 找到待删结点且不是首结点 */
			{
				q->hlink = p->hlink;

				break;
			}
		}

	

	}

	p = G->xlist[k].firstout ;  // 删除与顶点v有关的出弧 
		
	while (p)
	{
		q = p->tlink;
			
		if (p->pInfor)
		{
			free(p->pInfor);
		}
			
		free(p);
			
		G->arcnum--;
			
		p = q;
	}

	 // 以下删除顶点v的入弧 

	for (j=0;j<G->vexnum;j++)   // 顶点v的入弧是其它顶点的出弧 
	{

		if (j==k)
		{
			continue;
		}

		p = G->xlist[j].firstout;

		while (p)
		{
			if (p->headvex==k&&p==G->xlist[j].firstout)
			{
				G->xlist[j].firstout = p->tlink;


				break;
			}

			else if (p->headvex!=k)
			{
				q = p;

				p = p->tlink;
			}

			else
			{
				q->tlink = p->tlink;

				break;
			}
		}
	}

	// 删除与顶点v有关的入弧 

	p = G->xlist[k].firstin;
	while (p)
	{
		q = p->hlink;

		if (p->pInfor)
		{
			free(p->pInfor);
		}

		free(p);

		G->arcnum--;


		p = q;
	}



	/* 序号>k的顶点依次向前移 */
	for (j=k+1;j<G->vexnum;j++)
	{
		G->xlist[j-1] = G->xlist[j];
	}

	G->vexnum--;


	// 结点序号>k的要减1
	for (j=0;j<G->vexnum;j++)
	{
		// 处理出弧 
		p = G->xlist[j].firstout;

		while (p)
		{
			if (p->tailvex>k)
			{
				p->tailvex--;
			}

			if (p->headvex>k)
			{
				p->headvex--;
			}

			p = p->tlink;
		}
	}
}

bool InsertArc(OLGraph* G,char v,char w)
{
	int i = 0;
	int j = 0;

	char str[MAX_INFOR] = {0};

	pArcBox p = NULL;


	i = LocateVex(*G,v);

	j = LocateVex(*G,w);


	if (i<0||j<0)
	{
		return false;
	}

	p = (pArcBox)malloc(sizeof(ArcBox));

	p->tailvex = i;

	p->headvex = j;

	p->hlink = G->xlist[j].firstin;

	p->tlink = G->xlist[i].firstout;


	G->xlist[j].firstin = G->xlist[j].firstout = p;


	G->arcnum++;


	printf("要插入的弧是否含有其它信息(是: 1,否: 0):\n");

	int IncInfor = 0;
	scanf("%d",&IncInfor);

	if (IncInfor)
	{
		printf("请输入该弧的相关信息:\n");
	
		scanf("%s",str);
		
		p->pInfor = (char*)malloc((strlen(str)+1)*sizeof(char));
     
		strcpy(p->pInfor,str);
	}

	else
	{
		p->pInfor = NULL;
	}

	return true;
}

bool DeleteArc(OLGraph* G,char v,char w)
{
	int i = 0;
	int j = 0;

	pArcBox p1 = NULL;
	pArcBox p2 = NULL;
	i = LocateVex(*G,v);
	j = LocateVex(*G,w);

	if (i<0||j<0||i==j)
	{
		return false;
	}
	p2 = G->xlist[i].firstout;  // 将弧结点从出弧链表中删去 

	if (p2&&p2->headvex==j)
	{
		G->xlist[i].firstout = p2->tlink;
	}

	else
	{
		while (p2&&p2->headvex!=j)
		{
			p1 = p2;

			p2 = p2->tlink;
		}

		if (p2)
		{
			p1->tlink = p2->tlink;
		}
	}

	// 将弧结点从入弧链表中删去 

	p2 = G->xlist[j].firstin;

	if (p2&&p2->tailvex==i)
	{
		G->xlist[j].firstin = p2->hlink;
	}

	else
	{
		while (p2&&p2->tailvex!=i)
		{
			p1 = p2;

			p2 = p2->hlink;
		}

		if (p2)
		{
			p1->hlink = p2->hlink;
		}
	}

	if (p2->pInfor)
	{
		free(p2->pInfor);
	}

	free(p2);

	G->arcnum--;


	return true;


}

void DFSTravel(OLGraph* G,void (*Visit)(char))
{
  // 从第1个顶点起,按深度优先递归遍历有向图G,并对每个顶点调用 
  // 函数Visit一次且仅一次。一旦Visit()失败,则操作失败
	int v = 0;
	
	VisitFunc = Visit;
	
	for (v=0;v<G->vexnum;v++)
	{
		visited[v] = false;
	}
	
	for (v=0;v<G->vexnum;v++)
	{
		if (!visited[v])
		{
			DFS(*G,v);
		}
	}
	
	printf("\n");
	
	
}

void DFS(OLGraph G,int v)
{
	int w = 0;
	
	char v1,w1;
	
	v1 = GetVex(G,v);
	
	visited[v] = true;
	
	VisitFunc(G.xlist[v].data);

  ArcBox* p = G.xlist[v].firstout;

  while (p&&visited[p->headvex])// p没到表尾且该弧的头顶点已被访问 
  {
    p = p->tlink;
  }

  if (p&&!visited[p->headvex])
  {
    DFS(G,p->headvex);
  }
}



void BFSTravel(OLGraph G,void (*Visit)(char))
{
	
	int v = 0;
	int u = 0;
	int w = 0;
	
	char u1;
	
	SqQueue q;
	
	for (v=0;v<G.vexnum;v++)
	{
		visited[v] = false;
	}
	
	InitQueue(&q);
	
	for (v=0;v<G.vexnum;v++)
	{
		if (!visited[v])
		{
			visited[v] = true;
			
			VisitFunc(G.xlist[v].data);
			
			EnQueue(&q,v);
			
			
			while (!QueueEmpty(q))
			{
				DeQueue(&q,&u);
				
				
				u1 = GetVex(G,u);
				
				for (w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,GetVex(G,w)))
				{
					if (!visited[w])
					{
						visited[w] = true;
						
						VisitFunc(G.xlist[w].data);
						
						EnQueue(&q,w);
					}
				}
			}
		}
	}
	
	DestroyQueue(&q);
	
	printf("\n");
	
	
}







void Display(OLGraph G)
{
	int i = 0;

	pArcBox p = NULL;

	printf("共%d个顶点,%d条弧:\n",G.vexnum,G.arcnum);

	for (i=0;i<G.vexnum;i++)
	{
		 printf("顶点%c: 入度: ",G.xlist[i].data);

		 p = G.xlist[i].firstin;

		 while (p)
		 {
			 printf("%c ",G.xlist[p->tailvex].data);

			 p = p->hlink;
		 }

		 printf("\n出度:");

		 p = G.xlist[i].firstout;

		 while (p)
		 {
			   printf("%c ",G.xlist[p->headvex].data);
          
         if (p->pInfor)
         {
           printf("弧信息:%s\n",p->pInfor);
         }

			   p = p->tlink;
		 }


		 printf("\n");
	}
}



bool InitQueue(pSqQueue Q)
{ 
	(*Q).pBase = (int*)malloc(MAXQSIZE*sizeof(int));
	if(!(*Q).pBase)
	{
		return false;
	}
	(*Q).iFront = (*Q).iRear = 0;
	
	return true;
}

bool DestroyQueue(pSqQueue Q)
{ 
	if((*Q).pBase)
	{
		free((*Q).pBase);
	}
	(*Q).pBase = NULL;
	(*Q).iFront = (*Q).iRear = 0;
	
	return true;
}



bool EnQueue(pSqQueue Q,int e)
{ 
	if(((*Q).iRear+1)%MAXQSIZE==(*Q).iFront) 
	{
		return false;
	}
	(*Q).pBase[(*Q).iRear] = e;
	(*Q).iRear = ((*Q).iRear+1)%MAXQSIZE;
	return true;
}

bool DeQueue(pSqQueue Q,int* e)
{
	if((*Q).iFront==(*Q).iRear) 
	{
		return false;
	}
	*e=(*Q).pBase[(*Q).iFront];
	
	(*Q).iFront = ((*Q).iFront+1)%MAXQSIZE;
	
	return true;
}


bool QueueEmpty(SqQueue Q)
{ 
	if(Q.iFront==Q.iRear)
	{
		return true;
	}
	else
	{
		return false;
	}
}
