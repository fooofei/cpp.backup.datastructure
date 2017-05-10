#include <stdio.h>
#include <malloc.h>
#include <math.h>



//ע��ó����õ���άָ�룬���Ѵ�������ҪС�ģ��������ȫ�ֱ����Ļ�Ӧ�ü�Щ��
#define  N  9
#define  LT(a,b) ((a)<(b))

//��������Ԫ������
typedef struct _ELEMENT_
{
	char KeyWord;
	int  i;

}Element,*pElement;


//��̬���ұ��˳��ṹ
typedef struct _SFTable_
{
	pElement pEle;//����Ԫ�ش洢�ռ�Ļ���ַ
    int nLength;  //��ĳ���

}SFTable,*pSFTable;

//���ڵ�Ľṹ��
typedef struct _NODE_
{
	Element Data;//�ڵ��е�����
	_NODE_* pLeft;
	_NODE_* pRight; //�����������ӵ�ָ��

}Node,*pNode;

//��������
bool CreateSequance(pSFTable pSFT,int n);
void TravelSequance(SFTable SFT,void(*Function)(Element));
void Print(Element Ele);

void ElementSort(pSFTable pSFT);

//�������Ľṹ
void CreateTree(pNode *pTree,pSFTable pSFT);

void FindSW(int* Array,pSFTable pSFT);

void SecondOptimal(pNode *pTreeNode,pElement pEle,int* Array,int Low,int High);


//���Һ���
bool SearchData(pNode *pTreeNode,char KeyWord);

//����ȫ������

Element g_Array[N] = {{'C',778},{'A',110},{'B',120},{'E',0},{'D',1},{'F',5},{'G',6},{'H',33},{'I',9}};

//����һ��һ��ȫ�ֵ��ۼ�Ȩֵ��
int g_sw[N+1];


int main()
{
	SFTable SFT;
    
	//����һ���ڵ�Ľṹ��
	pNode   pTreeNode = NULL;

	
	//����һ������n������Ԫ�ص�˳����ұ�(��������ȫ������)
	
	
	if (CreateSequance(&SFT,N))
	{
		//Ϊ�˷�ֹԪ��û�н�����Ч���������ǻ���Ҫ��ȫ�������е����ݽ��а��ַ�����
		//���ȫ�������е�������
		//Element g_Array[N] = {{'B',120},{'A',110},{'E',1},{'C',778},{'D',0},{'F',5},{'I',9},{'G',6},{'H',33}}
		//��Ҫ�ٴν�������
		ElementSort(&SFT);


	}
	//��ӡ����

	TravelSequance(SFT,Print);

	printf("\n");


	//���������һ�����Ų�����

	CreateTree(&pTreeNode,&SFT);

	//��ѯ����

	printf("Input KeyWord\n");

	char KeyWord;

	scanf("%c",&KeyWord);
	bool i = SearchData(&pTreeNode,KeyWord);

	if (i==true)
	{
		printf("%c  is %d",KeyWord,pTreeNode->Data.i);

		printf("\n");
	}

	else
	{
		printf("No Found\n");
	}
		
}


bool CreateSequance(pSFTable pSFT,int n)
{
	//��̬�����ڴ�
	pSFT->pEle = (pElement)malloc(sizeof(Element)*10);

	if (pSFT->pEle==NULL)
	{
		return false;
	}

	//��ȫ�������е����ݿ������ڴ��в��ճ���һ���ڴ�

	int i = 1;
	for (i=1;i<=n;i++)
	{
		*(pSFT->pEle+i) = g_Array[i-1];   //��Ϊ�ṹ����Խ��еȺſ���
	}

	pSFT->nLength = n;

	return true;

}

void TravelSequance(SFTable SFT,void(*Function)(Element))
{
	//����һ���������͵�ָ��
	pElement pEle;

	pEle = ++SFT.pEle;

	int i = 1;
	for (i=1;i<=SFT.nLength;i++)
	{
		Function(*pEle);

		pEle++;
	}
}

void Print(Element Ele)
{
	printf("%c %d   ",Ele.KeyWord,Ele.i);
}

void ElementSort(pSFTable pSFT)
{
	//��Ϊ��һ���ڴ���һ����ֵ�������ǿ��Զ�����Ǹ�������ȫ�ֱ���

	//�����������һ��ѡ������
	int i;
	int j;
	int k;
	for (i=1;i<pSFT->nLength;i++)
	{
		k = i;
		//��Ҫ�Ƚϵ��Ǹ�ֵ�����һ���ڴ����
		pSFT->pEle[0] = pSFT->pEle[i];

		for (j = i+1;j<=pSFT->nLength;j++)
		{
			if (LT(pSFT->pEle[j].KeyWord,pSFT->pEle[0].KeyWord))
			{
				k = j;

				pSFT->pEle[0] = pSFT->pEle[j];
			}
		}

		if (k!=i)
		{
			pSFT->pEle[k] = pSFT->pEle[i];
			pSFT->pEle[i] = pSFT->pEle[0];
		}
		

	}
}

//������
void CreateTree(pNode *pTree,pSFTable pSFT)
{
	if (pSFT->nLength==0)
	{
		return;
	}

	else
	{
		//�����Ѿ��źõ�������еĸ���Ԫ�ص�ֵ�����ۼƵ�Ȩֵ��
		FindSW(g_sw,pSFT);

		SecondOptimal(&(*pTree),pSFT->pEle,g_sw,1,pSFT->nLength);

	}
}


void FindSW(int* Array,pSFTable pSFT)
{
     int i = 0;

	 //���������Ԫ��Ԥ������
	 Array[0] = 0;
	 for (i=1;i<=pSFT->nLength;i++)
	 {
		 Array[i] = Array[i-1] + pSFT->pEle->i; 
	 }
}

void SecondOptimal(pNode *pTreeNode,pElement pEle,int* Array,int Low,int High)
{
	int i;
	int j;

	i = Low;
	int Min;  //ѡ����Сֵ
	int dw;
	
	Min = abs(Array[High] - Array[Low]);
	dw  = Array[High] + Array[Low-1];

	//ѡ����СֵȻ����ݸ�ֵ����ڵ㹹�����ṹ
	for (j=Low+1;j<=High;j++)
	{
		if (abs(dw-Array[j]-Array[j-1])<Min)
		{
			i = j;
			//�ı�Minֵ
			Min = abs(dw - Array[j] - Array[j-1]);
		}
	}


	//�����ڴ�
	*pTreeNode = (pNode)malloc(sizeof(Node));

	if (*pTreeNode==NULL)
	{
		return;
	}

	//���ɽڵ�
	(*pTreeNode)->Data = pEle[i];

	//�жϺ���еݹ�
	if (i==Low)
	{
		(*pTreeNode)->pLeft = NULL;  //��ڵ��Ϊ��
	}

	else
	{
		SecondOptimal(&(*pTreeNode)->pLeft,pEle,Array,Low,i-1);
	}

	if (i==High)
	{
		(*pTreeNode)->pRight = NULL;  //�ҽڵ㴴��
	}

	else
	{
		SecondOptimal(&(*pTreeNode)->pRight, pEle,Array,i+1,High);
	}
	
}


bool SearchData(pNode *pTreeNode,char KeyWord)
{
	while (*pTreeNode)
	{
		if ((*pTreeNode)->Data.KeyWord==KeyWord)
		{
			return true;
		}
		else if ((*pTreeNode)->Data.KeyWord>KeyWord)
		{
			*pTreeNode = (*pTreeNode)->pLeft;
		}
		else
		{
			*pTreeNode = (*pTreeNode)->pRight;
		}
	}

	return false;
}