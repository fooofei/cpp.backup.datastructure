
// �ο����˵Ĵ���ʵ��
// 2012-9-8
// author��
#include <STDIO.H>
#include <WINDOWS.H>

// �Ľ��ĵط���ʹѰ�ҽ���ֱ��ǰ������ �������������   �Ľ�����ô�� �����޷�ֱ���ҵ����

typedef enum{LINK,THREAD}PointerTag;

typedef struct _BITREENODE_
{
		int iData;
		_BITREENODE_* pLeft;
		_BITREENODE_* pRight;
		PointerTag LTag; // ���塡0 ���� 1 ֱ�Ӻ��
		PointerTag RTag; // ����  0 �Һ��� 1 ֱ��ǰ��   // �Ľ���һ���
}BiTreeNode,*pBiTreeNode;


BOOL CreateBiTree(pBiTreeNode &T);
BOOL PosThreading(pBiTreeNode T);
BOOL PosOrderThreading(pBiTreeNode &Thrt,pBiTreeNode T);
BOOL PosOrderTravelThr(pBiTreeNode Thr);
BOOL PosOrderTravel(pBiTreeNode T);// ����������Ա�
pBiTreeNode PosPre(pBiTreeNode T);
pBiTreeNode g_pPre = NULL;
int main(int argc, char* argv[])
{

		pBiTreeNode pRoot = NULL;
		
		pBiTreeNode pThr = NULL;
		
		CreateBiTree(pRoot);
		
		PosOrderThreading(pThr,pRoot);

    printf("\n���Ա�\n");
    
    PosOrderTravel(pRoot);
		
		printf("\n�������(���)����������(��� ):\n");
		
		PosOrderTravelThr(pThr);

    
		
		printf("\n");
		return 0;
}

BOOL CreateBiTree(pBiTreeNode &T)
{
		
		int iValue = 0;
		
		scanf(" %c",&iValue);
		
		if (iValue=='#')
		{
				T = NULL;
		}
		else
		{
				if (NULL==(T=(pBiTreeNode)malloc(sizeof(BiTreeNode))))
				{
						return false;
				}
				
				memset(T,0,sizeof(BiTreeNode));
				
				T->iData = iValue;
				
				CreateBiTree(T->pLeft);
				
				CreateBiTree(T->pRight);
		}
		
		return TRUE;
}// CreateBiTree

BOOL PosThreading(pBiTreeNode T)
{

		if (NULL != T)
		{
			PosThreading(T->pLeft);	
			PosThreading(T->pRight);
			
				if (!T->pRight)
				{
						T->pRight= g_pPre;
						
						T->RTag = THREAD;
				}
				
				if (!g_pPre->pLeft)
				{
						g_pPre->pLeft = T;
						
						g_pPre->LTag = THREAD;
				}
				g_pPre = T;
	
				return TRUE;
		}
		
		return FALSE;

}// PosThreading
BOOL PosOrderThreading(pBiTreeNode &Thrt,pBiTreeNode T)
{

		if (NULL==(Thrt = (pBiTreeNode)malloc(sizeof(BiTreeNode))))
		{
				return FALSE;
		}
		memset(Thrt,0,sizeof(BiTreeNode));

		Thrt->pRight = Thrt;
		
		Thrt->RTag = THREAD;
		
		Thrt->LTag = LINK;
		
		if(NULL == T)
		{
				Thrt->pLeft = Thrt;
				
				return FALSE;
		}
		
		g_pPre = Thrt;
		
		Thrt->pLeft = T;
		
		PosThreading(T);
		Thrt->pRight = g_pPre;
		
		return TRUE;
}// PosOrderThreading

BOOL PosOrderTravelThr(pBiTreeNode Thr) // Ѱ��ֱ��ǰ����
{
  if (!Thr && !Thr->pRight)  // ������ӡ ֻ����ǰ�� ��Ϊ����Ҳ���   ���ǿ��԰ѱ�����ָ�뱣�浽ջ���� Ȼ��ͳ�ջ 
  {			//  �����������ӡ
    return FALSE;
  }
	
  pBiTreeNode p = Thr->pRight;

  while (p!=Thr)
  {
    printf("%c ",p->iData);

    p = p->pRight;
  }
		return TRUE;
}// PosOrderTravelThr

BOOL PosOrderTravel(pBiTreeNode T)
{
  if (NULL != T)
  {
    if (T->LTag==LINK)
    { 
      PosOrderTravel(T->pLeft);
    }

    if (T->RTag==LINK)
    {
      PosOrderTravel(T->pRight);
    }

    printf("%c ",T->iData);

    return TRUE;
  }

  return FALSE;
}// PosOrderTravel

// Ѱ�ҽڵ��ֱ��ǰ�� 
// �ں��������������� ���ڵ� RTag ==0 ��ô���Ҷ���  ����ǰ��
//   ��RTag==1  LTag==0������� ����ǰ��  LTag==1 pLeft�������� Ҳ��ǰ��

// Ѱ�ҽ���ֱ�Ӻ��
//  ��Ҫ֪������˫��  ������  ��������㷨ȱ�ݺܴ� 