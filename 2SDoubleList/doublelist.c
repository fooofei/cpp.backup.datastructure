
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "doublelist.h"

static void
__doublelist_del(doublelist_t * prior, doublelist_t * next)
{
    next->prior = prior;
    prior->next = next;
}

static void
__doublelist_add(doublelist_t * prior, doublelist_t * new1, doublelist_t * next) 
{
    prior->next = new1;
    next->prior = new1;
    
    new1->prior = prior;
    new1->next = next;
}

void doublelist_init(doublelist_t * list)
{
    list->next = list;
    list->prior = list;
}

void doublelist_clear(doublelist_t * list)
{
    doublelist_init(list);
}

bool doublelist_empty(const doublelist_t * list)
{
    return (list->next == list && list->prior == list);
}

int doublelist_length(const doublelist_t * list)
{
    int len;

    const doublelist_t * p;
    for (p = list->next, len = 0; p!=list; len += 1, p = p->next);
    
    return len;
}

bool doublelist_get(const doublelist_t * list, int position, doublelist_t ** e)
{
    *e = 0;
    if (position < 1) {
        return false;
    }
    position -= 1;
    doublelist_t * p;
    for (p = list->next; p != list && position > 0; p = p->next, position -= 1);
    
    p = (p == list) ? 0 : p;
    *e = p;
    return p ? true : false;
}

bool doublelist_rget(const doublelist_t * list, int position, doublelist_t ** e)
{
    *e = 0;
    if (position < 1) {
        return false;
    }

    position -= 1;
    doublelist_t * p;
    for (p = list->prior; p != list && position > 0; p = p->prior, position -= 1);
    p = (p == list) ? 0 : p;
    *e = p;
    return p ? true : false;
}


bool doublelist_pop_front(doublelist_t * list, doublelist_t ** out)
{
    doublelist_t * ret = 0;
    *out = 0;
    if (doublelist_empty(list)) {
        return false;
    }
    ret = list->next;
    __doublelist_del(list, ret->next);
    *out = ret;
    return true;
}


bool doublelist_front(const doublelist_t * list, doublelist_t ** node)
{
    *node = 0;
    if (doublelist_empty(list)) {
        return false;
    }
    *node = list->next;
    return true;
}
bool doublelist_back(const doublelist_t * list, doublelist_t ** node)
{
    *node = 0;
    if (doublelist_empty(list)) {
        return false;
    }
    *node = list->prior;
    return true;
}

bool doublelist_pop_back(doublelist_t * list, doublelist_t ** out)
{
    doublelist_t * ret = 0;
    *out = 0;
    if (doublelist_empty(list)) {
        return false;
    }
    ret = list->prior;
    __doublelist_del(ret->prior, list);
    *out = ret;
    return true;
}


bool doublelist_prior(const doublelist_t * list, doublelist_t * cur, doublelist_t ** prior)
{
    *prior = 0;
    cur = cur->prior;
    if (cur != list) {
        *prior = cur;
    }
    return (*prior) ? true : false;
}

bool doublelist_next(const doublelist_t * list, doublelist_t * cur, doublelist_t ** next)
{
    *next = 0;
    cur = cur->next;
    if (cur != list) {
        *next = cur;
    }
    return (*next) ? true : false;
}

void doublelist_insert(doublelist_t * list, int position, doublelist_t * node)
{
    doublelist_t * p;

    if (position < 1) {
        position = 1;
    }
    position -= 1;
    for (p = list; (p != list->prior) && (position > 0); position -= 1, p = p->next);
    __doublelist_add(p, node, p->next);
}

void doublelist_push_front(doublelist_t * list, doublelist_t * node)
{
    __doublelist_add(list, node, list->next);
}

void doublelist_push_back(doublelist_t * list, doublelist_t * node)
{
    __doublelist_add(list->prior, node, list);
}


/* 在带头结点的单链线性表L中，删除第i个元素,并由e返回其值 */
bool doublelist_remove_pos(doublelist_t * list, int position, doublelist_t ** e);
// 給结点地址 删除  假定条件 pNodeDel 是这个链表的结点
bool doublelist_remove(doublelist_t * list, doublelist_t * node)
{
    (void)list;
    __doublelist_del(node->prior, node->next);
    return true;
}

/* 初始条件：线性表L已存在 */
/* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
void doublelist_traverse(const doublelist_t * list, void(*vi)(const doublelist_t *))
{
    doublelist_t * p;
    p = list->next->prior;
    for (;(doublelist_next(list,p,&p));)
    {
        vi(p);
    }
}

//////////////////////////////////////////////////////////////////////////
// 合并链表
bool doublelist_merge(const doublelist_t * a, const doublelist_t * b, doublelist_t *c);

bool doublelist_reverse(doublelist_t * list);
