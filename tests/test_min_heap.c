#include "test_min_heap.h"
// Test case
void testAllocateHeap() {
    heap_t *heap = hp_alloc_heap(10);
    CU_ASSERT_PTR_NOT_NULL(heap);
    CU_ASSERT_EQUAL(heap->size, 0);
    CU_ASSERT_EQUAL(heap->capacity, 10);
    CU_ASSERT_PTR_NOT_NULL(heap->data);
    CU_ASSERT_EQUAL(heap->data[0], 0);
    hp_free_deep_heap(heap);
}

void testAllocateHeapFromArray()
{
    int data[] = {5, 4, 3, 2, 1};
    unsigned int size = sizeof(data) / sizeof(data[0]);

    heap_t *heap = hp_alloc_heap_from_array(data, size);

    CU_ASSERT_PTR_NOT_NULL(heap);
    CU_ASSERT_EQUAL(heap->size, size);
    CU_ASSERT_EQUAL(heap->capacity, DEFAULT_HEAP_CAPACITY);

    CU_ASSERT_PTR_NOT_NULL(heap->data);
    CU_ASSERT_EQUAL(heap->data[0], 1);
    CU_ASSERT_EQUAL(heap->data[1], 2);
    CU_ASSERT_EQUAL(heap->data[2], 3);
    CU_ASSERT_EQUAL(heap->data[3], 5);
    CU_ASSERT_EQUAL(heap->data[4], 4);

    hp_free_deep_heap(heap);

}

void testInsertIntoHeapArray()
{
    int data[] = {5, 4, 3, 2, 1};
    unsigned int size = sizeof(data) / sizeof(data[0]);

    heap_t *heap = hp_alloc_heap_from_array(data, size);
    hp_insert(heap, 6);

    CU_ASSERT_EQUAL(heap->size, 6);
    CU_ASSERT_EQUAL(heap->capacity, DEFAULT_HEAP_CAPACITY);
    CU_ASSERT_EQUAL(heap->data[0], 1);
    CU_ASSERT_EQUAL(heap->data[1], 2);
    CU_ASSERT_EQUAL(heap->data[2], 3);
    CU_ASSERT_EQUAL(heap->data[3], 5);
    CU_ASSERT_EQUAL(heap->data[4], 4);
    CU_ASSERT_EQUAL(heap->data[5], 6);

    hp_free_deep_heap(heap);

}

void testInsert()
{
    heap_t *heap = hp_alloc_heap(5);
    
    hp_insert(heap, 5);
    CU_ASSERT_EQUAL(heap->size, 1);
    CU_ASSERT_EQUAL(heap->data[0], 5);

    hp_insert(heap, 3);
    CU_ASSERT_EQUAL(heap->size, 2);
    CU_ASSERT_EQUAL(heap->data[0], 3);
    CU_ASSERT_EQUAL(heap->data[1], 5);

    hp_insert(heap, 7);
    CU_ASSERT_EQUAL(heap->size, 3);
    CU_ASSERT_EQUAL(heap->data[0], 3);
    CU_ASSERT_EQUAL(heap->data[1], 5);
    CU_ASSERT_EQUAL(heap->data[2], 7);

    hp_insert(heap, 1);
    CU_ASSERT_EQUAL(heap->size, 4);
    CU_ASSERT_EQUAL(heap->data[0], 1);
    CU_ASSERT_EQUAL(heap->data[1], 3);
    CU_ASSERT_EQUAL(heap->data[2], 7);
    CU_ASSERT_EQUAL(heap->data[3], 5);

    hp_insert(heap, 2);
    CU_ASSERT_EQUAL(heap->size, 5);
    CU_ASSERT_EQUAL(heap->data[0], 1);
    CU_ASSERT_EQUAL(heap->data[1], 2);
    CU_ASSERT_EQUAL(heap->data[2], 7);
    CU_ASSERT_EQUAL(heap->data[3], 5);
    CU_ASSERT_EQUAL(heap->data[4], 3);
    
    hp_insert(heap, 6);
    CU_ASSERT_EQUAL(heap->size, 6);
    CU_ASSERT_EQUAL(heap->data[0], 1);
    CU_ASSERT_EQUAL(heap->data[1], 2);
    CU_ASSERT_EQUAL(heap->data[2], 6);
    CU_ASSERT_EQUAL(heap->data[3], 5);
    CU_ASSERT_EQUAL(heap->data[4], 3);
    CU_ASSERT_EQUAL(heap->data[5], 7);
    CU_ASSERT_EQUAL(heap->capacity, 10);

    hp_free_deep_heap(heap);
}

int test_min_heap_suite(CU_pSuite min_heap_suite){
    if(NULL == CU_add_test(min_heap_suite, "testAllocateHeap", testAllocateHeap)){
        CU_cleanup_registry();
        return -1;
    }
        
    if (NULL == CU_add_test(min_heap_suite, "testInsert", testInsert)) {
        CU_cleanup_registry();
        return -1;
    }

    if (NULL == CU_add_test(min_heap_suite, "testAllocateHeapFromArray", testAllocateHeapFromArray)) {
        CU_cleanup_registry();
        return -1;
    }

    if (NULL == CU_add_test(min_heap_suite, "testInsertIntoHeapArray", testInsertIntoHeapArray)) {
        CU_cleanup_registry();
        return -1;
    }

    return 0;
}
