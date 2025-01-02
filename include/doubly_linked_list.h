#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <stdlib.h>
#include <stdio.h>
#include "node.h"

#define dll_is_empty(__list__) ((__list__)->length == 0)
#define dll_is_null(__list__) ((__list__) == NULL)
#define dll_is_not_null(__list__) ((__list__) != NULL)
#define dll_length(__list__) ((__list__)->length)

typedef dl_node_t dnode_t;

struct dl_list {
    dnode_t* head;
    dnode_t* tail;
    unsigned int length;
};
typedef struct dl_list dll_t;

dll_t dll_create_list(int data);

int dll_add_node_head(dll_t* list, dnode_t* node);
int dll_add_node_tail(dll_t* list, dnode_t* node);
int dll_insert_node_at(dll_t* list, dnode_t* node, unsigned int index);

dnode_t dll_remove_node_head(dll_t* list);
dnode_t dll_remove_node_tail(dll_t* list);
dnode_t dll_remove_node_at(dll_t* list, unsigned int index);

int dll_print_list(dll_t* list);

void dll_free_list(dll_t* list);
void dll_freeDeep_list(dll_t* list);

#endif // DOUBLY_LINKED_LIST_H
