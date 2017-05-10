//����һ�����ͣ��������Ĵ�ӡ��û�а�������Ĵ����  Ϊ���д��� ���� ����  ջ ���� ʵ�������ӡ 
//Ҳ���������  ��ջ ��ӡ ������ջ��ӡ��һ����   ���������������˼ 
#include <iostream>
using namespace std;


typedef struct _BTNODE_
{
	char c;
	_BTNODE_*pLNext;
	_BTNODE_*pRNext;

}BTNode,*pBTNode;

typedef struct  _STACKNODE_ 
{
	BTNode NodeTemp;  //����û�ж��� pBTNode pBTNodeTemp �ĺô����� ������ʹ����ջ��������� ���ǻ�����ʹ�ú������      
						//	����ʹ��pBTNode pBTNodeTemp ֮��  ���Ǿ��޷�ʹ�������ı����� ��Ϊ������ʱ���ı�ڵ�ĺ���
	_STACKNODE_* pNext;
}StackNode,*pStackNode;

void CreateBinNode(pBTNode& pBinNew);

void PopStack(BTNode &NodeTemp);
void PushStack(BTNode NodeTemp);
void FreeBTNode(pBTNode &pTemp);


void PreTravel(pBTNode pTemp);
void PrePrint(pBTNode pNodeTemp);

void ProPrint(pBTNode pNodeNew);
void PosTravel(pBTNode pNodeNew);


void MidTravel(pBTNode pNodeNew);
void MidPrint(pBTNode pNodeNew);
pStackNode pHead = NULL;


int main()
{
	pBTNode pRoot = NULL;
	cout<<"�����룬����������"<<endl;
	CreateBinNode(pRoot);


	cout<<"�������ݹ�ǰ����� ";
	PreTravel(pRoot);//������ǰ�� ��Ȼ���������ƻ�   �޷�����
	cout<<endl;
	cout<<"�ǵݹ���ջǰ����� ";
	PrePrint(pRoot);
	cout<<endl;
	
	
	cout<<"�������ݹ�������� ";
	MidTravel(pRoot);
	cout<<endl;
	cout<<"�ǵݹ���ջ������� ";
	MidPrint(pRoot);
	cout<<endl;
	
	
	cout<<"�������ݹ������� ";
	PosTravel(pRoot);
	cout<<endl;
	cout<<"�ǵݹ���ջ������� ";
	ProPrint(pRoot);
	cout<<endl;
	
	

	

	FreeBTNode(pRoot);

}




void  CreateBinNode(pBTNode& pBinNew)
{
	char a = 0;
	cin>>a;

	if (a=='#')
	{
		pBinNew =  NULL;
	}

	else
	{
		pBinNew = new BTNode;

		pBinNew->c = a;

		pBinNew->pLNext  =NULL;

		pBinNew ->pRNext = NULL;
		CreateBinNode(pBinNew->pLNext);
		CreateBinNode(pBinNew->pRNext);
		
	}
}

void FreeBTNode(pBTNode &pTemp)
{
// 	if (pTemp)
// 	{	
// 		if (pTemp->pLNext!=NULL&&pTemp->pRNext==NULL)
// 		{
// 			FreeBTNode(pTemp->pLNext);
// 		}
// 		if (pTemp->pLNext ==NULL&&pTemp->pRNext!= NULL)
// 		{
// 			FreeBTNode(pTemp->pRNext);
// 		}
// 		if (pTemp->pLNext!=NULL && pTemp->pRNext !=NULL)
// 		{
// 			FreeBTNode(pTemp->pLNext);
// 			FreeBTNode(pTemp->pRNext);
// 		}
// 		if (pTemp->pLNext ==NULL && pTemp->pRNext==NULL)
// 		{
// 			free(pTemp);
// 			
// 			pTemp = NULL;
// 		}
// 	}



	//�����ķ���

	if (pTemp)
	{
		FreeBTNode(pTemp->pLNext);
		
		FreeBTNode(pTemp->pRNext);
	

		free(pTemp);

		pTemp = NULL;
	}
}


void PushStack(BTNode NodeTemp)
{
	pStackNode p = new StackNode ;
	
	p->NodeTemp = NodeTemp;
	
	p->pNext = NULL;
		
	p->pNext = pHead;
	
	pHead = p;
	
}

void PopStack(BTNode &NodeTemp)
{
	NodeTemp= pHead->NodeTemp;

	pStackNode p = pHead ;

	pHead = pHead->pNext ;

	delete p;
}


//ջ ǰ�����
void PrePrint(pBTNode pNodeTemp)
{
	if (pNodeTemp!=NULL)
	{
		PushStack(*pNodeTemp);
	}

	

	BTNode NodeNew;
	while (pHead!=NULL)
	{
		PopStack(NodeNew);
		cout<<NodeNew.c<<" ";
		
		if (NodeNew.pRNext!=NULL)
		{
			
			PushStack(*(NodeNew.pRNext));
		
		}

		if (NodeNew.pLNext!=NULL)
		{
		
			PushStack(*(NodeNew.pLNext));
			
		}
	}
}
//������ǰ��
void PreTravel(pBTNode pTemp)
{
	if (pTemp!=NULL)
	{
		cout<<pTemp->c<<" ";
		PreTravel(pTemp->pLNext);
		PreTravel(pTemp->pRNext);
	}
}
//ջ ����  �Լ�����  ��TMD  ������
void MidPrint(pBTNode pNodeNew)
{
	if (pNodeNew!=NULL)
	{
		PushStack(*pNodeNew);
	}
	

	BTNode NodeTemp ;

	pBTNode pLNode = NULL;
	while(pHead!=NULL)
	{
		PopStack(NodeTemp);

		pLNode = NodeTemp.pLNext;
		if(pLNode==NULL)
		{
			cout<<NodeTemp.c<<" ";
		}
		else
		{
		
			NodeTemp.pLNext = NULL;

			if(NodeTemp.pRNext!=NULL)
			{
				PushStack(*(NodeTemp.pRNext));
			}
			PushStack(NodeTemp);

			PushStack(*(pLNode));
			
		}
	}
}
//����������
void MidTravel(pBTNode pNodeNew)
{
	if(pNodeNew!=NULL)
	{
		MidTravel(pNodeNew->pLNext);
		cout<<pNodeNew->c<<" ";

		MidTravel(pNodeNew ->pRNext);
	}
}

//ջ �������
void ProPrint(pBTNode pNodeNew)
{
	if(pNodeNew!=NULL)
	{
		PushStack(*pNodeNew);
	}
	

	BTNode NodeTemp ;

	pBTNode pRNode ,pLNode;

	while(pHead!=NULL)
	{
		PopStack(NodeTemp);

		pRNode = NodeTemp.pRNext;
		pLNode = NodeTemp.pLNext;
		if(pRNode==NULL&&pLNode==NULL)
		{
			cout<<NodeTemp.c<<" ";
		}


		else
		{
			NodeTemp.pRNext = NULL;

			NodeTemp.pLNext = NULL;

			PushStack(NodeTemp);

		
			if(pRNode != NULL)
			{
				PushStack(*pRNode);
			}
			if(pLNode!=NULL)
			{
				PushStack(*pLNode);
			}
			
			
		
		}
	}
}

//����������

void PosTravel(pBTNode pNodeNew)
{
	if(pNodeNew != NULL)
	{
		PosTravel(pNodeNew->pLNext);

		PosTravel(pNodeNew->pRNext);

		cout<<pNodeNew->c<<" ";
	}
}



// ��������  123##4##56##7##
// 
// �����룬����������
// 123##4##56##7##
// �������ݹ�ǰ����� 1 2 3 4 5 6 7
// �ǵݹ���ջǰ����� 1 2 3 4 5 6 7
// �������ݹ�������� 3 2 4 1 6 5 7
// �ǵݹ���ջ������� 3 2 4 1 6 5 7
// �������ݹ������� 3 4 2 6 7 5 1
// �ǵݹ���ջ������� 3 4 2 6 7 5 1
// Press any key to continue