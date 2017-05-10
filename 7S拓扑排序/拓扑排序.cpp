#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>


#define MAX_VERTEX_NUM 20
typedef enum{DG,DN,AG,AN}GraphKind; 

typedef struct ArcNode 
{
	int adjvex;   /* 该弧所指向的顶点的位置 */
	ArcNode* nexttarc;  /* 指向下一条弧的指针 */
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


int LocateVex(ALGraph G,char u);

bool CreateGraph(ALGraph* G);

bool CreateGraphFromFile(ALGraph* G);

void DestroyGraph(ALGraph* G);

void FindInDegree(ALGraph G,int* indegree);

bool TopologicalSort(ALGraph G);




#define MAXSSIZE 20 
#define STACKINCREMENT 5
typedef struct _SQSTACK_
{
	int* pBase;
	int* pTop; 
	int stacksize; 
}SqStack,*pSqStack; 


bool InitStack(pSqStack S);
bool StackEmpty(SqStack S);
bool DestroyStack(pSqStack S);
bool Push(pSqStack S, int e);
bool Pop(pSqStack S,int* e);



void main()
{
	ALGraph G;

	CreateGraphFromFile(&G);

	TopologicalSort(G);

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


 
	
	G->kind = DG;


	printf("请输入图的顶点数,边数:\n");
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


		i = LocateVex(*G,va);  //弧巴

		j = LocateVex(*G,vb);  //弧头


		p = (pArcNode)malloc(sizeof(ArcNode));

		p->adjvex = j;

		if (G->kind==1||G->kind==3)  //  网
		{
			p->pInfor = (int*)malloc(sizeof(int));

		
			memcpy(p->pInfor,&w,sizeof(int));

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


bool CreateGraphFromFile(ALGraph* G)
{
  G->kind = DG;
  FILE* fp = NULL;

  if (NULL==(fp = fopen("1.txt","r")))
  {
    return false;
  }
	int i = 0;
	int j = 0;
	int k = 0;

	int w = 0;

	char va,vb;

	pArcNode p = NULL;


 
	
	G->kind = DG;

	fscanf(fp,"%d",&G->vexnum);
	fscanf(fp,"%d",&G->arcnum);


	//构造顶点
	for (i=0;i<G->vexnum;i++)
	{
		fscanf(fp,"%s",&G->vertices[i].data);

		G->vertices[i].firstarc = NULL;
	}


	for (k=0;k<G->arcnum;k++)
	{
	
			fscanf(fp,"%s",&va);

			fscanf(fp,"%s",&vb);
	

		i = LocateVex(*G,va);  //弧巴

		j = LocateVex(*G,vb);  //弧头


		p = (pArcNode)malloc(sizeof(ArcNode));

		p->adjvex = j;

	  p->pInfor  = NULL;

		//插入表
		p->nexttarc = G->vertices[i].firstarc;

		G->vertices[i].firstarc = p;
	}

  fclose(fp);

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


void FindInDegree(ALGraph G,int* indegree)
{
	int i = 0;

	ArcNode* p = NULL;

	for (i=0;i<G.vexnum;i++)
	{
		indegree[i] = 0;
	}


	for (i=0;i<G.vexnum;i++)
	{
		p = G.vertices[i].firstarc;

		while (p)
		{
			indegree[p->adjvex]++;

			p = p->nexttarc;
		}
	}
}


bool TopologicalSort(ALGraph G)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;

	int indegree[MAX_VERTEX_NUM] = {0};

	ArcNode* p = NULL;

	FindInDegree(G,indegree);

	SqStack S;

	InitStack(&S);


	for (i=0;i<G.vexnum;i++)
	{
		if (!indegree[i])
		{
			Push(&S,i);
		}
	}

	count = 0;


	while (!StackEmpty(S))
	{
		Pop(&S,&i);

		printf("%c ",G.vertices[i].data);


		count++;


		for (p=G.vertices[i].firstarc;p;p=p->nexttarc)
		{
			k = p->adjvex;

			if (!(--indegree[k]))
			{
				Push(&S,k);
			}
		}
	}




	DestroyStack(&S);

	if (count<G.vexnum)
	{
		printf("此有向图有回路\n");
        return false;
	}

	else
	{
		printf("为一个拓扑序列。\n");
		return true;
	}


}






bool InitStack(pSqStack S)
{ 
	(*S).pBase = (int*)malloc(MAXSSIZE*sizeof(int));
	
	if(!(*S).pBase)
	{
		return false;
	}
	(*S).pTop=(*S).pBase;
	
	(*S).stacksize = MAXSSIZE;
	
	return true;
}


bool DestroyStack(pSqStack S)
{ 
	free((*S).pBase);
	(*S).pBase = NULL;
	(*S).pTop = NULL;
	(*S).stacksize = 0;
	
	return true;
}


bool StackEmpty(SqStack S)
{ 
	if(S.pBase==S.pTop)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


bool Push(pSqStack S, int e)
{ 
	if((*S).pTop -(*S).pBase>=(*S).stacksize) /* 栈满，追加存储空间 */
	{
		(*S).pBase = (int*)realloc((*S).pBase,((*S).stacksize+STACKINCREMENT)*sizeof(int));
		
		if(!(*S).pBase)
		{
			return false; /* 存储分配失败 */
		}
		(*S).pTop = (*S).pBase + (*S).stacksize;
		
		(*S).stacksize+=STACKINCREMENT;
	}
	*((*S).pTop) ++= e;
	
	return true;
}

bool Pop(pSqStack S,int* e)
{ 
	if((*S).pTop==(*S).pBase)
	{
		return false;
	}
	
	*e = *--(*S).pTop;
	
	return true;
}