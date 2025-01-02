#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define node_is_null(__node__) ((__node__) == NULL)
#define node_is_not_null(__node__) ((__node__) != NULL)

struct single_node {
    int data;
    struct single_node *next;
};
typedef struct single_node sl_node_t;

sl_node_t* n_create_node(int data);
void n_free_node(sl_node_t* node);

void n_print_node(node_t* node);

#endif // NODE_H