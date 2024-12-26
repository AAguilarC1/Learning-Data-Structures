#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define node_is_null(__node__) ((__node__) == NULL)
#define node_is_not_null(__node__) ((__node__) != NULL)

struct node {
    int data;
    struct node *next;
};
typedef struct node node_t;

node_t* n_create_node(int data);
void n_free_node(node_t* node);

void n_print_node(node_t* node);

#endif // NODE_H