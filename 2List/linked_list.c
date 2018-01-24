
#include <stdlib.h> // malloc
#include <string.h> // memset
#include "linked_list.h"



// for debug memory leak
int32_t
g_node_count = 0;

void
node_alloc(list_item_t ** out)
{
    g_node_count += 1;
    *out = (list_item_t *)malloc(sizeof(**out));
    memset(*out, 0, sizeof(**out));
}

void
node_free(list_item_t ** out)
{
    g_node_count -= 1;
    free(*out);
    *out = 0;
}




void 
list_release_simple(list_head_t * head)
{
    // not consider the first head empty node

    if (!(head && *head))
    {
        return;
    }

    list_item_t * pre = *head;
    list_item_t * next = 0;

    for (;pre;)
    {
        next = pre->next;
        // free(pre);
        node_free(&pre);
        pre = next;
    }

    *head = NULL;

}


void 
list_release_with_empty_node(list_head_t * head)
{
    if (!(head && *head))
    {
        return;
    }

    // consider the first head node as empty node
    list_item_t * tmp;
    for (;(*head)->next;)
    {
        tmp = (*head)->next;
        (*head)->next = tmp->next;
        node_free(&tmp);
    }
    node_free(head);
}

void 
list_release_with_empty_node2(list_head_t * head)
{
    if (!(head && *head))
    {
        return;
    }

    list_item_t ** pp;
    list_item_t *p;

    pp = &((*head)->next);

    for (;*pp;)
    {
        p = *pp;
        *pp = p->next;
        node_free(&p);
    }
    node_free(head);
}

void 
list_release_with_second_rank_pointer(list_head_t * head)
{
    if (!(head && *head))
    {
        return;
    }

    list_item_t * p;
    for (;*head;)
    {
        p = *head;
        *head = (*head)->next;
        node_free(&p);

        //p = (*head)->next;
        //node_free(head);
        //*head = p;

        // error use
        //list_item_t ** pp = &((*head)->next);
        //node_free(head);
        //head = pp;
    }

}

void 
linked_list_push_front(list_head_t * l, list_item_t * item)
{
    item->next = *l;
    *l = item;
}

/* search ->data == data, and return the node's pointer by out */
list_item_t **  
list_search(list_head_t * l, uint32_t data)
{
    list_item_t ** p;

    for (p=l; *p; p=&((*p)->next))
    {
        if ((*p)->data == data)
        {
            return p;
        }
    }
    return 0;
}

/* remove nodes which ->data == data , return true for found and removed success */
bool 
list_remove(list_head_t * l, uint32_t data)
{
    list_item_t ** p;
    list_item_t * remove;

    p = list_search(l, data);

    if (p && *p)
    {
        remove = *p;
        *p = (*p)->next;
        node_free(&remove);
        return true;
    }
    return false;
}

void 
linked_list_init(list_head_t * head)
{
    *head = 0;
}
