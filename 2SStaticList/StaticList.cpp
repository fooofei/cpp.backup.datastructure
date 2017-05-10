#include <stdio.h>
#include <windows.h>

#define MAXSIZE 5
#define INVALID_VALUE INFINITE // ѧϰ�궨��
#define EMPTY_VALUE 0
typedef int ElemType;

typedef struct _NODE{

	ElemType Data;
	int Cur;
}SLinkList[MAXSIZE];

// һ������ֻ����һ����̬���� �Ļ�������(13��) 
// 1���˽��ڴ�صĸ��� 2������ͷ�巨

// ����һ���յ�������ͷΪL�����һ����ԪL[MAXSIZE-1]�����൥Ԫ���� 
// һ������������ͷΪL�ĵ�һ����ԪL[0]����0����ʾ��ָ��/
bool InitList(SLinkList L);
// ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� 
bool ClearList(SLinkList L);

// ��L�ǿձ�����TRUE�����򷵻�FALSE
bool ListEmpty(SLinkList L);

/* ����L������Ԫ�ظ��� */
int ListLength(SLinkList L);

// ��e����L�е�i��Ԫ�ص�ֵ
bool GetElem(SLinkList L,int iPosition,ElemType &e);

/* �ھ�̬�������Ա�L�в��ҵ�1��ֵΪe��Ԫ�ء����ҵ����򷵻�����L�е� */
/* λ�򣬷��򷵻�0����������LocateElem()�Ķ��岻ͬ) */
int LocateElem(SLinkList L,ElemType e);

/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
/*           �������ʧ�ܣ�pre_e�޶��� */
bool PriorElem(SLinkList L,ElemType cur_e,ElemType &pre_e);

/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
/*           �������ʧ�ܣ�next_e�޶��� */
bool NextElem(SLinkList L,ElemType cur_e,ElemType& next_e);


/* ����������ǿ�,�򷵻ط���Ľ���±�(��������ĵ�һ�����),���򷵻�0 */
int Malloc(SLinkList space);
/* ���±�Ϊk�Ŀ��н����յ���������(��Ϊ��������ĵ�һ�����) */
bool Free(SLinkList space,int k);

/* ��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e */
bool ListInsert(SLinkList L,int iPosition,ElemType e);
bool AppendTail(SLinkList L,ElemType e);
/* ɾ����L�е�i������Ԫ��e����������ֵ */
bool ListDelete(SLinkList L,int iPosition,ElemType &e); // ����λ��ɾ��
bool ListDelete(SLinkList L,ElemType e); // ����Ԫ��ɾ�� �������� ����λ�� 
// ɾ��ɾ��  ���÷���������

/* ��ʼ����:���Ա�L�Ѵ��� */
/* �������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
bool ListTraverse(SLinkList L,void (*VisitFunc)(ElemType));

//////////////////////////////////////////////////////////////////////////
///* �㷨2.17  �������뼯��A��B��Ԫ�أ���һά����space�н�����ʾ����(A-B)��(B-A) */
   /* �ľ�̬����SΪ��ͷָ�롣���豸�ÿռ��㹻��space[0].curΪ���ÿռ��ͷָ�� */
void Difference(SLinkList L,int &s);


//////////////////////////////////////////////////////////////////////////
void Visit(ElemType e)
{
	printf("%d ",e);
}
int main()
{
	
	SLinkList L;
	//int s ;
//	Difference(L,s);

	InitList(L);
	ClearList(L);
	return 0;

}

// ����ε���Ĵ��벻��ͬ ��˼·��ͬ
// ��ʼ����ֻ��һ����̬����
void Difference(SLinkList L,int &s)
{
	InitList(L);
	int r  =s ;
	int i = 0;
	int j =0;
	int iCount_a = 0;
	printf("����A��Ԫ�ظ���:");
	scanf("%d",&iCount_a);
	ElemType e;
	for (j=0;j<iCount_a;++j)
	{
		printf("����A��Ԫ��:\n");
		scanf("%d",&e);
		AppendTail(L,e); // �嵽β��
	}
	printf("���A��");
	ListTraverse(L,Visit);

	printf("����B��Ԫ�ظ���:");
	int iCount_b = 0;
	scanf("%d",&iCount_b);

	for(j=0;j<iCount_b;++j)
	{
		printf("����B��Ԫ��:\n");
		scanf("%d",&e);
		if (LocateElem(L,e) == 0) // û���ҵ� ��ӽ�ȥ
		{
			AppendTail(L,e);
		}
		else// �ҵ��� ɾ��֮
		{
			ListDelete(L,e);
		}
	}

	printf("Difference֮��A��");
	ListTraverse(L,Visit);
}


bool ListDelete(SLinkList L,ElemType e)
{
	int iIndex = MAXSIZE-1;

	while (L[iIndex].Cur != 0 && L[L[iIndex].Cur].Data != e) // ����һ����� ���� ��Ϊ e
	{
		iIndex = L[iIndex].Cur;
	}
	
	if (L[iIndex].Cur != 0)
	{
		int iFree = L[iIndex].Cur; // ����ֵ
		L[iIndex].Cur = L[L[iIndex].Cur].Cur;
		Free(L,iFree); // ע������Free�ĸ�  �Լ��ͷ�����
		return true;
	}


	return false;
}

/* ��ʼ����:���Ա�L�Ѵ��� */
/* �������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
bool ListTraverse(SLinkList L,void (*VisitFunc)(ElemType))
{
	if(L == NULL)
		return false;
	int i = L[MAXSIZE-1].Cur;

	while(i)
	{
		VisitFunc(L[i].Data);
		i = L[i].Cur;
	}

	printf("\n");

	return true;

}

/* ɾ����L�е�i������Ԫ��e����������ֵ */
bool ListDelete(SLinkList L,int iPosition,ElemType &e)
{
	int j,k = MAXSIZE-1;
	if(iPosition<1 || iPosition>ListLength(L))
		return false;
	for (j=1;j<iPosition;++j)
	{
		k = L[k].Cur;
	}

	j = L[k].Cur;
	L[k].Cur = L[j].Cur;
	e = L[j].Data;
	Free(L,j);

	return true;
}	
/* ��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e */
bool ListInsert(SLinkList L,int iPosition,ElemType e)
{
	int i,j,k = MAXSIZE-1;

	if(iPosition <1 || iPosition>ListLength(L)+1)
		return false;

	i = Malloc(L);

	if (i)
	{
		L[i].Data = e;
		for (j=1;j<iPosition;j++)
		{
			k = L[k].Cur;
		}
		L[i].Cur = L[k].Cur;  // ͷ�巨
		L[k].Cur= i;

		return true;
	}
	return false;

}
// �嵽����β��
bool AppendTail(SLinkList L,ElemType e)
{
	if(ListLength(L)>=MAXSIZE-2)
		return false; // û�пռ�

	int iIndex = Malloc(L);

	if(iIndex == 0)
		return false; // û�пռ�

	L[iIndex].Data = e;
	L[iIndex].Cur = 0; // ��β��

	int i = MAXSIZE-1; // ����ͷ

	while (L[i].Cur != 0) // ��û�е������һ�����
	{
		i = L[i].Cur;	 // ���� �ҵ�β��
	}

	L[i].Cur = iIndex; // ���ӵ�β��

	return true;
}

/* ���±�Ϊk�Ŀ��н����յ���������(��Ϊ��������ĵ�һ�����) */
bool Free(SLinkList space,int k)
{
	if(space == NULL)
		return false;
	space[k].Cur = space[0].Cur;  // ʹ��ͷ�巨�ŵ����������ͷ��
	space[0].Cur = k;

	return true;
}

/* ����������ǿ�,�򷵻ط���Ľ���±�(��������ĵ�һ�����),���򷵻�0 */
int Malloc(SLinkList space)
{
	int i = space[0].Cur;
	if (i)
	{
		space[0].Cur = space[i].Cur;
	}

	return i;
}

/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ�̣� */
/*           �������ʧ�ܣ�next_e�޶��� */
bool NextElem(SLinkList L,ElemType cur_e,ElemType& next_e)
{
	int j,i = LocateElem(L,cur_e);

	if (i)
	{
		j = L[i].Cur;
		if (j)
		{
			next_e = L[j].Data;
			return true;
		}
	}

	next_e = INVALID_VALUE;
	return false;
}

/* ��ʼ���������Ա�L�Ѵ��� */
/* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
/*           �������ʧ�ܣ�pre_e�޶��� */
bool PriorElem(SLinkList L,ElemType cur_e,ElemType &pre_e)
{
	int j = L[MAXSIZE-1].Cur,i =L[j].Cur ;

	while (i && cur_e != L[i].Data)
	{
		j = i;
		i = L[i].Cur;
	}

	if(i && L[i].Data == cur_e)
	{
		pre_e = L[j].Data;
		return true;
	}
	pre_e = INVALID_VALUE;
	return false;
}
/* �ھ�̬�������Ա�L�в��ҵ�1��ֵΪe��Ԫ�ء����ҵ����򷵻�����L�е� */
/* λ�򣬷��򷵻�0����������LocateElem()�Ķ��岻ͬ) */
int LocateElem(SLinkList L,ElemType e)
{
	int i = L[MAXSIZE-1].Cur;

	while (i && L[i].Data !=e)
	{
		i = L[i].Cur;
	}
	return i;
}
// ��e����L�е�i��Ԫ�ص�ֵ
bool GetElem(SLinkList L,int iPosition,ElemType &e)
{
	int i,k = MAXSIZE-1;
	if(iPosition <1 || iPosition>ListLength(L))
	{
		e = INVALID_VALUE;
		return false;
	}
	for (i=1;i<=iPosition;++i)
	{
		k = L[k].Cur;
	}
	e = L[k].Data;
	return true;

}
/* ����L������Ԫ�ظ��� */
int ListLength(SLinkList L)
{
	int j =0,i = L[MAXSIZE-1].Cur; // iָ���һ��Ԫ��

	while (i)
	{
		i = L[i].Cur;
		j++;
	}

	return j;

}


// ��L�ǿձ�����TRUE�����򷵻�FALSE
bool ListEmpty(SLinkList L)
{
	return (L[MAXSIZE-1].Cur ==0);
}

// ��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� 
bool ClearList(SLinkList L)
{
	
	int i,j=0,k=0;
	i = L[MAXSIZE-1].Cur;// �����һ������λ��
	L[MAXSIZE-1].Cur =EMPTY_VALUE; // �����
	k = L[0].Cur;// ���������һ������λ��
	L[0].Cur = i;// ������Ľ��������������ı�ͷ
	while (i) // û������β
	{
		j =i;
		i = L[i].Cur;
	}
	L[j].Cur = k;  // ��˼����ʹ��ͷ�巨 ������嵽���������ͷ��
	return true;

/*
	// ���� ����������
	int i, j ,k ;

	i = L[MAXSIZE -1 ].Cur;
	L[MAXSIZE -1].Cur = EMPTY_VALUE;

	while (i)
	{
		// һ��������ͷ�巨
		L[i].Cur = L[0].Cur;
		L[0].Cur = i;
	
		i = L[i].Cur; // �������

	}

	return true;*/
}

// ����һ���յ�������ͷΪL�����һ����ԪL[MAXSIZE-1]�����൥Ԫ���� 
// һ������������ͷΪL�ĵ�һ����ԪL[0]����0����ʾ��ָ��/
bool InitList(SLinkList L)
{
	L[MAXSIZE-1].Cur =EMPTY_VALUE; // L�����һ����ԪΪ������ı�ͷ
	for (int i=0;i<MAXSIZE-2;++i)
	{
		L[i].Cur = i+1;
	}
	L[MAXSIZE-2].Cur = 0;  //��������Ϊ ÿ�ζ��Ǵӱ�ͷ��ֵ  �����������￪ʼ
	return true;
}
