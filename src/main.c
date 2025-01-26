#include <stdio.h>
#include "../include/heap.h"

int main(void) 
{   
    heap_t *heap = hp_alloc_heap(10);
    hp_insert(heap, 10);
    hp_insert(heap, 30);
    hp_insert(heap, 20);
    hp_print_heap(heap);
    hp_free_deep_heap(heap);
    return 0;
}
