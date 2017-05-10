#include "HashTable.h"
#include <stdio.h>
int main()
{
	HashTable H;
	InitHashTable(&H);
	for(int i = 0;i < MAXSIZE * 2;i += 2)
		InsertHashTable(&H,i);
	printf("请输入要查找的内容:\n");
	int key;
	scanf("%d",&key);
	if(SearchHashTable(&H,key))
		printf("在哈希表中找到关键字:%d\n",key);
	else
		printf("在哈希表中未找到关键字:%d\n",key);
	return 0;
}
