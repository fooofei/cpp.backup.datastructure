
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


// #ifdef __cplusplus
// extern "C" {
// #endif

#include "linux_kernel_list.h"


// #ifdef __cplusplus
// }
// #endif


struct list_item_t
{
    uint32_t data;
    list_head_t mlist;
};

typedef list_item_t list_item_t;


// ref https://isis.poly.edu/kulesh/stuff/src/klist/
// https://kernelnewbies.org/FAQ/LinkedLists
void
test_linux_kernel_list()
{


    list_head_t list_mananger;


    memset(&list_mananger, 0, sizeof(list_mananger));
    INIT_LIST_HEAD(&list_mananger);

    /* or you could have declared this with the following macro
    * LIST_HEAD(mylist); which declares and initializes the list
    */

    /* adding elements to mylist */

    list_item_t litem1;
    list_item_t litem2;
    list_item_t litem3;
    

    memset(&litem1, 0, sizeof(litem1));
    memset(&litem2, 0, sizeof(litem2));
    memset(&litem3, 0, sizeof(litem3));


    litem1.data = 1;
    litem2.data = 2;
    litem3.data = 3;


    // add item to list
    // add  head
    list_add_tail(&litem1.mlist, &list_mananger);
    // add tail
    list_add(&litem2.mlist, &list_mananger);
    list_add_tail(&litem3.mlist, &list_mananger);

    int expect1[] = {
        2,1,3
    };
    const int * pexpect = expect1;

    struct list_head * iter = 0;
    list_item_t * pitem = 0;

    // NOTICE we need iter type of struct list_head and 
    // type of list_item_t *
    
    /* list_for_each() is a macro for a for loop.
    * first parameter is used as the counter in for loop. in other words, inside the
    * loop it points to the current item's list_head.
    * second parameter is the pointer to the list. it is not manipulated by the macro.
    */
    list_for_each(iter, &list_mananger)
    {
        // `mlist` is a member of list_item_t
        pitem = list_entry(iter, list_item_t, mlist);

        if (!(pitem->data == *pexpect))
        {
            fprintf(stderr, "%s:%d ERROR, not as expect. get %d, expect %d\n", __FILE__, __LINE__, pitem->data, *pexpect);
            exit(1);
        }

        pexpect += 1;
    }



    // the another way
    pitem = 0;
    pexpect = expect1;

#ifdef _MSC_VER
         for (pitem = list_entry((&list_mananger)->next, list_item_t, mlist);	
            &(pitem->mlist) != (&list_mananger);
             pitem = list_entry(pitem->mlist.next, list_item_t, mlist))
#else
    list_for_each_entry(pitem, &list_mananger, mlist)
#endif    
    {
        if (!(pitem->data == *pexpect))
        {
            fprintf(stderr, "%s:%d ERROR, not as expect. get %d, expect %d\n", __FILE__, __LINE__, pitem->data, *pexpect);
            exit(1);
        }

        pexpect += 1;
    }




    // and other
    // list_for_each_safe(pos, q, &mylist.list) 


    fprintf(stdout,"pass test_linux_kernel_list()\n");
}
