#include <stdio.h>
#include "../include/linkedlist.h"

int main(void) 
{   
    head = ll_create_node(2);

    ll_insert_node_head(ll_create_node(1));
    ll_insert_node_tail(ll_create_node(3));
    ll_insert_node_at(ll_create_node(4), 1);

    // ll_delete_node_head();
    // ll_delete_node_tail();
    // ll_delete_node_head();
    // ll_delete_node_at(0);

    printf("Length: %zu\n", ll_length());

    ll_print_list_from(head);
    ll_search_full_list(4, ll_print_node);

    ll_freeDeep_node(head);

    return 0;
}
