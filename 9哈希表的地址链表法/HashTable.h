#ifndef HASHTABLE_H
#define HASHTABLE_H
#define MAXSIZE 17
#define NULLKEY -32768
typedef struct node{ //�ؼ��ֽ��
	int data;    //�ؼ���
	struct node *next;  //ָ����һ�����
}Node;
typedef struct Table{
	Node *table;  //��̬�����ϣ��
	int count;    //��ϣ��Ĺؼ��ָ���
}HashTable;

void InitHashTable(HashTable *H); //��ʼ����ϣ��
int Hash(int key);  //��ϣ����
void InsertHashTable(HashTable *H,int key); //�ѹؼ��ֲ����ϣ��
bool SearchHashTable(HashTable *H,int key); //�ڹ�ϣ���в��ҹؼ���key
#endif //HASHTABLE_H

