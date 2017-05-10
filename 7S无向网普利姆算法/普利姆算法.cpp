#include <stdio.h>
#include <windows.h>




typedef enum{DG,DN,AG,AN}GraphKind; /* {有向图,有向网,无向图,无向网} */

#define MAX_NAME 5        /* 顶点字符串的最大长度+1 */
#define MAX_INFO 20       /* 相关信息字符串的最大长度+1 */

#define INT_MAX 2147483647 

#define MAX_VERTEX_NUM 20  /* 最大顶点个数 */






typedef struct  
{
	int adj;   /* 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； */
	
	void* Infor;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];;


typedef struct  
{
	char vexs[MAX_VERTEX_NUM];  /* 顶点向量 */
	
	AdjMatrix arcs;               /* 邻接矩阵 */
	
	int vexnum;
	int arcnum;                 /* 图的当前顶点数和弧数 */
	
	GraphKind Kind;             //种类
}MGraph,*pMGraph;



typedef struct  
{
	char adjvex;
	int lowcost;
}minside[MAX_VERTEX_NUM];



int LocateVex(MGraph G,char u);
bool CreateAN(pMGraph G);


/* 用普里姆算法从第u个顶点出发构造网G的最小生成树T,输出T的各条边*/

void MiniSpanTree_PRIM(MGraph G,char u);


//严蔚敏 186

int mininum(minside SZ,MGraph G);

void main()
{


	MGraph G;

	CreateAN(&G);


	MiniSpanTree_PRIM(G,G.vexs[0]);




}

int LocateVex(MGraph G,char u)
{
	int i = 0;
	
	for (i=0;i<G.vexnum;i++)
	{
		if (u==G.vexs[i])   //单字符 
		{
			return i;
		}
	}
	
	return -1;
}

bool CreateAN(pMGraph G)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int w = 0;
	int IncInfor = 0;
	char s[MAX_INFO] = {0};
	
	char* pInfor = NULL;
	
	char va,vb;
	
	printf("请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0):\n");
	
	
	scanf("%d",&(G->vexnum));
	
	scanf("%d",&(G->arcnum));
	
	scanf("%d",&IncInfor);
	
	
	printf("请输入%d个顶点的值:\n",(*G).vexnum);
	
	
	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&(G->vexs[i]));
	}
	
	
	
	//初始化邻接矩阵
	
	for (i=0;i<G->vexnum;i++)
	{
		for (j=0;j<G->vexnum;j++)
		{
			G->arcs[i][j].adj = INT_MAX;
			
			G->arcs[i][j].Infor = NULL;
		}
	}
	
	
	printf("请输入%d条边的顶点1 顶点2 权值:\n",(*G).arcnum);
	
	for (k=0;k<G->arcnum;k++)
	{
		scanf(" %c",&va);
		scanf(" %c",&vb);
		
		scanf("%d",&w);
		
		i = LocateVex(*G,va);
		j = LocateVex(*G,vb);
		
		G->arcs[i][j].adj = G->arcs[j][i].adj = w;
		
		if (IncInfor)
		{
			printf("请输入该边的相关信息(<%d个字符):\n",MAX_INFO);
			
			scanf("%s",s);
			
			w = strlen(s);
			
			if (w)
			{
				pInfor = (char*)malloc(sizeof(char)*(w+1));
				
				strcpy(pInfor,s);
				
				G->arcs[i][j].Infor = G->arcs[j][i].Infor = (void*)pInfor; 
				
			}
		}
		
	}
	
	
	G->Kind = AN;
	return true;
	
}


void MiniSpanTree_PRIM(MGraph G,char u)
{
	int i = 0;
	int j = 0;
	int k = 0;

	minside closedge;
	k = LocateVex(G,u);

	for (j=0;j<G.vexnum;j++)
	{
		if (j!=k)
		{
		
			closedge[j].adjvex = u;

			closedge[j].lowcost = G.arcs[k][j].adj;
		}
	}


	closedge[k].lowcost = 0;

	printf("最小代价生成树的各条边为:\n");

	for (i=1;i<G.vexnum;i++)
	{
		k = mininum(closedge,G);

		printf("%c   %c\n",closedge[k].adjvex,G.vexs[k]);


		closedge[k].lowcost = 0;

		for (j=0;j<G.vexnum;j++)
		{
			if (G.arcs[k][j].adj<closedge[j].lowcost)
			{
				closedge[j].adjvex = G.vexs[k];

				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
 
	}
}


int mininum(minside SZ,MGraph G)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int min = 0;

	while (!SZ[i].lowcost)
	{
		i++;
	}

	min = SZ[i].lowcost;

	k = i;

	for (j=i+1;j<G.vexnum;j++)
	{
		if (SZ[j].lowcost>0)
		{
			if (min>SZ[j].lowcost)
			{
				min = SZ[j].lowcost;

				k = j;
			}
		}
	}

	return k;
}


