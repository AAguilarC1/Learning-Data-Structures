#include <stdio.h>
#include "../include/heap.h"

int main(void) 
{   
    heap_t *heap = hp_alloc_heap(10);
    hp_insert(heap, 10);
    hp_insert(heap, 20);
    hp_insert(heap, 30);
    hp_free_deep_heap(heap);
    printf("Hello, World!\n");
    return 0;
}
