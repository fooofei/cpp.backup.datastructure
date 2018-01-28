

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "list.h"

#ifdef __cplusplus
}
#endif

#define EXPECT(expr) do\
    {\
    if (!(expr))\
    {\
        fprintf(stderr, "unexpect "#expr" %s:%d\n", __FILE__, __LINE__);\
        fflush(stderr);\
    }\
    } while (0)


void visit(int* a)
{
    printf("%d ", *a);
}

bool compare(int a, int b)
{
    return a == b;
}

int main()
{
    
    
    sqlist_t L;
    memset(&L, 0, sizeof(L));
    sqlist_init(&L);
    EXPECT(sqlist_empty(&L));

    EXPECT(sqlist_insert(&L, 1, 11));
    EXPECT(sqlist_insert(&L, 2, 13));
    EXPECT(sqlist_insert(&L, 1, 12));

    EXPECT(!sqlist_empty(&L));
    EXPECT(3 == sqlist_length(&L));


    printf("打印线性表:");
    sqlist_travel(&L, visit);
    printf("\n");

    int e = 0;

    EXPECT(sqlist_index_at(&L, 1, &e));
    EXPECT(12 == e);
    
    EXPECT(sqlist_index_at(&L, sqlist_locate_elem(&L, 13, compare), &e));
    EXPECT(13 == e);

    
    sqlist_prior_elem(&L, 13, &e);
    EXPECT(11 == e);

    sqlist_next_elem(&L, 11, &e);
    EXPECT(13 == e);
   
    sqlist_delete(&L, 3, &e);
    EXPECT(13 == e);

    sqlist_travel(&L, visit);
    printf("\n");

    EXPECT(sqlist_destroy(&L));
    
    // 	SqList La,Lb, Lc;
    // 
    // 	InitList(&La);
    // 	InitList(&Lb);
    // 
    // 	ListInsert(&La,1,11);
    // 	ListInsert(&La,2,12);
    // 	ListInsert(&Lb,1,110);
    // 	ListInsert(&Lb,2,13);
    // 
    // 	SortList(&La);
    // 	SortList(&Lb);
    // 	MergeList(La,Lb,&Lc);
    // 	ListTravel(Lc,visit);
    //   
    // 
    // 	DestroyList(&La);
    // 	DestroyList(&Lb);
    // 	DestroyList(&Lc);



    return 0;
}
