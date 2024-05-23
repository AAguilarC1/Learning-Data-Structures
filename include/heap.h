#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>

#define GET_PARENT_INDEX(__INDEX__) (((__INDEX__) - 1) / 2)
#define SWAP_VALUES(__A__, __B__) { \
    int __TMP__ = (__A__);\
    (__A__) = (__B__);\
    (__B__) = __TMP__;\
}

struct heap {
    int *data;
    unsigned int size;
    unsigned int capacity;
};

typedef struct heap heap_t;

// Function prototypes

// Allocates a new heap with the given capacity
heap_t *hp_alloc_heap(unsigned int capacity);
void hp_insert(heap_t *heap, int value);

// Frees the heap
void hp_free_deep_heap(heap_t *heap);
void hp_free_heap(heap_t *heap);

#endif // HEAP_H
// Path: src/heap.c
