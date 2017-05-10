#include <STDIO.H>
#include <WINDOWS.H>
#include <ASSERT.H>
#define LIST_INIT_SIZE 10/* 线性表存储空间的初始分配量 */
#define LISTINCREMENT 2


typedef struct
{
  int *elem; /* 存储空间基址 */
  int length; /* 当前长度 */
  int listsize; /* 当前分配的存储容量(以sizeof(ElemType)为单位) */
 }SqList;

 /* 操作结果：构造一个空的顺序线性表 */
bool InitList(SqList* L);

/* 初始条件：顺序线性表L已存在。操作结果：销毁顺序线性表L */
bool DestroyList(SqList* L);


/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
bool ClearList(SqList* L);

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
bool ListEmpty(SqList L);


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
bool GetElem(SqList L,int i,int* e);


 /* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(SqList L);



/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在，则返回值为0 */
int LocateElem(SqList L,int e, bool (*Compare)(int a,int b));




/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
bool PriorElem(SqList L,int cur_e,int* pre_e);



/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */

bool NextElem(SqList L,int cur_e,int* next_e);



/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
bool ListInsert(SqList* L,int i,int e);



/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
bool ListDelete(SqList* L,int i,int* e);


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
/*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */


bool ListTravel(SqList L,void(*vi)(int*));

void visit(int* a)
{
  printf("%d ",*a);
}

bool compare(int a , int b)
{
  return(a==b);
}

// 在 b中  不在 a 中的 元素插入到 a 中

void Union(SqList *La, SqList *Lb);

void SortList(SqList *L);
// 有序的合并 线性表
void MergeList(SqList La, SqList Lb, SqList *Lc);

int main()
{

  SqList L;

  InitList(&L);

  printf("线性表为空1 不空0：%d.\n",ListEmpty(L));


  ListInsert(&L,1,11);

  ListInsert(&L,2,13);

  ListInsert(&L,1,12);

  printf("插入数据之后线性表为空1 不空0：%d. 线性表长度%d.\n",ListEmpty(L),ListLength(L));

  printf("打印线性表:");
  ListTravel(L,visit);
  printf("\n");

  int e = 0;

  GetElem(L,1,&e);

  printf("第一个元素是%d.\n",e);

  GetElem(L,LocateElem(L,13,compare),&e);

  printf("compare 函数 %d.\n",e);

 
  PriorElem(L,13,&e);

  printf("13的前边数字是%d.\n",e);

  NextElem(L,11,&e);

  printf("11的后边数字是%d.\n",e);

  ListDelete(&L,3,&e);

  printf("删除的第一个数字是%d.\n",e);

  printf("打印线性表:");
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



/* 操作结果：构造一个空的顺序线性表 */
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

// 在 b中  不在 a 中的 元素插入到 a 中

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

// 有序的合并  已经有序的 线性表 可以使用 SortList函数  排序
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