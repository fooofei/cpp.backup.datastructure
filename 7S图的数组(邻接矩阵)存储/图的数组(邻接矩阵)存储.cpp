#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>

#define INT_MAX 2147483647 

#define MAX_VERTEX_NUM 20  // 最大顶点个数   // 如果不够就动态申请



 #define MAX_NAME 5        // 顶点字符串的最大长度+1 
 #define MAX_INFO 20       // 相关信息字符串的最大长度+1 

typedef enum{DG,DN,AG,AN}GraphKind; // {有向图,有向网,无向图,无向网} 

// 本程序不支持从文件输入Infor

typedef struct  
{
	int adj;   /* 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； */

	void* Infor;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct  
{
	char vexs[MAX_VERTEX_NUM];  // 顶点向量 

	AdjMatrix arcs;               // 邻接矩阵  // 二维数组的地址

	int vexnum;
	int arcnum;                 // 图的当前顶点数和弧数 

	GraphKind Kind;             //种类
}MGraph,*pMGraph;


bool Visit(char v)
{
	printf("%c ",v);

	return true;
}



//  初始条件:图G存在,u和G中顶点有相同特征 
//  操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 
int LocateVex(MGraph G,char u);

// 采用数组(邻接矩阵)表示法,由文件构造没有相关信息的无向图G 
bool CreateFAG(pMGraph G);

// 采用数组(邻接矩阵)表示法,构造有向图G 
bool CreateDG(pMGraph G);


// 采用数组(邻接矩阵)表示法,构造有向网G 
bool CreateDN(pMGraph G);

// 采用数组(邻接矩阵)表示法,构造无向图G 
bool CreateAG(pMGraph G);


// 采用数组(邻接矩阵)表示法,构造无向网G
bool CreateAN(pMGraph G);


bool CreateGraph(pMGraph G);

void DestroyGraph(pMGraph G);

/* 初始条件: 图G存在，v是G中某个顶点的序号。操作结果: 返回v的值 */
char GetVex(MGraph G,int v);

/* 初始条件: 图G存在，v是G中某个顶点。操作结果: 对v赋新值value */
bool PutVex(pMGraph G,char v,char iValue);

/* 初始条件: 图G存在,v是G中某个顶点 */
/* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
int FirstAdjVex(MGraph G,char v);

/* 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 */
/* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号, */
/*           若w是v的最后一个邻接顶点,则返回-1 */
int NextAdjVex(MGraph G,char v,char w);
/* 初始条件: 图G存在,v和图G中顶点有相同特征 */
/* 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
void InsertVex(pMGraph G,char v);

/* 初始条件: 图G存在,v是G中某个顶点。操作结果: 删除G中顶点v及其相关的弧 */
bool DeleteVex(pMGraph G,char v);

/* 初始条件: 图G存在,v和W是G中两个顶点 */
/* 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v> */
bool InsertArc(pMGraph G,char v,char w);
/* 初始条件: 图G存在,v和w是G中两个顶点 */
/* 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v> */
bool DeleteArc(pMGraph G,char v,char w);
//深度优先
void DFSTravel(MGraph G,bool (*Visit)(char));

void DFS(MGraph G,int v);
//广度优先
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






bool (*VisitFunc)(char);  //全局函数指针 

bool visited[MAX_VERTEX_NUM]; //  访问标志数组(全局量) 
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
		if (u==G.vexs[i])   //单字符 
		{
			return i;
		}
	}

	return -1;
}


bool CreateFAG(pMGraph G) // 不支持从文件输入Infor
{
	int i = 0;
	int j = 0;
	int k = 0;

	char szFileName[20] = {0};

	char va;
	char vb;

	FILE* fp = NULL;            // dat txt def ini inf  都是文本文件创建的 没有文件头的文件

//	printf("请输入数据文件名(1.dat)：\n");

//	scanf("%s",szFileName);

	fp = fopen("1.txt","r");


  if (!fp)
  {
    printf("无文件\n");
    exit(0);
  }
	fscanf(fp,"%d",&(*G).vexnum); // 文件的输入函数
   
	fscanf(fp,"%d",&(*G).arcnum);

	int IncInfor = 0;

	fscanf(fp,"%d",&IncInfor);


	for(i=0;i<(*G).vexnum;i++) // 构造顶点向量 
	{
		fscanf(fp,"%s",&(*G).vexs[i]);
	}

	// 初始化邻接矩阵 

	for (i=0;i<G->vexnum;i++)
	{
		for (j=0;j<G->vexnum;j++)
		{
			G->arcs[i][j].adj = 0;  // 0 表示不通
			G->arcs[i][j].Infor = NULL;
		}
	}


	for (k=0;k<G->arcnum;++k)
	{
		fscanf(fp,"%s%s",&va,&vb); // 或者 %c

		i = LocateVex(*G,va); // i 是竖的 

		j = LocateVex(*G,vb);

		G->arcs[i][j].adj = G->arcs[j][i].adj = 1; // 无向图
	}
   fclose(fp);
   G->Kind = AG;
   return true;
}



bool CreateDG(pMGraph G) // 有向图  // 箭头的部分是尾 
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	int IncInfor = 0;

	char s[MAX_INFO] = {0};

	char* pInfor = NULL;


	char va,vb;


	printf("请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0):\n");


	scanf("%d",&(*G).vexnum);
	scanf("%d",&(*G).arcnum);
	scanf("%d",&IncInfor);

	printf("请输入%d个顶点的值:\n",(*G).vexnum);
	//构造顶点向量

	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->vexs[i]);
	}


	/* 初始化邻接矩阵 */

	for (i=0;i<G->vexnum;i++)
	{
		for (j=0;j<G->vexnum;j++)
		{
			G->arcs[i][j].adj = 0;
			
			
			G->arcs[i][j].Infor = NULL;
		}
	}

	printf("请输入%d条弧的弧尾 弧头:\n",(*G).arcnum);


	for (k=0;k<G->arcnum;k++)
	{
		printf("弧头\n");
		scanf(" %c",&va);

		printf("弧尾\n");
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
			printf("请输入该弧的相关信息(<%d个字符):\n",MAX_INFO);

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
    printf("无文件\n");
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
bool CreateDN(pMGraph G) // 有向网
{
	int i = 0;
	int j = 0;
	int k = 0;

	int w = 0;
	int IncInfor = 0;

	char s[MAX_INFO] = {0};

	char* pInfor = NULL;


	char va,vb;

	printf("请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0):\n");

	scanf("%d",&(G->vexnum));

	scanf("%d",&(G->arcnum));

	scanf("%d",&IncInfor);

	
	printf("请输入%d个顶点的值:\n",(*G).vexnum);

	//构造顶点

	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->vexs[i]);
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

	 printf("请输入%d条弧的弧尾 弧头 权值:\n",(*G).arcnum);

	 for (k=0;k<G->arcnum;k++)
	 {
		 printf("弧尾\n");
		 scanf(" %c",&va);

		 printf("弧头\n");

		 scanf(" %c",&vb);

		 printf("权值\n");

		 scanf("%d",&w);

		 i = LocateVex(*G,va);

		 j = LocateVex(*G,vb);

		 G->arcs[i][j].adj = w;


		 if (IncInfor)
		 {
			 printf("请输入该弧的相关信息(<%d个字符):\n",MAX_INFO);

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
    printf("无文件\n");
    exit(0);
  }

  int IncInfor = 0;
  fscanf(fp,"%d%d",&G->vexnum,&G->arcnum,&IncInfor);

  for (i=0;i<G->vexnum;++i)
  {
    fscanf(fp,"%s",&G->vexs[i]); // 不能使用%c
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
    fscanf(fp,"%s%s%d",&va,&vb,&w); // 不能使用%c

    i = LocateVex(*G,va);

    j = LocateVex(*G,vb);

    G->arcs[i][j].adj = w;
  }



  fclose(fp);

  G->Kind = DN;
  return true;
}
bool CreateAG(pMGraph G) // 无向图
{

	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;

	int IncInfor = 0;

	char s[MAX_INFO] = {0};
	char* pInfor = NULL;
	char va,vb;

	printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1,否:0):\n");

	scanf("%d",&(G->vexnum));
	
	scanf("%d",&(G->arcnum));
	
	scanf("%d",&IncInfor);

	printf("请输入%d个顶点的值:\n",(*G).vexnum);

	
	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->vexs[i]);
	}
	
	
	//初始化邻接矩阵
	
	for (i=0;i<G->vexnum;i++)
	{
		for (j=0;j<G->vexnum;j++)
		{
			G->arcs[i][j].adj = 0;
			
			G->arcs[i][j].Infor = NULL;
		}
	}

	printf("请输入%d条边的顶点\n",(*G).arcnum);


	for (k=0;k<G->arcnum;k++)
	{
    printf("%d 的顶点\n",k+1);
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
			 printf("请输入该边的相关信息(<%d个字符):\n",MAX_INFO);


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

bool CreateAN(pMGraph G) // 无向网
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


bool CreateFAN(pMGraph G)
{
  
  int i =0;
  int j =0;
  int k = 0;



  FILE* fp = fopen("AN.txt","r");

  if (!fp)
  {
    printf("无文件\n");
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
   printf("请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3):\n");

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

	if (G->Kind<2)  //有向  有向图 有向网
	{

		 for (i=0;i<G->vexnum;i++)
		 {

			 for (j=0;j<G->vexnum;j++)
			 {    // 有向图                               // 有向网
				 if (G->arcs[i][j].adj==1&&G->Kind==0||G->arcs[i][j].adj!=INT_MAX&&G->Kind==1)/* 有向图的弧||有向网的弧 */
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
	else   //无向
	{
			
		 for (i=0;i<G->vexnum;i++)
		 {
			 for (j=0;j<G->vexnum;j++)
			 {
				 if (G->arcs[i][j].adj==1&&G->Kind==2||G->arcs[i][j].adj!=INT_MAX&&G->Kind==3) /* 无向图的边||无向网的边 */
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
// 初始条件: 图G存在,v是G中某个顶点 
// 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 
int FirstAdjVex(MGraph G,char v) // 获得邻接点
{
	int i = 0;
	int j = 0;

	int k = 0;

	k = LocateVex(G,v); /* k为顶点v在图G中的序号 */

  if (k<0)
  {
    return -1;
  }
	if (G.Kind==DN||G.Kind==AN)   //网
	{
		j = INT_MAX; // 无效值
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
/* 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 */
/* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号, */
/*           若w是v的最后一个邻接顶点,则返回-1 */
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
		j = INT_MAX;     //网
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
/* 初始条件: 图G存在,v和图G中顶点有相同特征 */
/* 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
void InsertVex(pMGraph G,char v)
{
	int i = 0;

  G->vexs[G->vexnum] = v;

	for (i=0;i<=G->vexnum;i++)
	{
		if (G->Kind%2)  //网
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

bool DeleteVex(pMGraph G,char v)/* 初始条件: 图G存在,v是G中某个顶点。操作结果: 删除G中顶点v及其相关的弧 */
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

	if (G->Kind==DN||G->Kind==AN)  //网
	{
		m = INT_MAX;
	}

	for (j=0;j<G->vexnum;j++)
	{
		if (G->arcs[j][k].adj!=m)  //有边或弧
		{

			if (G->arcs[j][k].Infor)
			{
				free(G->arcs[j][k].Infor);

				G->arcs[j][k].Infor = NULL;
			}

			G->arcnum--;
		}
	}

	if (G->Kind==DG||G->Kind==DN)   //有向
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


	//移动字符数组

	for (j=k+1;j<G->vexnum;j++)
	{
    G->vexs[j-1] = G->vexs[j];
	}


	//移动矩阵 

	for (i=0;i<G->vexnum;i++)
	{
		for (j=k+1;j<G->vexnum;j++)
		{
			G->arcs[i][j-1] = G->arcs[i][j];/* 移动待删除顶点之后的矩阵元素 */
		}
	}


	for (i=0;i<G->vexnum;i++)
	{
		for (j=k+1;j<G->vexnum;j++)
		{
			G->arcs[j-1][i] = G->arcs[j][i];/* 移动待删除顶点之下的矩阵元素 */
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

	v1 = LocateVex(*G,v);/* 尾 */
	w1 = LocateVex(*G,w);/* 头 */


	if (v1<0||w1<0)
	{
		return false;
	}

	G->arcnum++;

	if (G->Kind%2)  //网
	{
		printf("请输入此弧或边的权值: ");
     
		scanf("%d",&(*G).arcs[v1][w1].adj);
	}

	else
	{
		G->arcs[v1][w1].adj = 1;
	}

	printf("是否有该弧或边的相关信息(0:无 1:有):\n");
  
	scanf("%d",&i);// scanf("%d%*c",&i);

	if (i)
	{

		  printf("请输入该弧或边的相关信息(<%d个字符):\n",MAX_INFO);

		  scanf("%s",s);

		  l = strlen(s);

		  if (l)
		  {
			  pInfor = (char*)malloc(sizeof(char)*(l+1));

			  strcpy(pInfor,s);

			  G->arcs[v1][w1].Infor = (void*)pInfor;
		  }
	}

	if (G->Kind>1)  //无向
	{
		G->arcs[w1][v1].adj = G->arcs[v1][w1].adj;

		G->arcs[w1][v1].Infor = G->arcs[v1][w1].Infor;/* 指向同一个相关信息 */
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

	if (G->Kind%2==0)  //图
	{

		G->arcs[v1][w1].adj =0;
	}

	else /* 网 */
	{
		G->arcs[v1][w1].adj = INT_MAX;
	}

	if (G->arcs[v1][w1].Infor)
	{
		free(G->arcs[v1][w1].Infor);

		G->arcs[v1][w1].Infor = NULL;
	}

	//无向
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
  /* 初始条件: 图G存在,Visit是顶点的应用函数. */
  /* 操作结果: 从第1个顶点起,深度优先遍历图G,并对每个顶点调用函数Visit */
  /*           一次且仅一次。一旦Visit()失败,则操作失败 */

	int v = 0;

	VisitFunc = Visit;/* 使用全局变量VisitFunc,使DFS不必设函数指针参数 */

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
// 从第v个顶点出发递归地深度优先遍历图G。
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
					if (!visited[w]) // 标记
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
			strcpy(s,"有向图\0");

			strcpy(s1,"弧\0");

			break;
		}

	case DN:
		{
			strcpy(s,"有向网\0");
            
			strcpy(s1,"弧\0");
			
			break;
		}

	case AG:
		{
			strcpy(s,"无向图\0");
            
			strcpy(s1,"边\0");
			
			break;
		}
	case AN:
		{
			strcpy(s,"无向网\0");
            
			strcpy(s1,"边\0");
			
			break;
		}
	}

	 printf("%d个顶点%d条%s的%s\n",G.vexnum,G.arcnum,s1,s);


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
         printf("%6s","∞");
       }
       else
       {
          printf("%6d",G.arcs[i][j].adj);
       }
			 
		 }
		 
		 printf("\n");
	}

	 printf("G.arcs.info:\n");
  
	 printf("顶点1(弧尾) 顶点2(弧头) 该%s信息:\n",s1);


	 if(G.Kind<2) /* 有向 */
	 {
		 for(i=0;i<G.vexnum;i++)
		 {
			 for(j=0;j<G.vexnum;j++)
			 {
				 if(G.arcs[i][j].Infor)
				 {
					 printf("%5c %11c     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].Infor);// 更改%s 为 %c
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