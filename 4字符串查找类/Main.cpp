#include <stdio.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include "StringFind.h"



bool show(int index)
{
	printf("%d ",index);
	return true; // for go on
}

int main()
{
	char* A = "HelloSbHello!WorldWorldHelloWorldHeHeHe";
	char* B = "HeHeHeHeHeHeHeHeHeHeHeHeHeHeHeHeHeHeHeHe";
	char* C = "He";
	
	int i;
	
	
	CStringFinder::zzl(B, strlen(B),C,strlen(C),1,show);
	printf("\n");
	
	CStringFinder::zzl_better(B, strlen(B),C,strlen(C),1,show);
	printf("\n");
	
	i=1;
	while (i != -1)
	{
		i = CStringFinder::kmp(B, strlen(B),C,strlen(C),i+1);
		printf("%d ",i);
	}
	return 0;
}