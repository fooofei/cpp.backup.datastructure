
#include <stdlib.h>
#include <string.h>

#include "simple_list_in_msvc.h"




void 
simple_list_construct(simple_list_t * l, size_t cb)
{
    l->cb_next_offset = cb;
    l->head = 0;
}

bool 
simple_list_empty(simple_list_t * l)
{
    return (l->head == 0);
}

void ** 
simple_list_get_next_ptr(simple_list_t * l, void * p)
{
    return (void**)((uint8_t*)p+l->cb_next_offset);
}

void * 
simple_list_get_next(simple_list_t * l, void *p)
{
    return *simple_list_get_next_ptr(l, p);
}

void
simple_list_push_front(simple_list_t * l, void * new_item)
{
    *simple_list_get_next_ptr(l, new_item) = l->head;
    l->head = new_item;
}


void * 
simple_list_peek_front(simple_list_t * l)
{
    return l->head;
}

void 
simple_list_clear(simple_list_t * l)
{
    l->cb_next_offset = 0;
    l->head = 0;
}

int 
simple_list_remove(simple_list_t * l, void * premove)
{
    if (!(l && premove))
    {
        return -1;
    }

    if (simple_list_empty(l))
    {
        return -2;
    }
        
    if (l->head == premove)
    {
        l->head = simple_list_get_next(l, premove);
        *simple_list_get_next_ptr(l, premove) = 0;
        return 0;
    }
    else
    {
        void * p = l->head;

        for (; p && simple_list_get_next(l, p) != premove; 
            p = simple_list_get_next(l, p));
        
        // found
        if (p)
        {
            *simple_list_get_next_ptr(l, p) = simple_list_get_next(l, premove);
            *simple_list_get_next_ptr(l, premove) = 0;
            return 0;
        }
    }

    return -3;
}
