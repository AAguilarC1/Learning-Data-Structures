#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define DEFAULT_HEAP_CAPACITY 8
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
heap_t *hp_alloc_heap_from_array(int *array, unsigned int size);

void hp_insert(heap_t *heap, int value);
int hp_extract_min(heap_t *heap);
void hp_min_heapify(heap_t *heap, unsigned int index);
void hp_print_heap(heap_t *heap);

// Frees the heap
void hp_free_deep_heap(heap_t *heap);
void hp_free_heap(heap_t *heap);

#endif // HEAP_H
// Path: src/heap.c
