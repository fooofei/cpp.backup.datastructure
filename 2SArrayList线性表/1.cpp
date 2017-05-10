#include <STDIO.H>
#include <WINDOWS.H>
#include <ASSERT.H>
#define LIST_INIT_SIZE 10/* ���Ա�洢�ռ�ĳ�ʼ������ */
#define LISTINCREMENT 2


typedef struct
{
  int *elem; /* �洢�ռ��ַ */
  int length; /* ��ǰ���� */
  int listsize; /* ��ǰ����Ĵ洢����(��sizeof(ElemType)Ϊ��λ) */
 }SqList;

 /* �������������һ���յ�˳�����Ա� */
bool InitList(SqList* L);

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������˳�����Ա�L */
bool DestroyList(SqList* L);


/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
bool ClearList(SqList* L);

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
bool ListEmpty(SqList L);


/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* �����������e����L�е�i������Ԫ�ص�ֵ */
bool GetElem(SqList L,int i,int* e);


 /* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(SqList L);



/* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
/*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
int LocateElem(SqList L,int e, bool (*Compare)(int a,int b));




/* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
/*           �������ʧ�ܣ�pre_e�޶��� */
bool PriorElem(SqList L,int cur_e,int* pre_e);



/* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
/*           �������ʧ�ܣ�next_e�޶��� */

bool NextElem(SqList L,int cur_e,int* next_e);



/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L)+1 */
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
bool ListInsert(SqList* L,int i,int e);



/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
bool ListDelete(SqList* L,int i,int* e);


/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ�ܣ������ʧ�� */
/*           vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ */


bool ListTravel(SqList L,void(*vi)(int*));

void visit(int* a)
{
  printf("%d ",*a);
}

bool compare(int a , int b)
{
  return(a==b);
}

// �� b��  ���� a �е� Ԫ�ز��뵽 a ��

void Union(SqList *La, SqList *Lb);

void SortList(SqList *L);
// ����ĺϲ� ���Ա�
void MergeList(SqList La, SqList Lb, SqList *Lc);

int main()
{

  SqList L;

  InitList(&L);

  printf("���Ա�Ϊ��1 ����0��%d.\n",ListEmpty(L));


  ListInsert(&L,1,11);

  ListInsert(&L,2,13);

  ListInsert(&L,1,12);

  printf("��������֮�����Ա�Ϊ��1 ����0��%d. ���Ա���%d.\n",ListEmpty(L),ListLength(L));

  printf("��ӡ���Ա�:");
  ListTravel(L,visit);
  printf("\n");

  int e = 0;

  GetElem(L,1,&e);

  printf("��һ��Ԫ����%d.\n",e);

  GetElem(L,LocateElem(L,13,compare),&e);

  printf("compare ���� %d.\n",e);

 
  PriorElem(L,13,&e);

  printf("13��ǰ��������%d.\n",e);

  NextElem(L,11,&e);

  printf("11�ĺ��������%d.\n",e);

  ListDelete(&L,3,&e);

  printf("ɾ���ĵ�һ��������%d.\n",e);

  printf("��ӡ���Ա�:");
  ListTravel(L,visit);
  printf("\n");

  DestroyList(&L);


// 	SqList La,Lb, Lc;
// 
// 	InitList(&La);
// 	InitList(&Lb);
// 
// 	ListInsert(&La,1,11);
// 	ListInsert(&La,2,12);
// 	ListInsert(&Lb,1,110);
// 	ListInsert(&Lb,2,13);
// 
// 	SortList(&La);
// 	SortList(&Lb);
// 	MergeList(La,Lb,&Lc);
// 	ListTravel(Lc,visit);
//   
// 
// 	DestroyList(&La);
// 	DestroyList(&Lb);
// 	DestroyList(&Lc);

  return 0;
}



/* �������������һ���յ�˳�����Ա� */
bool InitList(SqList* L)
{
  L->elem = (int *)malloc(sizeof(int)*LIST_INIT_SIZE);

  if (L->elem==NULL)
  {
    exit(0);
  }


  memset(L->elem,0,sizeof(int)*LIST_INIT_SIZE);

  L->length = 0;

  L->listsize = LIST_INIT_SIZE;

  return true;
}

bool DestroyList(SqList* L)
{
  if (L->elem==NULL)
  {
    return false;
  }

  free(L->elem);

  L->elem = NULL;

  L->listsize = 0;

  L->length = 0;

  return true;
}


bool ClearList(SqList* L)
{
  if (L->elem==NULL)
  {
    return false;
  }

  L->length = 0;

  return true;
}

bool ListEmpty(SqList L)
{
  return (L.length ==0);
}

bool GetElem(SqList L,int i,int* e)
{
  if (L.elem==NULL)
  {
    exit(0);
  }
  if (i<1 || i>L.length)
  {
    return false;
  }

  *e = L.elem[i-1];

  return true;
}

int ListLength(SqList L)
{
  if (L.elem==NULL)
  {
    exit(0);
  }

  return L.length;
}

int LocateElem(SqList L,int e, bool (*Compare)(int a,int b))
{
  if (L.elem==NULL)
  {
    exit(0);
  }

  int i = 0;

  for (;i<L.length;++i)
  {
    if (Compare(e,L.elem[i]))
    {
      return i+1;
    }
  }

  return 0;
}

bool PriorElem(SqList L,int cur_e,int* pre_e)
{
  if (L.elem==NULL)
  {
    exit(0);
  }

  int i = 1;

  for (;i<L.length;++i)
  {
    if (cur_e==L.elem[i])
    {
      *pre_e =  L.elem[i-1];

      return true;
    }
  }

  
   *pre_e = 0;

   return false;
 
}
bool NextElem(SqList L,int cur_e,int* next_e)
{
  if (L.elem==NULL)
  {
    exit(0);
  }
  
  int i = 0;
  
  for (;i<L.length-1;++i)
  {
    if (cur_e==L.elem[i])
    {
      *next_e =  L.elem[i-1];
      
      return true;
    }
  }
  
  
  *next_e = 0;
  
   return false;
}

bool ListInsert(SqList* L,int i,int e)
{
  assert(i>=1&&i<=L->length+1);

  if (L->length==L->listsize-1)
  {
    L->elem = (int*)realloc(L->elem,sizeof(int)*(L->listsize+LISTINCREMENT));

    L->listsize += LISTINCREMENT;
  }

  int j = 0;

  for (j=L->length-1;L->length>0 &&j>=i-1;--j)
  {
    L->elem[j+1] = L->elem[j];
  }

  L->elem[i-1] = e;

  ++L->length;

  return true;
}

bool ListDelete(SqList* L,int i,int* e)
{
  assert(i>=1 && i<=L->length);

  if(L->elem==NULL)
  {
    exit(0);
  }
 
  int j  = 0;

  *e = L->elem[i-1];

  for (j=i-1;j<L->length;++j)
  {
    L->elem[j] = L->elem[j+1];
  }
  
  --L->length;

  return true;

}

bool ListTravel(SqList L,void(*vi)(int*))
{
  if (L.elem==NULL)
  {
    exit(0);
  }

  int i = 0;

  for (i=0;i<L.length;++i)
  {
    vi(&L.elem[i]);
  }

  return true;
}

// �� b��  ���� a �е� Ԫ�ز��뵽 a ��

void Union(SqList *La, SqList *Lb)
{
	if(La->elem == NULL || Lb->elem == NULL){
		return ;
	}
	
	int aLen = ListLength(*La);
	
	int bLen = ListLength(*Lb);
	
	int i = 0;
	
	int e = 0;
	for (i=1;i<=Lb->length;++i)
	{
		GetElem(*Lb,i,&e);
		
		if(!LocateElem(*La,e,compare))
			ListInsert(La,++aLen,e);
	}
	
	
}

void Swap(int &a, int &b)
{
	if(&a == &b)
	{
		return;
	}	

	a ^= b ^= a ^= b;
}

int Partion(int a[], int Low, int High)
{
		int temp = a[Low];
		
		while(Low<High)
		{
			
			while (Low< High && a[High]>=temp)
			{
				--High;
			}
			Swap(a[High],a[Low]);
			while (Low < High && a[Low] <= temp)
			{
				++Low;
			}
			
			Swap(a[Low],a[High]);
	}

	return Low;
}

void QuickSort(int a[], int Low, int High)
{
	if(a == NULL)
		return;
	if(Low<High)
	{
		int Mid = Partion(a,Low,High);
		QuickSort(a,Low,Mid-1);
		QuickSort(a,Mid+1,High);
	}
}
void SortList(SqList *L)
{
	if(L->elem == NULL)
	{
		return;
	}

	QuickSort(L->elem,0,L->length-1);
}

// ����ĺϲ�  �Ѿ������ ���Ա� ����ʹ�� SortList����  ����
void MergeList(SqList La, SqList Lb, SqList *Lc)
{
	if(La.elem == NULL || Lb.elem == NULL){
		return ;
	}
	
	InitList(Lc);
	
	int aLen = ListLength(La);
	int bLen = ListLength(Lb);
	
	int i =1;
	int j =1;
	int ai =0;
	int bj = 0;
	int k =0;
	while (i<=aLen && j<=bLen)
	{
		GetElem(La,i,&ai);
		GetElem(Lb,j,&bj);
		if(ai<=bj)
		{
			ListInsert(Lc,++k,ai);
			++i;
		}
		else
		{
			ListInsert(Lc,++k,bj);
			++j;
		}
	}
	while (i<=aLen)
	{
		GetElem(La,i,&ai);
		ListInsert(Lc,++k,ai);
		++i;
	}
	while (j<=bLen)
	{
		GetElem(Lb,j,&bj);
		ListInsert(Lc,++k,bj);
		++j;
	}
}