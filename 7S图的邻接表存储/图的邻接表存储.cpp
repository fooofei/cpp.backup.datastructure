#include <stdio.h>
#include <malloc.h>
#include <windows.h>

#define MAX_VERTEX_NUM 20
typedef enum{DG,DN,AG,AN}GraphKind; 

typedef struct ArcNode 
{
	int adjvex;   /* �û���ָ��Ķ����λ�� */
	ArcNode* nexttarc;  /* ָ����һ������ָ�� */   // nextarc error 
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





/* ��ʼ����: ͼG����,u��G�ж�������ͬ���� */
/* �������: ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 */
int LocateVex(ALGraph G,char u);


/* �����ڽӱ�洢�ṹ,����û�������Ϣ��ͼG(��һ����������4��ͼ) */
bool CreateGraph(ALGraph* G);

void DestroyGraph(ALGraph* G);

char GetVex(ALGraph G,int v);

bool PutVex(ALGraph* G,char v,char value);


/* ��ʼ����: ͼG����,v��G��ĳ������ */
/* �������: ����v�ĵ�һ���ڽӶ�������,��������G��û���ڽӶ���,�򷵻�-1 */
int FirstAdjVex(ALGraph G,char v);

/* ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ��� */
/* �������: ����v��(�����w��)��һ���ڽӶ�������*/
/*           ��w��v�����һ���ڽӵ�,�򷵻�-1 */
int NextAdjVex(ALGraph G,char v,char w);

/* ��ʼ����: ͼG����,v��ͼ�ж�������ͬ���� */
/* �������: ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��) */
void InsertVex(ALGraph* G,char v);


/* ��ʼ����: ͼG����,v��G��ĳ������ */
/* �������: ɾ��G�ж���v������صĻ� */
bool DeleteVex(ALGraph* G,char v);


/* ��ʼ����: ͼG����,v��w��G���������� */
/* �������: ��G������<v,w>,��G�������,������Գƻ�<w,v> */
bool InsertArc(ALGraph* G,char v,char w);

/* ��ʼ����: ͼG����,v��w��G���������� */
/* �������: ��G��ɾ����<v,w>,��G�������,��ɾ���Գƻ�<w,v> */
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





void (*VisitFunc)(char);  //ȫ�ֺ���ָ�� 

bool visited[MAX_VERTEX_NUM]; /* ���ʱ�־����(ȫ����) */

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

	printf("������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3):\n");
 
	scanf("%d",&(*G).kind);


	printf("������ͼ�Ķ�����,����: ");
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


		i = LocateVex(*G,va);  

		j = LocateVex(*G,vb);  //��ͷ


		p = (pArcNode)malloc(sizeof(ArcNode));

		p->adjvex = j;

		if (G->kind==1||G->kind==3)  //  ��
		{
			p->pInfor = (int*)malloc(sizeof(int));

		
			memcpy(p->pInfor,&w,sizeof(int)); // ������Ҫ�Ķ�һ�� �Լ�����һ��Ȩֵ Infor���������Ϣ

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

			if (G->kind%2)   //��
			{
				free(q->pInfor);
			}

			free(q);

			G->arcnum--;
		}

		G->vexnum--;

		/* ����v����Ķ���ǰ�� */


		for (i=j;i<G->vexnum;i++)
		{
			G->vertices[i] = G->vertices[i+1];
		}




		for (i=0;i<G->vexnum;i++)// ɾ����vΪ��ȵĻ�����ұ�Ҫʱ�޸ı���Ķ���λ��ֵ
		{
			p = G->vertices[i].firstarc;    //ָ���һ����


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

						if (G->kind<2)  //����
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
						
						if (G->kind<2)  //����
						{
							G->arcnum--;
						}
						
					}
				}
				else
				{
					if (p->adjvex>j)
					{
						p->adjvex--;  // �޸ı���Ķ���λ��ֵ(���)
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

	if (G->kind%2)  //��
	{
		printf("�����뻡(��)%c��%c��Ȩֵ: ",v,w);


		scanf("%d",&w1);
	}

	p = (pArcNode)malloc(sizeof(ArcNode));

	p->adjvex = j;

	if (G->kind%2)// �� 
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

	if (G->kind>=2) // ����,������һ������ 
	{
		p = (pArcNode)malloc(sizeof(ArcNode));

		p->adjvex = i;


		if (G->kind==3)// ������
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


		if (G->kind%2)  // ��
		{
			free(p->pInfor);
		}

		free(p);

		G->arcnum--;
	}

	// ����,ɾ���Գƻ�<w,v> 

	if (G->kind>=2)
	{
		p = G->vertices[j].firstarc;

		while (p&&p->adjvex!=i)// p��������ָ֮�����Ǵ�ɾ����<w,v>
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
			printf("����ͼ\n");
			break;
		}

	case DN:
		{

			printf("������\n");
			break;
		}
	case AG:
		{
			printf("����ͼ\n");
			break;
		}

	case AN:
		{
			printf("������\n");
			break;
		}

	default:
		{

			break;
		}
	}
	
	printf("%d�����㣺\n",G.vexnum);
	
	for (i=0;i<G.vexnum;i++)
	{
		printf("%c  ",G.vertices[i].data);
	}

	printf("\n%d����(��):\n",G.arcnum);
	
	for (i=0;i<G.vexnum;i++)
	{
		p = G.vertices[i].firstarc;

		while (p)
		{
			if (G.kind<=1)
			{
				 printf("%c��%c ",G.vertices[i].data,G.vertices[p->adjvex].data);

				 if (G.kind==DN)
				 {
					 printf(":%d",p->pInfor);
				 }
			}

			else  //��������������
			{

				if (i<p->adjvex)
				{
					printf("%c��%c ",G.vertices[i].data,G.vertices[p->adjvex].data);
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