#include <STDIO.H>
#include <WINDOWS.H>
#include <ASSERT.H>

// 就只给这些个函数的声明 自己实现函数  

typedef struct DuLNode
{
  int data;
  struct DuLNode *prior,*next;
}DuLNode,*DuLinkList;


/* 产生空的双向循环链表L */
bool InitList(DuLinkList* L);

/* 操作结果：销毁双向循环链表L */
bool DestroyList(DuLinkList* L);

/* 初始条件：L已存在。操作结果：将L重置为空表 */
bool ClearList(DuLinkList L);

/* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
bool ListEmpty(DuLinkList L);

/* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
int ListLength(DuLinkList L);

/* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
bool GetElem(DuLinkList L,int i,int* e);


/* 初始条件：L已存在，compare()是数据元素判定函数 */
/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在，则返回值为0 */
int LocateElem(DuLinkList L,int e,bool (*CompareFunc)(int a,int b));


/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
bool PriorElem(DuLinkList L,int cur_e,int* pre_e);



/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */
bool NextElem(DuLinkList L,int cur_e,int* next_e);



/* 在双向链表L中返回第i个元素的位置指针*/
DuLinkList GetElemP(DuLinkList L,int i);


/* 在带头结点的双链循环线性表L中第i个位置之前插入元素e，i的合法值为1≤i≤表长+1 */
bool ListInsert(DuLinkList L,int i,int e);



/* 删除带头结点的双链循环线性表L的第i个元素,i的合法值为1≤i≤表长+1 */
bool ListDelete(DuLinkList L,int i,int* e);

void ListTraverseBack(DuLinkList L,void (*VisitFunc)(int a));

void ListTraverse(DuLinkList L,void (*VisitFunc)(int a));


bool compare(int a , int b)
{
  
  return (a== b);
}

void visit(int a)
{
  printf("%d ",a);
}

int main()
{

  DuLinkList L;

  InitList(&L);

  printf("双向循环链表是否为空(1空 0 不空):%d.\n",ListEmpty(L));

  int i = 0;

  for (i=1;i<6;++i)
  {
    ListInsert(L,i,i);
  }
 

  int n = 0;

  int j = 0;

  int e = 0;
 
  printf("正序输出链表：");
  ListTraverse(L,visit); /* 正序输出 */
  printf("\n");

  printf("逆序输出链表：");
  ListTraverseBack(L,visit); /* 逆序输出 */
  printf("\n");

  n=2;
  ListDelete(L,n,&e); /* 删除并释放第n个结点 */
  printf("删除第%d个结点，值为%d，其余结点为：",n,e);
  ListTraverse(L,visit); /* 正序输出 */
  printf("\n");

  printf("链表的元素个数为%d\n",ListLength(L));
  printf("链表是否空：%d(1:是 0:否)\n",ListEmpty(L));
  ClearList(L); /* 清空链表 */
  printf("清空后，链表是否空：%d(1:是 0:否)\n",ListEmpty(L));
  printf("重新插入5个结点:");
  for(i=1;i<=5;i++)
    ListInsert(L,i,i); /* 重新插入5个结点 */
  ListTraverse(L,visit); /* 正序输出 */
  printf("\n");

  n=3;
  j=GetElem(L,n,&e); /* 将链表的第n个元素赋值给e */
  if(j)
    printf("链表的第%d个元素值为%d\n",n,e);
  else
    printf("不存在第%d个元素\n",n);
  n=4;
  i=LocateElem(L,n,compare);
  if(i)
    printf("等于%d的元素是第%d个\n",n,i);
  else
    printf("没有等于%d的元素\n",n);
  j=PriorElem(L,n,&e);
  if(j)
    printf("%d的前驱是%d\n",n,e);
  else
    printf("不存在%d的前驱\n",n);
  j=NextElem(L,n,&e);
  if(j)
    printf("%d的后继是%d\n",n,e);
  else
    printf("不存在%d的后继\n",n);
   DestroyList(&L);


  return 0;
}

bool InitList(DuLinkList* L)
{
  *L = (DuLinkList)malloc(sizeof(DuLNode));

  assert(L!=NULL);

  memset(*L,0,sizeof(DuLNode));

 (*L)->next = (*L);

 (*L)->prior = (*L);

  return true;
}

bool ListEmpty(DuLinkList L)
{
  return (L->next==L && L->prior == L);

}


bool DestroyList(DuLinkList* L)
{
  DuLinkList dTemp = (*L)->next;

  while ((*L)->next!= *L)
  {
    (*L)->next = (*L)->next->next;

    free(dTemp);

    dTemp = (*L)->next;

  }

  free(*L);

  *L = NULL;

  return true;
}

bool ClearList(DuLinkList L)
{

  DuLinkList dTemp = L->next;
  
  while (L->next!= L)
  {
    L->next = L->next->next;
    
    free(dTemp);
    
    dTemp = L->next;
    
  }

  L->prior = L;


  return true;

}

int ListLength(DuLinkList L)
{

  DuLinkList dTemp = L->next;
  
  int nLen = 0;
  while (dTemp!= L)
  {
    dTemp = dTemp->next;

    ++nLen;
  }
  

  return nLen;
}


bool GetElem(DuLinkList L,int i,int* e)
{
  assert(i>=1 && i<=ListLength(L));
  
  DuLinkList dTemp = L->next;
  while (--i && dTemp!=L)
  {
    dTemp = dTemp->next;
  }

  *e = dTemp->data;


  return true;
}


int LocateElem(DuLinkList L,int e,bool (*CompareFunc)(int a,int b))
{
  DuLinkList dTemp = L->next;

  int iIndex = 0;
  while (dTemp!=L)
  {
    ++iIndex;

    if (CompareFunc(e,dTemp->data))
    {
      return iIndex;
    }

    dTemp = dTemp->next;
    
  }

  return 0;
}

bool PriorElem(DuLinkList L,int cur_e,int* pre_e)
{
  DuLinkList dTemp = L->prior;

  while (dTemp->prior!=L)
  {
    if (dTemp->data==cur_e)
    {
      *pre_e = dTemp->prior->data;

      return true;
    }

    dTemp = dTemp->prior;
  }

  return false;
}
bool NextElem(DuLinkList L,int cur_e,int* next_e)
{
  DuLinkList dTemp = L->next;

  while(dTemp->next!=L)
  {
    if (dTemp->data==cur_e)
    {
      *next_e = dTemp->next->data;

      return true;
    }

    dTemp = dTemp->next;
  }

  return  false;
}

DuLinkList GetElemP(DuLinkList L,int i)
{
  DuLinkList dTemp = L->next;

  while (--i &&dTemp!=L)
  {
    dTemp = dTemp->next;
  }

  if (dTemp!=L)
  {
    return dTemp;
  }

  else
  {
    return NULL;
  }
}

bool ListInsert(DuLinkList L,int i,int e)
{
  assert(i>=1 && i<=ListLength(L)+1);

  DuLinkList dPre = L;

  while (--i)
  {
    dPre = dPre->next;
  }

  DuLinkList dNew = (DuLinkList)malloc(sizeof(DuLNode));

  assert(dNew!=NULL);

  dNew->data = e;

  dNew->next = dPre->next;

  dPre->next = dNew;

  dNew->prior = dPre;

  dPre->next->next->prior = dNew;


  return true;
}

bool ListDelete(DuLinkList L,int i,int* e)
{

  assert(i>=1 && i<=ListLength(L));

  DuLinkList dPre = L;

  while (--i)
  {
    dPre = dPre->next;
  }

  *e = dPre->next->data;

  dPre->next->next->prior = dPre;

  dPre->next = dPre->next->next;

  return true;
}

void ListTraverse(DuLinkList L,void (*VisitFunc)(int a))
{
  DuLinkList dTemp = L->next;

  while (dTemp!=L)
  {
    VisitFunc(dTemp->data);
    dTemp = dTemp->next;
  }
}

void ListTraverseBack(DuLinkList L,void (*VisitFunc)(int a))
{
  DuLinkList dTemp = L->prior;
  
  while (dTemp!=L)
  {
    VisitFunc(dTemp->data);
    dTemp = dTemp->prior;
  }
}