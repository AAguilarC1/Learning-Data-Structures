#include "node.h"
sl_node_t* n_create_node(int data){

    sl_node_t* node = (sl_node_t*)malloc(sizeof(sl_node_t));
    assert(node_is_not_null(node) && "Memory allocation failed");

    node->data = data;
    node->next = NULL;
    return node;
}

void n_print_node(sl_node_t* node){
    if(node_is_null(node)){
        printf("Node is null\n");
        return;
    }
    printf("Node : {ref = %p; data = %d, next = %p}\n", node, node->data, node->next);
}

void n_free_node(sl_node_t* node){
    if(node_is_null(node)){
        return;
    }

    node->data = 0;
    node->next = NULL;
    free(node);
}

dl_node_t* n_create_dnode(int data){
    dl_node_t* node = (dl_node_t*)malloc(sizeof(dl_node_t));
    assert(node_is_not_null(node) && "Memory allocation failed");

    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void n_print_dnode(dl_node_t* node){
    if(node_is_null(node)){
        printf("Node is null\n");
        return;
    }
    printf("Node : {ref = %p; data = %d, next = %p, prev = %p}\n", node, node->data, node->next, node->prev);
}

void n_free_dnode(dl_node_t* node){
    if(node_is_null(node)){
        return;
    }

    node->data = 0;
    node->next = NULL;
    node->prev = NULL;
    free(node);
}