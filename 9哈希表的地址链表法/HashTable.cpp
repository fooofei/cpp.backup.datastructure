#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
void InitHashTable(HashTable *H) //��ʼ����ϣ��
{
	H->count = MAXSIZE; //��ʼ����ϣ��Ĵ�С
	H->table = (Node *)malloc(sizeof(Node) * H->count); //������ϣ��
	for(int i = 0;i < H->count;++i) //��ʼ����ϣ�������
	{
		H->table[i].data = NULLKEY;
		H->table[i].next = NULL;
	}
}
int Hash(int key)  //��ϣ����
{
	return key % MAXSIZE;
}
void InsertHashTable(HashTable *H,int key) //���ؼ���key�����ϣ��
{
	int addr = Hash(key);
	if(H->table[addr].data != key && H->table[addr].data != NULLKEY) //���Ϊ�棬����������
	{
		Node *temp = (Node *)malloc(sizeof(Node));
		temp->next = H->table[addr].next;
		temp->data = key;
		H->table[addr].next = temp;
	}
	else if(H->table[addr].data == NULLKEY)  //���ֱ������
		H->table[addr].data = key;
}
bool SearchHashTable(HashTable *H,int key) //���ҹؼ���key��ֵ
{
	int addr = Hash(key);
	if(H->table[addr].data == key)
		return true;
	Node *p = H->table[addr].next;
	while(p != NULL) //���ҵ�����
	{
		if(p->data == key)
			return true;
		else
			p = p->next;
	}
	return false;
}


