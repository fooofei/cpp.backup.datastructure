
#include <string.h>

#include "doubly_linked_list.h"




#define __list_next_ptr(list,base) ((void**) ((char*)(base) + (list)->noff))
#define __list_prev_ptr(list,base) ((void**) ((char*)(base) + (list)->poff))

#define __list_this_nptr(list, member) ((void *)((char *)(member) - (list)->noff))
#define __list_this_pptr(list, member) ((void *)((char *)(member) - (list)->poff))


//
// https://searchcode.com/codesearch/view/21481570/#
// https://searchcode.com/file/21481572/hunt-1.5/c/list.c

void 
list_init(list_t * l, uint32_t next_offset, uint32_t prev_offset)
{
    memset(l, 0, sizeof(*l));
    l->noff = next_offset;
    l->poff = prev_offset;
}

// insert into head
void 
list_push_front(list_t * l, void * item)
{
    *__list_next_ptr(l, item) = NULL;
    *__list_prev_ptr(l, item) = NULL;
    

    if (l->first)
    {
        *__list_prev_ptr(l, l->first) = item;
    }
    *__list_next_ptr(l, item) = l->first;
    l->first = item;

    if (!(l->last))
    {
        l->last = item;
    }

   
    // update_iterators
}

void 
list_push_back(list_t * l , void * item)
{
    *__list_next_ptr(l, item) = NULL;
    *__list_prev_ptr(l, item) = NULL;


    if (l->last)
    {
        *__list_next_ptr(l, l->last) = item;
        *__list_prev_ptr(l, item) = l->last;
    }
    l->last = item;

    if (!(l->first))
    {
        l->first = item;
    }
}


void 
list_pop_front(list_t * l, void ** out)
{
    void * ret;

    ret = l->first;

    if (ret)
    {
        l->first = *__list_next_ptr(l, ret);

        if (l->first)
        {
            *__list_prev_ptr(l, l->first) = 0;
        }
        else
        {
            l->last = 0;
        }

        // recommeded set  0
        *__list_next_ptr(l, ret) = 0;
        *__list_prev_ptr(l, ret) = 0;
    }

    *out = ret;
}

void 
list_pop_back(list_t * l, void ** out)
{
    void * ret = 0;
    void * prev = 0;

    ret = l->last;

    if (ret)
    {
        l->last = *__list_prev_ptr(l, ret);
        if (l->last)
        {
            *__list_next_ptr(l, l->last) = 0;
        }
        else
        {
            l->first = 0;
        }
        // recommeded set  0
        *__list_next_ptr(l, ret) = 0;
        *__list_prev_ptr(l, ret) = 0;
    }
}

uint32_t 
list_count(list_t * l)
{
    
    uint32_t count = 0;
    void * p ;
    for ( p = l->first; p; p = *__list_next_ptr(l, p), count += 1);
    return count;
}

bool 
list_empty(list_t * l)
{
    return (l->first == 0 && l->last == 0);
}

void 
list_clear(list_t * l)
{
    memset(l, 0, sizeof(*l));
}





void 
list_iterator_set(list_iterator_t * it, list_t * l)
{
    it->cur = l->first;
    it->list = l;
}

void *
list_iterator_get(list_iterator_t * it, void ** out)
{
    *out = 0;
    if (it->list && it->cur)
    {
        *out = it->cur;
        it->cur = *__list_next_ptr(it->list, *out);
    }
    return *out;
}

void 
list_iterator_end(list_iterator_t * it)
{
    memset(it, 0, sizeof(*it));
}
