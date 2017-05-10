#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>


#define MAX_VERTEX_NUM 20
typedef enum{DG,DN,AG,AN}GraphKind; 

typedef struct ArcNode 
{
	int adjvex;   /* �û���ָ��Ķ����λ�� */
	ArcNode* nexttarc;  /* ָ����һ������ָ�� */
    void* pInfor;
	
}ArcNode,*pArcNode;


typedef struct  
{
	char data;   //������Ϣ
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


	printf("������ͼ�Ķ�����,����:\n");
	scanf("%d",&G->vexnum);
	scanf("%d",&G->arcnum);
 
	printf("������%d�������ֵ:\n",(*G).vexnum);


	//���춥��
	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->vertices[i].data);

		G->vertices[i].firstarc = NULL;
	}


	if (G->kind==1||G->kind==3)  //��
	{
		printf("��˳������ÿ����(��)��Ȩֵ����β�ͻ�ͷ\n");
	}

	else
	{
		 printf("��˳������ÿ����(��)�Ļ�β�ͻ�ͷ\n");
	}


	for (k=0;k<G->arcnum;k++)
	{
		if (G->kind==1||G->kind==3)
		{
			printf("Ȩֵ\n");
			scanf("%d",&w);

			printf("��β\n");
			scanf(" %c",&va);

			printf("��ͷ\n");

			scanf(" %c",&vb);
		}

		else
		{
			
			printf("��β\n");
			scanf(" %c",&va);
			
			printf("��ͷ\n");
			
			scanf(" %c",&vb);
		}


		i = LocateVex(*G,va);  //����

		j = LocateVex(*G,vb);  //��ͷ


		p = (pArcNode)malloc(sizeof(ArcNode));

		p->adjvex = j;

		if (G->kind==1||G->kind==3)  //  ��
		{
			p->pInfor = (int*)malloc(sizeof(int));

		
			memcpy(p->pInfor,&w,sizeof(int));

		}

		else   //ͼ
		{

			p->pInfor = NULL;
		}

		//�����
		p->nexttarc = G->vertices[i].firstarc;

		G->vertices[i].firstarc = p;


		 /*����ͼ����,�����ڶ������� */

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


	//���춥��
	for (i=0;i<G->vexnum;i++)
	{
		fscanf(fp,"%s",&G->vertices[i].data);

		G->vertices[i].firstarc = NULL;
	}


	for (k=0;k<G->arcnum;k++)
	{
	
			fscanf(fp,"%s",&va);

			fscanf(fp,"%s",&vb);
	

		i = LocateVex(*G,va);  //����

		j = LocateVex(*G,vb);  //��ͷ


		p = (pArcNode)malloc(sizeof(ArcNode));

		p->adjvex = j;

	  p->pInfor  = NULL;

		//�����
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
			
			if (G->kind%2)  //��
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
		printf("������ͼ�л�·\n");
        return false;
	}

	else
	{
		printf("Ϊһ���������С�\n");
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
	if((*S).pTop -(*S).pBase>=(*S).stacksize) /* ջ����׷�Ӵ洢�ռ� */
	{
		(*S).pBase = (int*)realloc((*S).pBase,((*S).stacksize+STACKINCREMENT)*sizeof(int));
		
		if(!(*S).pBase)
		{
			return false; /* �洢����ʧ�� */
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