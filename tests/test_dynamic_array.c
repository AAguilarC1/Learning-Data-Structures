#include "test_dynamic_array.h"
#include "dynamic_array.h"
#include <CUnit/CUnit.h>

void test_dyn_arr_create(void){
  for(size_t i = 1; i < 100; i ++){
    dn_arr_t arr = dn_arr_create(i);
    CU_ASSERT_EQUAL(arr.size, 0);
    CU_ASSERT_EQUAL(arr.capacity, i);
    dn_arr_freeDeep(&arr);
    CU_ASSERT_PTR_NULL(arr.data);
  }
  
  dn_arr_t arr_cap_0 = dn_arr_create(0);
  CU_ASSERT_EQUAL(arr_cap_0.size, 0);
  CU_ASSERT_EQUAL(arr_cap_0.capacity, DN_DEFAULT_CAPACITY);
  dn_arr_freeDeep(&arr_cap_0);

  dn_arr_t arr_cap_neg = dn_arr_create(-10);
  CU_ASSERT_EQUAL(arr_cap_neg.size, 0);
  CU_ASSERT_EQUAL(arr_cap_neg.capacity, DN_DEFAULT_CAPACITY);
  dn_arr_freeDeep(&arr_cap_neg);
  
  dn_arr_t arr_cap_overMax = dn_arr_create(DN_MAX_ARRAY_CAPACITY * 10);
  CU_ASSERT_EQUAL(arr_cap_overMax.size, 0);
  CU_ASSERT_EQUAL(arr_cap_overMax.capacity, DN_MAX_ARRAY_CAPACITY);
  dn_arr_freeDeep(&arr_cap_overMax);

}

void test_dyn_arr_push_pop(void){
  dn_arr_t arr = dn_arr_create_default();
  size_t curr_capacity = arr.capacity;
  
  for(size_t i = 1; i < DN_MAX_ARRAY_CAPACITY  + 100; i++){
    if(dn_arr_isFull(&arr)){
      curr_capacity *= 2;
      
      if (curr_capacity >= DN_MAX_ARRAY_CAPACITY){
        curr_capacity = DN_MAX_ARRAY_CAPACITY;
      }
    }

    dn_arr_push(&arr, i);
    CU_ASSERT_EQUAL(arr.capacity, curr_capacity);

    if(i <= DN_MAX_ARRAY_CAPACITY){
      CU_ASSERT_EQUAL(dn_arr_top(&arr), i);
      CU_ASSERT_EQUAL(arr.size, i);
    }else{
      CU_ASSERT_EQUAL(dn_arr_top(&arr), DN_MAX_ARRAY_CAPACITY);
      CU_ASSERT_EQUAL(arr.size, DN_MAX_ARRAY_CAPACITY);
    }

  }
  
  CU_ASSERT_EQUAL(arr.capacity, DN_MAX_ARRAY_CAPACITY);
  CU_ASSERT_EQUAL(arr.size, DN_MAX_ARRAY_CAPACITY);

  int temp;
  for(size_t i = DN_MAX_ARRAY_CAPACITY; i > 0; i--){
    temp = dn_arr_pop(&arr);
    CU_ASSERT_EQUAL(temp, i);
  }

  dn_arr_freeDeep(&arr);

}

void test_dyn_arr_peek(void){
  dn_arr_t arr = dn_arr_create(DN_MAX_ARRAY_CAPACITY);
  
  for(size_t i = 1; i <= DN_MAX_ARRAY_CAPACITY; i++){
    dn_arr_push(&arr, i);
    CU_ASSERT_EQUAL(dn_arr_top(&arr), i);
    CU_ASSERT_EQUAL(dn_arr_bot(&arr), 1);
  }
  dn_arr_freeDeep(&arr);
}

int test_dynamic_arr_suite(CU_pSuite dyn_arr_suite){
  if(NULL == CU_add_test(dyn_arr_suite, "Test dynamic_array_create", test_dyn_arr_create)){
    return CU_get_error();
  }

  if(NULL == CU_add_test(dyn_arr_suite, "Test dynamic_array_push_pop", test_dyn_arr_push_pop)){
    return CU_get_error();
  }

  if(NULL == CU_add_test(dyn_arr_suite, "Test peek_top_bot", test_dyn_arr_peek)){
    return CU_get_error();
  }

  return CUE_SUCCESS;
}

