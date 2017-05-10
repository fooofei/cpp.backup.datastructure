#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX_VERTEX_NUM 20
#define MAX_INFOR 20

#define  QUEUESIZESTEP 3 // ���г���ÿһ���Ӻ�
#define  QUEUEDATA int  // ÿ��ʹ�� ��Ҫ���ĵ���������
typedef enum{unvisited,visited}VisitIf;

// ���ڽӶ��ر�������������ͬһ����ıߴ�����
// ͬһ������ ����ÿ������������������ ��ÿ���߽ڵ�ͬʱ������
// ����������

// ���ڽӱ�Ĳ��  ͬһ�������ڽӱ�������������ʾ
// ���ٽ���ر���ֻ��һ����� 
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
bool CreateGraph(AMLGraph* G);    /* �����ڽӶ��ر�洢�ṹ,��������ͼG */

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

void (*VisitFunc)(char);  //ȫ�ֺ���ָ�� 

bool visit[MAX_VERTEX_NUM]; /* ���ʱ�־����(ȫ����) */


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

	printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1����:0):\n");


	scanf("%d",&G->vexnum);

	scanf("%d",&G->edgenum);


//	scanf("%d",&IncInfor);

  IncInfor = 0;

	printf("������%d�������ֵ:\n",(*G).vexnum);

	for (i=0;i<G->vexnum;i++)
	{
		scanf(" %c",&G->adjmulist[i].data);

		G->adjmulist[i].firstedge = NULL;
	}

	printf("��˳������ÿ���ߵ������˵�:\n");

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
			 printf("������û��������Ϣ\n");


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
  fscanf(fp,"%d",&Infor); // Ϊ�˶�Ӧ��ʽһ��
  
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
  /* ��ʼ����: ����ͼG����,v��G��ĳ������ */
   /* �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1 */
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
			return G.adjmulist[i].firstedge->ivex;   //   ����ͼ�Ĵ���
		}



	}
		return -1;
	
}

/* ��ʼ����: ����ͼG����,v��G��ĳ������,w��v���ڽӶ��� */
/* �������: ����v��(�����w��)��һ���ڽӶ������š� */
   /*           ��w��v�����һ���ڽӵ�,�򷵻�-1 */
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

  // ������i��·���ҵ� ��ͷ�� i �� j �Ļ�

	p = G.adjmulist[i].firstedge;

	while (p)
	{
		if (p->ivex==i&&p->jvex!=j)  // �����ڽӶ���w(���1) 
		{

			p = p->iLink;
		}

		else if (p->jvex==i&&p->ivex!=j)  //�����ڽӵ�  ����ͼ ����һ�����
		{
			p = p->jLink;
		}

		else
		{
			break;// ���ڽӶ���w 
		}
  } // �ҵ��� 


	if (p&&p->ivex==i&&p->jvex==j)  // �ҵ��ڽӶ���w(���1)   
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


	if (p&&p->ivex==j&&p->jvex==i) // �ҵ��ڽӶ���w(���2) 
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

	if (LocateVex(*G,v)>=0)   //�ڵ����
	{
		 return false;
	}



	G->adjmulist[G->vexnum].data = v;

	G->adjmulist[G->vexnum].firstedge = NULL;


	G->vexnum++;


	return true;
}


bool DeleteArc(AMLGraph* G,char v,char w) // ɾ��
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

	if (p&&p->jvex==j)  // ��1���߼�Ϊ��ɾ����(���1)   yes
	{
		G->adjmulist[i].firstedge = p->iLink;
    // �����и����� ������Ѱ��һ���� i j  Ϊ�˵�Ļ� ���� ���ǲ�û���ж����� ����˵����
    // p->ivex==i && p->jvex==j ����ֻ���� p->jvex==j  Ϊʲô��  
    // ��Ϊ���Ǵ� i �ı�ԵѰ�ҵ�  ��Ȼ��i �й�ϵ  ����  ����ֻ��Ҫ����j��û�й�ϵ������ 
	}

	else if (p&&p->ivex==j) // ��1���߼�Ϊ��ɾ����(���2) 
	{
		G->adjmulist[i].firstedge = p->jLink;
	}

	else// ��1���߲��Ǵ�ɾ���� 
	{

		while(p)
		{
			if (p->ivex==i&&p->jvex!=j)// ���Ǵ�ɾ����
			{
				q = p;      // q is the p of pre node       yes

				p = p->iLink; // ����һ���ڽӶ���
			}

			else if (p->jvex==i&&p->ivex!=j)
			{

				q = p;

				p = p->jLink;
			}

			else
			{
				break;// ���ڽӶ���
			}

		}

		if (!p)// ���û���ҵ�  �ͷ�����  ��������Ĵӷ�����Ѱ�Ҳ���˵�����ڴ����
		{
			return false;
		}

		if (p->ivex==i&&p->jvex==j) // �ҵ���<v,w>(���1)  yes
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

		else if (p->ivex==j&&p->jvex==i)// �ҵ���<v,w>(���2) 
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


	 // ��������һ�������Ҵ�ɾ������ɾ��֮

	p = G->adjmulist[j].firstedge;


	if (p->jvex==i )// (j,i)  yes  ��һ���  
	{
		G->adjmulist[j].firstedge = p->iLink;

		if (p->pInfor)
		{
			free(p->pInfor);
		}

		free(p);
	}

	else if (p->ivex==i) // (i,j)  yes ��һ���
	{
		G->adjmulist[j].firstedge = p->jLink;

		if (p->pInfor)
		{
			free(p->pInfor);
		}

		free(p);
	}

	else// ��1���߲��Ǵ�ɾ����
	{
		while (p)// �����һ�<v,w>
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





bool InsertArc(AMLGraph* G,char v,char w) // �廡
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


//	printf("�ñ��Ƿ��������Ϣ(1:�� 0:��):\n");


//	scanf("%d",&IncInfor);

  IncInfor = 0;

	if (IncInfor)
	{
		printf("������ñߵ������Ϣ\n");


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



bool DeleteVex(AMLGraph* G,char v) // ɾ����
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

	// ���ڶ���v����Ķ������ż�1 

	for (j=i+1;j<G->vexnum;j++)
	{
		G->adjmulist[j-1] = G->adjmulist[j];
	}

	G->vexnum--;

	 // �޸Ķ������� 

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

	for (i=G->vexnum-1;i>=0;--i) // ��������ʵi һֱ���� vexnum-1
	{
		DeleteVex(G,G->adjmulist[i].data); // ɾ������ ֮�� ��ɾ����������ĺ�����ɾ����  ���� ���ùܱ�
	}

  // ����������   ֪��Ϊʲô�����Ҫ����ɾ������  ��Ϊÿ��ɾ������֮�� ���ǵ�vexnumҲ�ڱ仯�� ����
  // ����Ҫ������ɾ���Ͳ�����ô����
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


void Display(AMLGraph G)// �������ͼ���ڽӶ��ر�G 
{
	int i = 0;

	EBox* p = NULL;

	MarkUnVisited(G);

	printf("%d������:\n",G.vexnum);


	for (i=0;i<G.vexnum;i++)
	{
		 printf("%c ",G.adjmulist[i].data);
	}

	printf("\n%d����:\n",G.edgenum);


	for (i=0;i<G.vexnum;i++) // Bug  edgenum  ��Ϊ vexnum
	{
		p = G.adjmulist[i].firstedge;

		while (p)
		{
			if (p->ivex==i)// �ߵ�i����ö����й� 
			{
			
				if (!p->mark)
				{
					printf("%c��%c ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);

					p->mark = visited;

					if (p->pInfor)
					{
						printf("�����Ϣ%s\n",p->pInfor);
					}

				}


				p = p->iLink;
			}

			else // �ߵ�j����ö����й� 
			{
				if (!p->mark)
				{
					printf("%c��%c ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);


					p->mark = visited;


					if (p->pInfor)
					{
						printf("�����Ϣ%s\n",p->pInfor);
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

/* ��ʼ����: ͼG����,Visit�Ƕ����Ӧ�ú������㷨7.6 */
/* �������: �ӵ�1��������,��������ȷǵݹ����ͼG,����ÿ��������ú��� */
/*           Visitһ���ҽ�һ�Ρ�һ��Visit()ʧ��,�����ʧ�ܡ� */
/*           ʹ�ø�������Q�ͷ��ʱ�־����visite */
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
		Data = *(QUEUEDATA*)0;  // ���������Ҫ����  
		
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