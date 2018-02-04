

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


extern "C" {
#include "doublelist.h"

}

#define EXPECT(expr) \
    do { \
    if(!(expr)) \
        { \
        fprintf(stderr, "unexpect %s  (%s:%d)\n",#expr, __FILE__, __LINE__); \
        fflush(stderr);\
        } \
    } while (0)


typedef struct item
{
    doublelist_t list;
    int data;
}item_t;


void visit(const doublelist_t * v)
{
    const item_t * p = (const item_t *)v;
    printf("%d ", p->data);
}


void
test_doublelist1()
{

    doublelist_t head;
    int count_node = 0;
    int i;
    item_t * tmp;
    doublelist_t * p;
    const int size = 5;

    doublelist_init(&head);

    EXPECT(doublelist_empty(&head));

    for (i=0;i<size;i+=1)
    {
        tmp = (item_t*)calloc(1, sizeof(item_t));
        count_node += 1;

        tmp->data = i + 1;
        doublelist_push_back(&head, &(tmp->list));
    }

    EXPECT(size == doublelist_length(&head));

    

    for (i=1;(doublelist_pop_front(&head,&p));i+=1)
    {
        tmp = (item_t *)p;
        EXPECT(tmp->data == i);
        
        free(p);
        count_node -= 1;
    }

    EXPECT(doublelist_empty(&head));

    EXPECT(count_node == 0);

    printf("pass %s()\n", __FUNCTION__);
}


void
test_doublelist2()
{

    doublelist_t head;
    int count_node = 0;
    int i;
    item_t * tmp;
    doublelist_t * p;
    const int size = 5;

    doublelist_init(&head);

    EXPECT(doublelist_empty(&head));

    for (i = 0; i < size; i += 1)
    {
        tmp = (item_t*)calloc(1, sizeof(item_t));
        count_node += 1;

        tmp->data = i + 1;
        doublelist_push_front(&head, &(tmp->list));
    }

    EXPECT(size == doublelist_length(&head));



    for (i = 1; (doublelist_pop_back(&head,&p)); i += 1)
    {
        tmp = (item_t *)p;
        EXPECT(tmp->data == i);

        free(p);
        count_node -= 1;
    }

    EXPECT(doublelist_empty(&head));

    EXPECT(count_node == 0);

    printf("pass %s()\n", __FUNCTION__);
}

void
test_doublelist3()
{

    doublelist_t head;
    int count_node = 0;
    int i;
    item_t * tmp;
    doublelist_t * p;
    const int size = 5;

    doublelist_init(&head);

    EXPECT(doublelist_empty(&head));

    for (i = 0; i < size; i += 1)
    {
        tmp = (item_t*)calloc(1, sizeof(item_t));
        count_node += 1;

        tmp->data = i + 1;
        doublelist_push_front(&head, &(tmp->list));
    }

    EXPECT(size == doublelist_length(&head));



    for (i = size; (doublelist_pop_front(&head,&p)); i -= 1)
    {
        tmp = (item_t *)p;
        EXPECT(tmp->data == i);

        free(p);
        count_node -= 1;
    }

    EXPECT(doublelist_empty(&head));

    EXPECT(count_node == 0);

    printf("pass %s()\n", __FUNCTION__);
}

void
test_doublelist4()
{

    doublelist_t head;
    int count_node = 0;
    int i;
    item_t * tmp;
    doublelist_t * p;
    const int size = 5;

    doublelist_init(&head);

    EXPECT(doublelist_empty(&head));

    for (i = 0; i < size; i += 1)
    {
        tmp = (item_t*)calloc(1, sizeof(item_t));
        count_node += 1;

        tmp->data = i + 1;
        doublelist_push_back(&head, &(tmp->list));
    }

    EXPECT(size == doublelist_length(&head));

    for (i=0;i<size;i+=1)
    {
        EXPECT(doublelist_get(&head, i + 1, &p));
        tmp = (item_t *)p;
        EXPECT(tmp->data == i + 1);
    }

    EXPECT(size == doublelist_length(&head));

    for (i = 0; i < size; i += 1)
    {
        EXPECT(doublelist_rget(&head, size - i, &p));
        tmp = (item_t *)p;
        EXPECT(tmp->data == i + 1);
    }

    EXPECT(size == doublelist_length(&head));

    for (i = size; (doublelist_pop_front(&head,&p)); i -= 1)
    {
        free(p);
        count_node -= 1;
    }

    EXPECT(doublelist_empty(&head));

    EXPECT(count_node == 0);

    printf("pass %s()\n", __FUNCTION__);
}

void
test_doublelist5()
{

    doublelist_t head;
    int count_node = 0;
    int i;
    item_t * tmp;
    doublelist_t * p;
    doublelist_t *p2;
    const int size = 5;

    doublelist_init(&head);

    EXPECT(doublelist_empty(&head));

    for (i = 0; i < size; i += 1)
    {
        tmp = (item_t*)calloc(1, sizeof(item_t));
        count_node += 1;

        tmp->data = i + 1;
        doublelist_push_back(&head, &(tmp->list));
    }

    EXPECT(size == doublelist_length(&head));

    EXPECT(doublelist_get(&head, 3, &p));

    p2 = 0;
    EXPECT(doublelist_prior(&head, p, &p2));
    tmp = (item_t *)p2;
    EXPECT(tmp->data == 2);

    p2 = 0;
    EXPECT(doublelist_next(&head, p, &p2));
    tmp = (item_t *)p2;
    EXPECT(tmp->data == 4);


    EXPECT(doublelist_get(&head, 1, &p));
    EXPECT(!doublelist_prior(&head, p, &p2));
    EXPECT(doublelist_next(&head, p, &p2));
    tmp = (item_t *)p2;
    EXPECT(tmp->data == 2);


    EXPECT(doublelist_get(&head, size, &p));
    EXPECT(doublelist_prior(&head, p, &p2));
    tmp = (item_t *)p2;
    EXPECT(tmp->data == size - 1);
    EXPECT(!doublelist_next(&head, p, &p2));



    for (i = size; (doublelist_pop_front(&head,&p)); i -= 1)
    {
        free(p);
        count_node -= 1;
    }

    EXPECT(doublelist_empty(&head));

    EXPECT(count_node == 0);

    printf("pass %s()\n", __FUNCTION__);
}

void
test_doublelist6()
{

    doublelist_t head;
    int count_node = 0;
    int i;
    item_t * tmp;
    doublelist_t * p;
    const int size = 5;

    doublelist_init(&head);

    EXPECT(doublelist_empty(&head));


    // insert 1
    for (i = 0; i < size; i += 1)
    {
        tmp = (item_t*)calloc(1, sizeof(item_t));
        count_node += 1;

        tmp->data = i + 1;
        doublelist_insert(&head, i + 10, &(tmp->list));
       // doublelist_push_back(&head, &(tmp->list));
    }
    EXPECT(size == doublelist_length(&head));

   
    for (i = size; (doublelist_pop_back(&head,&p)); i -= 1)
    {
        tmp = (item_t *)p;
        EXPECT(tmp->data == i);

        free(p);
        count_node -= 1;
    }
    EXPECT(doublelist_empty(&head));
    EXPECT(count_node == 0);


    // insert 2
    for (i = 0; i < size; i += 1)
    {
        tmp = (item_t*)calloc(1, sizeof(item_t));
        count_node += 1;

        tmp->data = i + 1;
        doublelist_insert(&head, 0, &(tmp->list));
        // doublelist_push_front(&head, &(tmp->list));
    }

    EXPECT(size == doublelist_length(&head));
    for (i = size; (doublelist_pop_front(&head,&p)); i -= 1)
    {
        tmp = (item_t *)p;
        EXPECT(tmp->data == i);

        free(p);
        count_node -= 1;
    }
    EXPECT(doublelist_empty(&head));
    EXPECT(count_node == 0);

    printf("pass %s()\n", __FUNCTION__);
}


void
test_doublelist7()
{

    doublelist_t head;
    int count_node = 0;
    int i;
    item_t * tmp;
    doublelist_t * p;
    const int size = 5;

    doublelist_init(&head);

    EXPECT(doublelist_empty(&head));

    for (i = 0; i < size; i += 1)
    {
        tmp = (item_t*)calloc(1, sizeof(item_t));
        count_node += 1;

        tmp->data = i + 1;
        doublelist_push_back(&head, &(tmp->list));
    }

    EXPECT(size == doublelist_length(&head));


    for (;doublelist_back(&head,&p);)
    {
        EXPECT(doublelist_remove(&head, p));
        free(p);
        count_node -= 1;
    }



    EXPECT(doublelist_empty(&head));

    EXPECT(count_node == 0);

    printf("pass %s()\n", __FUNCTION__);
}


int main()
{
    test_doublelist1();
    test_doublelist2();
    test_doublelist3();
    test_doublelist4();
    test_doublelist5();
    test_doublelist6();
    test_doublelist7();
    return 0;
}
