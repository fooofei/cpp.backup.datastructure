#include <STDIO.H>
#include <WINDOWS.H>
#include <ASSERT.H>

#define MAXQSIZE 5 /* 最大队列长度(对于循环队列，最大队列长度要减1) */
typedef struct
{
  int *base; /* 初始化的动态分配存储空间 */
  int front; /* 头指针,若队列不空,指向队列头元素 */
  int rear; /* 尾指针,若队列不空,指向队列尾元素的下一个位置 */
 }SqQueue;

/* 构造一个空队列Q */
bool InitQueue(SqQueue* Q);


/* 销毁队列Q,Q不再存在 */
bool DestroyQueue(SqQueue* Q);


/* 将Q清为空队列 */
bool ClearQueue(SqQueue *Q);


/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
bool QueueEmpty(SqQueue Q);

/* 返回Q的元素个数,即队列的长度 */
int QueueLength(SqQueue Q);

/* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
bool GetHead(SqQueue Q,int *e);

/* 插入元素e为Q的新的队尾元素 */
bool EnQueue(SqQueue *Q,int e);

/* 若队列不空,则删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
bool DeQueue(SqQueue *Q,int *e);


/* 从队头到队尾依次对队列Q中每个元素调用函数vi()。一旦vi失败,则操作失败 */
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
   printf("初始化队列后，队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("请输入整型队列元素(不超过%d个),-1为提前结束符: ",MAXQSIZE-1);
   do
   {
     scanf("%d",&d);
     if(d==-1)
       break;
     i++;
     EnQueue(&Q,d);
   }while(i<MAXQSIZE-1);
   printf("队列长度为: %d\n",QueueLength(Q));
   printf("现在队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("连续%d次由队头删除元素,队尾插入元素:\n",MAXQSIZE);
   for(l=1;l<=MAXQSIZE;l++)
   {
     DeQueue(&Q,&d);
     printf("删除的元素是%d,请输入待插入的元素: ",d);
     scanf("%d",&d);
     EnQueue(&Q,d);
   }
   l=QueueLength(Q);
   printf("现在队列中的元素为: \n");
   QueueTraverse(Q,visit);
   printf("共向队尾插入了%d个元素\n",i+MAXQSIZE);
   if(l-2>0)
     printf("现在由队头删除%d个元素:\n",l-2);
   while(QueueLength(Q)>2)
   {
     DeQueue(&Q,&d);
     printf("删除的元素值为%d\n",d);
   }
   j=GetHead(Q,&d);
   if(j)
     printf("现在队头元素为: %d\n",d);
   ClearQueue(&Q);
   printf("清空队列后, 队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   DestroyQueue(&Q);

  return 0;
}


/* 构造一个空队列Q */
bool InitQueue(SqQueue* Q)
{
  Q->base = (int*)malloc(sizeof(int)*MAXQSIZE);

  assert(Q->base!=NULL);

  Q->front = Q->rear = 0;

  return true;
}


/* 销毁队列Q,Q不再存在 */
bool DestroyQueue(SqQueue* Q)
{
  assert(Q->base!=NULL);

  free(Q->base);

  Q->base  = NULL;

  Q->front = Q->rear = 0;

  return true;
}


/* 将Q清为空队列 */
bool ClearQueue(SqQueue* Q)
{
  assert(Q->base!=NULL);

  Q->front = Q->rear = 0;

  return true;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
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


/* 返回Q的元素个数,即队列的长度 */
int QueueLength(SqQueue Q)
{
 // return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;

  return abs(Q.rear-Q.front);
}


/* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
bool GetHead(SqQueue Q,int* e)
{
  assert(Q.front!=Q.rear);

  *e = *(Q.base+Q.front);

  return true;
}



/* 插入元素e为Q的新的队尾元素 */
bool EnQueue(SqQueue* Q,int e)
{
  assert((Q->rear+1)%MAXQSIZE!=Q->front); // 队列满

  Q->base[Q->rear] = e;

  Q->rear = (Q->rear+1)%MAXQSIZE;

  return true;
}



/* 若队列不空,则删除Q的队头元素,用e返回其值,并返回OK;否则返回ERROR */
bool DeQueue(SqQueue* Q,int* e)
{
  assert(Q->front!=Q->rear);

  *e = Q->base[Q->front];

  Q->front = (Q->front+1)%MAXQSIZE;

  return true;
}

/* 从队头到队尾依次对队列Q中每个元素调用函数vi().一旦vi失败,则操作失败 */
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