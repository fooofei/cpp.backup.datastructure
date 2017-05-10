#include <stdio.h>
#include <iostream.h>
#include <windows.h>

typedef struct  
{
	char key;
}data;


typedef struct  
{
	data* elem;
	int length;
}SSTable;


#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))


bool Create_Seq(SSTable* ST,int n);

void Ascend(SSTable* ST);/* 重建静态查找表为按关键字非降序排序 */

bool Create_Ord(SSTable* ST,int n);  /* 操作结果: 构造一个含n个数据元素的静态按关键字非降序查找表ST */

bool Destroy(SSTable* ST);

int Search_Seq(SSTable ST,char key);  /* 在顺序表ST中顺序查找其关键字等于key的数据元素。若找到，则函数值为 */

int Search_Bin(SSTable ST,char Key);  /* 在有序表ST中折半查找其关键字等于key的数据元素。若找到，则函数值为 */

bool Traverse(SSTable ST,void(*VisitFunc)(data)); /* 初始条件: 静态查找表ST存在，Visit()是对元素操作的应用函数 */

void Visit(data a);

data r[10] = {1,2,3,4,5,6,7,8,9,10};

void main()
{
	SSTable ST;

	Create_Seq(&ST,10);

  Traverse(ST,Visit);
	printf("\n");

  Traverse(ST,Visit);
	printf("\n");

  Destroy(&ST);
  
}

void Visit(data a)
{
  printf("%d ",a.key);
}

bool Create_Seq(SSTable* ST,int n)
{
	int i = 0;

	(*ST).elem = (data*)calloc(n+1,sizeof(data));


	if (!(*ST).elem)
	{
		return false;
	}

	for (i=1;i<=n;i++)
	{
		*((*ST).elem+i) = r[i-1];
	}

	(*ST).length = n;


	return true;
}

// 类似选择排序 
void Ascend(SSTable* ST) 
{
	int i = 0;
	int j = 0;
	int k = 0;


	for (i=1;i<(*ST).length;i++)
	{
		k = i;

		(*ST).elem[0] = (*ST).elem[i];


		for (j=i+1;j<=(*ST).length;j++)
		{
			if (LT((*ST).elem[j].key,(*ST).elem[0].key))
			{
				k = j;

				(*ST).elem[0] = (*ST).elem[j];
			}
		}

		if (k!=j)
		{
			(*ST).elem[k] = (*ST).elem[i];

			(*ST).elem[i] = (*ST).elem[0];
		}

	}
}

bool Create_Ord(SSTable* ST,int n)
{
	bool f  = Create_Seq(ST,n);

	if (f)
	{
		Ascend(ST);
	}


	return f;
}


bool Destroy(SSTable* ST)
{
	if(ST == NULL)
		return false;

	free((*ST).elem);

	(*ST).elem = NULL;

	(*ST).length = 0;


	return true;
}


int Search_Seq(SSTable ST,char key)
{
	int i = ST.length;

	ST.elem[0].key = key;

	while(!EQ(ST.elem[i].key,key))
	{
    --i;
	}
	return i;
}

int Search_Bin(SSTable ST,char Key)
{
	int low = 0;

	int high = 0;

	int mid = 0;


	low = 1;

	high = ST.length;

	while (low<=high)
	{
		//mid = (low+high)/2;
		mid = low + ((high-low)>>1);

		if (EQ(Key,ST.elem[mid].key))
		{
			return mid;
		}

		else if (LT(Key,ST.elem[mid].key))
		{
			high = mid-1;
		}

		else
		{
			low = mid+1;
		}
	}

	return 0;
}


bool Traverse(SSTable ST,void (*VisitFunc)(data))
{


	data* p = NULL;

	int i = 0;


	p = ++ST.elem;

	for (i=1;i<=ST.length;i++)
	{
		VisitFunc(*p++);
	}


	return true;


}