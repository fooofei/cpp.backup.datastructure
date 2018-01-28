
#include <stdio.h>
#include <string.h>
#include <iostream>

extern void
test_doubly_linked_list();

extern void
test_linux_kernel_list();

extern void
test_linked_list();

extern void
test_simple_list_in_msvc();

int main()
{

    test_doubly_linked_list();
    
    test_linux_kernel_list();

    test_linked_list();

    test_simple_list_in_msvc();

    return 0;
}
