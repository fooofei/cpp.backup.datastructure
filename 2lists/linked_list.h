
#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdint.h>
#include <stdbool.h>

// simple single linked list

struct list_item
{
    uint32_t data;
    struct list_item * next;
};

typedef struct list_item list_item_t;

typedef list_item_t * list_head_t;



void linked_list_init(list_head_t *);

void list_release_simple(list_head_t *);
void list_release_with_empty_node(list_head_t *);
void list_release_with_empty_node2(list_head_t *);

// recommended
void list_release_with_second_rank_pointer(list_head_t *);



void node_alloc(list_item_t **);
void node_free(list_item_t **);





void linked_list_push_front(list_head_t * l, list_item_t * item);

/* search ->data == data, and return the node's pointer's pointer */
list_item_t ** list_search(list_head_t * l, uint32_t data);

/* remove nodes which ->data == data , return true for found and removed success */
bool list_remove(list_head_t * l, uint32_t data);

#endif // __LINKED_LIST_H__
