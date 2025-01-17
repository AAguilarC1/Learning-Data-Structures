#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include<stdio.h>
#include<stdlib.h>
#include "dynamical_array.h"
#include "util.h"

#define MAX_CAPACITY 255
#define INITIAL_CAPACITY 8
#define ELEMENT  int* // This can later be change to void * to generalise the binary tree 

#define bnt_create_bntree_default() bnt_create_bntree(INITIAL_CAPACITY)
#define bnt_get_prnt_index(__index__)     (__index__)/2
#define bnt_get_lchild_index(__index__)   (2 * (__index__) - 1) + 1
#define bnt_get_rchild_index(__index__)   (2 * (__index__) - 1) + 2
#define bnt_get_Capacity(__root__) (__root__)->capacity

#define bnt_isNull(__root__) (__root__) == NULL
#define bnt_isNotNull(__root__) (__root__) != NULL
#define bnt_isEmpty(__root__) (__root__)->size == 0
#define bnt_isFull(__root__) (__root__)->size == (__root__)->capacity

#define BNT_MAX_HEAP 0
#define BNT_MIN_HEAP 1

#define BNT_COMPARE_LOGIC BNT_MIN_HEAP

#if BNT_COMPARE_LOGIC == BNT_MIN_HEAP
#define bnt_compare(__val1__, __val2__) (__val1__) < (__val2__)
#elif BNT_COMPARE_LOGIC == BNT_MAX_HEAP
#define bnt_compare(__val1__, __val2__) (__val1__) > (__val2__)
#else 
#define bnt_compare(__val1__, __val2__) (__val1__) < (__val2__)
#endif

#define bnt_swap(__A__, __B__) {\ 
    int __TMP__ = (__A__);\
    (__A__) = (__B__);\
    (__B__) = __TMP__;\
}

typedef enum status bnt_stat_t;

struct binary_tree {
  size_t size;
  size_t capacity;
  ELEMENT data;
};

typedef struct binary_tree bnt_t;

bnt_t bnt_create_bn_tree(int capacity);
bnt_t bnt_create_bn_tree_arr(ELEMENT arr, size_t length_arr);
bnt_stat_t bnt_heapify(bnt_t* root, int index);

void bnt_bubble_up(bnt_t* root, int index);
bnt_stat_t bnt_enqueue(bnt_t* root, ELEMENT value);
ELEMENT bnt_dequeue(bnt_t* root);

bnt_stat_t bnt_contains(bnt_t* root, ELEMENT value);
bnt_stat_t bnt_index_of(bnt_t* root, dn_arr_t* indexes, size_t curr_index, ELEMENT value);

void bnt_free(bnt_t* root);
void bnt_freeDeep(bnt_t* root);

#endif

