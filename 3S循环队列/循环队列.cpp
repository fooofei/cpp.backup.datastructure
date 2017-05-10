#include <STDIO.H>
#include <WINDOWS.H>
#include <ASSERT.H>

#define MAXQSIZE 5 /* �����г���(����ѭ�����У������г���Ҫ��1) */
typedef struct
{
  int *base; /* ��ʼ���Ķ�̬����洢�ռ� */
  int front; /* ͷָ��,�����в���,ָ�����ͷԪ�� */
  int rear; /* βָ��,�����в���,ָ�����βԪ�ص���һ��λ�� */
 }SqQueue;

/* ����һ���ն���Q */
bool InitQueue(SqQueue* Q);


/* ���ٶ���Q,Q���ٴ��� */
bool DestroyQueue(SqQueue* Q);


/* ��Q��Ϊ�ն��� */
bool ClearQueue(SqQueue *Q);


/* ������QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
bool QueueEmpty(SqQueue Q);

/* ����Q��Ԫ�ظ���,�����еĳ��� */
int QueueLength(SqQueue Q);

/* �����в���,����e����Q�Ķ�ͷԪ��,������OK,���򷵻�ERROR */
bool GetHead(SqQueue Q,int *e);

/* ����Ԫ��eΪQ���µĶ�βԪ�� */
bool EnQueue(SqQueue *Q,int e);

/* �����в���,��ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK,���򷵻�ERROR */
bool DeQueue(SqQueue *Q,int *e);


/* �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi()��һ��viʧ��,�����ʧ�� */
bool QueueTraverse(SqQueue Q,void(*vi)(int a));

void visit(int a)
{
  printf("%d ",a);
}

int main()
{

  bool j;
   int i=0,l;
   int d;
   SqQueue Q;
   InitQueue(&Q);
   printf("��ʼ�����к󣬶��пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   printf("���������Ͷ���Ԫ��(������%d��),-1Ϊ��ǰ������: ",MAXQSIZE-1);
   do
   {
     scanf("%d",&d);
     if(d==-1)
       break;
     i++;
     EnQueue(&Q,d);
   }while(i<MAXQSIZE-1);
   printf("���г���Ϊ: %d\n",QueueLength(Q));
   printf("���ڶ��пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   printf("����%d���ɶ�ͷɾ��Ԫ��,��β����Ԫ��:\n",MAXQSIZE);
   for(l=1;l<=MAXQSIZE;l++)
   {
     DeQueue(&Q,&d);
     printf("ɾ����Ԫ����%d,������������Ԫ��: ",d);
     scanf("%d",&d);
     EnQueue(&Q,d);
   }
   l=QueueLength(Q);
   printf("���ڶ����е�Ԫ��Ϊ: \n");
   QueueTraverse(Q,visit);
   printf("�����β������%d��Ԫ��\n",i+MAXQSIZE);
   if(l-2>0)
     printf("�����ɶ�ͷɾ��%d��Ԫ��:\n",l-2);
   while(QueueLength(Q)>2)
   {
     DeQueue(&Q,&d);
     printf("ɾ����Ԫ��ֵΪ%d\n",d);
   }
   j=GetHead(Q,&d);
   if(j)
     printf("���ڶ�ͷԪ��Ϊ: %d\n",d);
   ClearQueue(&Q);
   printf("��ն��к�, ���пշ�%u(1:�� 0:��)\n",QueueEmpty(Q));
   DestroyQueue(&Q);

  return 0;
}


/* ����һ���ն���Q */
bool InitQueue(SqQueue* Q)
{
  Q->base = (int*)malloc(sizeof(int)*MAXQSIZE);

  assert(Q->base!=NULL);

  Q->front = Q->rear = 0;

  return true;
}


/* ���ٶ���Q,Q���ٴ��� */
bool DestroyQueue(SqQueue* Q)
{
  assert(Q->base!=NULL);

  free(Q->base);

  Q->base  = NULL;

  Q->front = Q->rear = 0;

  return true;
}


/* ��Q��Ϊ�ն��� */
bool ClearQueue(SqQueue* Q)
{
  assert(Q->base!=NULL);

  Q->front = Q->rear = 0;

  return true;
}

/* ������QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
bool QueueEmpty(SqQueue Q)
{
  assert(Q.base!=NULL);

  if(Q.front==Q.rear)
  {
    return true;
  }

  else
  {
    return false;
  }
}


/* ����Q��Ԫ�ظ���,�����еĳ��� */
int QueueLength(SqQueue Q)
{
 // return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;

  return abs(Q.rear-Q.front);
}


/* �����в���,����e����Q�Ķ�ͷԪ��,������OK,���򷵻�ERROR */
bool GetHead(SqQueue Q,int* e)
{
  assert(Q.front!=Q.rear);

  *e = *(Q.base+Q.front);

  return true;
}



/* ����Ԫ��eΪQ���µĶ�βԪ�� */
bool EnQueue(SqQueue* Q,int e)
{
  assert((Q->rear+1)%MAXQSIZE!=Q->front); // ������

  Q->base[Q->rear] = e;

  Q->rear = (Q->rear+1)%MAXQSIZE;

  return true;
}



/* �����в���,��ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������OK;���򷵻�ERROR */
bool DeQueue(SqQueue* Q,int* e)
{
  assert(Q->front!=Q->rear);

  *e = Q->base[Q->front];

  Q->front = (Q->front+1)%MAXQSIZE;

  return true;
}

/* �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi().һ��viʧ��,�����ʧ�� */
bool QueueTraverse(SqQueue Q,void (*vi)(int a))
{
  while(Q.front!=Q.rear)
  {
    vi(*Q.base+Q.front);

    Q.front = (Q.front+1)%MAXQSIZE;
  }

  printf("\n");

  return true;
}