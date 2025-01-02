#include <stdio.h>
#include "doubly_linked_list.h"
#include "linkedlist.h"

int main(void) 
{   
    dll_t dlist = dll_create_list(0);

    dll_add_node_head(&dlist, n_create_dnode(1));
    dll_add_node_head(&dlist, n_create_dnode(2));
    dll_add_node_tail(&dlist, n_create_dnode(3));
    dll_add_node_tail(&dlist, n_create_dnode(4));
    printf("-------Before-------\n");
    dll_print_list(&dlist);

    dl_node_t node;
    
    node = dll_remove_node_head(&dlist);
    // n_print_dnode(&node);
    node =dll_remove_node_tail(&dlist);
    // n_print_dnode(&node);
    node =dll_remove_node_at(&dlist,2);
    // n_print_dnode(&node);
    // node =dll_remove_node_head(&dlist);
    // n_print_dnode(&node);
    // node =dll_remove_node_head(&dlist);
    // n_print_dnode(&node);

    printf("-------After-------\n");
    dll_print_list(&dlist);
  
    dll_freeDeep_list(&dlist);

    return 0;
    // ll_t list = ll_create_list(0);

    // ll_insert_node_head(&list, n_create_node(1));
    // ll_insert_node_tail(&list, n_create_node(2));
    // ll_insert_node_at(&list, n_create_node(4), 1);
    // ll_print_list(&list);
    
    // ll_delete_node_tail(&list);
    // ll_delete_node_tail(&list);
    // ll_delete_node_tail(&list);
    // ll_delete_node_tail(&list);

    // ll_print_list(&list);

    // ll_freeDeep_list(&list);

    return 0;
}
