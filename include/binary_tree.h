#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include<stdio.h>
#include<stdlib.h>

#define MAX_CAPACITY 255
#define INITIAL_CAPACITY 8
#define ELEMENT  int*

#define bnt_create_bntree_default(void) bnt_create_bntree(INITIAL_CAPACITY)
#define bnt_get_prnt(__child_index__)    ((__child_index__) - 1)/2
#define bnt_get_lchld(__parent_index__)  (2 * (__parent_index__)) + 1
#define bnt_get_rchld(__parent_index__)  (2 * (__parent_index__)) + 2

struct binary_tree {
  size_t size;
  size_t capacity;
  ELEMENT nodes;
};

typdef struct binary_tree bnt_t;

bnt_t bnt_create_bn_tree(int capacity);
int bnt_enqueue(bnt_t* root, int data);

void bnt_free_bn_tree(bnt_t *root);
void bnt_freeDeep_bn_tree(bnt_t *root);

#endif

