#include "test_binary_heap.h"
#include "binary_heap.h"
#include "test_util.h"
#include "util.h"
#include <CUnit/CUnit.h>
#include <stddef.h>

void test_binary_heap_create_free(void){
  for(size_t i = 8; i <= MAX_CAPACITY; i *= 2){
    bnt_t heap = bnt_create_bn_tree(i);
    CU_ASSERT_EQUAL(heap.size, 0);
    CU_ASSERT_EQUAL(heap.capacity, i);

    bnt_free(&heap);
    CU_ASSERT_EQUAL(heap.size, 0);
    CU_ASSERT_EQUAL(heap.capacity, 0);
    CU_ASSERT_PTR_NULL(heap.data);
  }

  size_t over_capacity = MAX_CAPACITY * 10;

  bnt_t over_cap_heap = bnt_create_bn_tree(over_capacity);
  CU_ASSERT_EQUAL(over_cap_heap.size, 0);
  CU_ASSERT_EQUAL(over_cap_heap.capacity, MAX_CAPACITY);

  bnt_freeDeep(&over_cap_heap);
  CU_ASSERT_EQUAL(over_cap_heap.size, 0);
  CU_ASSERT_EQUAL(over_cap_heap.capacity, 0);
  CU_ASSERT_PTR_NULL(over_cap_heap.data);

  int arr1[] = {1,2,3,
                5,1,2,
                7,4,8,
                0,2,1,
                4,353,4,
                3,2,46};

  bnt_t heap_from_arr = bnt_create_bn_tree_arr(arr1, 18);

  CU_ASSERT_EQUAL(heap_from_arr.size, 18);
  CU_ASSERT_EQUAL(heap_from_arr.capacity, 32);
  
  //TODO: how to test a heap has been formed correctly?

  bnt_freeDeep(&heap_from_arr);
  
  CU_ASSERT_EQUAL(heap_from_arr.size, 0);
  CU_ASSERT_EQUAL(heap_from_arr.capacity, 0);
  CU_ASSERT_PTR_NULL(heap_from_arr.data);

}

void test_binary_heap_enqueue_dequeue(void){
  bnt_t heap = bnt_create_bntree_default();
  
  int arr[11] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
              // 0   1  2  3  4  5  6  7  8  9  10

  for(size_t i = 0; i < 11; i++){
    bnt_enqueue(&heap, arr[i]);
  }

  CU_ASSERT_EQUAL(heap.size, 11);
  CU_ASSERT_EQUAL(heap.capacity, 16);

  for(size_t i = 0; i < heap.size; i++){
    CU_ASSERT_TRUE(bnt_contains(&heap, (int) i));
  }  
  
  for(int i = 10; i >= 0; i--){
    int temp = (int) bnt_dequeue(&heap);
    CU_ASSERT_EQUAL(temp,  arr[i]);
  } 

  bnt_freeDeep(&heap);
  CU_ASSERT_PTR_NULL(heap.data);
  
  bnt_t heap2 = bnt_create_bntree_default();

  for(size_t i = 3; i < 8; i++){
    int prev =-1000;
    size_t size = 1 << i;

    for(size_t j = 0; j < size; j++){
      int temp = test_random_int(10, -10);
      bnt_enqueue(&heap2, temp);
    }

    CU_ASSERT_EQUAL(heap2.capacity, size);
    CU_ASSERT_TRUE(bnt_isFull(&heap2));

    while(!(bnt_isEmpty(&heap2))){
      int curr = (int) bnt_dequeue(&heap2);
      CU_ASSERT_TRUE(curr >= prev);
      /*if(!(curr >= prev)){*/
        /*printf("capacity: %d, size: %d", heap2.capacity, heap2.size);*/
        /*printf("\ncurr: %d, prev: %d\n",curr, prev);*/
      /*}*/
      prev = curr;
    }
    CU_ASSERT_TRUE(bnt_isEmpty(&heap2));
    /*printf("capacity: %d, size: %d", heap2.capacity, heap2.size);*/
  }
  
  bnt_freeDeep(&heap2);
  CU_ASSERT_EQUAL(heap2.size, 0);
  CU_ASSERT_EQUAL(heap2.capacity, 0);
  CU_ASSERT_PTR_NULL(heap.data);

}

int test_binary_heap_suite(CU_pSuite bnt_suite){
  if(bnt_suite == NULL){
    return CUE_NOSUITE;
  }

  if(CU_add_test(bnt_suite, "Test heap_create_free", test_binary_heap_create_free) == NULL){
    return CU_get_error();
  }

  if(CU_add_test(bnt_suite, "Test heap_enqueue_dequeue", test_binary_heap_enqueue_dequeue) == NULL){
    return CU_get_error();
  }

  return CUE_SUCCESS;
}

