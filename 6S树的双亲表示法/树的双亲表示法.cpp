// ����ɭ�ֵ�ת��
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Queue.h"



typedef struct _BITREENODE_ 
{
	int a;
	int iParent;
}BiTreeNode,*pBiTreeNode;

typedef struct _DATA_ 
{
	BiTreeNode BiTreeNodeArray[MAX];
	int iCount;
}Data,*pData;





int GetRoot(Data DataTemp);
bool InitTree(pData pDataTemp);
bool TreeEmpty(pData pDataTemp);
int TreeDepth(pData pDataTemp);
bool CreateTree(pData pDataTemp);
int GetValue(Data DataTemp,int i);
int GetLeft(Data DataTemp,int e);
int GetRightSibling(Data DataTemp,int e);
void TravelTree(Data DataTemp);
bool Swap(int &a, int &b);
bool Swap(BiTreeNode& a, BiTreeNode& b);

/* ��ʼ����: ��T����,p��T��ĳ�����,1��i��p��ָ���Ķ� */
   /* �������: ɾ��T�н��p�ĵ�i������ */
bool DelChild(pData pDataTemp,int p,int e);


/* ��ʼ����: ��T����,p��T��ĳ�����,1��i��p��ָ���Ķ�+1,�ǿ���c��T���ཻ */
/* �������: ����cΪT��p���ĵ�i������ */
bool InsertChild(pData pDataTemp,int p,int e,Data DataNew);


bool Assign(pData pDataTemp,int iCur,int iValue);

int iDeleted[MAX] = {0};  // DelChild ���õ�

int main()
{
	Data DataTemp;

	Data DataNew;

	int iIndex = 0;


	InitTree(&DataTemp);

	InitTree(&DataNew);

	printf("Input Root\n");
	CreateTree(&DataTemp);
	TravelTree(DataTemp);

// 	printf("Node Count: %d\n",DataTemp.iCount);
// 
// 	printf("Tree Depth:%d\n",TreeDepth(&DataTemp));
// 
// 	printf("Tree Root:%c\n",GetRoot(DataTemp));

//	printf("Input Index To Get Value\n");
//	scanf("%d",&iIndex);
//	printf("Value:%c\n",GetValue(DataTemp,iIndex-1));


//	printf("Input Father To Get Left\n");
//	scanf(" %c",&iIndex);
//	printf("Left Value:%c\n",GetLeft(DataTemp,iIndex));


//	printf("Input Left Son To Get Right\n");
//	scanf(" %c",&iIndex);
//	printf("Right Value:%c\n",GetRightSibling(DataTemp,iIndex));


		printf("Input New Tree Root\n");
  	CreateTree(&DataNew);
		printf("����ڼ�������\n");
		scanf("%d",&iIndex);
	  InsertChild(&DataTemp,'2',iIndex,DataNew);
  	TravelTree(DataTemp);

//	printf("Del\n");


//	DelChild(&DataTemp,'1',3);

//	TravelTree(DataTemp);

  	return 0;

}

bool InitTree(pData pDataTemp)
{
	pDataTemp->iCount = 0;

	int i = 0;
	for (i=0;i<MAX;i++)
	{
		pDataTemp->BiTreeNodeArray[i].a = 0;
		pDataTemp->BiTreeNodeArray[i].iParent = -1;

	}

	return true;
}

bool CreateTree(pData pDataTemp)
{
	Queue QueueTemp;

	InitQueue(&QueueTemp);


	char Array[MAX] = {0};

	int i = 1;

	QueueData ParentTemp = {0};

	QueueData ChildTemp = {0};

	scanf(" %c",&pDataTemp->BiTreeNodeArray[0].a);  //�������ǵ�Root


	if (pDataTemp->BiTreeNodeArray[0].a!=0)
	{
		pDataTemp->BiTreeNodeArray[0].iParent = -1;

		ParentTemp.a = pDataTemp->BiTreeNodeArray[0].a;

		ParentTemp.iIndex = 0;

		EnQueue(&QueueTemp,ParentTemp);


		while (i<MAX&&!QueueEmpty(&QueueTemp))
		{
			DeQueue(&QueueTemp,&ParentTemp);


			printf("���ճ�������ڵ�%c������Child:  '#' break\n",ParentTemp.a);


			scanf("%s",Array);

			if (Array[0]!='#')
			{
				int iLen = strlen(Array);
				
				for (int j=0;j<iLen;j++)
				{
					pDataTemp->BiTreeNodeArray[i].a = Array[j];
					
					pDataTemp->BiTreeNodeArray[i].iParent = ParentTemp.iIndex;
					
					
					ChildTemp.a = Array[j];
					
					
					ChildTemp.iIndex = i;
					
					
					EnQueue(&QueueTemp,ChildTemp);	
					i++;
					
				}
			}
		
		}


		if (i>MAX)
		{
			printf("Overflow\n");

			return false;
		}

		else
		{
			pDataTemp->iCount = i;
		}
	}

	DestroyQueue(&QueueTemp);


	return true;
}


bool TreeEmpty(pData pDataTemp)
{
	if (pDataTemp->iCount)
	{
		return false;
	}

	else
	{
		return true;
	}
}


bool Assign(pData pDataTemp,int iCur,int iValue)
{
	int j = 0;

	for (j=0;j<(*pDataTemp).iCount;j++)
	{
		if ((*pDataTemp).BiTreeNodeArray[j].a==iCur)
		{
			(*pDataTemp).BiTreeNodeArray[j].a = iValue;
			
			return true;
		}
	}
	
	
	return false;
}

int TreeDepth(pData pDataTemp) // ����һ����  ������������ ��Ϊ������������
{

	int i = 0;
	int iDepth = 0;

	int iMaxDepth = 0;
	int e = 0;
	for (i=0;i<pDataTemp->iCount;i++)
	{

		iDepth = 1;

		e = pDataTemp->BiTreeNodeArray[i].iParent;

		while (e!=-1)
		{
			e = pDataTemp->BiTreeNodeArray[e].iParent;

			iDepth++;
		}

		if (iMaxDepth<iDepth)
		{
			iMaxDepth = iDepth;
		}
	}
	return iMaxDepth;
}



int GetRoot(Data DataTemp)
{
		int i = 0;//ֱ�ӷ��� DataTemp.BireeNodeArray[0].a
		
		// 	for (i=0;i<DataTemp.iCount;i++)
		// 	{
		// 		if (DataTemp.BiTreeNodeArray[i].iParent<0)
		// 		{
		// 			return DataTemp.BiTreeNodeArray[i].a;
		// 		}
		// 	}
		
		if (DataTemp.BiTreeNodeArray[0].iParent==-1)
		{
				return DataTemp.BiTreeNodeArray[0].a;
		}


	return 0;
}


int GetValue(Data DataTemp,int i)
{
	if (i<DataTemp.iCount)
	{
		return DataTemp.BiTreeNodeArray[i].a;
	}

	return '#';
	
}


int GetLeft(Data DataTemp,int e)
{
	int i = 0;

	int j = 0;
	for (i=0;i<DataTemp.iCount;i++)
	{
		if (DataTemp.BiTreeNodeArray[i].a==e)
		{

			break;
		}
	}

	for (j=i+1;j<DataTemp.iCount;j++)
	{
		if (DataTemp.BiTreeNodeArray[j].iParent==i)
		{
			return DataTemp.BiTreeNodeArray[j].a;
		}
	}

	return 0;
}

int GetRightSibling(Data DataTemp,int e)
{
	int i = 0;

	for (i=0;i<DataTemp.iCount;i++)
	{
		if (DataTemp.BiTreeNodeArray[i].a==e)
		{
			break;
		}
	}

	if (DataTemp.BiTreeNodeArray[i+1].iParent==DataTemp.BiTreeNodeArray[i].iParent)
	{
		return DataTemp.BiTreeNodeArray[i+1].a;
	}

	return 0;
}


void TravelTree(Data DataTemp)
{
	int i = 0;
	for (i=0;i<DataTemp.iCount;i++)
	{


		printf("�ڵ� %c",DataTemp.BiTreeNodeArray[i].a);

		if (DataTemp.BiTreeNodeArray[i].iParent>=0)
		{
			printf("        ˫�� %c",DataTemp.BiTreeNodeArray[DataTemp.BiTreeNodeArray[i].iParent]);
		}


		printf("\n");
	}
}


bool InsertChild(pData pDataTemp,int p,int e,Data DataNew)
{

		// ���������⣺  ���� 1�ĺ�����23 ��2�ĺ�����456 ��3û�к��� ����2�ĵ�һ������  DataNew Ϊ9 ������ ��ô�����ʾΪ��
//�����ڴ��� 9���뵽�� 3�� ǰ�� ���ǲ��Ե�   (�ҵĴ����Ѿ����)
		// �����Ǹ糭����ε���Ĵ��� �����ֻ���˲�����ǵ�һ�����ӵ���� ����������˵�� ��������
		// ���� ���벻Ҫ  �Լ���
		/*
	int j = 0;

	int n = 0;

	int l = 0;

	int k = 0;

	bool bOk = true;
	
	if (!TreeEmpty(pDataTemp))
	{
		for (j=0;j<pDataTemp->iCount;j++)
		{
			if (pDataTemp->BiTreeNodeArray[j].a==p)
			{
				break;
			}
		}
		l = j + 1;   //��һ������  

		//��� DataNew ����p�ĵ�һ������

		if(e>1)
		{
			k = j+1;
			for (k=j+1;k<pDataTemp->iCount;k++)
			{

				if (pDataTemp->BiTreeNodeArray[k].iParent==j)
				{
					n++;

					if (n==e-1) 
					{
						break;
					}
				}
			}

			l = k+1;		
		}

		//����ƶ����ǵĳ�Ա

		if (l<pDataTemp->iCount)
		{
			for (k=pDataTemp->iCount-1;k>=l;k--)
			{
				pDataTemp->BiTreeNodeArray[k+DataNew.iCount] = pDataTemp->BiTreeNodeArray[k];


				if (pDataTemp->BiTreeNodeArray[k].iParent>=l)
				{
					pDataTemp->BiTreeNodeArray[k+DataNew.iCount].iParent += DataNew.iCount;
				}
			}
		}


		//����������

		for (k=0;k<DataNew.iCount;k++)
		{
			pDataTemp->BiTreeNodeArray[l+k].a = DataNew.BiTreeNodeArray[k].a;

			pDataTemp->BiTreeNodeArray[l+k].iParent = DataNew.BiTreeNodeArray[k].iParent+l;
		}


		pDataTemp->BiTreeNodeArray[l].iParent = j; // ��ʵ�������for�������Ѿ���ֵ�� ���ܹ���Ҫ����ȥ��
																								//  ���Բ���ʡ��

		pDataTemp->iCount+=DataNew.iCount;
	

		return true;


	}

	else
	{
		return false;
	}

	*/


	int j = 0;

	int l = 0;

	int k = 0;

	int n = 0;
	
	if (!TreeEmpty(pDataTemp))
	{
		for (j=0;j<pDataTemp->iCount;j++)
		{
			if (pDataTemp->BiTreeNodeArray[j].a==p)		// j �Ǹ��ڵ������
			{
				break;
			}
		}
		
			for (l=j+1;l<pDataTemp->iCount;++l)
			{

				if (pDataTemp->BiTreeNodeArray[l].iParent==j)		// l �Ǻ��ӵ�����
				{
					++n;

					if (n==e)
					{
						break;
					}
				}
			}


		//����ƶ����ǵĳ�Ա

		if (l<pDataTemp->iCount)
		{
			for (k=pDataTemp->iCount-1;k>=l;k--)
			{
				pDataTemp->BiTreeNodeArray[k+DataNew.iCount] = pDataTemp->BiTreeNodeArray[k];


				if (pDataTemp->BiTreeNodeArray[k].iParent>=l)// ���׵�����Ҳ�ڸı�  ����Ҫ���¸�ֵ
				{
					pDataTemp->BiTreeNodeArray[k+DataNew.iCount].iParent += DataNew.iCount;
				}
			}
		}


		//����������

		for (k=0;k<DataNew.iCount;k++)
		{
			pDataTemp->BiTreeNodeArray[l+k].a = DataNew.BiTreeNodeArray[k].a;

			pDataTemp->BiTreeNodeArray[l+k].iParent = DataNew.BiTreeNodeArray[k].iParent+l;
		}


		pDataTemp->BiTreeNodeArray[l].iParent = j;

		pDataTemp->iCount+=DataNew.iCount;


		//////////////////////////////////////////////////////////////////////////
		//���Լ�����һ�������ı���λ�� ʹ����������

		int nFlag = 1;
		while(nFlag)
		{
				nFlag = 0;
				for (j =1;j<pDataTemp->iCount-1;j++)
				{
						if (pDataTemp->BiTreeNodeArray[j].iParent>pDataTemp->BiTreeNodeArray[j+1].iParent)
								
						{

								Swap(pDataTemp->BiTreeNodeArray[j],pDataTemp->BiTreeNodeArray[j+1]);
								
								nFlag = 1;
								
								for (k = j;k<pDataTemp->iCount;k++)
								{
										if (pDataTemp->BiTreeNodeArray[k].iParent==j) // �����ǽ���������֮��  ���Ǻ�ߵĺ��ӵ�˫�׵�����ҲҪ�ı�
										{
												pDataTemp->BiTreeNodeArray[k].iParent++;
										}
										
										else if (pDataTemp->BiTreeNodeArray[k].iParent==j+1)
										{
												pDataTemp->BiTreeNodeArray[k].iParent--;
										}
								}
								
						}
				}
		}
		
	

		return true;


	}

	else
	{
		return false;
	}

}// InsertChild


bool DelChild(pData pDataTemp,int p,int e)
{
		if (TreeEmpty(pDataTemp))
		{
				return false;
		}
	Queue QueueTemp;

	InitQueue(&QueueTemp);


	QueueData Family = {0};

	QueueData Family1 = {0};


	int j = 0;
	int k = 0;
	int n = 0;
	for (j=0;j<pDataTemp->iCount;j++)
	{
		if (pDataTemp->BiTreeNodeArray[j].a==p)
		{
			break;
		}
	}


	for (k=j+1;k<pDataTemp->iCount;k++)   //������
	{
		if (pDataTemp->BiTreeNodeArray[k].iParent==j)
		{
				n++;	
				if (n==e)
				{
						break;
				}
		}

	
	}// k  Ϊ  Ҫɾ���� p ������������ (iIndex)

	if (k<pDataTemp->iCount)
	{
		n = 0;

		Family.iIndex = k;


		iDeleted[k] = 1;


		n++;


		EnQueue(&QueueTemp,Family);

		while (!QueueEmpty(&QueueTemp))
		{
			DeQueue(&QueueTemp,&Family1);
			for (j=Family1.iIndex+1;j<pDataTemp->iCount;j++)
			{
				if (pDataTemp->BiTreeNodeArray[j].iParent==Family1.iIndex) //  �������ҵ�����Ҫɾ���ĸ��ڵ� ��һ��Ҫɾ���ı�־
				{
					Family.iIndex = j;

					iDeleted[j] = 1;

					n++;

					EnQueue(&QueueTemp,Family);
				}
			}
		}


		for (j=0;j<pDataTemp->iCount;j++)
		{
			if (iDeleted[j]==1)
			{
				for (k=j+1;k<=pDataTemp->iCount;k++)
				{
					iDeleted[k-1] = iDeleted[k];

					pDataTemp->BiTreeNodeArray[k-1] = pDataTemp->BiTreeNodeArray[k];


					if((pDataTemp->BiTreeNodeArray[k].iParent)>j)
					{
					   --pDataTemp->BiTreeNodeArray[k-1].iParent;
					}

				}

				j--;
			}
		
		}

		pDataTemp->iCount -= n;
	}

	DestroyQueue(&QueueTemp);

	return true;
}// DelChild
bool Swap(int &a, int &b)
{
		if (&a==&b)
		{
				return false;
		}
		a ^= b ^= a ^= b;

		return true;
}// Swap int

bool Swap(BiTreeNode& a, BiTreeNode& b)
{

		BiTreeNode c = a;
		a = b;
		b = c;

		return true;
}// Swap BiTreeNode