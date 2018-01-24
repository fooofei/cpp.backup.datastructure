


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "doubly_linked_list.h"


#ifdef __cplusplus
}
#endif

#define EXPECT(expr) \
    do { \
    if(!(expr)) \
        { \
        fflush(stdout); \
        fflush(stderr); \
        fprintf(stderr, "unexpect-> %s:%d\n", __FILE__, __LINE__); \
        } \
    } while (0)



struct list_item
{
    uint32_t data;
    struct list_item * next;
    struct list_item * prev;
};

typedef list_item list_item_t;


void
_doubly_make_list(list_t * list, list_item_t * item, size_t count)
{
    list_init(list, list_offset_of(list_item_t, next), list_offset_of(list_item_t, prev));
    
    memset(item, 0, sizeof(*item)*count);

    item[0].data = 1;
    item[1].data = 2;
    item[2].data = 3;

    list_push_back(list, &item[0]);
    list_push_front(list, &item[1]);
    list_push_back(list, &item[2]);

    // 2 -> 1 -> 3
}

void
test_doubly_linked_list()
{

    list_t l;
    list_item_t items[3];
    list_item_t * pitem;
    list_iterator_t it;


    _doubly_make_list(&l, items, sizeof(items) / sizeof(items[0]));

    pitem = 0;

    int expect[] = {
      2,1,3  
    };
    const int * pexpect = expect;

    for (;!list_empty(&l); pexpect += 1)
    {
        list_pop_front(&l, (void**)&pitem);
        if (!(pitem->data == *pexpect))
        {
            fprintf(stderr, "%s:%d ERROR, not as expect. get %d, expect %d\n",__FILE__, __LINE__, pitem->data, *pexpect);
            exit(1);
        }
        
    }

    // test iterator
    _doubly_make_list(&l, items, sizeof(items) / sizeof(items[0]));

    pexpect = expect;
    list_iterator_set(&it, &l);

    for (;0 != list_iterator_get(&it,(void**)&pitem); pexpect += 1)
    {
        EXPECT(*pexpect == pitem->data);
    }

    list_iterator_end(&it);
    fprintf(stdout, "pass test_doubly_linked_list()\n");
}

