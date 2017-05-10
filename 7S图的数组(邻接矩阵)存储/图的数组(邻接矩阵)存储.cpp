#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>

#define INT_MAX 2147483647 

#define MAX_VERTEX_NUM 20  // ��󶥵����   // ��������Ͷ�̬����



 #define MAX_NAME 5        // �����ַ�������󳤶�+1 
 #define MAX_INFO 20       // �����Ϣ�ַ�������󳤶�+1 

typedef enum{DG,DN,AG,AN}GraphKind; // {����ͼ,������,����ͼ,������} 

// ������֧�ִ��ļ�����Infor

typedef struct  
{
	int adj;   /* �����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ� */

	void* Infor;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct  
{
	char vexs[MAX_VERTEX_NUM];  // �������� 

	AdjMatrix arcs;               // �ڽӾ���  // ��ά����ĵ�ַ

	int vexnum;
	int arcnum;                 // ͼ�ĵ�ǰ�������ͻ��� 

	GraphKind Kind;             //����
}MGraph,*pMGraph;


bool Visit(char v)
{
	printf("%c ",v);

	return true;
}



//  ��ʼ����:ͼG����,u��G�ж�������ͬ���� 
//  �������:��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 
int LocateVex(MGraph G,char u);

// ��������(�ڽӾ���)��ʾ��,���ļ�����û�������Ϣ������ͼG 
bool CreateFAG(pMGraph G);

// ��������(�ڽӾ���)��ʾ��,��������ͼG 
bool CreateDG(pMGraph G);


// ��������(�ڽӾ���)��ʾ��,����������G 
bool CreateDN(pMGraph G);

// ��������(�ڽӾ���)��ʾ��,��������ͼG 
bool CreateAG(pMGraph G);


// ��������(�ڽӾ���)��ʾ��,����������G
bool CreateAN(pMGraph G);


bool CreateGraph(pMGraph G);

void DestroyGraph(pMGraph G);

/* ��ʼ����: ͼG���ڣ�v��G��ĳ���������š��������: ����v��ֵ */
char GetVex(MGraph G,int v);

/* ��ʼ����: ͼG���ڣ�v��G��ĳ�����㡣�������: ��v����ֵvalue */
bool PutVex(pMGraph G,char v,char iValue);

/* ��ʼ����: ͼG����,v��G��ĳ������ */
/* �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1 */
int FirstAdjVex(MGraph G,char v);

/* ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ��� */
/* �������: ����v��(�����w��)��һ���ڽӶ�������, */
/*           ��w��v�����һ���ڽӶ���,�򷵻�-1 */
int NextAdjVex(MGraph G,char v,char w);
/* ��ʼ����: ͼG����,v��ͼG�ж�������ͬ���� */
/* �������: ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��) */
void InsertVex(pMGraph G,char v);

/* ��ʼ����: ͼG����,v��G��ĳ�����㡣�������: ɾ��G�ж���v������صĻ� */
bool DeleteVex(pMGraph G,char v);

/* ��ʼ����: ͼG����,v��W��G���������� */
/* �������: ��G������<v,w>,��G�������,������Գƻ�<w,v> */
bool InsertArc(pMGraph G,char v,char w);
/* ��ʼ����: ͼG����,v��w��G���������� */
/* �������: ��G��ɾ����<v,w>,��G�������,��ɾ���Գƻ�<w,v> */
bool DeleteArc(pMGraph G,char v,char w);
//�������
void DFSTravel(MGraph G,bool (*Visit)(char));

void DFS(MGraph G,int v);
//�������
void BFSTravel(MGraph G,bool (*Visit)(char));

void Display(MGraph G);


bool CreateFAN(pMGraph G);
bool CreateFDN(pMGraph G);
bool CreateFDG(pMGraph G);



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






bool (*VisitFunc)(char);  //ȫ�ֺ���ָ�� 

bool visited[MAX_VERTEX_NUM]; //  ���ʱ�־����(ȫ����) 
void main()
{

	MGraph G;
	CreateFAG(&G);

//	CreateDG(&G);

//  CreateFAN(&G);

//  CreateGraph(&G);

//  CreateFDN(&G);

 // CreateFDG(&G);
  Display(G);


  DFSTravel(G,Visit);

  BFSTravel(G,Visit);

//   a b c d e f g h
//   a b c d e h f g



//  Display(G);

  DestroyGraph(&G);
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


bool CreateFAG(pMGraph G) // ��֧�ִ��ļ�����Infor
{
	int i = 0;
	int j = 0;
	int k = 0;

	char szFileName[20] = {0};

	char va;
	char vb;

	FILE* fp = NULL;            // dat txt def ini inf  �����ı��ļ������� û���ļ�ͷ���ļ�

//	printf("�����������ļ���(1.dat)��\n");

//	scanf("%s",szFileName);

	fp = fopen("1.txt","r");


  if (!fp)
  {
    printf("���ļ�\n");
    exit(0);
  }
	fscanf(fp,"%d",&(*G).vexnum); // �ļ������뺯��
   
	fscanf(fp,"%d",&(*G).arcnum);

	int IncInfor = 0;

	fscanf(fp,"%d",&IncInfor);


	for(i=0;i<(*G).vexnum;i++) // ���춥������ 
	{
		fscanf(fp,"%s",&(*G).vexs[i]);
	}

	// ��ʼ���ڽӾ��� 

	for (i=0;i<G->vexnum;i++)
	{
		for (j=0;j<G->vexnum;j++)
		{
			G->arcs[i][j].adj = 0;  // 0 ��ʾ��ͨ
			G->arcs[i][j].Infor = NULL;
		}
	}


	for (k=0;k<G->arcnum;++k)
	{
		fscanf(fp,"%s%s",&va,&vb); // ���� %c

		i = LocateVex(*G,va); // i ������ 

		j = LocateVex(*G,vb);

		G->arcs[i][j].adj = G->arcs[j][i].adj = 1; // ����ͼ
	}
   fclose(fp);
   G->Kind = AG;
   return true;
}



bool CreateDG(pMGraph G) // ����ͼ  // ��ͷ�Ĳ�����β 
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	int IncInfor = 0;

	char s[MAX_INFO] = {0};

	char* pInfor = NULL;


	char va,vb;


	printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0):\n");


	scanf("%d",&(*G).vexnum);
	scanf("%d",&(*G).arcnum);
	scanf("%d",&IncInfor);

	printf("������%d�������ֵ:\n",(*G).vexnum);
	//���춥������

	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->vexs[i]);
	}


	/* ��ʼ���ڽӾ��� */

	for (i=0;i<G->vexnum;i++)
	{
		for (j=0;j<G->vexnum;j++)
		{
			G->arcs[i][j].adj = 0;
			
			
			G->arcs[i][j].Infor = NULL;
		}
	}

	printf("������%d�����Ļ�β ��ͷ:\n",(*G).arcnum);


	for (k=0;k<G->arcnum;k++)
	{
		printf("��ͷ\n");
		scanf(" %c",&va);

		printf("��β\n");
		scanf(" %c",&vb);


		i = LocateVex(*G,va);

		j = LocateVex(*G,vb);

    if (i<0||j<0)
    {
      return false;
    }

		G->arcs[i][j].adj = 1;

		if (IncInfor)
		{
			printf("������û��������Ϣ(<%d���ַ�):\n",MAX_INFO);

			scanf("%s",s);

			l = strlen(s);

			if (l)
			{
				pInfor = (char*)malloc(sizeof(char)*(l+1));

				strcpy(pInfor,s);

				G->arcs[i][j].Infor = (void*)pInfor;
			}

		}
	}

	(*G).Kind = DG;
   
	return true;

}

bool CreateFDG(pMGraph G)
{
  int i =0;
  int j =0;

  int  k =0;
  char va = 0;

  char vb = 0;

  FILE* fp = fopen("DG.TXT","r");

  if (!fp)
  {
    printf("���ļ�\n");
    exit(0);
  }
  int  IncInfor = 0;

  fscanf(fp,"%d%d%d",&G->vexnum,&G->arcnum,&IncInfor);

  for (i=0;i<G->vexnum;++i)
  {
    fscanf(fp,"%s",&G->vexs[i]);
  }

  for (i=0;i<G->vexnum;++i)
  {
    for (j=0;j<G->vexnum;++j)
    {
      G->arcs[i][j].adj = 0;

      G->arcs[i][j].Infor = NULL;
    }
  }

  for(k=0;k<G->arcnum;++k)
  {
    fscanf(fp,"%s%s",&va,&vb);

    i = LocateVex(*G,va);

    j = LocateVex(*G,vb);

    if (i<0||j<0)
    {
      return false;
    }

    G->arcs[i][j].adj = 1;
  }
  fclose(fp);

  G->Kind = DG;
  return true;
}
bool CreateDN(pMGraph G) // ������
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

	//���춥��

	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->vexs[i]);
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

	 printf("������%d�����Ļ�β ��ͷ Ȩֵ:\n",(*G).arcnum);

	 for (k=0;k<G->arcnum;k++)
	 {
		 printf("��β\n");
		 scanf(" %c",&va);

		 printf("��ͷ\n");

		 scanf(" %c",&vb);

		 printf("Ȩֵ\n");

		 scanf("%d",&w);

		 i = LocateVex(*G,va);

		 j = LocateVex(*G,vb);

		 G->arcs[i][j].adj = w;


		 if (IncInfor)
		 {
			 printf("������û��������Ϣ(<%d���ַ�):\n",MAX_INFO);

			 scanf("%s",s);

			 w = strlen(s);

			 if(w)
			 {

				 pInfor = (char*)malloc(sizeof(char)*(w+1));

				 strcpy(pInfor,s);

				 G->arcs[i][j].Infor = (void*)pInfor;
			 }

		 }
	 }


	 G->Kind = DN;

	return true;
}

bool CreateFDN(pMGraph G)
{
  int i =0;
  int j = 0;

  int k = 0;

  int w =0;

  FILE* fp = fopen("DN.TXT","r");

  if (!fp)
  {
    printf("���ļ�\n");
    exit(0);
  }

  int IncInfor = 0;
  fscanf(fp,"%d%d",&G->vexnum,&G->arcnum,&IncInfor);

  for (i=0;i<G->vexnum;++i)
  {
    fscanf(fp,"%s",&G->vexs[i]); // ����ʹ��%c
  }

  for (i=0;i<G->vexnum;++i)
  {
    for (j=0;j<G->vexnum;++j)
    {
      G->arcs[i][j].adj = INT_MAX;

      G->arcs[i][j].Infor = NULL;
    }
  }


  char va = 0;

  char vb = 0;

  for (k=0;k<G->arcnum;++k)
  {
    fscanf(fp,"%s%s%d",&va,&vb,&w); // ����ʹ��%c

    i = LocateVex(*G,va);

    j = LocateVex(*G,vb);

    G->arcs[i][j].adj = w;
  }



  fclose(fp);

  G->Kind = DN;
  return true;
}
bool CreateAG(pMGraph G) // ����ͼ
{

	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	int IncInfor = 0;

	char s[MAX_INFO] = {0};
	char* pInfor = NULL;
	char va,vb;

	printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0):\n");

	scanf("%d",&(G->vexnum));
	
	scanf("%d",&(G->arcnum));
	
	scanf("%d",&IncInfor);

	printf("������%d�������ֵ:\n",(*G).vexnum);

	
	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->vexs[i]);
	}
	
	
	//��ʼ���ڽӾ���
	
	for (i=0;i<G->vexnum;i++)
	{
		for (j=0;j<G->vexnum;j++)
		{
			G->arcs[i][j].adj = 0;
			
			G->arcs[i][j].Infor = NULL;
		}
	}

	printf("������%d���ߵĶ���\n",(*G).arcnum);


	for (k=0;k<G->arcnum;k++)
	{
    printf("%d �Ķ���\n",k+1);
		scanf(" %c",&va);
		scanf(" %c",&vb);

		i = LocateVex(*G,va);
		j = LocateVex(*G,vb);

    if (i<0||j<0)
    {
      return false;
    }

		G->arcs[i][j].adj = G->arcs[j][i].adj = 1;

		if (IncInfor)
		{
			 printf("������ñߵ������Ϣ(<%d���ַ�):\n",MAX_INFO);


			 scanf("%s",s);
			 
			 l = strlen(s);
			 
			 if(l)
			 {
				 
				 pInfor = (char*)malloc(sizeof(char)*(l+1));
				 
				 strcpy(pInfor,s);
				 
				 G->arcs[i][j].Infor = G->arcs[j][i].Infor = (void*)pInfor;
			 }

		}
	}


	G->Kind = AG;

	return true;
}

bool CreateAN(pMGraph G) // ������
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


bool CreateFAN(pMGraph G)
{
  
  int i =0;
  int j =0;
  int k = 0;



  FILE* fp = fopen("AN.txt","r");

  if (!fp)
  {
    printf("���ļ�\n");
    exit(0);
  }
  int IncInfor = 0;
  fscanf(fp,"%d",&(G->vexnum));

  fscanf(fp,"%d",&(G->arcnum));

  fscanf(fp,"%d",&IncInfor);

  for (i=0;i<G->vexnum;++i)
  {
    fscanf(fp,"%s",&(G->vexs[i]));
  }
  

  for (i=0;i<G->vexnum;++i)
  {
    for (j=0;j<G->vexnum;++j)
    {
      G->arcs[i][j].adj = INT_MAX;

      G->arcs[i][j].Infor = NULL;
    }
  }

  char va = 0;

  char vb = 0;

  int w = 0;
  for (k=0;k<G->arcnum;++k)
  {
    fscanf(fp,"%s%s%d",&va,&vb,&w);
    i = LocateVex(*G,va);

    j = LocateVex(*G,vb);


    G->arcs[i][j].adj = G->arcs[j][i].adj = w;


  }


  fclose(fp);

  G->Kind = AN;
  return true;
}
bool CreateGraph(pMGraph G)
{
   printf("������ͼG������(����ͼ:0,������:1,����ͼ:2,������:3):\n");

   scanf("%d",&(G->Kind));
   switch (G->Kind)
   {
   case DG:
	   {
		   return CreateDG(G);
	   }
   case DN:
	   {
		   return CreateDN(G);
	   }
   case AG:
	   {
		   return CreateAG(G);
	   }
   case AN:
	   {

		   return CreateAN(G);
	   }

   default:
	   {
		   return false;
	   }
   }
}


void DestroyGraph(pMGraph G)
{
	int i = 0;
	int j = 0;

	if (G->Kind<2)  //����  ����ͼ ������
	{

		 for (i=0;i<G->vexnum;i++)
		 {

			 for (j=0;j<G->vexnum;j++)
			 {    // ����ͼ                               // ������
				 if (G->arcs[i][j].adj==1&&G->Kind==0||G->arcs[i][j].adj!=INT_MAX&&G->Kind==1)/* ����ͼ�Ļ�||�������Ļ� */
				 {
					 if (G->arcs[i][j].Infor)
					 {
						 free(G->arcs[i][j].Infor);


						 G->arcs[i][j].Infor = NULL;
					 }
				 }
			 }
		 }
	}
	else   //����
	{
			
		 for (i=0;i<G->vexnum;i++)
		 {
			 for (j=0;j<G->vexnum;j++)
			 {
				 if (G->arcs[i][j].adj==1&&G->Kind==2||G->arcs[i][j].adj!=INT_MAX&&G->Kind==3) /* ����ͼ�ı�||�������ı� */
				 {
					 if (G->arcs[i][j].Infor)
					 {
						 free(G->arcs[i][j].Infor);
						 
						 
						 G->arcs[i][j].Infor = NULL;

						 G->arcs[j][i].Infor = NULL; // ???
					 }
				 }
			 }
		 }
	}

	G->vexnum = 0;
	G->arcnum = 0;
}

char GetVex(MGraph G,int v)
{
	if (v>=G.vexnum||v<0)
	{
		exit(0);
	}

	return G.vexs[v];
}

bool PutVex(pMGraph G,char v,char iValue)
{
	int k = 0;

	k = LocateVex(*G,v);

	if (k<0)
	{
		return false;
	}

  strcpy(&G->vexs[k],&iValue);

	return true;
}
// ��ʼ����: ͼG����,v��G��ĳ������ 
// �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1 
int FirstAdjVex(MGraph G,char v) // ����ڽӵ�
{
	int i = 0;
	int j = 0;

	int k = 0;

	k = LocateVex(G,v); /* kΪ����v��ͼG�е���� */

  if (k<0)
  {
    return -1;
  }
	if (G.Kind==DN||G.Kind==AN)   //��
	{
		j = INT_MAX; // ��Чֵ
	}

	for (i=0;i<G.vexnum;i++)
	{
		if (G.arcs[k][i].adj!=j)
		{
			return i;
		}
	}

	return -1;
}
/* ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ��� */
/* �������: ����v��(�����w��)��һ���ڽӶ�������, */
/*           ��w��v�����һ���ڽӶ���,�򷵻�-1 */
int NextAdjVex(MGraph G,char v,char w)
{
	int i = 0;
	int j = 0;
	int k1 = 0;
  int k2 = 0;

	k1 = LocateVex(G,v);
	k2 = LocateVex(G,w);

	if (G.Kind==DN||G.Kind==AN)
	{
		j = INT_MAX;     //��
	}

	for (i=k2+1;i<G.vexnum;i++)
	{
		if (G.arcs[k1][i].adj!=j)
		{
			return i;
		}
	}


	return -1;
}
/* ��ʼ����: ͼG����,v��ͼG�ж�������ͬ���� */
/* �������: ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��) */
void InsertVex(pMGraph G,char v)
{
	int i = 0;

  G->vexs[G->vexnum] = v;

	for (i=0;i<=G->vexnum;i++)
	{
		if (G->Kind%2)  //��
		{

			 G->arcs[G->vexnum][i].adj = INT_MAX;

			 G->arcs[i][G->vexnum].adj = INT_MAX;
		}

		else
		{
			G->arcs[G->vexnum][i].adj = 0;
			G->arcs[i][G->vexnum].adj = 0;
		}

		G->arcs[G->vexnum][i].Infor = NULL;
		G->arcs[i][G->vexnum].Infor = NULL;
		
	}

	G->vexnum+=1;
}

bool DeleteVex(pMGraph G,char v)/* ��ʼ����: ͼG����,v��G��ĳ�����㡣�������: ɾ��G�ж���v������صĻ� */
{
	int i = 0;
	int j = 0;

	int k = 0;

	int m = 0;

	k = LocateVex(*G,v);

	if (k<0)
	{
		return false;
	}

	if (G->Kind==DN||G->Kind==AN)  //��
	{
		m = INT_MAX;
	}

	for (j=0;j<G->vexnum;j++)
	{
		if (G->arcs[j][k].adj!=m)  //�б߻�
		{

			if (G->arcs[j][k].Infor)
			{
				free(G->arcs[j][k].Infor);

				G->arcs[j][k].Infor = NULL;
			}

			G->arcnum--;
		}
	}

	if (G->Kind==DG||G->Kind==DN)   //����
	{
		for (j=0;j<G->vexnum;j++)
		{
			if (G->arcs[k][j].adj!=m)
			{
				if (G->arcs[k][j].Infor)
				{
					free(G->arcs[k][j].Infor);

					G->arcs[k][j].Infor = NULL;
				}
        --G->arcnum;
			}

			
		}
	}


	//�ƶ��ַ�����

	for (j=k+1;j<G->vexnum;j++)
	{
    G->vexs[j-1] = G->vexs[j];
	}


	//�ƶ����� 

	for (i=0;i<G->vexnum;i++)
	{
		for (j=k+1;j<G->vexnum;j++)
		{
			G->arcs[i][j-1] = G->arcs[i][j];/* �ƶ���ɾ������֮��ľ���Ԫ�� */
		}
	}


	for (i=0;i<G->vexnum;i++)
	{
		for (j=k+1;j<G->vexnum;j++)
		{
			G->arcs[j-1][i] = G->arcs[j][i];/* �ƶ���ɾ������֮�µľ���Ԫ�� */
		}
	}

	G->vexnum--;

	return true;
}


bool InsertArc(pMGraph G,char v,char w)
{
	int i = 0;
	int l = 0;
	int v1 = 0;
	int w1 = 0;

	char* pInfor = NULL;

	char s[MAX_INFO] = {0};

	v1 = LocateVex(*G,v);/* β */
	w1 = LocateVex(*G,w);/* ͷ */


	if (v1<0||w1<0)
	{
		return false;
	}

	G->arcnum++;

	if (G->Kind%2)  //��
	{
		printf("������˻���ߵ�Ȩֵ: ");
     
		scanf("%d",&(*G).arcs[v1][w1].adj);
	}

	else
	{
		G->arcs[v1][w1].adj = 1;
	}

	printf("�Ƿ��иû���ߵ������Ϣ(0:�� 1:��):\n");
  
	scanf("%d",&i);// scanf("%d%*c",&i);

	if (i)
	{

		  printf("������û���ߵ������Ϣ(<%d���ַ�):\n",MAX_INFO);

		  scanf("%s",s);

		  l = strlen(s);

		  if (l)
		  {
			  pInfor = (char*)malloc(sizeof(char)*(l+1));

			  strcpy(pInfor,s);

			  G->arcs[v1][w1].Infor = (void*)pInfor;
		  }
	}

	if (G->Kind>1)  //����
	{
		G->arcs[w1][v1].adj = G->arcs[v1][w1].adj;

		G->arcs[w1][v1].Infor = G->arcs[v1][w1].Infor;/* ָ��ͬһ�������Ϣ */
	}


	return true;
}

bool DeleteArc(pMGraph G,char v,char w)
{
	int v1 = 0;
	int w1 = 0;

	v1 = LocateVex(*G,v);
	w1 = LocateVex(*G,w);

	if (v1<0||w1<0)
	{
		return false;
	}

	if (G->Kind%2==0)  //ͼ
	{

		G->arcs[v1][w1].adj =0;
	}

	else /* �� */
	{
		G->arcs[v1][w1].adj = INT_MAX;
	}

	if (G->arcs[v1][w1].Infor)
	{
		free(G->arcs[v1][w1].Infor);

		G->arcs[v1][w1].Infor = NULL;
	}

	//����
	if (G->Kind>=2)
	{
		G->arcs[w1][v1].adj = G->arcs[v1][w1].adj;

		G->arcs[w1][v1].Infor = NULL;
	}

	G->arcnum--;

	return true;
}


void DFSTravel(MGraph G,bool (*Visit)(char))
{
  /* ��ʼ����: ͼG����,Visit�Ƕ����Ӧ�ú���. */
  /* �������: �ӵ�1��������,������ȱ���ͼG,����ÿ��������ú���Visit */
  /*           һ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ�� */

	int v = 0;

	VisitFunc = Visit;/* ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ����� */

	for (v=0;v<G.vexnum;++v)
	{
		visited[v] = false;
	}

	for (v=0;v<G.vexnum;++v)
	{
		if (!visited[v])
		{
			DFS(G,v);
		}
	}

	printf("\n");
	
}


void DFS(MGraph G,int v)
{
// �ӵ�v����������ݹ��������ȱ���ͼG��
	char w1;
	char v1;

	int w = 0;
	visited[v] = true;

	VisitFunc(G.vexs[v]);

	v1 = GetVex(G,v);

	for (w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,w1 = GetVex(G,w)))
	{
		if (!visited[w])
		{
			DFS(G,w);
		}
	}
}




void BFSTravel(MGraph G,bool (*Visit)(char))
{

  VisitFunc = Visit;
	int v = 0;
	int u = 0;
	int w = 0;

	char w1,u1;

	SqQueue q;

	for (v=0;v<G.vexnum;++v)
	{
		visited[v] = false;
	}

	InitQueue(&q);

	for (v=0;v<G.vexnum;v++)
	{
		if (!visited[v])
		{
			visited[v] = true;

			VisitFunc(G.vexs[v]);

			EnQueue(&q,v);


			while (!QueueEmpty(q))
			{
				DeQueue(&q,&u);


				u1 = GetVex(G,u);

				for (w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,GetVex(G,w)))
				{
					if (!visited[w]) // ���
					{
						visited[w] = true;

						VisitFunc(G.vexs[w]);

						EnQueue(&q,w);
					}
				}
			}
		}
	}

	DestroyQueue(&q);

	printf("\n");
}







void Display(MGraph G)
{
	int i = 0;
	int j = 0;

	char s[7]  = {0};

	char s1[3] = {0};


	switch(G.Kind)
	{

	case DG:
		{
			strcpy(s,"����ͼ\0");

			strcpy(s1,"��\0");

			break;
		}

	case DN:
		{
			strcpy(s,"������\0");
            
			strcpy(s1,"��\0");
			
			break;
		}

	case AG:
		{
			strcpy(s,"����ͼ\0");
            
			strcpy(s1,"��\0");
			
			break;
		}
	case AN:
		{
			strcpy(s,"������\0");
            
			strcpy(s1,"��\0");
			
			break;
		}
	}

	 printf("%d������%d��%s��%s\n",G.vexnum,G.arcnum,s1,s);


	 for(i=0;i<G.vexnum;++i)
	 {
		 printf("G.vexs[%d]=%c\n",i,G.vexs[i]);
	 }

	 
	 printf("G.arcs.adj:\n");

	 for(i=0;i<G.vexnum;++i)
	 {
		 for(j=0;j<G.vexnum;++j)
		 {
       if (G.arcs[i][j].adj==INT_MAX)
       {
         printf("%6s","��");
       }
       else
       {
          printf("%6d",G.arcs[i][j].adj);
       }
			 
		 }
		 
		 printf("\n");
	}

	 printf("G.arcs.info:\n");
  
	 printf("����1(��β) ����2(��ͷ) ��%s��Ϣ:\n",s1);


	 if(G.Kind<2) /* ���� */
	 {
		 for(i=0;i<G.vexnum;i++)
		 {
			 for(j=0;j<G.vexnum;j++)
			 {
				 if(G.arcs[i][j].Infor)
				 {
					 printf("%5c %11c     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].Infor);// ����%s Ϊ %c
				 }
			 }
		 }
	 }

	 else
	 {
		 for(i=0;i<G.vexnum;i++)
		 {
			 for(j=i+1;j<G.vexnum;j++)
			 {
				 if(G.arcs[i][j].Infor)
				 {
					 printf("%5c %11c     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].Infor);
				 }
			 }
		 }
   
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