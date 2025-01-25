#include "queue.h"
#include "test_queue.h"

void test_queue_create_free(void){
 queue_t queue;
 
  for(size_t i = 0; i < 100; i++){
    
    queue = qe_create_queue();
    CU_ASSERT_EQUAL(qe_is_null(queue.front), 1);
    CU_ASSERT_EQUAL(qe_is_null(queue.rear), 1);
    CU_ASSERT_EQUAL(queue.size, 0);
  
    qe_freeDeep_queue(&queue);

  }

}

void test_queue_enqueue_dequeue(void){
  queue_t queue = qe_create_queue();

  for(size_t i = 1; i < 1000; i++){
    qe_enqueue(&queue, (int) i);
    CU_ASSERT_EQUAL(qe_length(&queue), i);
    CU_ASSERT_EQUAL(qe_peek_rear(&queue), i);
  }
  
  for(size_t i = 1; i < 1000; i++){
    CU_ASSERT_EQUAL(qe_length(&queue), 1000 - i);
    int temp = qe_dequeue(&queue);
    CU_ASSERT_EQUAL(temp, i);
  }

  qe_freeDeep_queue(&queue);

}

void test_queue_peek(void){
  queue_t queue = qe_create_queue();

  for(size_t i = 1; i < 1000; i++){
    qe_enqueue(&queue, i);
    CU_ASSERT_EQUAL(qe_peek_front(&queue), 1);
    CU_ASSERT_EQUAL(qe_peek_rear(&queue), i);
  }

  qe_freeDeep_queue(&queue);

}

int test_queue_suite(CU_pSuite q_suite){
  if(NULL == CU_add_test(q_suite, "Test queue_create_free", test_queue_create_free)){
    return CU_get_error();
  }
    
  if(NULL == CU_add_test(q_suite, "Test queue_enqueue_dequeue", test_queue_enqueue_dequeue)){
    return CU_get_error();
  }
  
  if(NULL == CU_add_test(q_suite, "Test queue_peek", test_queue_peek)){
    return CU_get_error();
  }

  return CUE_SUCCESS;
}
