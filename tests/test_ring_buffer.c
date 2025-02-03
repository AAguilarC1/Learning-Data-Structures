#include "test_ring_buffer.h"
#include "ring_buffer.h"
#include <CUnit/CUnit.h>
#include <stddef.h>

void test_rb_create_free(void){
  rb_t rb = rb_create_buffer(16);
  CU_ASSERT_EQUAL(rb.capacity, 16);
  CU_ASSERT_EQUAL(rb.read_index, 0);
  CU_ASSERT_EQUAL(rb.write_index, 0);
  CU_ASSERT_PTR_NOT_NULL(rb.buffer);
  rb_freeDeep_buffer(&rb);
  CU_ASSERT_PTR_NULL(rb.buffer);

  RB_ELEMENT arr[16] = {0};

  rb_t rb2 = rb_create_buffer_array(arr, 16);
  CU_ASSERT_EQUAL(rb2.capacity, 16);
  CU_ASSERT_EQUAL(rb2.read_index, 0);
  CU_ASSERT_EQUAL(rb2.write_index, 16);

  for(size_t i = 0; i < 16; i++){
    CU_ASSERT_EQUAL(rb2.buffer[i], arr[i]);
  }
  
  for(size_t i = DEFAULT_RING_BUFFER_SIZE; i < MAX_RING_BUFFER_SIZE; i <<= 1){
    rb_t rb3 = rb_create_buffer(i);
    CU_ASSERT_EQUAL(rb3.capacity, i);
    CU_ASSERT_EQUAL(rb3.read_index, 0);
    CU_ASSERT_EQUAL(rb3.write_index, 0);
    CU_ASSERT_PTR_NOT_NULL(rb3.buffer);
    rb_freeDeep_buffer(&rb3);
    CU_ASSERT_PTR_NULL(rb3.buffer);
  }
}

void test_rb_push_pop(void){
  rb_t rb = rb_create_buffer(16);
  for(size_t i = 0; i < 16; i++){
    rb_push(&rb, i);
  }

  for(size_t i = 0; i < 16; i++){
    RB_ELEMENT data = rb_pop(&rb);
    CU_ASSERT_EQUAL(data, i);
  }

  CU_ASSERT_PTR_NOT_NULL(rb.buffer);
  CU_ASSERT_EQUAL(rb.capacity, 16);
  CU_ASSERT(rb_isEmpty(&rb));

  rb_freeDeep_buffer(&rb);
  CU_ASSERT_PTR_NULL(rb.buffer);

  RB_ELEMENT arr[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  rb_t rb2 = rb_create_buffer(32);
  rb_add_array(&rb2, arr, 16);

  for(size_t i = 16; i < 32; i++){
    rb_push(&rb2, i);
  }

  CU_ASSERT(rb_isFull(&rb2));

  for(size_t i = 0; i < 32; i++){
    RB_ELEMENT data = rb_pop(&rb2);
    CU_ASSERT_EQUAL(data, i);
  }

  CU_ASSERT_PTR_NOT_NULL(rb2.buffer);
  CU_ASSERT_EQUAL(rb2.capacity, 32);
  CU_ASSERT(rb_isEmpty(&rb2));

  for(size_t i = 0; i < 32; i++){
    rb_push(&rb2, i<<1);
  }

  CU_ASSERT(rb_isFull(&rb2));
  rb_flush(&rb2);
  CU_ASSERT(rb_isEmpty(&rb2));
  
  for(size_t i = 0; i < 64; i++){
    rb_push(&rb2, i);
    if(i >= 32){
      CU_ASSERT(rb_isFull(&rb2));
    }
  }

  for(size_t i = 0; i < 64; i++){
    RB_ELEMENT data = rb_pop(&rb2);
    if(i < 32){
      CU_ASSERT_EQUAL(data, i);
    }else{
      CU_ASSERT(rb_isEmpty(&rb2));
      CU_ASSERT_EQUAL(data, -1);
    }
  }
  
  CU_ASSERT_PTR_NOT_NULL(rb2.buffer);
  CU_ASSERT_EQUAL(rb2.capacity, 32);
  CU_ASSERT(rb_isEmpty(&rb2));

  rb_freeDeep_buffer(&rb2);
  CU_ASSERT_PTR_NULL(rb2.buffer);
}

int test_rb_suite(CU_pSuite rb_suite){
  if(CU_add_test(rb_suite, "Test ring_buffer_create_free", test_rb_create_free) == NULL){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if(CU_add_test(rb_suite, "Test ring_buffer_push_pop", test_rb_push_pop) == NULL){
    CU_cleanup_registry();
    return CU_get_error();
  }

  return CUE_SUCCESS;
}

