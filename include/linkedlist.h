#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define ll_is_empty() ((head) == NULL)
#define ll_is_null(__node__) ((__node__) == NULL)
#define ll_is_not_null(__node__) ((__node__) != NULL)
#define ll_travel_full_list(__callback__) ll_travel_list((__callback__), head)
#define ll_search_full_list(__data__, __callback__) ll_search_list_from((__data__), (__callback__), head)

struct node {
    int data;
    struct node *next;
};
typedef struct node node_t;

extern node_t* head;
extern node_t* tail;

node_t* ll_create_node(int data);

void ll_insert_node_head(node_t* node);
void ll_insert_node_tail(node_t* node);
void ll_insert_node_at(node_t* node, uint32_t index);

node_t ll_delete_node_head();
node_t ll_delete_node_tail();
node_t ll_delete_node_at(uint32_t index);

void ll_travel_list(void (*callback)(void*), node_t* node);
void ll_search_list_from(int data, void (*callback)(void*), node_t* node);
size_t ll_length();

int ll_peek_head();
int ll_peek_tail();
int ll_peek_at(uint32_t index);

void ll_print_node(node_t* node);
void ll_print_list();
void ll_print_list_from(node_t* node);

void ll_free_node(node_t* node);
void ll_freeDeep_node(node_t* node);

#endif // LINKED_LIST_H