#include <iostream>
#include <STDIO.H>
#include <WINDOWS.H>
using namespace std;
#define LH 1
#define EH 0
#define RH -1

// ƽ������������ڲ������ݣ�����ƽ����������ǿŶ�����������

typedef struct _BSTREE_
{
	int bf;

	int Data;

	_BSTREE_* pLNext;
	_BSTREE_* pRNext;
}BSTree,*pBSTree;

void L_Rotate(pBSTree &pBSTreeTemp);
void R_Rotate(pBSTree &pBSTreeTemp);
void DestroyBSTree(pBSTree &pBSTreeTemp);
void RightBalance(pBSTree &pBSTreeTemp);
void LeftBalance(pBSTree &pBSTreeTemp);
BOOL InsertAVL(pBSTree &pBSTreeTemp,int Data,BOOL &bTaller);
void TraverseBSTree(pBSTree pBSTreeTemp);
pBSTree GetPoint(pBSTree pBSTreeTemp,int Data);

int main(int argc, char** argv)
{
  BOOL bTaller;

  pBSTree pRoot = NULL;

  int p[] = {13,24,37,90,53};
  int Size =sizeof(p)/sizeof(int);

  int i = 0;

  for (i=0;i<Size;++i)
  {
    InsertAVL(pRoot,p[i],bTaller);
  }

  TraverseBSTree(pRoot);

  DestroyBSTree(pRoot);
  return 0;
}




pBSTree GetPoint(pBSTree pBSTreeTemp,int Data)
{

  while (pBSTreeTemp)
  {
    if (pBSTreeTemp->Data==Data)
    {
      return pBSTreeTemp;
    }

    else if (pBSTreeTemp->Data>Data)
    {
      pBSTreeTemp = pBSTreeTemp->pLNext;
    }
    else 
    {
      pBSTreeTemp = pBSTreeTemp->pRNext;
    }
  }

  return NULL;
}


BOOL InsertAVL(pBSTree &pBSTreeTemp,int Data,BOOL &bTaller)
{
  if (!pBSTreeTemp)
  {
   
    if (NULL==( pBSTreeTemp = (pBSTree)malloc(sizeof(BSTree))))
    {
      exit(0);
    }

    memset(pBSTreeTemp,0,sizeof(BSTree));

    pBSTreeTemp->Data = Data;

    bTaller = TRUE;

    return TRUE;
  }

  if (pBSTreeTemp->Data==Data)
  {
    bTaller = FALSE;

    return FALSE;
  }

  if (pBSTreeTemp->Data>Data)
  {
    if (!InsertAVL(pBSTreeTemp->pLNext,Data,bTaller))
    {
      return FALSE;
    }

    if (bTaller)
    {
      switch(pBSTreeTemp->bf)
      {
      case LH:
        {
          LeftBalance(pBSTreeTemp);

          bTaller = FALSE;

          break;
        }
      case EH:
        {
          pBSTreeTemp->bf = LH;
          
          bTaller = TRUE;

          break;
        } 

      case RH:
        {
          pBSTreeTemp->bf = EH;

          bTaller = FALSE;
        }
      }
    }
  }

  else // pBSTreeTemp->Data < Data
  {
    if (!InsertAVL(pBSTreeTemp->pRNext,Data,bTaller))
    {
      return FALSE;
    }

    if (bTaller)
    {
      switch(pBSTreeTemp->bf)
      {
      case LH:
        {
          pBSTreeTemp->bf = EH;

          bTaller = FALSE;
          break;
        }
      case EH:
        {
          pBSTreeTemp->bf = RH;
          bTaller = TRUE;
          break;
        }
      case RH:
        {
          RightBalance(pBSTreeTemp);

          bTaller = FALSE;
          break;
        }
      }
    }
  }

  return TRUE;

}

void TraverseBSTree(pBSTree pBSTreeTemp)
{
  if (pBSTreeTemp)
  {
    TraverseBSTree(pBSTreeTemp->pLNext);

    printf("%d ",pBSTreeTemp->Data);

    TraverseBSTree(pBSTreeTemp->pRNext);
  }
}

void L_Rotate(pBSTree &pBSTreeTemp) // Χ�� pBSTreeTemp ���� ��ͼ�о��� 80
{
	/*
 ��ĳԪ������ת  
                                 80										                  90  
                                 /  \             ����               /      \
                               60    90          ---- ->			     80       120
                                    /  \                          /  \       /
                                  85   120						         60     85   100
                                        /
                                      100     
                               a)  BST��                              b ) AVL��

	����һ�£��ڲ�������100֮ǰ��aͼ��B ST��ֻ��80�ڵ��ƽ��������-1(���-�Ҹ�)��������������ƽ��ġ�����100֮��80�ڵ��ƽ�����Ӿͳ�Ϊ��-2����ʱƽ�ⱻ�ƻ�����Ҫ����ת��b ͼ��
     �����нڵ�X���Һ��ӵ��Һ����ϲ�����Ԫ�أ���ƽ�����Ӵ�-1���-2�󣬾���Ҫ�ƽڵ�X��������ת��   
							   */
	pBSTree pBSTreeCur = NULL;

	pBSTreeCur = pBSTreeTemp->pRNext;

	pBSTreeTemp->pRNext = pBSTreeCur->pLNext;

	pBSTreeCur->pLNext = pBSTreeTemp;

	pBSTreeTemp = pBSTreeCur;
}

void R_Rotate(pBSTree &pBSTreeTemp) // Χ�� pBSTreeTemp ���� ��ͼ�о��� 100
{
	/*��ĳԪ������ת  
                                 100									                     85
                                 /  \               ����                /       \
                              85     120         ------ ->		  		  60        100  
                              /  \                                      \      /   \
                            60   90									                  	 80  90		120
                              \
                              80
                             a) B ST��                                b) AVL��
     �����нڵ�X�����ӵ������ϲ�����Ԫ�أ���ƽ�����Ӵ�1���2�󣬾���Ҫ�ƽڵ�X��������ת��
	 */
	pBSTree pBSTreeCur = NULL;

	pBSTreeCur = pBSTreeTemp->pLNext;

	pBSTreeTemp->pLNext = pBSTreeCur ->pRNext;

	pBSTreeCur->pRNext = pBSTreeTemp;

	pBSTreeTemp = pBSTreeCur ;
}

void DestroyBSTree(pBSTree &pBSTreeTemp)
{
	if(pBSTreeTemp!=NULL)
	{
		DestroyBSTree(pBSTreeTemp->pLNext);

		DestroyBSTree(pBSTreeTemp->pRNext);

		delete pBSTreeTemp;

		pBSTreeTemp = NULL;
	}
}


void LeftBalance(pBSTree &pBSTreeTemp)
{
	pBSTree p = NULL;
	p = pBSTreeTemp->pLNext;

	pBSTree q= NULL;

	switch(p->bf)
	{
	case LH:/* �½�������*T�����ӵ��������ϣ�Ҫ������������ */
		{
			pBSTreeTemp->bf = p->bf = EH;

			R_Rotate(pBSTreeTemp);
			break;
		}
	case RH:/* �½�������*T�����ӵ��������ϣ�Ҫ��˫������ */
		{
			q = p->pRNext;

			switch(q->bf)
			{
			case LH:
				{
					pBSTreeTemp->bf = RH;

					p->bf = EH;
					break;
				}
			case EH:
				{
					pBSTreeTemp->bf = p->bf = EH;

					break;
				}

			case RH:
				{
					pBSTreeTemp->bf = EH;
					
					p->bf  =  LH;


					break;
				}
			
			}

			q->bf = EH;

			L_Rotate(pBSTreeTemp->pLNext);

			R_Rotate(pBSTreeTemp);

			break;
		}

	}
}

void RightBalance(pBSTree &pBSTreeTemp)
{
	pBSTree p = NULL;

	p = pBSTreeTemp->pRNext;

	pBSTree q = NULL;

	switch(p->bf)
	{
	case RH:
		{
			pBSTreeTemp->bf = p->bf = EH;
			L_Rotate(pBSTreeTemp);
			break;
		}
	case LH:
		{
			q = p->pLNext;
			switch(q->bf)
			{
			case LH:
				{
					pBSTreeTemp->bf = EH;

					p->bf = RH;

					break;
				}
			case  EH:
				{
					pBSTreeTemp->bf = LH;

					p->bf = EH;

					break;
				}
			case RH:
				{
						pBSTreeTemp->bf = p->bf = EH;

						break;
				}

			}

			q->bf  = EH;

			R_Rotate(pBSTreeTemp->pRNext);

			L_Rotate(pBSTreeTemp);

			break;
		}



	}
}




/*

ƽ��������Ĳ���
 
1. ���Ҳ���
       ƽ��������Ĳ��һ���������������ͬ��
 
2. �������
       ��ƽ��������в������������������Ĳ�ͬ����Ҫ��ʱ��֤��������ö�������ƽ��ġ���ô������ƽ�����Ļ����������ǣ� ��ת �� �������ǹ���һ��ƽ����ת��4�����
1) ��ĳԪ������ת  �����±���    80 �ǲ�ƽ��� Χ��80��ת
                                 80                                    90  
                                 /  \             ����               /    \
     RR                         60  90          ---- ->             80     120
                                    /  \                           /  \     /
                                  85 120                          60  85 100
                                        /
                                      100     
                               a)  BST��                              b ) AVL��
     ����һ�£��ڲ�������100֮ǰ��aͼ��B ST��ֻ��80�ڵ��ƽ��������-1(���-�Ҹ�)��������������ƽ��ġ�����100֮��80�ڵ��ƽ�����Ӿͳ�Ϊ��-2����ʱƽ�ⱻ�ƻ�����Ҫ����ת��b ͼ��
     �����нڵ�X���Һ��ӵ��Һ����ϲ�����Ԫ�أ���ƽ�����Ӵ�-1���-2�󣬾���Ҫ�ƽڵ�X��������ת��
 
2) ��ĳԪ������ת  
                                100                                    85
     LL                          /  \               ����              /    \
                              85  120         ------ ->              60    100  
                              /  \                                   \      /   \
                            60 90                                      80  90 120
                              \
                              80
                             a) B ST��                                b) AVL��
     �����нڵ�X�����ӵ������ϲ�����Ԫ�أ���ƽ�����Ӵ�1���2�󣬾���Ҫ�ƽڵ�X��������ת��
 
3) ��ĳԪ�ص����ӽڵ�����ת���������Ƹ�Ԫ���Լ�����ת�� ������¾������������� �Ľ�ϣ��������ʱ���Է� ��������ֲ�����ֻ��Χ�Ƶ㲻һ�����ѡ�
                                                      
                              100                             100                                90
                             /  \             ����            /  \              ����           /    \
    LR                    80   120       ------>             90  120        ------>            80   100  
                          / \                                /                                /  \      \
                         60 90                               80                              60  85    120
                            /                               / \
                          85                               60 85 
      �����нڵ�X�����ӵ��Һ����ϲ�����Ԫ�أ��� ƽ�����Ӵ�1���2�󣬾���Ҫ ����X�����ӽڵ�Y����ת����������X����ת

4) ��ĳԪ�ص����ӽڵ�����ת���������Ƹ�Ԫ���Լ�����ת�� ������¾��� ���������� �Ľ�ϣ��������ʱ���Էֽ� �������ֲ�����ֻ��Χ�Ƶ㲻һ������ ��
 
                                80                               80                                       85  
                               /   \             �� ��          /  \                 �� ��               /   \     
                             60   100      ------>              60 85            ------->               80  100
   RL                              /  \                              \                                 /   /   \       
                                  85  120                            100                             60    90 120
                                   \                                 /  \
                                   90                               90  120
       �����нڵ�X���Һ��ӵ������ϲ�����Ԫ�أ��� ƽ�����Ӵ�-1���-2�󣬾���Ҫ ����X�����ӽڵ�Y����ת����������X����ת

	   */