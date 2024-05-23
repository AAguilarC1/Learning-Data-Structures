#include "../include/heap.h"

heap_t *hp_alloc_heap(unsigned int capacity)
{
    heap_t* ret;

    ret = (heap_t*)malloc(sizeof(heap_t));
    
    ret->data = (int*)calloc(capacity, sizeof(int));    
    ret->capacity = capacity;
    ret->size = 0;

    return ret;
}

void hp_insert(heap_t *heap, int value)
{
    if (heap->size >= heap->capacity)
    {
        heap->capacity *= 2;
        heap->data = (int*)realloc(heap->data, heap->capacity * sizeof(int));
    }

    heap->data[heap->size] = value;
    
    if(heap->size == 0)
    {
        heap->size++;
        return;
    }

    unsigned int parent_index = GET_PARENT_INDEX(heap->size);

    while(heap->data[heap->size] < heap->data[parent_index])
    {
        SWAP_VALUES(heap->data[heap->size], heap->data[parent_index]);
    }

    heap->size++;

}

void hp_free_deep_heap(heap_t *heap)
{
    for (unsigned int i = 0; i < heap->size; i++)
    {
        heap->data[i] = 0;
    }
    
    heap->capacity = 0;
    heap->size = 0;

    free(heap->data);
    free(heap);
}

void hp_free_heap(heap_t *heap)
{
    heap->capacity = 0;
    heap->size = 0;
    free(heap->data);
    free(heap);
}
// Path: include/heap.h
