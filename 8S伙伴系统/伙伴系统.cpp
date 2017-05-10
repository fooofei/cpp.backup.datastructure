#include <stdio.h>
#include <malloc.h>
#include <math.h>

//严蔚敏 216

// 优点 是 算法简单 速度快，但是由于只归并伙伴容易产生碎片

#define  m 10

typedef struct WORD  
{
	struct WORD* llink; // 前驱
	int tag;  // 取 0 或 1 
	int kval; // 其值为2的幂次k
	struct WORD* rlink; // 后继
}WORD,head,*Space;


typedef struct HeadNode 
{
	int nodesize; // 该链表中空闲块的大小
	struct WORD* first; // 该链表的表头指针
}FreeList[m+1];


#define  N 100
Space   r = NULL;


void Print(FreeList p);
Space AllocBuddy(FreeList* avail,int n);
void PrintUser(Space* p);
void Reclaim(FreeList* pav,Space* p);
Space buddy(Space p);

// 当用户申请n个字的内存时，分配的占用块大小为2的k次 并且pow(2,k-1)<n<=pow(2,k)   


int main()
{

	int i = 0;
	int n = 0;

	FreeList a; // 是 m+1 个


	Space q[N] = {0};

	printf("sizeof(WORD)=%u m=%u (int)pow(2,m)=%u\n",sizeof(WORD),m,(int)pow(2,m));


	for (i=0;i<=m;i++)
	{
		a[i].nodesize =  (int)pow(2,i);

		a[i].first = NULL;
	}

	r = a[m].first = (WORD*)malloc(sizeof(WORD)*a[m].nodesize);

	if (r)
	{
		r->llink = r->rlink = r;

		r->tag = 0;

		r->kval = m;

		Print(a);

		PrintUser(q);

		printf("______________________________________________________________\n");

		n = 511;

		q[0] = AllocBuddy(&a,n);

		printf("申请%d个字后:\n",n);
		Print(a);
    PrintUser(q);

   

		printf("______________________________________________________________\n");
		n=511;
		q[2]=AllocBuddy(&a,n); 
		printf("申请%d个字后:\n",n);
		Print(a);
    PrintUser(q);

    printf("回收第二块511______________________________________________________________\n");
    Reclaim(&a,&q[2]);
    Print(a);
		PrintUser(q);

		n=127;
		q[3]=AllocBuddy(&a,n); 
		printf("申请%d个字后:\n",n);
		Print(a);
    PrintUser(q);


		printf("______________________________________________________________\n");
		Reclaim(&a,&q[0]);
		printf("回收第一块511q[0]后:\n");
		Print(a);
		PrintUser(q);
		printf("______________________________________________________________\n");
		Reclaim(&a,&q[3]); 
		printf("回收127q[3]后:\n");
		Print(a);
    PrintUser(q);
	}




  getchar();

	free(r);

	
}



void Print(FreeList p)
{
	int i = 0;

	Space h = NULL;

	for (i=0;i<=m;i++)
	{
		if (p[i].first)
		{
			h = p[i].first;
			do 
			{
				printf("可利用块的大小=%5d 块的首地址=%#p ",(int)pow(2,h->kval),h); /* 输出结点信息 */
				
				printf("块标志=%d(0:空闲 1:占用)\n",h->tag);
							
				h=h->rlink; /* 指向下一个结点的头部域(首地址) */
			} while (h!=p[i].first);
		}

	
	}
}


void PrintUser(Space* p)
{
	int i = 0;

	for (i=0;i<N;i++)
	{
		if (p[i])
		{
			printf("使用块%d的首地址=%#p ",i,p[i]); // 输出结点信息 
			printf("块的大小=%5d",(int)pow(2,p[i]->kval));
            printf(" 块标志=%d(0:空闲 1:占用)\n",p[i]->tag);
		}
	}
}


Space AllocBuddy(FreeList* avail,int n)
{
	/* 查找满足分配要求的子表 */

	int i = 0;
	int k = 0;

	Space pa = NULL;
	Space pre = NULL;
	Space suc = NULL;

	Space pi = NULL;

  // 查找满足分配要求的子表
  while(k<=m&&((*avail)[k].nodesize<n+1||!(*avail)[k].first)) // 为什么 +1  ,因为书上说Space 是大小为 pow(2,k)-1个字的连续内存空间
  {
    ++k;
  }

	if (k>m)
	{
		return NULL;
	}

	else
	{

		pa = (*avail)[k].first;

		pre = pa->llink;

		suc = pa->rlink;


		if (pa==suc) // 如果只有这一个结点 那么 直接摘出来
		{
			(*avail)[k].first = NULL;   //分配后该子表变成空表 
		}

		else // 不只有一个结点的时候就把该结点之后的结点向前推 
		{
			pre->rlink = suc;

			suc->llink = pre;

			(*avail)[k].first = suc;
		}
    // 分析 avail[k-1]->nodesize *2 就是 avail[k]->nodesize 我们现在瓜分的就是avail[k]  
    // 所以  avail[k]->nodesize-1 >= avail[k-1]->nodesize + n 的时候 就是剩下的再放到链表里去  只有剩余一半以上的空间才会放到链表里去

		for (i=1;(*avail)[k-i].nodesize>=n+1;i++)  // n+1  如果是128 
		{

			pi = pa+(int)pow(2,k-i);  // 先分的大块  然后慢慢分小 直到接近 n

			pi->rlink = pi;
			pi->llink = pi;

			pi->tag = 0;

			pi->kval = k-i;

			(*avail)[k-i].first = pi;
		
		}  // 将剩余块插入相应子表   // 插入表中的时候 为什么  不用头插法？ 不考虑已经存在的空间？
     // 因为他是从前面找过来的   前面的不够 说明 前边的  已经为空 意思是 使用 nodesize >=n+1 判断的就是 跟哪一个 pow(2,k-1) 最接近
     // 还是上面提到的那样  使用的空间小于一半 的时候 才会分割

		pa->tag = 1;

		pa->kval = k-(--i); 

		printf("%d  ",pa->kval);
		
	}

	return pa;
}


void Reclaim(FreeList* pav,Space* p)
{
  if (*p==NULL)
  {
    return;
  }
	Space s = NULL;

	s = buddy(*p);

	while (s>=r&&s<r+(*pav)[m].nodesize&&s->tag==0)
	{
		 /* 从链表上删除该结点 */

		if (s->llink==s&&s->rlink==s)
		{
			(*pav)[s->kval].first = NULL;  /* 链表上仅此一个结点 */
		}

		else
		{
			s->llink->rlink = s->rlink;  /* 前驱的后继为该结点的后继 */

			s->rlink->llink = s->llink;  /* 后继的前驱为该结点的前驱 */


			if ((*pav)[s->kval].first==s)
			{
				(*pav)[s->kval].first = s->rlink;
			}
		}

		if ((*p-r)%(int)pow(2,(*p)->kval+1)==0)
		{
			(*p)->kval++;  // p为前块   p块的大小加倍
		}

		else // p为后块  s 为前块
		{
			s->kval = (*p)->kval+1; // s的大小加倍   按道理说分配出来的两块大小相同  那么  这里的 加倍为什么不是向上边的那样 自增呢？
 
			*p = s; // 调试的时候 我们的 s->kval 总是等于 p->kval 
		}

		s = buddy(*p);   /* 归并伙伴块,伙伴块起始地址在有效范围内且伙伴块空闲 */
	}

	
	
	  /* 以下将p插到可利用空间表中 */

	(*p)->tag = 0;

	if((*pav)[(*p)->kval].first==NULL) /* 该链表空 */
	{
		 (*pav)[(*p)->kval].first=(*p)->llink=(*p)->rlink=*p;
	}
	else
	{
		(*p)->rlink=(*pav)[(*p)->kval].first;
		(*p)->llink=(*pav)[(*p)->kval].first->llink;
		(*p)->rlink->llink=*p;
		(*p)->llink->rlink=*p;
        (*pav)[(*p)->kval].first=*p;
	}

	*p = NULL;
}

// 何为伙伴？ 如前所述，在分配时经常需要将一个大的空闲块分成两个大小相等的存储区 
// 这两个由同一大块分裂出来的小块就称之为 互为伙伴  例如 p 为 pow(2,k) 的空闲块的初始地址
// 且p%pow(2,k+1)==0 则初始地址 p 和 p+pow(2,k) 的两个空闲块互为伙伴


// 在回收空闲块时 只当其伙伴为空闲块时才合并为大块  若有两个空闲块 即使大小相同地址相邻
// 但不是由同一大块分裂出来的 也不归并
Space buddy(Space p)
{
	if ((p-r)%(int)pow(2,p->kval+1)==0) // 为什么要这么做  因为要找伙伴嘛 肯定他是被分割过 既然分割了 他肯定不在他本来应该在的地方
	{                                   //  比如原来1024 字的内存  如果需要511字 我们把剩余的512 分割不放到他本来应该放的 pow(2,10)
		return p+(int)pow(2,p->kval);     // 而是放到pow(2,9)的地方 于是他就不在他本来应该在的地方 但是他的地址 是等于0+pow(2,10) 的呀
                                       // 也就是 MOD pow(2,10) == 0    于是才有了这个判断 
  }


// 	else   
// 	{
// 		return p-(int)pow(2,p->kval);
// 	}
// 根据严蔚敏树上所示  我们这里应该这样写 但是很多书都是上面的写法 
  if((p-r)%(int)pow(2,p->kval+1)==(int)pow(2,p->kval))
  {
    return p-(int)pow(2,p->kval);
  }

	return NULL;
}


// 分配算法： 
// 当用户提出大小为n的内存请求时，首先在可利用表上寻找结点大小与n相匹配的子表，若此子表非空，则将子表中任意一个结点分配之即可；若此子表为空，
// 则需从结点更大的非空子表中去查找，直至找到一个空闲块，则将其中一部分分配给用户，而将剩余部分插入相应的子表中。
// 若2k-1 < n ≤ 2k-1，又第k+1个子表不空，则只要删除此链表中第一个结点并分配给用户即可；若 2k-2 < n ≤ 2k-1-1，此时由于结点大小为2k-1 的子表
// 为空，则需从结点大小为2k 的子表中取出一块，将其中一半分配给用户，剩余的一半作为一个新结点插入在结点大小为2k-1的子表中，
// 若2k-i-1 < n ≤ 2k-i-1(i为小于是的整数)，并且所有结点小于2k的子表均为空，则同样需从结点大小为2k的子表中取出一块，将其中2k-i的一
// 小部分分配给用户，剩余部分分割成若干个结点分别插入在结点大小为2k-1 、 2k-2 、…、 2k-i的子表中。
// 回收算法：                                                                                                                                                                        
// 在用户释放不再使用的占用块时，系统需将这新的空闲块插入到可利用空间表中去。这里，同样有一个地址相邻的空闲块归并成大块的问题。但是在伙伴系统
// 中仅考虑互为“伙伴”的两个空闲块的归并。
//                                                                                                                                                                            
//  何谓“伙伴”?如前所述，在分配时经常需要将一个大的空闲块分裂成两个大小相等的存储区，这两个由同一大块分裂出来的小块就称之“互为伙伴”。
//  例如：假设p为大小为pow(2,k)的空闲块的初始地址，且p MOD pow(2,k+1)=0，则初始地址为p和p+pow(2,k)的两个空闲块互为伙伴。在伙伴系统中回收
//  空闲块时，只当其伙伴为空闲块时才归并成大块。也就是说，若有两个空闲块，即使大小相同且地址相邻，但不是由同一大块分裂出来的，也不归并在一起。
//  由此，在回收空闲块时，应首先判别其伙伴是否为空闲块，若否，则只要将释放的空闲块简单插入在相应子表中即可；若是，则需在相应子表中找
// 到其伙伴并删除之，然后再判别合并后的空闲块的伙伴是否是空闲块。依此重复，直到归并所得空闲块的伙伴不是空闲块时，再插入到相应的子表中去