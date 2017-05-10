#ifndef HASHTABLE_H
#define HASHTABLE_H
#define MAXSIZE 17
#define NULLKEY -32768
typedef struct node{ //关键字结点
	int data;    //关键字
	struct node *next;  //指向下一个结点
}Node;
typedef struct Table{
	Node *table;  //动态分配哈希表
	int count;    //哈希表的关键字个数
}HashTable;

void InitHashTable(HashTable *H); //初始化哈希表
int Hash(int key);  //哈希表函数
void InsertHashTable(HashTable *H,int key); //把关键字插入哈希表
bool SearchHashTable(HashTable *H,int key); //在哈希表中查找关键字key
#endif //HASHTABLE_H

