// Error
// ������Ϊ��˫��ѭ������  �ش˼�¼�ҵĴ���
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

bool InOrderTravel(pBiTreeNode T);

pBiTreeNode g_pPre = NULL;

int main()
{
	pBiTreeNode H,T;

	CreateBiTree(&T);

	InOrderThreading(&H,T);

	printf("�������(���)����������:\n");
	InOrderTravel(H); /* �������(���)���������� */
  
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
}



void InThreading(pBiTreeNode p)
{
	if (p)
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
}

										// �����ϱߵĿս��
bool InOrderThreading(ppBiTreeNode Thrt,pBiTreeNode T)
{
	if (NULL==(*Thrt = (pBiTreeNode)malloc(sizeof(BiTreeNode))))
	{
		return false;
	}
	memset(*Thrt,0,sizeof(BiTreeNode));
	(*Thrt)->LTag = LINK;

	(*Thrt)->RTag = THREAD; // ���Լ��Ž�ȥ��

	(*Thrt)->pRight = *Thrt;   //��ָ���ָ 

	if (!T) // ���� 
	{
		(*Thrt)->pLeft = *Thrt;

		return false;
	}

		(*Thrt)->pLeft = T;

		g_pPre = *Thrt;

		InThreading(T);

		g_pPre->pRight = *Thrt;

		g_pPre->RTag = THREAD; //���һ�����������

	//	(*Thrt)->pRight = g_pPre; // ������ ����Ϊ˫��ѭ������

		pBiTreeNode pTemp = (*Thrt)->pLeft;

		while (pTemp->pLeft!=(*Thrt))
		{
				pTemp = pTemp->pLeft;
		}

		(*Thrt)->pRight  = pTemp;
		return true;

		// ������˫��ѭ������  ������
		
// 						1
// 								5
// 							6   
}


bool InOrderTravel(pBiTreeNode T)
{
	pBiTreeNode p = T->pRight;

	while (p!=T)
	{
			printf("%d ",p->iData);

			p = p->pRight;
	}
	return true;
}