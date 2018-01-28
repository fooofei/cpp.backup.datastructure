
#include <cstdio>
#include <string.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "linked_list.h"

    extern int32_t
        g_node_count;

#ifdef __cplusplus
}
#endif



/*
  this file is to test list_release_with_second_rank_pointer()
*/




void 
make_list(list_head_t * list)
{

    list_item_t * p;

    linked_list_init(list);

    for (uint32_t i = 0; i < 4; i += 1)
    {
        p = 0;
        node_alloc(&p);
        p->data = i;
        linked_list_push_front(list, p);
    }
}

void
test_framework(void(*pfn_list_release)(list_head_t *), const char * pfn_name)
{

    list_head_t list;

    make_list(&list);

    pfn_list_release(&list);

    if (!(g_node_count == 0 && list == 0))
    {
        fprintf(stderr, "%s:%d ERROR, memory leak, fun is %s \n", __FILE__, __LINE__, pfn_name);
        exit(1);
    }
}

void
test_list_remove1(list_head_t * list)
{
    const uint32_t a[] = { 0,1,2,3 };
    const uint32_t * p = a;

    for (; list_remove(list, *p); p += 1);
}

void 
test_list_remove2(list_head_t * list)
{
    const uint32_t a[] = { 3,2,1,0 };
    const uint32_t * p = a;

    for (; list_remove(list, *p); p += 1);
}

void
test_list_remove3(list_head_t * list)
{
    const uint32_t a[] = { 0,3,1,2 };
    const uint32_t * p = a;

    for (; list_remove(list, *p); p += 1);
}

void 
test_list_remove4(list_head_t * list)
{
    const uint32_t a[] = { 2,0,3,1 };
    const uint32_t * p = a;

    for (; list_remove(list, *p); p += 1);
}


void
test_linked_list()
{
    

    test_framework(list_release_simple, "list_release_simple()");
    test_framework(list_release_with_empty_node, "list_release_with_empty_node()");
    test_framework(list_release_with_empty_node2, "list_release_with_empty_node2()");
    test_framework(list_release_with_second_rank_pointer, "list_release_with_second_rank_pointer()");

    test_framework(test_list_remove1, "test_list_remove1()");
    test_framework(test_list_remove2, "test_list_remove2()");
    test_framework(test_list_remove3, "test_list_remove3()");
    test_framework(test_list_remove4, "test_list_remove4()");

    fprintf(stdout, "pass test_linked_list()\n");
}
