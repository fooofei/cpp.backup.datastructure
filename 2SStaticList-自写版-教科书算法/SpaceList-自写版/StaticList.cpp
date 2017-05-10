#include "staticlist.h"


StaticList::StaticList(){}
StaticList::~StaticList(){}

void StaticList::InitStaticList(pSp pSpaceTemp)
{
	pSpaceTemp[MAXSIZE-1].Cur = 0; // 我们的真正使用的链表
	int i =0;
	for (i=0;i<MAXSIZE;i++)
	{
		pSpaceTemp[i].Cur = i+1;
	}

	pSpaceTemp[MAXSIZE-2].Cur = 0; // 备用链表尾部置空
}
int StaticList::MyMalloc(pSp pSpaceTemp)
{
	int i = pSpaceTemp[0].Cur;
	if (i)
	{
		pSpaceTemp[0].Cur = pSpaceTemp[i].Cur;

	}
	return i;
}

void StaticList::MyFree(pSp pSpaceTemp,int k)
{
	pSpaceTemp[k].Cur = pSpaceTemp[0].Cur;//判断只有一个结点的时候 是不是
	pSpaceTemp[0].Cur = k;
}

void StaticList::Difference(pSp pSpaceTemp,int& S)
{
	InitStaticList(pSpaceTemp);
	S = MyMalloc(pSpaceTemp);
	int r = S;
	cout<<"输入A表个数:";
	int iACount= 0;
	int j =0;
	int i=0;
	cin>>iACount;
	for (j=0;j<iACount;j++)
	{
		i = MyMalloc(pSpaceTemp);
		cout<<"输入A表元素:";
		cin>>pSpaceTemp[i].DataTemp.a;//输入A的元素
		pSpaceTemp[r].Cur = i;  //插入到表尾
		r = i;
	}
	pSpaceTemp[r].Cur =0;

	// 蛋疼死了 需要在这里调用 A 表打印函数 因为A表的输入直接在
	// 此函数 下面紧跟着插入和删除 就不得不在这里打印A表 来看A表
	// 的变化
	TravelList(pSpaceTemp,S);
	cout<<"输入B表的元素个数\n";
	int iBCount = 0;
	cin>>iBCount;
	for(j=0;j<iBCount;j++)//依次输入B的元素 若不在当前表中则插入 否则删除
	{
		int b = 0;
		cout<<"输入B表元素:";
		cin>>b;
		int p = S;
		int k = pSpaceTemp[S].Cur;//k 指向集合A 的第一个结点
		while (k!=pSpaceTemp[r].Cur&&pSpaceTemp[k].DataTemp.a!=b)//不是头结点 不是尾结点
		{
			p = k;
			k = pSpaceTemp[k].Cur;//将k 下移
		}

		if (k==pSpaceTemp[r].Cur)//当前表中不存在该元素 插入R所指结点之后且r位置不变
		{
			i =MyMalloc(pSpaceTemp);
			pSpaceTemp[i].DataTemp.a =b;
			pSpaceTemp[i].Cur = pSpaceTemp[r].Cur;
			pSpaceTemp[r].Cur = i;
			//r=i; //这个改变了r的位置  将数据按照输入顺序插入到了尾部
		}
		else//存在就删除
		{
			pSpaceTemp[p].Cur = pSpaceTemp[k].Cur;
			MyFree(pSpaceTemp,k);
			if (r==k)//若删除的r 指向尾结点 则修改尾指针 
			{
				r=p;
			}
		}
	}

}

void StaticList::TravelList(pSp pSpaceTemp,int S)//S 是Difference里面的头 
{
	
	cout<<"A表数据是:";
	int n = pSpaceTemp[S].Cur;
	while(n!=0)
	{
		cout<<pSpaceTemp[n].DataTemp.a<<" ";

		n  =pSpaceTemp[n].Cur;
	}
	cout<<endl;
}