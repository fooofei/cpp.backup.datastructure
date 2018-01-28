
#pragma once

#include <stdint.h>
#include <stdbool.h> // c not have bool



#ifdef _MSC_VER // not work
 // #pragma warning(disable:4819) //chinese chars in utf-8 files
#endif

/*
  1 list's item is void *
  2 list use noff, poff to caculate the next and prev 's offset 
    use *() to get the next node's address.
  
  3 this list is not malloc memory
  4 iter is a single linked list
*/


struct list
{
    void * first;
    void * last;
    
    uint32_t noff;
    uint32_t poff;
    // struct list_iterator_t * iter; // need to bind ? 
};

typedef struct list list_t;


struct list_iterator
{
    list_t * list;
    void * cur;
};

typedef struct list_iterator list_iterator_t;


// for list_init()
#ifndef list_offset_of
#define list_offset_of(type, member)	((char *)(&((type *)0)->member) - (char *)0)
#endif

void list_init(list_t *, uint32_t next_offset, uint32_t prev_offset);


void list_clear(list_t *);

void list_push_front(list_t *, void *);
void list_push_back(list_t *, void *);
void list_pop_front(list_t *, void **);
void list_pop_back(list_t *, void **);
uint32_t list_count(list_t *);
bool list_empty(list_t *);


void list_iterator_set(list_iterator_t *, list_t *);

/* return value same with param, for convenient of if condition */
void * list_iterator_get(list_iterator_t *, void **);
void list_iterator_end(list_iterator_t *);



