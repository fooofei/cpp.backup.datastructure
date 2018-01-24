
#pragma once

#include <stdint.h>
#include <stdbool.h>

// from msvc's afxtls.h 

struct simple_list_t
{
    size_t cb_next_offset;
    void * head;
};


typedef struct simple_list_t simple_list_t;


#ifdef __cplusplus
#ifdef  _WIN64
#define simple_list_offset(type,member)   (size_t)( (ptrdiff_t)&reinterpret_cast<const volatile char&>((((type *)0)->member)) )
#else
#define simple_list_offset(type,member)     (size_t)&reinterpret_cast<const volatile char&>((((type *)0)->member))
#endif

#else

#ifdef  _WIN64
#define simple_list_offset(type,member)    (size_t)( (ptrdiff_t)&(((type *)0)->member) )
#else
#define simple_list_offset(type,member)    (size_t)&(((type *)0)->member) //#define offset(s,m) (size_t)(&((s*)0)->m)
#endif

#endif	// __cplusplus 

void simple_list_construct(simple_list_t * l, size_t cb);
bool simple_list_empty(simple_list_t * l);

// get next node's address from p
void ** simple_list_get_next_ptr(simple_list_t * l, void * p);
void * simple_list_get_next(simple_list_t * l, void *p );


void simple_list_push_front(simple_list_t *, void *);
void * simple_list_peek_front(simple_list_t *);

// not free nodes's memory
void simple_list_clear(simple_list_t *);

// return 0 for found and remove success
int simple_list_remove(simple_list_t *, void *);
