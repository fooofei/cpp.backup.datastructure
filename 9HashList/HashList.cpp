#include <stdio.h>
#include <malloc.h>
#include <windows.h>

#define  MAX 1
#define  HASHMAX 10

//����ƫ����
#define  Offset(m,s)      (BYTE)(&((m*)0)->s)

//������ֵ��Ľṹ��
typedef struct _DATA_
{
	char Name[20];
	int Age;
}Data,*pData;


//����һ��ȫ��ƫ����

UINT g_offset = 0;

//������ϣ�������еĽڵ�ṹ��

typedef struct _HASHLISTNODE_
{
	_HASHLISTNODE_* pNext;
	pData  pDt;
	
}HashListNode,*pHashListNode,**ppHashListNode;


//������ϣ����Ľṹ���ڹ�ϣ��������Ҫ��һ��ֵ�������������Ϊ����һ��ָ��������������Ҫ����һ����άָ��

typedef struct _HASHLIST_
{
	ppHashListNode ppBuckets;
	int            nBucketCount;    //������ĸ���
	int            nNodeCount;        //�ڵ�ĸ���
	
}HashList,*pHashList;




//�ض��庯����ָ��
typedef int (*HASHLISTFUNC)(int Key,int nBacketCount);




typedef int (*DATACMPFUNC)(char* pData1,char* pData2);



int HashInt(int Key,int nBacketCount);
int DataCmp(char* pData1,char* pData2);

//����һ����ϣ��
pHashList CreateHashList();

//���ӹ�ϣ��
void InsertNodeToHashList(pHashList pHashTemp,HASHLISTFUNC HashListFunc,int key, pData pDaTemp);

//���Һ���
pHashListNode FindDataFromHashList(pHashList pHashTemp,DATACMPFUNC DataCmpFunc,HASHLISTFUNC HashListFunc,char* pData1,int Key);



void FreeHashList(pHashList &pHashListTemp);  // ���Լ�����ȥ��  

int main()
{
	int i = 0;
	int KeyWord = 0;
	char Name[20];
	int  Age;
	pData pNew = NULL;

	pHashList pHashNew = CreateHashList();

    //����һ������ָ��
	HASHLISTFUNC HashListFunc;
	
	for (i=0;i<MAX;i++)
	{
		printf("Input Name...Age\n");
		scanf("%s",Name);
		scanf("%d",&Age);

		//������ڴ�

		pNew = (pData)malloc(sizeof(Data));

		if(pNew==NULL)
		{
			return;
		}

		else
		{

			//������ָ����и�ֵ
			HashListFunc = HashInt;
			

            //�ӻ������н����ݿ���������

			pNew->Age = Age;

			strcpy(pNew->Name,Name);

			printf("Input KeyWord\n");

			scanf("%d",&KeyWord);
			//���ӹ�ϣ��
			InsertNodeToHashList(pHashNew,HashListFunc,KeyWord, pNew);

		}
	   
	}


	//����һ�����Һ�����ָ��
	DATACMPFUNC DataCmpFunc = DataCmp;

	printf("Input KeyWord \n");
	scanf("%d",&KeyWord);

	printf("Input Name\n");

	scanf("%s",Name);

	pHashListNode pHashListNodeTemp;

	if (pHashListNodeTemp =  FindDataFromHashList(pHashNew,DataCmpFunc,HashListFunc,Name,KeyWord))
	{
		g_offset = Offset(Data,Age);
		printf("%s",pHashListNodeTemp->pDt);
		printf("%d",*((char*)(pHashListNodeTemp->pDt)+g_offset));
	}

   


	FreeHashList(pHashNew);



}


pHashList CreateHashList()

{
	//����һ����ϣ��

	pHashList pHashListTemp = NULL;
	pHashListTemp = (pHashList)malloc(sizeof(HashList));

	if(pHashListTemp == NULL)
	{
		return NULL;
	}

	else
	{
		//��ʼ����ϣ�����������еĸ���
		pHashListTemp->nBucketCount = HASHMAX;	//10
		
		//������ϣ���е�������
		//Ϊ���ܹ��������Ŀ����Ҷ�����һ����Ϊ��ȷ��������ĸ���

		pHashListTemp->ppBuckets = (ppHashListNode)malloc(sizeof(pHashListNode)*pHashListTemp->nBucketCount);


		if(pHashListTemp->ppBuckets == NULL)
		{
			
			//���Ϊ���ͷŵ�һ������Ĺ�ϣ��
			free(pHashListTemp);
			
			return NULL;
		}


		else
		{
			//��ʼ���������е�ֵ
			memset(pHashListTemp->ppBuckets,0,(pHashListTemp->nBucketCount)*sizeof(pHashListNode));

			pHashListTemp->nNodeCount  = 0;
		}
	}


	return pHashListTemp;
}

void InsertNodeToHashList(pHashList pHashTemp,HASHLISTFUNC HashListFunc,int key, pData pDaTemp)
{
	UINT uBucketIndex = 0;
	
	//�����ж�
	if (pHashTemp==NULL||pDaTemp==NULL)
	{
		return;
	}

	else
	{
		//����Ҫ����ڵ���ڴ�
		pHashListNode pHashListNodeTemp = (pHashListNode)malloc(sizeof(HashListNode));

		if (pHashListNodeTemp==NULL)
		{
			free(pHashTemp->ppBuckets);
			free(pHashTemp);
			free(pDaTemp);
			
			return;
		}

		else
		{
			//Ϊ�ڵ�������Ӹ�ֵ
			pHashListNodeTemp->pDt = pDaTemp;
			pHashListNodeTemp->pNext = NULL;


			//���ڵ���뵽��ϣ����

			//���ȼ�������ֵ
			uBucketIndex = HashListFunc(key,pHashTemp->nBucketCount);
			
			if (pHashTemp->ppBuckets[uBucketIndex]==NULL)
			{
				pHashTemp->ppBuckets[uBucketIndex] = pHashListNodeTemp;
			}

			else
			{
				//��һ����ʱ���������ֵ
				pHashListNode pCheckTemp = pHashTemp->ppBuckets[uBucketIndex];

				while(pCheckTemp->pNext!=NULL)
				{
					pCheckTemp = pCheckTemp->pNext;
				}

				pCheckTemp->pNext = pHashListNodeTemp;
			}



			pHashTemp->nNodeCount+=1;
		}
	}

}

pHashListNode FindDataFromHashList(pHashList pHashTemp,DATACMPFUNC DataCmpFunc,HASHLISTFUNC HashListFunc,char* pData1,int Key)
{

	pHashListNode pHashListNodeTemp = NULL;

	if (pHashTemp==NULL||DataCmpFunc==NULL||HashListFunc==NULL)
	{
		return NULL;
	}

	//ͨ��������������				//�Ҿ�����ô�Ѿ��� ���ݺ����׵�ַ����  ��Ϊ����ϰѧ��  ��Ϊʵ���ǲ�ֵ��

	UINT uIndex = HashListFunc(Key,pHashTemp->nBucketCount);


	pHashListNodeTemp = pHashTemp->ppBuckets[uIndex];

	while(pHashListNodeTemp!=NULL)
	{
		if (DataCmpFunc(pData1,pHashListNodeTemp->pDt->Name)==0)
		{
			return pHashListNodeTemp;
		}

		pHashListNodeTemp = pHashListNodeTemp->pNext;
	}


	printf("No Data\n");

	return NULL;
}


int HashInt(int Key,int nBacketCount)
{
	return ((UINT)Key%nBacketCount);
}



int DataCmp(char* pData1,char* pData2)
{
	int i = strcmp(pData1,pData2);

	if (i==0)
	{
		return 0;
	}

	return 1;
}


void FreeHashList(pHashList &pHashListTemp)
{
	if (pHashListTemp==NULL)
	{
		return;
	}
	int i =0;
	pHashListNode pHashListNodeTemp = NULL;

	for (i=0;i<pHashListTemp->nBucketCount;i++)
	{
		pHashListNodeTemp = pHashListTemp->ppBuckets[i];

		while (pHashListNodeTemp!=NULL)
		{
			pHashListTemp->ppBuckets[i] = pHashListTemp->ppBuckets[i]->pNext;
			free(pHashListNodeTemp);
			pHashListNodeTemp = pHashListTemp->ppBuckets[i];
		}
	}
	
	free(pHashListTemp);
	pHashListTemp =  NULL;
}