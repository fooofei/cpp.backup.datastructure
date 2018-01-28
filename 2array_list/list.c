

#include <stdlib.h>
#include <string.h>

#include "list.h"

#define LIST_INIT_SIZE 10/* 线性表存储空间的初始分配量 */
#define LISTINCREMENT 2



bool sqlist_init(sqlist_t * self)
{
    self->elem = (int *)malloc(sizeof(int)*LIST_INIT_SIZE);
    if (!self->elem) {
        return false;
    }
    memset(self->elem, 0, sizeof(int)*LIST_INIT_SIZE);
    self->length = 0;
    self->listsize = LIST_INIT_SIZE;
    return true;
}

bool sqlist_destroy(sqlist_t * self)
{
    if (self->elem) {
        free(self->elem);
    }
    memset(self, 0, sizeof(*self));
    return true;
}

bool sqlist_clear(sqlist_t * self)
{
    if (!self->elem) {
        return false;
    }
    self->length = 0;
    return true;
}

bool sqlist_empty(const sqlist_t * self)
{
    return self->length == 0;
}

// 1<=i<= sqlist_length()
bool sqlist_index_at(const sqlist_t * self, int i, int * val)
{
    if (!(i>=1 && i<=self->length))
    {
        return false;
    }
    *val = self->elem[i - 1];
    return true;
}

int sqlist_length(const sqlist_t * self)
{
    if (self->elem == 0) {
        return 0;
    }
    return self->length;
}

/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在，则返回值为0 */
int sqlist_locate_elem(sqlist_t * self, int e, bool(*pfn_compare)(int a, int b))
{
    int i = 0;
    for (i=0;i<self->length; i+=1)
    {
        if (pfn_compare(e, self->elem[i])) {
            return i + 1;
        }
    }
    return 0;
}


static bool 
_compare_equal(int a, int b)
{
    return a == b;
}

/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
bool sqlist_prior_elem(sqlist_t * self, int cur, int * pre)
{
    int i;
    i = sqlist_locate_elem(self, cur, _compare_equal);
    if (i <= 1) {
        return false;
    }
    return sqlist_index_at(self, i - 1, pre);
}


/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */
bool sqlist_next_elem(sqlist_t * self, int cur, int * next)
{
    int i;
    i = sqlist_locate_elem(self, cur, _compare_equal);
    if (i >= self->length) {
        return false;
    }
    return sqlist_index_at(self, i + 1, next);
}


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
bool sqlist_insert(sqlist_t * self, int i, int e)
{
    if (self->length >= self->listsize -1)
    {
        int * p = (int*)malloc(sizeof(int)*(self->listsize + LISTINCREMENT));
        if (!p) return false;
        memcpy(p, self->elem, sizeof(int)*(self->listsize));
        free(self->elem);
        self->elem = p;
        self->listsize = self->listsize + LISTINCREMENT;
    }

    if (i < 1) {
        return false;
    }
    i -= 1;

    if (i > self->length) {
        return false;
    }

    memmove(self->elem + i+1, self->elem + i , sizeof(int)*(self->length-i));
    
    self->elem[i ] = e;
    self->length += 1;

    return true;
}


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
bool sqlist_delete(sqlist_t * self, int i, int * e)
{
    if (i < 1) {
        return false;
    }
    i -= 1;
    if (i > self->length) {
        return false;
    }
    *e = self->elem[i];
    memmove(self->elem + i, self->elem + i + 1, self->length - i - 1);
    self->length -= 1;
    return true;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
/*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
bool sqlist_travel(sqlist_t * self, void(*vi)(int *))
{
    int i = 0;
    for (i=0;i<self->length; i+=1)
    {
        vi(self->elem + i);
    }
    return true;
}



// 在 b中  不在 a 中的 元素插入到 a 中
void sqlist_union(sqlist_t *La, const sqlist_t *Lb)
{
    if (sqlist_empty(La) || sqlist_empty(Lb)) {
        return;
    }

    int alen;
    int blen;
    int i;
    int val;

    alen = sqlist_length(La);
    blen = sqlist_length(Lb);

    for (i=0;i<blen; i+=1)
    {
        val = 0;
        sqlist_index_at(Lb, i + 1, &val);
        if (sqlist_locate_elem(La,val,_compare_equal)==0)
        {
            sqlist_insert(La, ++alen, val);
        }
    }
}


// 有序的合并  已经有序的 线性表 可以使用 SortList函数  排序
void sqlist_merge(const sqlist_t * La, const  sqlist_t * Lb, sqlist_t * Lc)
{
    if (sqlist_empty(La) || sqlist_empty(Lb)) {
        return;
    }

    int i;
    int j;
    int k;
    int alen;
    int blen;
    int aval;
    int bval;

    alen = sqlist_length(La);
    blen = sqlist_length(Lb);


    for (i=0, j=0,k=0;i<alen && j<blen;)
    {
        sqlist_index_at(La, i + 1, &aval);
        sqlist_index_at(Lb, j + 1, &bval);

        if (aval <= bval)
        {
            sqlist_insert(Lc, ++k, aval);
            i += 1;
        }
        else
        {
            sqlist_insert(Lc, ++k, bval);
            j += 1;
        }
    }

    for (;i<alen; i+= 1)
    {
        sqlist_index_at(La, i + 1, &aval);
        sqlist_insert(Lc, ++k, aval);
    }

    for (;j<blen; j+=1)
    {
        sqlist_index_at(Lb, j + 1, &bval);
        sqlist_insert(Lc, ++k, bval);
    }
}
