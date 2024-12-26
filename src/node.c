#include "node.h"

node_t* n_create_node(int data){

    node_t* node = (node_t*)malloc(sizeof(node_t));
    assert(node_is_not_null(node) && "Memory allocation failed");

    node->data = data;
    node->next = NULL;
    return node;
}

void n_print_node(node_t* node){
    if(node_is_null(node)){
        printf("Node is null\n");
        return;
    }
    printf("Node : {ref = %p; data = %d, next = %p}\n", node, node->data, node->next);
}

void n_free_node(node_t* node){
    if(node_is_null(node)){
        return;
    }

    node->data = 0;
    free(node);
}
