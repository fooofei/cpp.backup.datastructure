#include <stdio.h>
#include <malloc.h>
#include <math.h>

//��ε�� 216

// �ŵ� �� �㷨�� �ٶȿ죬��������ֻ�鲢������ײ�����Ƭ

#define  m 10

typedef struct WORD  
{
	struct WORD* llink; // ǰ��
	int tag;  // ȡ 0 �� 1 
	int kval; // ��ֵΪ2���ݴ�k
	struct WORD* rlink; // ���
}WORD,head,*Space;


typedef struct HeadNode 
{
	int nodesize; // �������п��п�Ĵ�С
	struct WORD* first; // ������ı�ͷָ��
}FreeList[m+1];


#define  N 100
Space   r = NULL;


void Print(FreeList p);
Space AllocBuddy(FreeList* avail,int n);
void PrintUser(Space* p);
void Reclaim(FreeList* pav,Space* p);
Space buddy(Space p);

// ���û�����n���ֵ��ڴ�ʱ�������ռ�ÿ��СΪ2��k�� ����pow(2,k-1)<n<=pow(2,k)   


int main()
{

	int i = 0;
	int n = 0;

	FreeList a; // �� m+1 ��


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

		printf("����%d���ֺ�:\n",n);
		Print(a);
    PrintUser(q);

   

		printf("______________________________________________________________\n");
		n=511;
		q[2]=AllocBuddy(&a,n); 
		printf("����%d���ֺ�:\n",n);
		Print(a);
    PrintUser(q);

    printf("���յڶ���511______________________________________________________________\n");
    Reclaim(&a,&q[2]);
    Print(a);
		PrintUser(q);

		n=127;
		q[3]=AllocBuddy(&a,n); 
		printf("����%d���ֺ�:\n",n);
		Print(a);
    PrintUser(q);


		printf("______________________________________________________________\n");
		Reclaim(&a,&q[0]);
		printf("���յ�һ��511q[0]��:\n");
		Print(a);
		PrintUser(q);
		printf("______________________________________________________________\n");
		Reclaim(&a,&q[3]); 
		printf("����127q[3]��:\n");
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
				printf("�����ÿ�Ĵ�С=%5d ����׵�ַ=%#p ",(int)pow(2,h->kval),h); /* ��������Ϣ */
				
				printf("���־=%d(0:���� 1:ռ��)\n",h->tag);
							
				h=h->rlink; /* ָ����һ������ͷ����(�׵�ַ) */
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
			printf("ʹ�ÿ�%d���׵�ַ=%#p ",i,p[i]); // ��������Ϣ 
			printf("��Ĵ�С=%5d",(int)pow(2,p[i]->kval));
            printf(" ���־=%d(0:���� 1:ռ��)\n",p[i]->tag);
		}
	}
}


Space AllocBuddy(FreeList* avail,int n)
{
	/* �����������Ҫ����ӱ� */

	int i = 0;
	int k = 0;

	Space pa = NULL;
	Space pre = NULL;
	Space suc = NULL;

	Space pi = NULL;

  // �����������Ҫ����ӱ�
  while(k<=m&&((*avail)[k].nodesize<n+1||!(*avail)[k].first)) // Ϊʲô +1  ,��Ϊ����˵Space �Ǵ�СΪ pow(2,k)-1���ֵ������ڴ�ռ�
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


		if (pa==suc) // ���ֻ����һ����� ��ô ֱ��ժ����
		{
			(*avail)[k].first = NULL;   //�������ӱ��ɿձ� 
		}

		else // ��ֻ��һ������ʱ��ͰѸý��֮��Ľ����ǰ�� 
		{
			pre->rlink = suc;

			suc->llink = pre;

			(*avail)[k].first = suc;
		}
    // ���� avail[k-1]->nodesize *2 ���� avail[k]->nodesize �������ڹϷֵľ���avail[k]  
    // ����  avail[k]->nodesize-1 >= avail[k-1]->nodesize + n ��ʱ�� ����ʣ�µ��ٷŵ�������ȥ  ֻ��ʣ��һ�����ϵĿռ�Ż�ŵ�������ȥ

		for (i=1;(*avail)[k-i].nodesize>=n+1;i++)  // n+1  �����128 
		{

			pi = pa+(int)pow(2,k-i);  // �ȷֵĴ��  Ȼ��������С ֱ���ӽ� n

			pi->rlink = pi;
			pi->llink = pi;

			pi->tag = 0;

			pi->kval = k-i;

			(*avail)[k-i].first = pi;
		
		}  // ��ʣ��������Ӧ�ӱ�   // ������е�ʱ�� Ϊʲô  ����ͷ�巨�� �������Ѿ����ڵĿռ䣿
     // ��Ϊ���Ǵ�ǰ���ҹ�����   ǰ��Ĳ��� ˵�� ǰ�ߵ�  �Ѿ�Ϊ�� ��˼�� ʹ�� nodesize >=n+1 �жϵľ��� ����һ�� pow(2,k-1) ��ӽ�
     // ���������ᵽ������  ʹ�õĿռ�С��һ�� ��ʱ�� �Ż�ָ�

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
		 /* ��������ɾ���ý�� */

		if (s->llink==s&&s->rlink==s)
		{
			(*pav)[s->kval].first = NULL;  /* �����Ͻ���һ����� */
		}

		else
		{
			s->llink->rlink = s->rlink;  /* ǰ���ĺ��Ϊ�ý��ĺ�� */

			s->rlink->llink = s->llink;  /* ��̵�ǰ��Ϊ�ý���ǰ�� */


			if ((*pav)[s->kval].first==s)
			{
				(*pav)[s->kval].first = s->rlink;
			}
		}

		if ((*p-r)%(int)pow(2,(*p)->kval+1)==0)
		{
			(*p)->kval++;  // pΪǰ��   p��Ĵ�С�ӱ�
		}

		else // pΪ���  s Ϊǰ��
		{
			s->kval = (*p)->kval+1; // s�Ĵ�С�ӱ�   ������˵��������������С��ͬ  ��ô  ����� �ӱ�Ϊʲô�������ϱߵ����� �����أ�
 
			*p = s; // ���Ե�ʱ�� ���ǵ� s->kval ���ǵ��� p->kval 
		}

		s = buddy(*p);   /* �鲢����,������ʼ��ַ����Ч��Χ���һ������ */
	}

	
	
	  /* ���½�p�嵽�����ÿռ���� */

	(*p)->tag = 0;

	if((*pav)[(*p)->kval].first==NULL) /* ������� */
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

// ��Ϊ��飿 ��ǰ�������ڷ���ʱ������Ҫ��һ����Ŀ��п�ֳ�������С��ȵĴ洢�� 
// ��������ͬһ�����ѳ�����С��ͳ�֮Ϊ ��Ϊ���  ���� p Ϊ pow(2,k) �Ŀ��п�ĳ�ʼ��ַ
// ��p%pow(2,k+1)==0 ���ʼ��ַ p �� p+pow(2,k) ���������п黥Ϊ���


// �ڻ��տ��п�ʱ ֻ������Ϊ���п�ʱ�źϲ�Ϊ���  �����������п� ��ʹ��С��ͬ��ַ����
// ��������ͬһ�����ѳ����� Ҳ���鲢
Space buddy(Space p)
{
	if ((p-r)%(int)pow(2,p->kval+1)==0) // ΪʲôҪ��ô��  ��ΪҪ�һ���� �϶����Ǳ��ָ�� ��Ȼ�ָ��� ���϶�����������Ӧ���ڵĵط�
	{                                   //  ����ԭ��1024 �ֵ��ڴ�  �����Ҫ511�� ���ǰ�ʣ���512 �ָ�ŵ�������Ӧ�÷ŵ� pow(2,10)
		return p+(int)pow(2,p->kval);     // ���Ƿŵ�pow(2,9)�ĵط� �������Ͳ���������Ӧ���ڵĵط� �������ĵ�ַ �ǵ���0+pow(2,10) ��ѽ
                                       // Ҳ���� MOD pow(2,10) == 0    ���ǲ���������ж� 
  }


// 	else   
// 	{
// 		return p-(int)pow(2,p->kval);
// 	}
// ������ε��������ʾ  ��������Ӧ������д ���Ǻܶ��鶼�������д�� 
  if((p-r)%(int)pow(2,p->kval+1)==(int)pow(2,p->kval))
  {
    return p-(int)pow(2,p->kval);
  }

	return NULL;
}


// �����㷨�� 
// ���û������СΪn���ڴ�����ʱ�������ڿ����ñ���Ѱ�ҽ���С��n��ƥ����ӱ������ӱ�ǿգ����ӱ�������һ��������֮���ɣ������ӱ�Ϊ�գ�
// ����ӽ�����ķǿ��ӱ���ȥ���ң�ֱ���ҵ�һ�����п飬������һ���ַ�����û�������ʣ�ಿ�ֲ�����Ӧ���ӱ��С�
// ��2k-1 < n �� 2k-1���ֵ�k+1���ӱ��գ���ֻҪɾ���������е�һ����㲢������û����ɣ��� 2k-2 < n �� 2k-1-1����ʱ���ڽ���СΪ2k-1 ���ӱ�
// Ϊ�գ�����ӽ���СΪ2k ���ӱ���ȡ��һ�飬������һ�������û���ʣ���һ����Ϊһ���½������ڽ���СΪ2k-1���ӱ��У�
// ��2k-i-1 < n �� 2k-i-1(iΪС���ǵ�����)���������н��С��2k���ӱ��Ϊ�գ���ͬ����ӽ���СΪ2k���ӱ���ȡ��һ�飬������2k-i��һ
// С���ַ�����û���ʣ�ಿ�ַָ�����ɸ����ֱ�����ڽ���СΪ2k-1 �� 2k-2 ������ 2k-i���ӱ��С�
// �����㷨��                                                                                                                                                                        
// ���û��ͷŲ���ʹ�õ�ռ�ÿ�ʱ��ϵͳ�轫���µĿ��п���뵽�����ÿռ����ȥ�����ͬ����һ����ַ���ڵĿ��п�鲢�ɴ������⡣�����ڻ��ϵͳ
// �н����ǻ�Ϊ����顱���������п�Ĺ鲢��
//                                                                                                                                                                            
//  ��ν����顱?��ǰ�������ڷ���ʱ������Ҫ��һ����Ŀ��п���ѳ�������С��ȵĴ洢������������ͬһ�����ѳ�����С��ͳ�֮����Ϊ��顱��
//  ���磺����pΪ��СΪpow(2,k)�Ŀ��п�ĳ�ʼ��ַ����p MOD pow(2,k+1)=0�����ʼ��ַΪp��p+pow(2,k)���������п黥Ϊ��顣�ڻ��ϵͳ�л���
//  ���п�ʱ��ֻ������Ϊ���п�ʱ�Ź鲢�ɴ�顣Ҳ����˵�������������п飬��ʹ��С��ͬ�ҵ�ַ���ڣ���������ͬһ�����ѳ����ģ�Ҳ���鲢��һ��
//  �ɴˣ��ڻ��տ��п�ʱ��Ӧ�����б������Ƿ�Ϊ���п飬������ֻҪ���ͷŵĿ��п�򵥲�������Ӧ�ӱ��м��ɣ����ǣ���������Ӧ�ӱ�����
// �����鲢ɾ��֮��Ȼ�����б�ϲ���Ŀ��п�Ļ���Ƿ��ǿ��п顣�����ظ���ֱ���鲢���ÿ��п�Ļ�鲻�ǿ��п�ʱ���ٲ��뵽��Ӧ���ӱ���ȥ