
#pragma once

#include <stdbool.h>

struct sqlist
{
    int * elem;
    int length;
    int listsize;
};

typedef struct sqlist sqlist_t;

bool sqlist_init(sqlist_t * self);
bool sqlist_destroy(sqlist_t * self);
bool sqlist_clear(sqlist_t * self);
bool sqlist_empty(const sqlist_t * self);
// 1<=i<= sqlist_length()
bool sqlist_index_at(const sqlist_t * self, int i, int * val);
int sqlist_length(const sqlist_t * self);

/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在，则返回值为0 */
int sqlist_locate_elem(sqlist_t * self, int e, bool(*pfn_compare)(int a, int b));



/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
bool sqlist_prior_elem(sqlist_t * self, int cur, int * pre);


/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */
bool sqlist_next_elem(sqlist_t * self, int cur, int * next);


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
bool sqlist_insert(sqlist_t * self, int i, int e);


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
bool sqlist_delete(sqlist_t * self, int i, int * e);

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
/*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
bool sqlist_travel(sqlist_t * self, void(*vi)(int *));


// 在 b中  不在 a 中的 元素插入到 a 中
void sqlist_union(sqlist_t *La, const sqlist_t *Lb);


// 有序的合并  已经有序的 线性表 可以使用 SortList函数  排序
void sqlist_merge(const sqlist_t * La, const  sqlist_t * Lb, sqlist_t * Lc);
