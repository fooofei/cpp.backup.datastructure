
#include <string.h>
#include <stdlib.h>

#include "lockfreelist.h"


/*
 我看到其他人的实现中， push 是要重新 malloc 结点的， push 的参数作为 data 域放入结点中
 这不符合我的预期  我想做无锁链表 目的是提高性能 然后我还在不断的 malloc free 不合适
 目前还是使用 ring 吧 固定大小的空间
*/


// http://blog.kongfy.com/2017/02/%E6%97%A0%E9%94%81%E9%98%9F%E5%88%97%E7%9A%84%E4%B8%80%E7%A7%8D%E5%AE%9E%E7%8E%B0/
// 这篇文章里 出队列代码 data = next->data;  不应该为  data=h->data; 吗， h 才是那个待删除的结点

//#define LIST_NEXT_PTR(list, member) ((void **)((char *)(member) + (list)->noff))
//#define LIST_THIS_NPTR(list, member) ((void *)((char *)(member) - (list)->noff))
#define LIST_NEXT_PTR(member) ((void **)((char *)(member)))

void lockfree_list_init(struct lockfree_list_s * l)
{
    memset(l, 0, sizeof(*l));
    l->head = &l->dummy;
    l->tail = &l->dummy;
}

void lockfree_list_destroy(struct lockfree_list_s * l)
{
    memset(l, 0, sizeof(*l));
}

void lockfree_list_pushback(struct lockfree_list_s * l, void * m)
{
    *LIST_NEXT_PTR(m)=NULL;

    void * tail=NULL;
    void * next = NULL;

    for(;;)
    {
        tail = l->tail;
        next = *LIST_NEXT_PTR(tail);

        asm volatile("" ::: "memory");
        if(tail != l->tail)
        {
            continue;
        }
        if(next)
        {
            __sync_bool_compare_and_swap(&l->tail, tail, next);
            continue;
        }

        if(__sync_bool_compare_and_swap(LIST_NEXT_PTR(tail), NULL, m))
        {
            break;
        }
    }
    __sync_bool_compare_and_swap(&l->tail, tail, m);
    __sync_add_and_fetch(&l->count, 1);
}

void * lockfree_list_popfront(struct lockfree_list_s * l)
{
    void * tail = NULL;
    void * next = NULL;
    void * next_next = NULL;
    void * ret = NULL;

    for(;;)
    {
        tail = l->tail;
        next = *LIST_NEXT_PTR(head);
        asm volatile("" ::: "memory");

        if(NULL == next)
        {
            return NULL;
        }
        if(head == tail)
        {
            __sync_bool_compare_and_swap(&l->tail, tail, next);
            continue;
        }
        ret = next;
        // 这里不正确 head 所在的空结点不应该被删除的 
        if(__sync_bool_compare_and_swap(LIST_NEXT_PTR(l->head), next, *(LIST_NEXT_PTR(next))))
        {
            break;
        }
    }

    if(ret)
    {
        *LIST_NEXT_PTR(ret) = NULL;
        __sync_sub_and_fetch(&l->count,1);
    }

    return ret;
}

void lockfree_list_remove(struct lockfree_list_s * l, void * m)
{

}

uint32_t lockfree_list_count(const struct lockfree_list_s * l)
{
    return l->count;
}
