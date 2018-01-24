

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "simple_list_in_msvc.h"

#ifdef __cplusplus
}
#endif





struct list_item_t
{
    uint32_t data;
    struct list_item_t * next;
};

typedef struct list_item_t  list_item_t;

static int32_t
g_node_count = 0;

static void 
node_alloc(list_item_t ** p)
{
    *p = (list_item_t *)malloc(sizeof(**p));
    memset(*p, 0, sizeof(**p));
    g_node_count += 1;
}

static void 
node_free(list_item_t ** p)
{
    free(*p);
    *p = 0;
    g_node_count -= 1;
}


static void
simple_list_release(simple_list_t * l)
{
    if (simple_list_empty(l))
    {
        return;
    }

    void * p;
    for (;l->head;)
    {
        p = simple_list_get_next(l, l->head);
        node_free((list_item_t**)&(l->head));
        l->head = p;
    }
}


void 
test_simple_list_in_msvc()
{

    simple_list_t list;
    list_item_t * pitem;
    memset(&list, 0, sizeof(list));


    simple_list_construct(&list, simple_list_offset(list_item_t, next));


    for (uint32_t i=1;i<5;i += 1)
    {
        pitem = 0;
        node_alloc(&pitem);
        pitem->data = i;
        simple_list_push_front(&list, pitem);
    }

    pitem = (list_item_t *)simple_list_peek_front(&list);

    for (;pitem; pitem=pitem->next)
    {
        printf(" item value %d ", pitem->data);
    }

    printf("\n");
    fflush(stdout);


    simple_list_release(&list);
    simple_list_clear(&list);



    if (!(g_node_count==0 && simple_list_empty(&list)))
    {
        fprintf(stderr, "%s:%d ERROR, memory leak\n", __FILE__, __LINE__);
        exit(1);
    }


    fprintf(stdout, "pass test_simple_list_in_msvc()\n");

}
