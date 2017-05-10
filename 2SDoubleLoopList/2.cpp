#include <STDIO.H>
#include <WINDOWS.H>
#include <ASSERT.H>

// ��ֻ����Щ������������ �Լ�ʵ�ֺ���  

typedef struct DuLNode
{
  int data;
  struct DuLNode *prior,*next;
}DuLNode,*DuLinkList;


/* �����յ�˫��ѭ������L */
bool InitList(DuLinkList* L);

/* �������������˫��ѭ������L */
bool DestroyList(DuLinkList* L);

/* ��ʼ������L�Ѵ��ڡ������������L����Ϊ�ձ� */
bool ClearList(DuLinkList L);

/* ��ʼ���������Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
bool ListEmpty(DuLinkList L);

/* ��ʼ������L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(DuLinkList L);

/* ����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻�ERROR */
bool GetElem(DuLinkList L,int i,int* e);


/* ��ʼ������L�Ѵ��ڣ�compare()������Ԫ���ж����� */
/* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
/*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
int LocateElem(DuLinkList L,int e,bool (*CompareFunc)(int a,int b));


/* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
/*           �������ʧ�ܣ�pre_e�޶��� */
bool PriorElem(DuLinkList L,int cur_e,int* pre_e);



/* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
/*           �������ʧ�ܣ�next_e�޶��� */
bool NextElem(DuLinkList L,int cur_e,int* next_e);



/* ��˫������L�з��ص�i��Ԫ�ص�λ��ָ��*/
DuLinkList GetElemP(DuLinkList L,int i);


/* �ڴ�ͷ����˫��ѭ�����Ա�L�е�i��λ��֮ǰ����Ԫ��e��i�ĺϷ�ֵΪ1��i�ܱ�+1 */
bool ListInsert(DuLinkList L,int i,int e);



/* ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ��,i�ĺϷ�ֵΪ1��i�ܱ�+1 */
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

  printf("˫��ѭ�������Ƿ�Ϊ��(1�� 0 ����):%d.\n",ListEmpty(L));

  int i = 0;

  for (i=1;i<6;++i)
  {
    ListInsert(L,i,i);
  }
 

  int n = 0;

  int j = 0;

  int e = 0;
 
  printf("�����������");
  ListTraverse(L,visit); /* ������� */
  printf("\n");

  printf("�����������");
  ListTraverseBack(L,visit); /* ������� */
  printf("\n");

  n=2;
  ListDelete(L,n,&e); /* ɾ�����ͷŵ�n����� */
  printf("ɾ����%d����㣬ֵΪ%d��������Ϊ��",n,e);
  ListTraverse(L,visit); /* ������� */
  printf("\n");

  printf("�����Ԫ�ظ���Ϊ%d\n",ListLength(L));
  printf("�����Ƿ�գ�%d(1:�� 0:��)\n",ListEmpty(L));
  ClearList(L); /* ������� */
  printf("��պ������Ƿ�գ�%d(1:�� 0:��)\n",ListEmpty(L));
  printf("���²���5�����:");
  for(i=1;i<=5;i++)
    ListInsert(L,i,i); /* ���²���5����� */
  ListTraverse(L,visit); /* ������� */
  printf("\n");

  n=3;
  j=GetElem(L,n,&e); /* ������ĵ�n��Ԫ�ظ�ֵ��e */
  if(j)
    printf("����ĵ�%d��Ԫ��ֵΪ%d\n",n,e);
  else
    printf("�����ڵ�%d��Ԫ��\n",n);
  n=4;
  i=LocateElem(L,n,compare);
  if(i)
    printf("����%d��Ԫ���ǵ�%d��\n",n,i);
  else
    printf("û�е���%d��Ԫ��\n",n);
  j=PriorElem(L,n,&e);
  if(j)
    printf("%d��ǰ����%d\n",n,e);
  else
    printf("������%d��ǰ��\n",n);
  j=NextElem(L,n,&e);
  if(j)
    printf("%d�ĺ����%d\n",n,e);
  else
    printf("������%d�ĺ��\n",n);
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