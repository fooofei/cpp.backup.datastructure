#include "staticlist.h"

#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	StaticList One;
	Sp SpTemp[MAXSIZE] = {0};
	One.InitStaticList(SpTemp);
	int pHead = 0;
	One.Difference(SpTemp,pHead);
	One.TravelList(SpTemp,pHead);
	system("pause");
	return 0;
}