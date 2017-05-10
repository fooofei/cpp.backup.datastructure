#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
void InitHashTable(HashTable *H) //初始化哈希表
{
	H->count = MAXSIZE; //初始化哈希表的大小
	H->table = (Node *)malloc(sizeof(Node) * H->count); //创建哈希表
	for(int i = 0;i < H->count;++i) //初始化哈希表的数据
	{
		H->table[i].data = NULLKEY;
		H->table[i].next = NULL;
	}
}
int Hash(int key)  //哈希表函数
{
	return key % MAXSIZE;
}
void InsertHashTable(HashTable *H,int key) //将关键字key插入哈希表
{
	int addr = Hash(key);
	if(H->table[addr].data != key && H->table[addr].data != NULLKEY) //如果为真，创建单链表
	{
		Node *temp = (Node *)malloc(sizeof(Node));
		temp->next = H->table[addr].next;
		temp->data = key;
		H->table[addr].next = temp;
	}
	else if(H->table[addr].data == NULLKEY)  //则否直接填入
		H->table[addr].data = key;
}
bool SearchHashTable(HashTable *H,int key) //查找关键字key的值
{
	int addr = Hash(key);
	if(H->table[addr].data == key)
		return true;
	Node *p = H->table[addr].next;
	while(p != NULL) //查找单链表
	{
		if(p->data == key)
			return true;
		else
			p = p->next;
	}
	return false;
}


