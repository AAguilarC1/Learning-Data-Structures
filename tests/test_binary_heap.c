#include "test_binary_heap.h"
#include "binary_heap.h"
#include "test_linkedlist.h"
#include "test_util.h"
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdbool.h>
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
  const int limits = 20;

  for(size_t i = 3; i <= 8; i++){
    int prev = -1000;
    size_t size = 1 << i;
    /*size_t c = 1;*/

    for(size_t j = 0; j < size; j++){
      int temp = test_random_int(limits, -limits);
      bnt_enqueue(&heap2, temp);
    }

    CU_ASSERT_EQUAL(heap2.capacity, size);
    CU_ASSERT_TRUE(bnt_isFull(&heap2));

    while(!(bnt_isEmpty(&heap2))){
      int curr = (int) bnt_dequeue(&heap2);
      CU_ASSERT_TRUE(curr >= prev);
      /*printf("%li. prev: %d, curr %d\n",c, prev, curr);*/
      /*c++;*/
      prev = curr;
    }
    CU_ASSERT_TRUE(bnt_isEmpty(&heap2));
  }
  
  bnt_freeDeep(&heap2);
  CU_ASSERT_EQUAL(heap2.size, 0);
  CU_ASSERT_EQUAL(heap2.capacity, 0);
  CU_ASSERT_PTR_NULL(heap.data);

}

void test_binary_heap_peek(void){
  bnt_t heap = bnt_create_bn_tree(MAX_CAPACITY);
  int top; 
  for(size_t i = 1; i <= MAX_CAPACITY; i++){
    bnt_enqueue(&heap, (int*) i );
  }

  for(size_t i = 1; i <= MAX_CAPACITY; i++){
    bnt_peek_top(&heap, &top);
    CU_ASSERT_EQUAL(top, i);
    bnt_dequeue(&heap);
  }

  bnt_freeDeep(&heap); 
}

void test_binary_heap_merge(void){
  const int value_limit = 10;
  for(size_t i = 4; i < 8; i++){
    int prev = -1000;
    size_t cap_heap1 = 1 << i;
    size_t cap_heap2 = 1 << i;
    size_t size1 = test_random_int(cap_heap1, 8);
    size_t size2 = test_random_int(cap_heap2, 8);
    size_t total_size = size2 + size1;

    bnt_t heap1 = bnt_create_bn_tree(cap_heap1);
    bnt_t heap2 = bnt_create_bn_tree(cap_heap2);
    
    for(size_t j = 1; j <= size1; j++){
      int temp = test_random_int(value_limit, -value_limit);
      bnt_enqueue(&heap1, temp);
    }

    for(size_t j = 1; j <= size2; j++){
      int temp = test_random_int(value_limit, -value_limit);
      bnt_enqueue(&heap2, temp);
    }

    bnt_merge_heaps(&heap1, &heap2);
    CU_ASSERT_EQUAL(heap1.size, total_size);
    CU_ASSERT_TRUE(!(bnt_isEmpty(&heap2)));
    CU_ASSERT_TRUE(heap2.size == size2);
    CU_ASSERT_TRUE(heap2.capacity == cap_heap2);
    CU_ASSERT_PTR_NOT_NULL(&heap2.data);

    while(!(bnt_isEmpty(&heap1))){
      int curr = (int) bnt_dequeue(&heap1);
      CU_ASSERT_TRUE(curr >= prev);
      if(!(curr >= prev)){
        printf("\ncurr: %d, prev: %d\n", curr, prev);
      }
      prev = curr;
    }

    bnt_freeDeep(&heap1);
    bnt_freeDeep(&heap2);
  }
  
  for(size_t i = 4; i < 8; i++){
    int prev = -1000;
    size_t cap_heap1 = 1 << i;
    size_t cap_heap2 = 1 << i;
    size_t size1 = test_random_int(cap_heap1, 8);
    size_t size2 = test_random_int(cap_heap2, 8);
    size_t total_size = size2 + size1;

    bnt_t heap1 = bnt_create_bn_tree(cap_heap1);
    bnt_t heap2 = bnt_create_bn_tree(cap_heap2);
    
    for(size_t j = 1; j <= size1; j++){
      int temp = test_random_int(value_limit, -value_limit);
      bnt_enqueue(&heap1, temp);
    }

    for(size_t j = 1; j <= size2; j++){
      int temp = test_random_int(value_limit, -value_limit);
      bnt_enqueue(&heap2, temp);
    }

    bnt_merge_heaps_consumer(&heap1, &heap2);

    CU_ASSERT_EQUAL(heap1.size, total_size);
    CU_ASSERT_TRUE(bnt_isEmpty(&heap2));
    CU_ASSERT_TRUE(heap2.capacity == 0);
    CU_ASSERT_PTR_NULL(heap2.data);

    while(!(bnt_isEmpty(&heap1))){
      int curr = (int) bnt_dequeue(&heap1);
      CU_ASSERT_TRUE(curr >= prev);
      if(!(curr >= prev)){
        printf("\ncurr: %d, prev: %d\n", curr, prev);
      }
      prev = curr;
    }

    bnt_freeDeep(&heap1);
  }

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

  if(CU_add_test(bnt_suite, "Test heap_peek_top", test_peek) == NULL){
    return CU_get_error();
  }

  if(CU_add_test(bnt_suite, "Test heap_merge", test_binary_heap_merge)== NULL) {
    return CU_get_error();
  }

  return CUE_SUCCESS;
}

