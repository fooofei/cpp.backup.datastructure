//具有头结点的 静态链表 
#pragma  once
#include <iostream>
using namespace std;
#define  MAXSIZE 20
typedef struct _DATA_
{
	int a ;

}Data,*pData;

typedef struct _SPACELIST_
{
	Data DataTemp;
	int Cur;
}Sp,*pSp;

class SpaceList
{
public:
	SpaceList();
	~SpaceList();
	void InitSpaceList(pSp pSpaceTemp);
	int MyMalloc(pSp pSpaceTemp);
	void MyFree(pSp pSpaceTemp,int k);
	void InsertAndDelete(pSp pSpTemp,Data DataTemp,bool Flag);
	void TravelList(pSp pSpaceTemp,int S);
	void Difference(pSp pSpaceTemp,int& S);
};