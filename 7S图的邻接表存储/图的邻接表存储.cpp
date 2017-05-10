#include <stdio.h>
#include <malloc.h>
#include <windows.h>

#define MAX_VERTEX_NUM 20
typedef enum{DG,DN,AG,AN}GraphKind; 

typedef struct ArcNode 
{
	int adjvex;   /* 该弧所指向的顶点的位置 */
	ArcNode* nexttarc;  /* 指向下一条弧的指针 */   // nextarc error 
  void* pInfor;

}ArcNode,*pArcNode;


typedef struct  
{
	char data;   //顶点信息
	ArcNode* firstarc;

}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct  
{
	AdjList vertices;
	int vexnum;
	int arcnum;
	int kind;
}ALGraph;





/* 初始条件: 图G存在,u和G中顶点有相同特征 */
/* 操作结果: 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
int LocateVex(ALGraph G,char u);


/* 采用邻接表存储结构,构造没有相关信息的图G(用一个函数构造4种图) */
bool CreateGraph(ALGraph* G);

void DestroyGraph(ALGraph* G);

char GetVex(ALGraph G,int v);

bool PutVex(ALGraph* G,char v,char value);


/* 初始条件: 图G存在,v是G中某个顶点 */
/* 操作结果: 返回v的第一个邻接顶点的序号,若顶点在G中没有邻接顶点,则返回-1 */
int FirstAdjVex(ALGraph G,char v);

/* 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 */
/* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号*/
/*           若w是v的最后一个邻接点,则返回-1 */
int NextAdjVex(ALGraph G,char v,char w);

/* 初始条件: 图G存在,v和图中顶点有相同特征 */
/* 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
void InsertVex(ALGraph* G,char v);


/* 初始条件: 图G存在,v是G中某个顶点 */
/* 操作结果: 删除G中顶点v及其相关的弧 */
bool DeleteVex(ALGraph* G,char v);


/* 初始条件: 图G存在,v和w是G中两个顶点 */
/* 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v> */
bool InsertArc(ALGraph* G,char v,char w);

/* 初始条件: 图G存在,v和w是G中两个顶点 */
/* 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v> */
bool DeleteArc(ALGraph* G,char v,char w);


void Visit(char p)
{
	printf("%c ",p);

}

void DFSTravel(ALGraph* G,void (*Visit)(char));

void DFS(ALGraph G,int v);

void Display(ALGraph G);




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
  ALGraph G;

  CreateGraph(&G);

  Display(G);

  DestroyGraph(&G);
}


int LocateVex(ALGraph G,char u)
{
	int i = 0;

	for (i=0;i<G.vexnum;i++)
	{
		if (G.vertices[i].data==u)
		{
			return i;
		}
	}

	return -1;
}


bool CreateGraph(ALGraph* G)
{
	int i = 0;
	int j = 0;
	int k = 0;

	int w = 0;

	char va,vb;

	pArcNode p = NULL;

	printf("请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3):\n");
 
	scanf("%d",&(*G).kind);


	printf("请输入图的顶点数,边数: ");
	scanf("%d",&G->vexnum);
	scanf("%d",&G->arcnum);
 
	printf("请输入%d个顶点的值:\n",(*G).vexnum);


	//构造顶点
	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->vertices[i].data);

		G->vertices[i].firstarc = NULL;
	}


	if (G->kind==1||G->kind==3)  //网
	{
		printf("请顺序输入每条弧(边)的权值、弧尾和弧头\n");
	}

	else
	{
		 printf("请顺序输入每条弧(边)的弧尾和弧头\n");
	}


	for (k=0;k<G->arcnum;k++)
	{
		if (G->kind==1||G->kind==3)
		{
			printf("权值\n");
			scanf("%d",&w);

			printf("弧尾\n");
			scanf(" %c",&va);

			printf("弧头\n");

			scanf(" %c",&vb);
		}

		else
		{
			
			printf("弧尾\n");
			scanf(" %c",&va);
			
			printf("弧头\n");
			
			scanf(" %c",&vb);
		}


		i = LocateVex(*G,va);  

		j = LocateVex(*G,vb);  //弧头


		p = (pArcNode)malloc(sizeof(ArcNode));

		p->adjvex = j;

		if (G->kind==1||G->kind==3)  //  网
		{
			p->pInfor = (int*)malloc(sizeof(int));

		
			memcpy(p->pInfor,&w,sizeof(int)); // 这里需要改动一下 自己设置一个权值 Infor用来存放信息

		}

		else   //图
		{

			p->pInfor = NULL;
		}

		//插入表
		p->nexttarc = G->vertices[i].firstarc;

		G->vertices[i].firstarc = p;


		 /*无向图或网,产生第二个表结点 */

		if (G->kind>=2)
		{
			p = (pArcNode)malloc(sizeof(ArcNode));

			p->adjvex = i;


			if (G->kind==3)
			{
				p->pInfor = (int*)malloc(sizeof(int));

				memcpy(p->pInfor,&w,sizeof(int));

			}

			else
			{
				p->pInfor = NULL;
			}

			p->nexttarc = G->vertices[j].firstarc;

			G->vertices[j].firstarc = p;
		}
	}
	return true;
}

void DestroyGraph(ALGraph* G)
{
	int i = 0;

	pArcNode p = NULL;
	pArcNode q = NULL;


	for (i=0;i<G->vexnum;i++)
	{
		p = G->vertices[i].firstarc;

		while (p)
		{
			q = p->nexttarc;

			if (G->kind%2)  //网
			{
				free(p->pInfor);
			}

			free(p);

			p = q;
		}
	}
}


char GetVex(ALGraph G,int v)
{
	if (v>=G.vexnum||v<0)
	{
		exit(0);
	}
	return G.vertices[v].data;
}

bool PutVex(ALGraph* G,char v,char value)
{
	int i = 0;

	i = LocateVex(*G,v);

	if (i>-1)
	{
		G->vertices[i].data = value;


		return true;
	}

	return false;
}

int FirstAdjVex(ALGraph G,char v)
{
	pArcNode p = NULL;

	int v1 = 0;

	v1 = LocateVex(G,v);

	p = G.vertices[v1].firstarc;

	if (p)
	{
		return p->adjvex;
	}

	else
	{
		return -1;
	}
}


int NextAdjVex(ALGraph G,char v,char w)
{
	pArcNode p = NULL;

	int v1 = 0;
	int w1 = 0;

	v1 = LocateVex(G,v);

	w1 = LocateVex(G,w);


	p = G.vertices[v1].firstarc;

	while (p&&p->adjvex!=w1)
	{
		p = p->nexttarc;
	}

	if (!p||!p->nexttarc)
	{
		return -1;
	}

	else // p->adjvex==w
	{
		return p->nexttarc->adjvex;
	}
}


void InsertVex(ALGraph* G,char v)
{
  if(G->vexnum==MAX_VERTEX_NUM)
  {
    return;
  }
	G->vertices[G->vexnum].data = v;

	G->vertices[G->vexnum].firstarc = NULL;
	G->vexnum++;
}

bool DeleteVex(ALGraph* G,char v)
{
	int i = 0;
	int j = 0;


	pArcNode p = NULL;

	pArcNode q = NULL;

	j = LocateVex(*G,v);

	if (j<0)
	{

		return false;
	}

	else
	{
		p = G->vertices[j].firstarc;

		while (p)
		{
			q = p;

			p = p->nexttarc;

			if (G->kind%2)   //网
			{
				free(q->pInfor);
			}

			free(q);

			G->arcnum--;
		}

		G->vexnum--;

		/* 顶点v后面的顶点前移 */


		for (i=j;i<G->vexnum;i++)
		{
			G->vertices[i] = G->vertices[i+1];
		}




		for (i=0;i<G->vexnum;i++)// 删除以v为入度的弧或边且必要时修改表结点的顶点位置值
		{
			p = G->vertices[i].firstarc;    //指向第一条弧


			while (p)
			{
				if (p->adjvex==j)
				{
					if (p==G->vertices[i].firstarc)
					{
						G->vertices[i].firstarc = p->nexttarc;

						if (G->kind%2)
						{
							free(p->pInfor);
						}

						free(p);

						p = G->vertices[i].firstarc;

						if (G->kind<2)  //有向
						{
							G->arcnum--;
						}
					}

					else
					{
						q->nexttarc = p->nexttarc;

						if (G->kind%2)
						{
							free(p->pInfor);
						}

						free(p);

						p = q->nexttarc;
						
						if (G->kind<2)  //有向
						{
							G->arcnum--;
						}
						
					}
				}
				else
				{
					if (p->adjvex>j)
					{
						p->adjvex--;  // 修改表结点的顶点位置值(序号)
					}

					q = p;

					p = p->nexttarc;
				}
			}
		}
	}


	return true;



}


bool InsertArc(ALGraph* G,char v,char w)
{
	pArcNode p = NULL;

	int w1 = 0;
	int i = 0;
	int j = 0;

	i = LocateVex(*G,v);
	j = LocateVex(*G,w);

	if (i<0||j<0)
	{
		return false;
	}

	G->arcnum++;

	if (G->kind%2)  //网
	{
		printf("请输入弧(边)%c→%c的权值: ",v,w);


		scanf("%d",&w1);
	}

	p = (pArcNode)malloc(sizeof(ArcNode));

	p->adjvex = j;

	if (G->kind%2)// 网 
	{
		p->pInfor = (int*)malloc(sizeof(int));

		memcpy(p->pInfor,&w1,sizeof(int));


	}
	else
	{
		p->pInfor = NULL;
	}

	p->nexttarc = G->vertices[i].firstarc;

	G->vertices[i].firstarc = p;

	if (G->kind>=2) // 无向,生成另一个表结点 
	{
		p = (pArcNode)malloc(sizeof(ArcNode));

		p->adjvex = i;


		if (G->kind==3)// 无向网
		{
			p->pInfor = (int*)malloc(sizeof(int));

			memcpy(p->pInfor,&w1,4);


		}

		else
		{
			p->pInfor = NULL;
		}

			p->nexttarc = G->vertices[j].firstarc;

			G->vertices[j].firstarc = p;
		
	}



	return true;

}


bool DeleteArc(ALGraph* G,char v,char w)
{
	pArcNode p = NULL;

	pArcNode q = NULL;


	int i = 0;
	int j = 0;


	i = LocateVex(*G,v);
	j = LocateVex(*G,w);


	if (i<0||j<0||i==j)
	{
		return false;
	}

	p = G->vertices[i].firstarc;

	while (p&&p->adjvex!=j)
	{
		q = p;

		p = p->nexttarc;
	}

	if (p&&p->adjvex==j)
	{
		if (p==G->vertices[i].firstarc)
		{
			G->vertices[i].firstarc = p->nexttarc;
		}

		else
		{
			q->nexttarc = p->nexttarc;
		}


		if (G->kind%2)  // 网
		{
			free(p->pInfor);
		}

		free(p);

		G->arcnum--;
	}

	// 无向,删除对称弧<w,v> 

	if (G->kind>=2)
	{
		p = G->vertices[j].firstarc;

		while (p&&p->adjvex!=i)// p不空且所指之弧不是待删除弧<w,v>
		{
			q = p;

			p = p->nexttarc;
		}

		if (p&&p->adjvex==i)
		{
			if (p==G->vertices[j].firstarc)
			{
				G->vertices[j].firstarc = p->nexttarc;
			}

			else
			{
				q->nexttarc = p->nexttarc;
			}

			if (G->kind==3)
			{
				free(p->pInfor);
			}

			free(p);
		}
	}


	return true;
}


void Display(ALGraph G)
{
	int i = 0;

	pArcNode p = NULL;

	switch(G.kind)
	{
	case DG:
		{
			printf("有向图\n");
			break;
		}

	case DN:
		{

			printf("有向网\n");
			break;
		}
	case AG:
		{
			printf("无向图\n");
			break;
		}

	case AN:
		{
			printf("无向网\n");
			break;
		}

	default:
		{

			break;
		}
	}
	
	printf("%d个顶点：\n",G.vexnum);
	
	for (i=0;i<G.vexnum;i++)
	{
		printf("%c  ",G.vertices[i].data);
	}

	printf("\n%d条弧(边):\n",G.arcnum);
	
	for (i=0;i<G.vexnum;i++)
	{
		p = G.vertices[i].firstarc;

		while (p)
		{
			if (G.kind<=1)
			{
				 printf("%c→%c ",G.vertices[i].data,G.vertices[p->adjvex].data);

				 if (G.kind==DN)
				 {
					 printf(":%d",p->pInfor);
				 }
			}

			else  //无向避免输出两次
			{

				if (i<p->adjvex)
				{
					printf("%c－%c ",G.vertices[i].data,G.vertices[p->adjvex].data);
				}

				if (G.kind==AN)
				{
					printf(":%d",p->pInfor);
				}
			}
		}

		p = p->nexttarc;
	}

	printf("\n");




}


void DFSTravel(ALGraph* G,void (*Visit)(char))
{

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

void DFS(ALGraph G,int v)
{
	int w = 0;

	char v1;

	v1 = GetVex(G,v);

	visited[v] = true;

	VisitFunc(G.vertices[v].data);

	for (w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,GetVex(G,w)))
	{
		if (!visited[w])
		{
			DFS(G,w);
		}
	}
}





void BFSTravel(ALGraph G,void (*Visit)(char))
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
			
			VisitFunc(G.vertices[v].data);
			
			EnQueue(&q,v);
			
			
			while (!QueueEmpty(q))
			{
				DeQueue(&q,&u);
				
				
				u1 = GetVex(G,u);
				
				for (w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1, GetVex(G,w)))
				{
					if (!visited[w])
					{
						visited[w] = true;
						
						VisitFunc(G.vertices[w].data);
						
						EnQueue(&q,w);
					}
				}
			}
		}
	}
	
	DestroyQueue(&q);
	
	printf("\n");
	
	
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