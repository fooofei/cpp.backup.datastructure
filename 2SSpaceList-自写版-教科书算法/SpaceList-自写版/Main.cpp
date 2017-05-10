#include "SpaceList.h"

#include <iostream>
using namespace std;

int main()
{
	SpaceList One;
	Sp SpTemp[MAXSIZE] = {0};
	One.InitSpaceList(SpTemp);
	int pHead = 0;
	One.Difference(SpTemp,pHead);
	One.TravelList(SpTemp,pHead);
	return 0;

}