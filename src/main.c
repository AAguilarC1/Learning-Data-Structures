#include <stdio.h>
#include "linkedlist.h"

int main(void) 
{   
    ll_t list = ll_create_list(0);

    ll_insert_node_head(&list, n_create_node(1));
    ll_insert_node_tail(&list, n_create_node(2));
    ll_insert_node_at(&list, n_create_node(4), 1);

    // ll_delete_node_head();
    // ll_delete_node_tail();
    // ll_delete_node_head();
    // ll_delete_node_at(0);

    // ll_print_list_from(head);
    // ll_search_full_list(4, ll_print_node);
    ll_print_list(&list);

    ll_freeDeep_list(&list);

    return 0;
}
