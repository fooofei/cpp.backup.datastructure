#ifndef LOCKFREE_LIST_H
#define LOCKFREE_LIST_H

#include <stdint.h>


struct lockfree_list_s 
{
	void * head;
	void * tail;
	int  noff;
	uint32_t count;
	struct 
	{
		void * next; // next must be the first element
	}dummy;
};

//#ifndef offset_of
//#define offset_of(str, member)	((char *)(&((str *)0)->member) - (char *)0)
//#endif

void 	lockfree_list_init(struct lockfree_list_s * l);
void 	lockfree_list_destroy(struct lockfree_list_s * l);

void 	lockfree_list_pushback(struct lockfree_list_s * l, void * m);
void 	lockfree_list_pushfront(struct lockfree_list_s * l, void *m);
void * 	lockfree_list_popfront(struct lockfree_list_s * l);
void * 	lockfree_list_popback(struct lockfree_list_s * l);
void 	lockfree_list_remove(struct lockfree_list_s * l, void * m);
uint32_t lockfree_list_count(const struct lockfree_list_s * l);
	
#endif
