#include "HashTable.h"
#include <stdio.h>
int main()
{
	HashTable H;
	InitHashTable(&H);
	for(int i = 0;i < MAXSIZE * 2;i += 2)
		InsertHashTable(&H,i);
	printf("������Ҫ���ҵ�����:\n");
	int key;
	scanf("%d",&key);
	if(SearchHashTable(&H,key))
		printf("�ڹ�ϣ�����ҵ��ؼ���:%d\n",key);
	else
		printf("�ڹ�ϣ����δ�ҵ��ؼ���:%d\n",key);
	return 0;
}
