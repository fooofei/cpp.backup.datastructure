// ��Ϊѭ����  ��Ҫ���ڶ�̬����
#include <STDIO.H>
#include <WINDOWS.H>

typedef enum{LINK,THREAD}PointerTag; // LINK �����˼ұ������к��� THREAD ��ʾû�����Һ��ӵȴ�������


typedef struct _BiTreeNode_
{
	int iData;
	_BiTreeNode_* pLeft;
	_BiTreeNode_* pRight;
	PointerTag RTag;
	PointerTag LTag;
}BiTreeNode,*pBiTreeNode,**ppBiTreeNode;



bool CreateBiTree(ppBiTreeNode T);

void InThreading(pBiTreeNode p);

bool InOrderThreading(ppBiTreeNode Thrt,pBiTreeNode T);

bool InOrderTravelThrPost(pBiTreeNode T);  // ������ε���д��ı��� ���� ��ͨ�����

bool InOrderTravelThrPre(pBiTreeNode T);// �������������������ͨ��ǰ��(���Լ�����)

pBiTreeNode InOrderNext(pBiTreeNode T);// ���Լ��ӵ� ���Һ��

pBiTreeNode InOrderPre(pBiTreeNode T); // ����ǰ��

pBiTreeNode g_pPre = NULL;

int main()
{
	pBiTreeNode H,T;

	CreateBiTree(&T);

	InOrderThreading(&H,T);

	printf("�������(���)����������(��� ):\n");
	InOrderTravelThrPost(H); /* �������(���)���������� */
	printf("\n");

	printf("%d ",H->pRight->iData);
  
	printf("\n");
}


bool CreateBiTree(ppBiTreeNode T)
{
	int iValue = 0;

	scanf("%d",&iValue);


	if (iValue==-1)
	{
		*T = NULL;
	}

	else
	{
			if (NULL==(*T = (pBiTreeNode)malloc(sizeof(BiTreeNode))))
			{
					return false;
			}
			
			memset(*T,0,sizeof(BiTreeNode));
			(*T)->iData = iValue;
			
		//	(*T)->LTag = LINK;  // ��Ϊ Link ���� 0  ���ǳ�ʼ���ľ���0 ���Բ��ø�ֵ ���žͿ��ڴ�
		//	(*T)->RTag = LINK;
			CreateBiTree(&(*T)->pLeft);
			
			// 	if ((*T)->pLeft)
			// 	{
			// 		(*T)->LTag = LINK;
			// 	}
			
			CreateBiTree(&(*T)->pRight);
			
			// 	if ((*T)->pRight)
			// 	{
			// 		(*T)->RTag = LINK;
			// 	}
			
	}
	
	return true;
}// CreateBiTree



void InThreading(pBiTreeNode p)
{
	if (NULL != p)
	{

		InThreading(p->pLeft); 
		
		if (!p->pLeft) // Ϊ�ղŽ�ȥ 
		{
			p->LTag = THREAD;

			p->pLeft = g_pPre;
		}

		if (!g_pPre->pRight)
		{
			g_pPre->RTag = THREAD;

			g_pPre->pRight = p;
		}

		g_pPre = p;

		InThreading(p->pRight);
	}
}// InThreading

										// �����ϱߵĿս��
bool InOrderThreading(ppBiTreeNode Thrt,pBiTreeNode T)
{
	if (NULL==(*Thrt = (pBiTreeNode)malloc(sizeof(BiTreeNode))))
	{
		return false;
	}
	// �¼ӵĽڵ㣨ͷ�ڵ㣩������û������� 
	// ������������������ĵ�һ���ڵ��ǰ��������ָ�룩ָ����� ͷ�ڵ㣬 
	// ͬʱ�������һ���ڵ�ĺ�̣��Һ���ָ�룩Ҳָ����� ͷ��㣬 
  // ����� ͷ���� ����ָ�� ָ��������ĸ��ڵ㣬�Һ���ָ�� ָ��������������������һ���ڵ� 
	memset(*Thrt,0,sizeof(BiTreeNode));
	(*Thrt)->LTag = LINK;

	(*Thrt)->RTag = THREAD; // ���Լ��Ž�ȥ��

	(*Thrt)->pRight = *Thrt;   //��ָ���ָ 

	if (NULL == T) // ���� 
	{
		(*Thrt)->pLeft = *Thrt;

		return false;
	}


		(*Thrt)->pLeft = T;

		g_pPre = *Thrt;

		InThreading(T);

		g_pPre->pRight = *Thrt;

		g_pPre->RTag = THREAD; //���һ�����������

		(*Thrt)->pRight = g_pPre;

		return true;

}// InOrderThreading


bool InOrderTravelThrPost(pBiTreeNode T) // �������������������ͨ�����
{
	pBiTreeNode p = T->pLeft;;

	// ReadMe 
// 	Ҫ�����������������ϲ��ҽ��*p�������̽�㣬Ҫ�����������
// 	�� �����*p��rtag��ֵΪ1�������p->rchildΪ����������ֱ��ָ����*p�������̽�㣻
// ���� �����*p��rtag��ֵΪ0�������p->rchildָ���Һ��ӽ�㣬���*p�������̽���
// 		������������һ������������Ľ�㣬��˴ӽ��*p���Һ��ӿ�ʼ������ָ�������²��ң�
// 		ֱ���ҵ�һ��û������(��ltagΪ1)�Ľ��Ϊֹ,�ý���ǽ��*p����������"������"�Ľ�㣬�����ǽ��*p�������̽�㡣
	while (p!=T)
	{
		while (p->LTag==LINK) // ����ע�� ��˳���ܷ�����
		{
				p = p->pLeft;
		}
			
		printf("%d ",p->iData);

		while(p->RTag==THREAD&&p->pRight!=T)
		{
			p = p->pRight;

			printf("%d ",p->iData);
		}

		p = p->pRight;
	}


	return true;
}// InOrderTravelThrPost

bool InOrderTravelThrPre(pBiTreeNode T)// �������������������ͨ��ǰ�� (���ⲹ��) 
{// ��ӡ˳��պø�����ĺ�̷����෴   ��Ϊ��ǰ��

		pBiTreeNode p = T->pLeft;

		while (p!=T)
		{
				while (p->RTag==LINK)
				{
						p = p->pRight;
				}

				printf("%d ",p->iData);

				while (p->LTag==THREAD && p->pLeft !=T)
				{
						p = p->pLeft;
						printf("%d ",p->iData);
				}

				p = p->pLeft;
		}
		return true;
}// InOrderTravelThrPre


// ���������������� ����ǰ���ͺ�̵� 
pBiTreeNode InOrderNext(pBiTreeNode T)
{
		if (T==NULL)
		{
				return NULL;
		}
		if (T->RTag==THREAD)
		{
				return T->pRight;
		}

		// δ��������

		pBiTreeNode p = T->pRight;

		while(p->LTag==LINK)
		{
				p = p->pLeft;
		}

		return p;
}// InOrderNext

pBiTreeNode InOrderPre(pBiTreeNode T)
{
		if (T==NULL)
		{
				return NULL;
		}

		if (T->LTag==THREAD)
		{
				return T->pLeft;
		}

		pBiTreeNode p = T->pLeft;

		while(p->RTag==LINK)
		{
				p = p->pRight;
		}

		return p;
}// InOrderPre



// 1
// 2
// 3
// -1
// -1
// 4
// -1
// -1
// 5
// 6
// -1
// -1
// 7
// -1
// -1
// �������(���)����������(��� ):
// 3 2 4 1 6 5 7
// 7
// Press any key to continue