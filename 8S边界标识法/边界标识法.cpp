#include <stdio.h>
#include <malloc.h>
#include <MEMORY.H>   // �ڴ�� һ�������ڷ�������

//#include <WINDOWS.H> ������Ҳ��WORD �� ���Բ��ܰ��� ���ض���

typedef struct  WORD  // ��û����ṹ������
{
	union
	{
		struct WORD* llink;  // ͷ����ָ��ǰ����� 
		struct WORD* uplink;  // �ײ���ָ�򱾽��ͷ��
	}a; 

	int tag; // ���־��0�����У�1��ռ�ã�ͷ����β������ 
	int size; // ͷ���򣬿��С 
	struct WORD* rlink;  // ͷ����ָ���̽�� 
}head,foot,*Space;

#define MAX 1000
#define  e 10

#define FootLoc(p) (p)+(p)->size-1  // ָ��p���ĵײ�


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

	printf("�ṹ��WORDΪ%d���ֽ�\n",sizeof(WORD));


	g_head = p = (WORD*)malloc((MAX+2)*sizeof(WORD));

  memset(p,0,(MAX+2)*sizeof(WORD));

	p->tag = 1;   //���õ�ַ�߽�

	pav = p+1;   // �����ÿռ��ı�ͷ 


	pav->rlink = pav->a.llink = pav;

	pav->tag = 0;

	pav->size = MAX;


	p = FootLoc(pav);   // pָ��ײ��� 

	p->a.uplink = pav;

	p->tag = 0;

	//���ø�ַ�߽�

	(p+1)->tag = 1;

    printf("��ʼ���󣬿����ÿռ��Ϊ:\n");


	Print(pav);


    printf("_______________________________________________\n");
	n = 300;

	v[0] = AllocBoundTag(&pav,n);

	Print(pav);

	PrintUser(v);


	printf("_______________________________________________\n");
	n=450;
	v[1]=AllocBoundTag(&pav,n);
	
	
	printf("����%u���洢�ռ��pavΪ:\n",n);
	
	Print(pav);
  
	PrintUser(v);

	printf("_______________________________________________\n");

	n=242; /* ����������(250) */
    v[2]=AllocBoundTag(&pav,n);


	printf("����%u���洢�ռ��pavΪ:\n",n);
	
	Print(pav);
	
	PrintUser(v);


	printf("_______________________________________________\n");
	printf("����v[0](%d)��(��pav��ʱ����)pavΪ:\n",v[0]->size);

	Reclaim(&pav,&v[0]); /* pavΪ�� */
	Print(pav);
    PrintUser(v);


	printf("_______________________________________________\n");
	printf("����v[2](%d)��(����������Ϊռ�ÿ�)pavΪ:\n",v[2]->size);
	Reclaim(&pav,&v[2]); /* ����������Ϊռ�ÿ� */
	Print(pav);
    PrintUser(v);



	printf("_______________________________________________\n");
	n=270; /* ���ҿռ��㹻��Ŀ� */
	v[0]=AllocBoundTag(&pav,n);
	printf("����%u���洢�ռ��(���ҿռ��㹻��Ŀ�)��pavΪ:\n",n);
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
		h = p; /* hָ���һ������ͷ����(�׵�ַ) */

		f = FootLoc(h); /* fָ���һ�����ĵײ��� */

		do 
		{
			printf("��Ĵ�С=%d ����׵�ַ=%x \n",h->size,f->a.uplink); /* ��������Ϣ */
       
			printf("���־=%d(0:���� 1:ռ��) �ڿ��׵�ַ=%x\n",h->tag,f+1);
		
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
			printf("��%d���׵�ַ=%x\n",i,p[i]); /* ��������Ϣ */
			printf("��Ĵ�С=%d��ͷ��־=%d(0:���� 1:ռ��)\n",p[i]->size,p[i]->tag);
            printf("��β��־=%d\n",(FootLoc(p[i]))->tag);
		}
	}
}


Space AllocBoundTag(Space* pav,int n)
{
	Space p = NULL;

	Space f = NULL;


	for (p=*pav;p&&p->size<n&&p->rlink!=*pav;p=p->rlink)
	{
	   //�ڴ���û��ʹ����ʱ�������
    // ��һ�����е�ʱ�� ����ѭ��
	}

	if (!p||p->size<n)
	{
		return NULL;
	}
	
	else
	{
		f = FootLoc(p);

		*pav = p->rlink; /* pavָ��*p���ĺ�̽�� */

		if (p->size-n<=e) // ȫ��������
		{
			if (*pav==p)
			{
				*pav = NULL;                //�ڴ�ʹ�����  ����Ҫ�ȴ��ڴ���ո��ڴ��    // �����ÿռ��� 
			}

			else // û��ʹ�� ���� ��һ��
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

	// s��t�ֱ�ָ���ͷſ�������ڿ�(����ʱ)���׵�ַ


	int l = (*p-1)->tag;

	int r = (*p+(*p)->size)->tag;

	// l��r�ֱ�ָʾ�ͷſ�������ڿ��Ƿ���� 

	if (!*pav)   /* �����ÿռ��� */
	{
		*pav = (*p)->a.llink = (*p)->rlink = *p;  /* ͷ���������ָ�뼰pav��ָ���ͷſ� */

		(*p)->tag = 0;

		(FootLoc(*p))->a.uplink=*p; /* �޸�β���� */
        (FootLoc(*p))->tag=0;
	}

	else  /* �����ÿռ���� */
	{
		/* ����������Ϊռ�ÿ� */

		if (l==1&&r==1)
		{
			(*p)->tag = 0;

			(FootLoc(*p))->a.uplink = *p;  // �޸�β���� 

			(FootLoc(*p))->tag = 0;


			(*pav)->a.llink->rlink = *p;// ��p��ָ���(���ͷŵĽ��)����pav��ָ���֮ǰ 

			(*p)->a.llink = (*pav)->a.llink;

			(*p)->rlink = (*pav);

			(*pav)->a.llink = *p;

			*pav = *p;   // �޸�pav,����ͷŵĽ��Ϊ�´η���ʱ�����Ȳ�ѯ�Ľ�� 
		}

		else if (l==0&&r==1)  // ������Ϊ���п�,������Ϊռ�ÿ� 
		{

			s = (*p-1)->a.uplink;      // ���ڿ��п��ͷ����ַ 
            s->size+=(*p)->size;       // �����µĿ��п��С 

			t = FootLoc(*p);

			t->a.uplink = s;

			t->tag = 0;
		}

		else if (l==1&&r==0)
		{
			(*p)->tag=0;						/* PΪ�ϲ���Ľ��ͷ����ַ */
			(*p)->a.llink=t->a.llink;			/* p��ǰ��Ϊԭt��ǰ�� */
			(*p)->a.llink->rlink=*p;			/* p��ǰ���ĺ��Ϊp */
			(*p)->rlink=t->rlink;				/* p�ĺ��Ϊԭt�ĺ�� */
			(*p)->rlink->a.llink=*p;			/* p�ĺ�̵�ǰ��Ϊp */
            (*p)->size+=t->size;				/* �µĿ��п�Ĵ�С */


			(FootLoc(t))->a.uplink = *p;         /* �ײ�(ԭt�ĵײ�)ָ��ָ���½���ͷ�� */


			if (*pav==t)                        /* �����ÿռ���ͷָ��ָ��t(t�Ѳ��ǿ��н���׵�ַ��) */
			{
				*pav = *p;
			}
		}

		else         /* ����������Ϊ���п� */
		{

			s->size+=(*p)->size+t->size;				/* �����½��Ĵ�С */
			t->a.llink->rlink=t->rlink;							/* ɾȥ���ڿ��п��� */
			t->rlink->a.llink=t->a.llink;
            (FootLoc(t))->a.uplink=s;					 /* �½��ײ�(ԭt�ĵײ�)ָ��ָ����ͷ�� */

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


