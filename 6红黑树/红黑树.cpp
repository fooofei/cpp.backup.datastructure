#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>

//����������� 1�ڵ��Ǻ�ɫ���ߺ�ɫ  2���ڵ��Ǻ�ɫ  3ÿ��Ҷ�ӽڵ��Ǻ�ɫ  4ÿ����ɫ�ڵ�������ӽڵ㶼�Ǻ�ɫ����ÿ��Ҷ�ӽڵ�
//����������·�����������������ĺ�ɫ�ڵ�   5����һ�ڵ㵽��ÿ��Ҷ�ӵ�����·����������ͬ��Ŀ�ĺ�ɫ�ڵ�

//�㷨���� 13��  ����������   ��Ҫ��


#define     RBTREE_COLOR_RED    0
#define     RBTREE_COLOR_BLACK  1


typedef struct _RBTREENODE_ 
{
	_RBTREENODE_* pLeft;
	_RBTREENODE_* pRight;
	_RBTREENODE_* pParent;
	int iMagic;
	void* pData;
}RBTreeNode,*pRBTreeNode;


typedef struct _RBTREE_ 
{
	pRBTreeNode pRoot;
	UINT uNodeCount;
}RBTree,*pRBTree;





//����ָ��
typedef void (*DESTROYFUNC)(void* pData ); 
void DestroyData(void* pData);

typedef int (COMPAREFUNC)(void* pDataA,void* pDataB);
int CompareData(void* pDataA,void* pDataB);  //�Զ���ȽϹ��� �������õ���int ������


pRBTree RBTreeCreate(); //���Ĵ���
void* RBTreeNodeCreate(void* pData); //Ҷ�ӵĴ���

void RBTreeDestroy(pRBTree pRBTreeTemp,DESTROYFUNC DestroyFunc);
void RBTreeNodeDestroy(pRBTreeNode pRBTreeNodeTemp,DESTROYFUNC DestroyFunc);

// ���������������,��תǰA�ڵ�������ҽڵ�B������,��ת��A�ڵ����ָ��ָ��B�ڵ����ڵ㣬B�ڵ����ָ��ָ��A�ڵ㣬
void RBTreeRotateLeft(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA);
//���������������,��תǰA�ڵ��������ڵ�B������,��ת��A�ڵ����ָ��ָ��B�ڵ���ҽڵ㣬B�ڵ����ָ��ָ��A�ڵ㣬
void RBTreeRotateRight(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA);


// ����������һ�����������ϲ���һ��������
//���AΪ��׼�ڵ�,��BΪA����ڵ�,CΪB���ҽڵ�,�ȶ�C������,�ٶ�B����,�ٶ�A�����������ɡ�
void RBTreeRotateLeftLeftRight(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeStartNode);

// ����������һ�����������ϲ���һ��������
//���AΪ��׼�ڵ�,��BΪA���ҽڵ�,CΪB����ڵ��ȶ�C������,�ٶ�B����,�ٶ�A�����������ɡ�
void RBTreeRotateRightRightLeft(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeStartNode);


//ɾ��
void RBTreeAdjustColorForDel(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeParent,pRBTreeNode pRBTreeNodeReplace);
int  RBTreeDelete(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc,DESTROYFUNC DestroyFunc);

//����
int RBTreeInsert(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc);
int RBTreeInterInsert(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeNew,COMPAREFUNC CompareFunc);
void RBTreeAdjustColorForInsert(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA);


//����
void* RBTreeFind(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc);

void main()
{

}


pRBTree RBTreeCreate()
{
	pRBTree pTreeTemp = NULL;

	pTreeTemp = (pRBTree)malloc(sizeof(RBTree));

	if (pTreeTemp!=NULL)
	{
		pTreeTemp->pRoot = NULL;

		pTreeTemp->uNodeCount = 0;
	}


	return pTreeTemp;
}


void* RBTreeNodeCreate(void* pData)
{
	pRBTreeNode pRBTreeNodeNew = NULL;

	pRBTreeNodeNew = (pRBTreeNode)malloc(sizeof(RBTreeNode));

	if (pRBTreeNodeNew!=NULL)
	{
		pRBTreeNodeNew->pLeft = pRBTreeNodeNew->pRight = NULL;

		pRBTreeNodeNew->iMagic = RBTREE_COLOR_RED;

		pRBTreeNodeNew->pData = pData;
	}


	return (void*)pRBTreeNodeNew;
}

void RBTreeNodeDestroy(pRBTreeNode pRBTreeNodeTemp,DESTROYFUNC DestroyFunc)
{
	if (pRBTreeNodeTemp!=NULL)
	{
		if (pRBTreeNodeTemp->pLeft!=NULL)
		{
			RBTreeNodeDestroy(pRBTreeNodeTemp->pLeft,DestroyFunc);
		}

		if (pRBTreeNodeTemp->pRight!=NULL)
		{
			RBTreeNodeDestroy(pRBTreeNodeTemp->pRight,DestroyFunc);
		}

		if (DestroyFunc!=NULL&&pRBTreeNodeTemp->pData!=NULL)
		{
			DestroyFunc(pRBTreeNodeTemp->pData);
		}


		free(pRBTreeNodeTemp);
	}
}


void RBTreeDestroy(pRBTree pRBTreeTemp,DESTROYFUNC DestroyFunc)
{
	if (pRBTreeTemp!=NULL)
	{
		RBTreeNodeDestroy(pRBTreeTemp->pRoot,DestroyFunc);

		free(pRBTreeTemp);
	}
}


void RBTreeRotateLeft(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA)
{
	pRBTreeNode pRBTreeNodeB = NULL;

	pRBTreeNodeB = pRBTreeNodeA->pRight;

	//��B�ڵ����ڵ���A�ڵ���ҽڵ�

	pRBTreeNodeA->pRight = pRBTreeNodeB->pLeft;

	if (pRBTreeNodeB->pLeft!=NULL)
	{
		pRBTreeNodeB->pLeft->pParent = pRBTreeNodeA;
	}


	//�޸�A�ڵ�ĸ�ָ���B�ڵ�Ĺ�ϵ
	pRBTreeNodeB->pParent = pRBTreeNodeA->pParent;

	if (pRBTreeNodeA==pRBTreeTemp->pRoot)
	{
		pRBTreeTemp->pRoot = pRBTreeNodeB;
	}

	else if (pRBTreeNodeA==pRBTreeNodeA->pParent->pLeft)
	{
		pRBTreeNodeA->pParent->pLeft = pRBTreeNodeB;
	}

	else
	{
		pRBTreeNodeA->pParent->pRight = pRBTreeNodeB;
	}

	 //��A�ڵ���B�ڵ����ڵ�

	pRBTreeNodeB->pLeft = pRBTreeNodeA;

	pRBTreeNodeA->pParent = pRBTreeNodeB;

}


void RBTreeRotateRight(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA)
{
	pRBTreeNode pRBTreeNodeB = NULL;

	pRBTreeNodeB = pRBTreeNodeA->pLeft;

	//��B�ڵ���ҽڵ���A�ڵ����ڵ�
	
	pRBTreeNodeA->pLeft = pRBTreeNodeB->pRight;

	if (pRBTreeNodeB->pRight!=NULL)
	{
		pRBTreeNodeB->pRight->pParent = pRBTreeNodeA;
	}

	//�޸�A�ڵ�ĸ�ָ���B�ڵ�Ĺ�ϵ

	pRBTreeNodeB->pParent = pRBTreeNodeA->pParent;

	if (pRBTreeNodeA==pRBTreeTemp->pRoot)
	{
		pRBTreeTemp->pRoot = pRBTreeNodeB;
	}

	else if (pRBTreeNodeA==pRBTreeNodeA->pParent->pRight)
	{
		pRBTreeNodeA->pParent->pRight = pRBTreeNodeB;
	}

	else
	{
		pRBTreeNodeA->pParent->pLeft = pRBTreeNodeB;
	}

	 //��A�ڵ���B�ڵ���ҽڵ�
	pRBTreeNodeB->pRight = pRBTreeNodeA;

	pRBTreeNodeA->pParent = pRBTreeNodeB;


}


int RBTreeInsert(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc)
{
	int iRet = 0;

	pRBTreeNode pRBTreeNodeTemp;

	pRBTreeNodeTemp = (pRBTreeNode)RBTreeNodeCreate(pData);

	if (pRBTreeNodeTemp!=NULL)
	{
		iRet = RBTreeInterInsert(pRBTreeTemp,pRBTreeNodeTemp,CompareFunc);
	}

	return iRet;
}



int RBTreeInterInsert(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeNew,COMPAREFUNC CompareFunc)
{

	pRBTreeNode pRBTreeNodeTemp = NULL;

	pRBTreeNode pRBTreeNodeParent = NULL;

	int iRet = 0;

	pRBTreeNodeTemp = pRBTreeTemp->pRoot;

	while (pRBTreeNodeTemp!=NULL)
	{
		pRBTreeNodeParent = pRBTreeNodeTemp;

		iRet = CompareFunc(pRBTreeNodeTemp->pData,pRBTreeNodeNew->pData);

		if (iRet<0)
		{
			pRBTreeNodeTemp = pRBTreeNodeTemp->pRight;
		}

		else
		{
			pRBTreeNodeTemp = pRBTreeNodeTemp->pLeft;
		}


	}

	if (pRBTreeNodeParent==NULL)
	{
		//��Ϊ�յ����

		pRBTreeTemp->pRoot = pRBTreeNodeNew;

		pRBTreeNodeNew->pParent = NULL;
	}

	else
	{
		if (iRet<0)
		{
			pRBTreeNodeParent->pRight = pRBTreeNodeNew;
		}

		else
		{
			pRBTreeNodeParent->pLeft = pRBTreeNodeNew;
		}

		pRBTreeNodeNew->pParent = pRBTreeNodeParent;
	}

	pRBTreeTemp->uNodeCount+=1;

	
    RBTreeAdjustColorForInsert(pRBTreeTemp,pRBTreeNodeNew);

	return 1;

}



void RBTreeAdjustColorForInsert(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeA)
{
	pRBTreeNodeA->iMagic = RBTREE_COLOR_RED;

	while (pRBTreeNodeA!=pRBTreeTemp->pRoot&&pRBTreeNodeA->pParent->iMagic==RBTREE_COLOR_RED)
	{
		if (pRBTreeNodeA->pParent==pRBTreeNodeA->pParent->pParent->pLeft)
		{
			//���ڵ�Ϊ�游�ڵ���ڵ�����

			pRBTreeNode pRBTreeNodeTemp = pRBTreeNodeA->pParent->pParent->pRight;

			if (pRBTreeNodeTemp!=NULL&&pRBTreeNodeTemp->iMagic==RBTREE_COLOR_RED)
			{
				pRBTreeNodeA->pParent->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeTemp->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeA->pParent->pParent->iMagic = RBTREE_COLOR_RED;


				//�����游�ڵ���ɫ���ı���˺�ɫ������游�ڵ�����ĸ��ڵ�
                //�п��ܶ��Ǻ�ɫ��������Ҫ����ѭ���������游�ڵ����ɫƽ����� 
                
				pRBTreeNodeA = pRBTreeNodeA->pParent->pParent;
			}

			else
			{
				if (pRBTreeNodeA==pRBTreeNodeA->pParent->pRight)
				{
					pRBTreeNodeA = pRBTreeNodeA->pParent;

					RBTreeRotateLeft(pRBTreeTemp,pRBTreeNodeA);
				}

				pRBTreeNodeA->pParent->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeA->pParent->pParent->iMagic = RBTREE_COLOR_RED;

				RBTreeRotateRight(pRBTreeTemp,pRBTreeNodeA->pParent->pParent);
			}


		}

		else
		{
			//���ڵ�Ϊ�游�ڵ��ҽڵ�����
			pRBTreeNode pRBTreeNodeTemp = pRBTreeNodeA->pParent->pParent->pLeft;


			if (pRBTreeNodeTemp!=NULL&&pRBTreeNodeTemp->iMagic==RBTREE_COLOR_RED)
			{
				pRBTreeNodeA->pParent->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeTemp->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeA->pParent->pParent->iMagic = RBTREE_COLOR_RED;


				pRBTreeNodeA = pRBTreeNodeA->pParent->pParent;


			}

			else
			{
				if (pRBTreeNodeA==pRBTreeNodeA->pParent->pLeft)
				{
					pRBTreeNodeA = pRBTreeNodeA->pParent;

					RBTreeRotateRight(pRBTreeTemp,pRBTreeNodeA);
				}

				pRBTreeNodeA->pParent->iMagic = RBTREE_COLOR_BLACK;

				pRBTreeNodeA->pParent->pParent->iMagic = RBTREE_COLOR_RED;

				RBTreeRotateLeft(pRBTreeTemp,pRBTreeNodeA->pParent->pParent);
			}

		}
	}

	pRBTreeTemp->pRoot->iMagic = RBTREE_COLOR_BLACK;
}



void RBTreeRotateLeftLeftRight(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeStartNode)
{
	pRBTreeNode pRBTreeNodeParent = NULL;

	pRBTreeNode pRBTreeNodeB = NULL;

	pRBTreeNode pRBTreeNodeC = NULL;
	
	pRBTreeNode pRBTreeNodeD = NULL;
	
	pRBTreeNodeParent = pRBTreeStartNode;

	pRBTreeNodeB = pRBTreeNodeParent->pLeft;

	pRBTreeNodeC = pRBTreeNodeParent->pRight;

	pRBTreeNodeD = pRBTreeNodeC->pRight;

	if (pRBTreeNodeParent->pParent==NULL)
	{

		pRBTreeTemp->pRoot = pRBTreeNodeD;
	}

	else if (pRBTreeNodeParent->pParent->pLeft == pRBTreeNodeParent)
	{
		pRBTreeNodeParent->pParent->pLeft = pRBTreeNodeD;
	}

	else
	{
		pRBTreeNodeParent->pParent->pRight = pRBTreeNodeD;
	}

	pRBTreeNodeD->pParent = pRBTreeNodeParent->pParent;

	pRBTreeNodeC->pRight = pRBTreeNodeD->pLeft;

	if (pRBTreeNodeD->pLeft!=NULL)
	{
		pRBTreeNodeD->pLeft->pParent = pRBTreeNodeC;
	}

	pRBTreeNodeParent->pLeft = pRBTreeNodeD->pRight;

	if (pRBTreeNodeD->pRight!=NULL)
	{

		pRBTreeNodeD->pRight->pParent = pRBTreeNodeParent;
	}

	pRBTreeNodeD->pLeft = pRBTreeNodeB;

	pRBTreeNodeB->pParent = pRBTreeNodeD;

	pRBTreeNodeD->pRight = pRBTreeNodeParent;

	pRBTreeNodeParent->pParent = pRBTreeNodeD;
}


void RBTreeRotateRightRightLeft(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeStartNode)
{
	pRBTreeNode pRBTreeNodeParent;
	pRBTreeNode pRBTreeNodeB = NULL;
	pRBTreeNode pRBTreeNodeC = NULL;
	pRBTreeNode pRBTreeNodeD = NULL;


	pRBTreeNodeParent = pRBTreeStartNode;

	pRBTreeNodeB = pRBTreeNodeParent->pRight;

	pRBTreeNodeC = pRBTreeNodeB->pLeft;

	pRBTreeNodeD = pRBTreeNodeC->pLeft;

	//ʹD�ڵ��ΪA�ڵ��游�ڵ���ӽڵ�,���ڵ�����游�ڵ�λ��

	if (pRBTreeNodeParent->pParent==NULL)
	{
		pRBTreeTemp->pRoot = pRBTreeNodeD;
	}

	else if (pRBTreeNodeParent->pParent->pLeft==pRBTreeNodeParent)
	{
		pRBTreeNodeParent->pParent->pLeft = pRBTreeNodeD;
	}

	else
	{
		pRBTreeNodeParent->pParent->pRight = pRBTreeNodeD;
	}

	pRBTreeNodeD->pParent = pRBTreeNodeParent->pParent;


	//D�ڵ���ҽڵ���C�ڵ����ڵ�

	pRBTreeNodeC->pLeft = pRBTreeNodeD->pRight;

	if (pRBTreeNodeD->pRight!=NULL)
	{
		pRBTreeNodeD->pRight->pParent = pRBTreeNodeC;
	}

	 //D�ڵ����ڵ��ɸ��ڵ���ҽڵ�

	pRBTreeNodeParent->pRight = pRBTreeNodeD->pLeft;

	if (pRBTreeNodeD->pLeft!=NULL)
	{
		pRBTreeNodeD->pLeft->pParent = pRBTreeNodeParent;
	}

	//B�ڵ���D�ڵ���ҽڵ�
	pRBTreeNodeD->pRight = pRBTreeNodeB;

	pRBTreeNodeB->pParent = pRBTreeNodeD;

	//���ڵ���D�ڵ����ڵ�

	pRBTreeNodeD->pLeft = pRBTreeNodeParent;

	pRBTreeNodeParent->pParent = pRBTreeNodeD;
}


//���������˺ܸ���
void RBTreeAdjustColorForDel(pRBTree pRBTreeTemp,pRBTreeNode pRBTreeNodeParent,pRBTreeNode pRBTreeNodeReplace)
{
	pRBTreeNode  pRBTreeNodeA;                  // ��Ҫ����ƽ��Ľڵ� 
    pRBTreeNode  pRBTreeNodeAParent;			  // A�ڵ�ĸ��ڵ� 
    pRBTreeNode  pRBTreeNodeB;            // pRBTreeNodeA����һ�ӽڵ� 
    pRBTreeNode  pRBTreeNodeC;           // ��ʱ����������¼B�ڵ��һ���ӽڵ� 


	pRBTreeNodeA = pRBTreeNodeReplace;
	
    pRBTreeNodeAParent = pRBTreeNodeParent;
	
	while (pRBTreeNodeA != pRBTreeTemp->pRoot 
            && (pRBTreeNodeA == NULL || pRBTreeNodeA->iMagic == RBTREE_COLOR_BLACK))
	{
		if (pRBTreeNodeA == pRBTreeNodeAParent->pLeft)   //������
		{
			pRBTreeNodeB = pRBTreeNodeAParent->pRight;

			if (pRBTreeNodeB->iMagic == RBTREE_COLOR_RED)
			{
				pRBTreeNodeC = pRBTreeNodeB->pLeft;

				if ((pRBTreeNodeC->pLeft == NULL 
                    || pRBTreeNodeC->pLeft->iMagic == RBTREE_COLOR_BLACK)
                    && (pRBTreeNodeC->pRight == NULL 
                    || pRBTreeNodeC->pRight->iMagic == RBTREE_COLOR_BLACK))
				{
					//C�ڵ����ҽڵ㶼�Ǻ�ɫ�����
					pRBTreeNodeC->iMagic = RBTREE_COLOR_RED;
                    pRBTreeNodeB->iMagic = RBTREE_COLOR_BLACK;
                    
					RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}

				else if (pRBTreeNodeC->pRight != NULL 
                    && pRBTreeNodeC->pRight->iMagic == RBTREE_COLOR_RED 
                    && ( pRBTreeNodeC->pLeft == NULL 
                    || pRBTreeNodeC->pLeft->iMagic == RBTREE_COLOR_BLACK))
				{
					//��C�ڵ���ڵ�Ϊ��ɫ���ҽڵ�Ϊ��ɫ�����
					pRBTreeNodeC->pRight->iMagic = RBTREE_COLOR_BLACK;
                    RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeB);
                    RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}

				else
				{
					//����Һ� �� ˫�� �����

					pRBTreeNodeC->pLeft->iMagic = RBTREE_COLOR_BLACK;
                    RBTreeRotateRightRightLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}
			}

			else
			{
				if ((pRBTreeNodeB->pLeft == NULL 
                    || pRBTreeNodeB->pLeft->iMagic == RBTREE_COLOR_BLACK)
                    && ( pRBTreeNodeB->pRight == NULL  
                    || pRBTreeNodeB->pRight->iMagic == RBTREE_COLOR_BLACK))
				{
					// B�ڵ�������ӽڵ㶼�Ǻ�ɫ�����
					if (pRBTreeNodeAParent->iMagic == RBTREE_COLOR_BLACK )
					{
						 //���A�ڵ�ĸ��ڵ���ɫΪ��ɫ�Ļ�,��Ҫ��B�ڵ�ĳɺ�ɫ��
                         //Ȼ��A�ڵ�ĸ��ڵ���A�ڵ����µ���ƽ�⡣
                        
                        pRBTreeNodeB->iMagic = RBTREE_COLOR_RED;
                        pRBTreeNodeA = pRBTreeNodeAParent;
                        pRBTreeNodeAParent = pRBTreeNodeA->pParent;
                        
						continue;
					}

					else
                    {
                         // A�ڵ�ĸ��ڵ�Ϊ��ɫ�����,ֻ��Ҫ��A�ڵ����ɫ
                         // �ĳɺ�ɫ,��B�ڵ���ɫ�ĳɺ�ɫ���ɴﵽƽ��
                         
                        pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
                        pRBTreeNodeB->iMagic = RBTREE_COLOR_RED;
                    }
				}

				else if (pRBTreeNodeB->pRight != NULL 
                    && pRBTreeNodeB->pRight->iMagic == RBTREE_COLOR_RED
                    && (pRBTreeNodeB->pLeft == NULL 
                    || pRBTreeNodeB->pLeft->iMagic == RBTREE_COLOR_BLACK ))
				{
					//��B�ڵ�����ӽڵ�Ϊ��ɫ�����ӽڵ�Ϊ��ɫ�����

					pRBTreeNodeB->iMagic = pRBTreeNodeAParent->iMagic;
                    pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
                    pRBTreeNodeB->pRight->iMagic = RBTREE_COLOR_BLACK;
                    RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}

				else
				{
					//B�ڵ�����ӽڵ��ںͶ�Ϊ��ɫ�����,��
                    //Ҫ�ȶ�B�ڵ���������ٶ�A�ڵ�ĸ��ڵ�����������ɴﵽƽ��

					pRBTreeNodeB->pLeft->iMagic = pRBTreeNodeAParent->iMagic;
                    pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
                    RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeB);
                    RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent);
				}
			}
		}

		else               //������
		{
			 pRBTreeNodeB = pRBTreeNodeAParent->pLeft;

			 if (pRBTreeNodeB->iMagic == RBTREE_COLOR_RED)
			 {
				 pRBTreeNodeC = pRBTreeNodeB->pRight;

				 if ((pRBTreeNodeC->pLeft == NULL 
					 || pRBTreeNodeC->pLeft->iMagic == RBTREE_COLOR_BLACK)
					 && (pRBTreeNodeC->pRight == NULL 
                    || pRBTreeNodeC->pRight->iMagic == RBTREE_COLOR_BLACK))
				 {
					 
					 
					 pRBTreeNodeB->iMagic = RBTREE_COLOR_BLACK;
					 pRBTreeNodeC->iMagic = RBTREE_COLOR_RED;
                     RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeAParent);

				 }

				 else if(pRBTreeNodeC->pRight == NULL 
					 ||pRBTreeNodeC->pRight->iMagic == RBTREE_COLOR_BLACK)
				 {
				
					 pRBTreeNodeC->pLeft->iMagic = RBTREE_COLOR_BLACK;
					 RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeAParent->pLeft);
					 RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeAParent);
				 }

				 else
				 {
					 pRBTreeNodeC->pRight->iMagic = RBTREE_COLOR_BLACK;
                     RBTreeRotateLeftLeftRight(pRBTreeTemp, pRBTreeNodeAParent);
				 }
			 }

			 else
			 {
				 if ((pRBTreeNodeB->pLeft == NULL 
					 || pRBTreeNodeB->pLeft->iMagic == RBTREE_COLOR_BLACK)
					 && ( pRBTreeNodeB->pRight == NULL  
                    || pRBTreeNodeB->pRight->iMagic == RBTREE_COLOR_BLACK ))
				 {
					 if (pRBTreeNodeAParent->iMagic == RBTREE_COLOR_BLACK )
					 {
						 pRBTreeNodeB->iMagic = RBTREE_COLOR_RED;
						 pRBTreeNodeA = pRBTreeNodeAParent;
						 pRBTreeNodeAParent = pRBTreeNodeA->pParent;
                         continue;
					 }

					 else
					 {
						 pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
                         pRBTreeNodeB->iMagic = RBTREE_COLOR_RED;
					 }
				 }

				 else if (pRBTreeNodeB->pLeft != NULL 
					 && pRBTreeNodeB->pLeft->iMagic == RBTREE_COLOR_RED
					 && (pRBTreeNodeB->pRight == NULL 
                    || pRBTreeNodeB->pRight->iMagic == RBTREE_COLOR_BLACK ))
				 {
					 pRBTreeNodeB->iMagic = pRBTreeNodeAParent->iMagic;
					 pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
					 pRBTreeNodeB->pLeft->iMagic = RBTREE_COLOR_BLACK;
                     RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeAParent);
				 }

				 else
				 {
					 pRBTreeNodeB->pRight->iMagic = pRBTreeNodeAParent->iMagic;
					 pRBTreeNodeAParent->iMagic = RBTREE_COLOR_BLACK;
					 RBTreeRotateLeft(pRBTreeTemp, pRBTreeNodeB);
                     RBTreeRotateRight(pRBTreeTemp, pRBTreeNodeAParent);
				 }
			 }
		}

		break;
	}

	if (pRBTreeNodeA!=NULL)
	{
		pRBTreeNodeA->iMagic = RBTREE_COLOR_BLACK;
	}
}

int RBTreeDelete(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc,DESTROYFUNC DestroyFunc)
{
	pRBTreeNode pRBTreeNodeParent = NULL;

	pRBTreeNode pRBTreeNodeA = NULL;

	pRBTreeNode pRBTreeNodeAParent = NULL;

	int iRet = 0;

	pRBTreeNode pRBTreeNodeTravel = NULL;

	pRBTreeNode pRBTreeNodeDel = NULL;

	if (pRBTreeTemp == NULL ||pData == NULL ||CompareFunc == NULL )
    {
        return -1;
    }

	pRBTreeNodeTravel = pRBTreeTemp->pRoot;

	while (pRBTreeNodeTravel!=NULL)
	{
		pRBTreeNodeParent = pRBTreeNodeTravel;

		iRet = CompareFunc(pRBTreeNodeTravel->pData,pData);

		if (iRet<0)
		{
			pRBTreeNodeTravel = pRBTreeNodeTravel->pRight;
		}

		else if (iRet>0)
		{
			pRBTreeNodeTravel =  pRBTreeNodeTravel->pLeft;
		}

		else
		{
			break;
		}
	}

	if (pRBTreeNodeTravel==NULL)
	{
		return -1;  //û�и�����
	}

	pRBTreeNodeDel = pRBTreeNodeTravel;

	if (pRBTreeNodeTravel->pLeft != NULL && pRBTreeNodeTravel->pRight != NULL)
	{
		int iMagic;

		//pRBTreeNodeTravel�������ӽڵ�����
		pRBTreeNodeDel = pRBTreeNodeDel->pLeft;  
		
		while (pRBTreeNodeDel->pRight!=0)
		{
			pRBTreeNodeDel = pRBTreeNodeDel->pRight;
		}

		pRBTreeNodeA = pRBTreeNodeDel->pLeft;

		pRBTreeNodeTravel->pRight->pParent = pRBTreeNodeDel; 
        pRBTreeNodeDel->pRight = pRBTreeNodeTravel->pRight;


		if (pRBTreeNodeDel != pRBTreeNodeTravel->pLeft)
		{
			pRBTreeNodeAParent = pRBTreeNodeDel->pParent;
            if (pRBTreeNodeA != NULL)
            {
                pRBTreeNodeA->pParent = pRBTreeNodeDel->pParent;
            }
            pRBTreeNodeDel->pParent->pRight = pRBTreeNodeTravel;
            pRBTreeNodeDel->pLeft = pRBTreeNodeTravel->pLeft;
            pRBTreeNodeTravel->pLeft->pParent = pRBTreeNodeDel;
		}

		else
		{
			 pRBTreeNodeAParent = pRBTreeNodeDel;  
		}

		if (pRBTreeTemp->pRoot == pRBTreeNodeTravel)
		{
			pRBTreeTemp->pRoot = pRBTreeNodeDel;
		}

		else if (pRBTreeNodeTravel->pParent->pLeft == pRBTreeNodeTravel)
		{
			  pRBTreeNodeTravel->pParent->pLeft = pRBTreeNodeDel;
		}

		else
		{
			pRBTreeNodeTravel->pParent->pRight = pRBTreeNodeDel;
		}

		pRBTreeNodeDel->pParent = pRBTreeNodeTravel->pParent;
		
        iMagic = pRBTreeNodeDel->iMagic;
        pRBTreeNodeDel->iMagic = pRBTreeNodeTravel->iMagic;
        pRBTreeNodeTravel->iMagic = iMagic;
		
        pRBTreeNodeDel = pRBTreeNodeTravel;
	}

	else
	{
		//�������ֻ��һ���ӽڵ�����

		if (pRBTreeNodeTravel->pLeft!=NULL)
		{
			pRBTreeNodeA = pRBTreeNodeTravel->pLeft;
		}

		else
		{
			pRBTreeNodeA = pRBTreeNodeTravel->pRight;
		}

		pRBTreeNodeAParent = pRBTreeNodeDel->pParent;

		if (pRBTreeNodeA!=NULL)
		{
			 pRBTreeNodeA->pParent = pRBTreeNodeDel->pParent;   
		}

		if (pRBTreeTemp->pRoot==pRBTreeNodeTravel)
		{
			pRBTreeTemp->pRoot = pRBTreeNodeA;
		}

		else
		{
			if (pRBTreeNodeTravel->pParent->pLeft == pRBTreeNodeTravel)
			{
				pRBTreeNodeTravel->pParent->pLeft = pRBTreeNodeA;
			}

			else
			{
				pRBTreeNodeTravel->pParent->pRight = pRBTreeNodeA;
			}
		}

	}

	if (pRBTreeNodeDel->iMagic != RBTREE_COLOR_RED)
	{
		RBTreeAdjustColorForDel(pRBTreeTemp, pRBTreeNodeAParent, pRBTreeNodeA);

        if (DestroyFunc != NULL )
        {
            DestroyFunc(pRBTreeNodeDel->pData);
        }
        free(pRBTreeNodeDel);

	}

    pRBTreeTemp->uNodeCount -= 1;
	
    return 1;

}




void* RBTreeFind(pRBTree pRBTreeTemp,void* pData,COMPAREFUNC CompareFunc)
{
	pRBTreeNode pRBTreeNodeTemp = NULL;

	if (pRBTreeTemp==NULL||pData==NULL||CompareFunc==NULL)
	{
		return NULL;
	}

	pRBTreeNodeTemp = pRBTreeTemp->pRoot;

	while (pRBTreeNodeTemp!=NULL)
	{
		int iRet = CompareFunc(pRBTreeNodeTemp->pData,pData);


		if (iRet<0)
		{
			pRBTreeNodeTemp = pRBTreeNodeTemp->pRight;
		}

		else if (iRet>0)
		{
			pRBTreeNodeTemp = pRBTreeNodeTemp->pLeft;
		}

		else
		{
			return pRBTreeNodeTemp->pData;
		}
	}


	return NULL;
}



void DestroyData(void* pData)
{
	if (pData!=NULL)
	{
		free(pData);
	}
}


int CompareData(void* pDataA,void* pDataB)
{
	if (*((int*)pDataA)>*((int*)pDataB))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}