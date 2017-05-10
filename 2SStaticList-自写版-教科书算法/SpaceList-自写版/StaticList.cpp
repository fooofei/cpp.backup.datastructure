#include "staticlist.h"


StaticList::StaticList(){}
StaticList::~StaticList(){}

void StaticList::InitStaticList(pSp pSpaceTemp)
{
	pSpaceTemp[MAXSIZE-1].Cur = 0; // ���ǵ�����ʹ�õ�����
	int i =0;
	for (i=0;i<MAXSIZE;i++)
	{
		pSpaceTemp[i].Cur = i+1;
	}

	pSpaceTemp[MAXSIZE-2].Cur = 0; // ��������β���ÿ�
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
	pSpaceTemp[k].Cur = pSpaceTemp[0].Cur;//�ж�ֻ��һ������ʱ�� �ǲ���
	pSpaceTemp[0].Cur = k;
}

void StaticList::Difference(pSp pSpaceTemp,int& S)
{
	InitStaticList(pSpaceTemp);
	S = MyMalloc(pSpaceTemp);
	int r = S;
	cout<<"����A�����:";
	int iACount= 0;
	int j =0;
	int i=0;
	cin>>iACount;
	for (j=0;j<iACount;j++)
	{
		i = MyMalloc(pSpaceTemp);
		cout<<"����A��Ԫ��:";
		cin>>pSpaceTemp[i].DataTemp.a;//����A��Ԫ��
		pSpaceTemp[r].Cur = i;  //���뵽��β
		r = i;
	}
	pSpaceTemp[r].Cur =0;

	// �������� ��Ҫ��������� A ���ӡ���� ��ΪA�������ֱ����
	// �˺��� ��������Ų����ɾ�� �Ͳ��ò��������ӡA�� ����A��
	// �ı仯
	TravelList(pSpaceTemp,S);
	cout<<"����B���Ԫ�ظ���\n";
	int iBCount = 0;
	cin>>iBCount;
	for(j=0;j<iBCount;j++)//��������B��Ԫ�� �����ڵ�ǰ��������� ����ɾ��
	{
		int b = 0;
		cout<<"����B��Ԫ��:";
		cin>>b;
		int p = S;
		int k = pSpaceTemp[S].Cur;//k ָ�򼯺�A �ĵ�һ�����
		while (k!=pSpaceTemp[r].Cur&&pSpaceTemp[k].DataTemp.a!=b)//����ͷ��� ����β���
		{
			p = k;
			k = pSpaceTemp[k].Cur;//��k ����
		}

		if (k==pSpaceTemp[r].Cur)//��ǰ���в����ڸ�Ԫ�� ����R��ָ���֮����rλ�ò���
		{
			i =MyMalloc(pSpaceTemp);
			pSpaceTemp[i].DataTemp.a =b;
			pSpaceTemp[i].Cur = pSpaceTemp[r].Cur;
			pSpaceTemp[r].Cur = i;
			//r=i; //����ı���r��λ��  �����ݰ�������˳����뵽��β��
		}
		else//���ھ�ɾ��
		{
			pSpaceTemp[p].Cur = pSpaceTemp[k].Cur;
			MyFree(pSpaceTemp,k);
			if (r==k)//��ɾ����r ָ��β��� ���޸�βָ�� 
			{
				r=p;
			}
		}
	}

}

void StaticList::TravelList(pSp pSpaceTemp,int S)//S ��Difference�����ͷ 
{
	
	cout<<"A��������:";
	int n = pSpaceTemp[S].Cur;
	while(n!=0)
	{
		cout<<pSpaceTemp[n].DataTemp.a<<" ";

		n  =pSpaceTemp[n].Cur;
	}
	cout<<endl;
}