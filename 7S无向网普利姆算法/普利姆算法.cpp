#include <stdio.h>
#include <windows.h>




typedef enum{DG,DN,AG,AN}GraphKind; /* {����ͼ,������,����ͼ,������} */

#define MAX_NAME 5        /* �����ַ�������󳤶�+1 */
#define MAX_INFO 20       /* �����Ϣ�ַ�������󳤶�+1 */

#define INT_MAX 2147483647 

#define MAX_VERTEX_NUM 20  /* ��󶥵���� */






typedef struct  
{
	int adj;   /* �����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ� */
	
	void* Infor;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];;


typedef struct  
{
	char vexs[MAX_VERTEX_NUM];  /* �������� */
	
	AdjMatrix arcs;               /* �ڽӾ��� */
	
	int vexnum;
	int arcnum;                 /* ͼ�ĵ�ǰ�������ͻ��� */
	
	GraphKind Kind;             //����
}MGraph,*pMGraph;



typedef struct  
{
	char adjvex;
	int lowcost;
}minside[MAX_VERTEX_NUM];



int LocateVex(MGraph G,char u);
bool CreateAN(pMGraph G);


/* ������ķ�㷨�ӵ�u���������������G����С������T,���T�ĸ�����*/

void MiniSpanTree_PRIM(MGraph G,char u);


//��ε�� 186

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
		if (u==G.vexs[i])   //���ַ� 
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
	
	printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0):\n");
	
	
	scanf("%d",&(G->vexnum));
	
	scanf("%d",&(G->arcnum));
	
	scanf("%d",&IncInfor);
	
	
	printf("������%d�������ֵ:\n",(*G).vexnum);
	
	
	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&(G->vexs[i]));
	}
	
	
	
	//��ʼ���ڽӾ���
	
	for (i=0;i<G->vexnum;i++)
	{
		for (j=0;j<G->vexnum;j++)
		{
			G->arcs[i][j].adj = INT_MAX;
			
			G->arcs[i][j].Infor = NULL;
		}
	}
	
	
	printf("������%d���ߵĶ���1 ����2 Ȩֵ:\n",(*G).arcnum);
	
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
			printf("������ñߵ������Ϣ(<%d���ַ�):\n",MAX_INFO);
			
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

	printf("��С�����������ĸ�����Ϊ:\n");

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


