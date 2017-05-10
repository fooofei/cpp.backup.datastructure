#include <stdio.h>
#include <malloc.h>
#include <MEMORY.H>   // 内存池 一般运行在服务器中

//#include <WINDOWS.H> 这里面也有WORD 型 所以不能包含 会重定义

typedef struct  WORD  // 最好换个结构体名字
{
	union
	{
		struct WORD* llink;  // 头部域，指向前驱结点 
		struct WORD* uplink;  // 底部域，指向本结点头部
	}a; 

	int tag; // 块标志，0：空闲，1：占用，头部和尾部均有 
	int size; // 头部域，块大小 
	struct WORD* rlink;  // 头部域，指向后继结点 
}head,foot,*Space;

#define MAX 1000
#define  e 10

#define FootLoc(p) (p)+(p)->size-1  // 指向p结点的底部


Space AllocBoundTag(Space* pav,int n);

void Print(Space p);

void PrintUser(Space* p);

void Destroy();
void Reclaim(Space* pav,Space* p);

Space g_head = NULL;
int main()
{


	Space pav = NULL;
	Space p = NULL;

	Space v[MAX/e] = {NULL};


	int n = 0;

	printf("结构体WORD为%d个字节\n",sizeof(WORD));


	g_head = p = (WORD*)malloc((MAX+2)*sizeof(WORD));

  memset(p,0,(MAX+2)*sizeof(WORD));

	p->tag = 1;   //设置低址边界

	pav = p+1;   // 可利用空间表的表头 


	pav->rlink = pav->a.llink = pav;

	pav->tag = 0;

	pav->size = MAX;


	p = FootLoc(pav);   // p指向底部域 

	p->a.uplink = pav;

	p->tag = 0;

	//设置高址边界

	(p+1)->tag = 1;

    printf("初始化后，可利用空间表为:\n");


	Print(pav);


    printf("_______________________________________________\n");
	n = 300;

	v[0] = AllocBoundTag(&pav,n);

	Print(pav);

	PrintUser(v);


	printf("_______________________________________________\n");
	n=450;
	v[1]=AllocBoundTag(&pav,n);
	
	
	printf("分配%u个存储空间后pav为:\n",n);
	
	Print(pav);
  
	PrintUser(v);

	printf("_______________________________________________\n");

	n=242; /* 分配整个块(250) */
    v[2]=AllocBoundTag(&pav,n);


	printf("分配%u个存储空间后pav为:\n",n);
	
	Print(pav);
	
	PrintUser(v);


	printf("_______________________________________________\n");
	printf("回收v[0](%d)后(当pav空时回收)pav为:\n",v[0]->size);

	Reclaim(&pav,&v[0]); /* pav为空 */
	Print(pav);
    PrintUser(v);


	printf("_______________________________________________\n");
	printf("回收v[2](%d)后(左右邻区均为占用块)pav为:\n",v[2]->size);
	Reclaim(&pav,&v[2]); /* 左右邻区均为占用块 */
	Print(pav);
    PrintUser(v);



	printf("_______________________________________________\n");
	n=270; /* 查找空间足够大的块 */
	v[0]=AllocBoundTag(&pav,n);
	printf("分配%u个存储空间后(查找空间足够大的块)，pav为:\n",n);
	Print(pav);
    PrintUser(v);

	Destroy();



}


void Print(Space p)
{
	Space h = NULL;
	Space f = NULL;

	if (p)
	{
		h = p; /* h指向第一个结点的头部域(首地址) */

		f = FootLoc(h); /* f指向第一个结点的底部域 */

		do 
		{
			printf("块的大小=%d 块的首地址=%x \n",h->size,f->a.uplink); /* 输出结点信息 */
       
			printf("块标志=%d(0:空闲 1:占用) 邻块首地址=%x\n",h->tag,f+1);
		
			h = h->rlink;

			f = FootLoc(h);
		
		}while(h!=p);


	}
}


void PrintUser(Space* p)
{
	int i = 0;

	for (i=0;i<MAX/e;i++)
	{
		if (p[i])
		{
			printf("块%d的首地址=%x\n",i,p[i]); /* 输出结点信息 */
			printf("块的大小=%d块头标志=%d(0:空闲 1:占用)\n",p[i]->size,p[i]->tag);
            printf("块尾标志=%d\n",(FootLoc(p[i]))->tag);
		}
	}
}


Space AllocBoundTag(Space* pav,int n)
{
	Space p = NULL;

	Space f = NULL;


	for (p=*pav;p&&p->size<n&&p->rlink!=*pav;p=p->rlink)
	{
	   //内存在没有使用完时不会进入
    // 第一次运行的时候 不进循环
	}

	if (!p||p->size<n)
	{
		return NULL;
	}
	
	else
	{
		f = FootLoc(p);

		*pav = p->rlink; /* pav指向*p结点的后继结点 */

		if (p->size-n<=e) // 全部给它了
		{
			if (*pav==p)
			{
				*pav = NULL;                //内存使用完毕  我们要等待内存回收给内存池    // 可利用空间表空 
			}

			else // 没有使用 这里 查一下
      {

				(*pav)->a.llink = p->a.llink;
				p->a.llink->rlink = *pav;
			}
			p->tag = f->tag = 1;
		}

		else
		{
			f->tag = 1;
			p->size-=n;
			f = FootLoc(p);
			f->tag = 0;
			f->a.uplink = p;

			p = f+1;
			p->tag = 1;
			p->size = n;
		}


		return p;

	}
}



void Reclaim(Space* pav,Space* p)
{
	Space s = NULL;
	Space t = NULL;


	s = (*p-1)->a.uplink;

	t = *p + (*p)->size;

	// s、t分别指向释放块的左、右邻块(空闲时)的首地址


	int l = (*p-1)->tag;

	int r = (*p+(*p)->size)->tag;

	// l、r分别指示释放块的左、右邻块是否空闲 

	if (!*pav)   /* 可利用空间表空 */
	{
		*pav = (*p)->a.llink = (*p)->rlink = *p;  /* 头部域的两个指针及pav均指向释放块 */

		(*p)->tag = 0;

		(FootLoc(*p))->a.uplink=*p; /* 修改尾部域 */
        (FootLoc(*p))->tag=0;
	}

	else  /* 可利用空间表不空 */
	{
		/* 左右邻区均为占用块 */

		if (l==1&&r==1)
		{
			(*p)->tag = 0;

			(FootLoc(*p))->a.uplink = *p;  // 修改尾部域 

			(FootLoc(*p))->tag = 0;


			(*pav)->a.llink->rlink = *p;// 将p所指结点(刚释放的结点)插在pav所指结点之前 

			(*p)->a.llink = (*pav)->a.llink;

			(*p)->rlink = (*pav);

			(*pav)->a.llink = *p;

			*pav = *p;   // 修改pav,令刚释放的结点为下次分配时的最先查询的结点 
		}

		else if (l==0&&r==1)  // 左邻区为空闲块,右邻区为占用块 
		{

			s = (*p-1)->a.uplink;      // 左邻空闲块的头部地址 
            s->size+=(*p)->size;       // 设置新的空闲块大小 

			t = FootLoc(*p);

			t->a.uplink = s;

			t->tag = 0;
		}

		else if (l==1&&r==0)
		{
			(*p)->tag=0;						/* P为合并后的结点头部地址 */
			(*p)->a.llink=t->a.llink;			/* p的前驱为原t的前驱 */
			(*p)->a.llink->rlink=*p;			/* p的前驱的后继为p */
			(*p)->rlink=t->rlink;				/* p的后继为原t的后继 */
			(*p)->rlink->a.llink=*p;			/* p的后继的前驱为p */
            (*p)->size+=t->size;				/* 新的空闲块的大小 */


			(FootLoc(t))->a.uplink = *p;         /* 底部(原t的底部)指针指向新结点的头部 */


			if (*pav==t)                        /* 可利用空间表的头指针指向t(t已不是空闲结点首地址了) */
			{
				*pav = *p;
			}
		}

		else         /* 左右邻区均为空闲块 */
		{

			s->size+=(*p)->size+t->size;				/* 设置新结点的大小 */
			t->a.llink->rlink=t->rlink;							/* 删去右邻空闲块结点 */
			t->rlink->a.llink=t->a.llink;
            (FootLoc(t))->a.uplink=s;					 /* 新结点底部(原t的底部)指针指向其头部 */

			if (*pav==t)
			{
				*pav = s;
			}
		}
	}

	*p = NULL;
}





void Destroy()
{
  if (g_head)
  {
    free(g_head);
  }
	
}


