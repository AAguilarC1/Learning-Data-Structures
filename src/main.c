#include <stdio.h>
#include "linkedlist.h"

int main(void) 
{   
    ll_t list = ll_create_list(0);

    ll_insert_node_head(&list, n_create_node(1));
    ll_insert_node_tail(&list, n_create_node(2));
    ll_insert_node_at(&list, n_create_node(4), 1);
    ll_print_list(&list);
    
    ll_delete_node_head(&list);
    ll_delete_node_tail(&list);
    ll_delete_node_head(&list);
    ll_delete_node_at(&list, 0);

    ll_print_list(&list);

    ll_freeDeep_list(&list);

    return 0;
}
