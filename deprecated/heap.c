#include "heap.h"

heap_t *hp_alloc_heap(unsigned int capacity)
{
    heap_t* ret;

    ret = (heap_t*)malloc(sizeof(heap_t));
    
    ret->data = (int*)calloc(capacity, sizeof(int));    
    ret->capacity = capacity;
    ret->size = 0;

    return ret;
}

heap_t *hp_alloc_heap_from_array(int *array, unsigned int size)
{
    heap_t* ret = (heap_t*)malloc(sizeof(heap_t));
    
    unsigned int capacity = DEFAULT_HEAP_CAPACITY;

    while (capacity < size)
    {
        capacity *= 2;
    }

    ret->data = (int*)calloc(capacity, sizeof(int));    
    ret->capacity = capacity;
    ret->size = size;

    for(unsigned int i = 0; i < size; i++)
    {
        ret->data[i] = array[i];
    }

    int i = (size - 2) / 2;

    while(i >= 0)
    {
        hp_min_heapify(ret, i);
        i--;
    }

    return ret;

}

int hp_extract_min(heap_t *heap)
{
    int ret;
    
    if(heap->size == 0)
    {
        return -1;
    }

    ret = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    hp_min_heapify(heap, 0);

    return ret;
}

void hp_min_heapify(heap_t *heap, unsigned int index)
{
    assert(heap != NULL);

    int left_child  = 2 * index + 1;
    int right_child = 2 * index + 2;
    int min         = index;

    if (left_child >= (int) heap->size || left_child < 0)
    {
        left_child = -1;
    }

    if (right_child >= (int) heap->size || right_child < 0)
    {
        right_child = -1;
    }

    // assert(left_child < heap->size);
    // assert(right_child < heap->size);

    if (left_child != -1 && heap->data[left_child] < heap->data[index])
    {
        min = left_child;
    }

    if (right_child != -1 && heap->data[right_child] < heap->data[min])
    {
        min = right_child;
    }

    if (min != (int) index)
    {
        SWAP_VALUES(heap->data[index], heap->data[min]);
        hp_min_heapify(heap, min);
    }

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

    unsigned int parent_index = 0;

    for(unsigned int i = heap->size; i > 0; i = parent_index)
    {
        parent_index = GET_PARENT_INDEX(i);

        if(heap->data[i] < heap->data[parent_index] && parent_index >= 0)
        {
            SWAP_VALUES(heap->data[i], heap->data[parent_index]);
        }
        else
        {
            break;
        }
    }

    heap->size++;

}

/**
 * @brief This function frees the heap without freeing its elements
 * 
 * @param heap - The heap to be freed
 */
void hp_free_heap(heap_t *heap)
{
    heap->capacity = 0;
    heap->size = 0;
    free(heap->data);
    free(heap);
}


/**
 * @brief This function frees the heap and all its elements
 * 
 * @param heap - The heap to be freed
 */
void hp_free_deep_heap(heap_t *heap)
{
    for (unsigned int i = 0; i < heap->size; i++)
    {
        heap->data[i] = 0;
    }

    hp_free_heap(heap);
}

void hp_print_heap(heap_t *heap)
{
    for(unsigned int i = 0; i < heap->size; i++)
    {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// Path: include/heap.h
