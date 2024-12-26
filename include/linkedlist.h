#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "node.h"

#define ll_is_empty(__list__) ((__list__)->length == 0)
#define ll_is_null(__list__) ((__list__) == NULL)
#define ll_is_not_null(__list__) ((__list__) != NULL)
#define ll_is_tail(__list__, __node__) ((__list__)->tail == (__node__))
#define ll_is_not_tail(__list__, __node__) ((__list__)->tail != (__node__))

struct list {
    size_t length;
    node_t* head;
    const node_t* tail;
};
typedef struct list ll_t;

ll_t ll_create_list(int data);

void ll_insert_node_head(ll_t* list, node_t* node);
void ll_insert_node_tail(ll_t* list, node_t* node);
void ll_insert_node_at(ll_t* list, node_t* node, uint32_t index);

node_t ll_delete_node_head(ll_t* list);
node_t ll_delete_node_tail(ll_t* list);
node_t ll_delete_node_at(ll_t* list, uint32_t index);

void ll_travel_list(ll_t* list, void (*callback)(void*));
void ll_search_list_from(ll_t* list, int data, void (*callback)(void*));
size_t ll_length(ll_t* list);

int ll_peek_head(ll_t* list);
int ll_peek_tail(ll_t* list);
int ll_peek_at(ll_t* list, uint32_t index);

void ll_print_list(ll_t* list);
void ll_print_list_from(ll_t* list, node_t* node);

void ll_free_list(ll_t* list);
void ll_freeDeep_list(ll_t* list);

#endif // LINKED_LIST_H