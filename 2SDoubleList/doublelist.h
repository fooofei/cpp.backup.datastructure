#pragma once

#include <stdbool.h>

// 双向循环链表
typedef struct doublelist
{
    struct doublelist * prior;
    struct doublelist * next;
}doublelist_t;


// 以下的函数不要申请内存

/* 操作结果：构造一个空的线性表L */
void doublelist_init(doublelist_t * list);

/* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
/* 初始条件：线性表L已存在。操作结果：销毁线性表L */
void doublelist_clear(doublelist_t * list);


/* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
bool doublelist_empty(const doublelist_t * list);


/* 初始条件：线性表L已存在。操作结果：返回L中数据元素个数 */
int doublelist_length(const doublelist_t * list);

/* L为带头结点的单链表的头指针。当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
bool doublelist_get(const doublelist_t * list, int position, doublelist_t ** e);
// 输出链表倒数第几个结点 返回的是结点的指针
bool doublelist_rget(const doublelist_t * list, int position, doublelist_t ** e);


bool doublelist_prior(const doublelist_t * list, doublelist_t * cur, doublelist_t ** prior);
bool doublelist_next(const doublelist_t * list, doublelist_t * cur, doublelist_t ** next);


// insert at before the position
// if position <=1 then insert front
// if position >length then insert back
void doublelist_insert(doublelist_t * list, int position, doublelist_t * node);
void doublelist_push_front(doublelist_t * list, doublelist_t * node);
void doublelist_push_back(doublelist_t * list, doublelist_t * node);
bool doublelist_front(const doublelist_t * list, doublelist_t ** node);
bool doublelist_back(const doublelist_t * list, doublelist_t ** node);
bool doublelist_pop_front(doublelist_t * list, doublelist_t ** out);
bool doublelist_pop_back(doublelist_t * list, doublelist_t ** out);
bool doublelist_remove_pos(doublelist_t * list, int position, doublelist_t ** e);
bool doublelist_remove(doublelist_t * list, doublelist_t * node);

/* 初始条件：线性表L已存在 */
/* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
void doublelist_traverse(const doublelist_t * list, void(*vi)(const doublelist_t *));

//////////////////////////////////////////////////////////////////////////
// 合并链表
bool doublelist_merge(const doublelist_t * a, const doublelist_t * b, doublelist_t *c);

bool doublelist_reverse(doublelist_t * list);


