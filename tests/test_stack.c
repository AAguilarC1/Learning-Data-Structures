#include "test_stack.h"

void test_stack_create(void){
    stack_t stack = stack_create();
    CU_ASSERT_EQUAL(stack.size, 0);
    CU_ASSERT_EQUAL(stack_is_empty(&stack), 1);
    CU_ASSERT_EQUAL(stack_is_full(&stack), 0);
    stack_free(&stack);
    CU_ASSERT_EQUAL(stack.size, 0);
}

void test_stack_push_pop(void){
    unsigned int num = MAX_STACK_SIZE;
    stack_t stack = stack_create();
    for (unsigned int i = 0; i < num; i++){
        stack_push(&stack, i);
        CU_ASSERT_EQUAL(stack_peek(&stack), (int) i);
    }

    CU_ASSERT_EQUAL(stack.size, num);
    CU_ASSERT_EQUAL(stack_push(&stack, 0), -1);
    CU_ASSERT_EQUAL(stack.size, num);

    CU_ASSERT_EQUAL(stack_is_empty(&stack), 0);
    CU_ASSERT_EQUAL(stack_is_full(&stack), 1);

    for (unsigned int i = num - 1; (i + 1) > 0; i--){
        CU_ASSERT_EQUAL(stack_pop(&stack), i);
    }

    CU_ASSERT_EQUAL(stack.size, 0);
    CU_ASSERT_EQUAL(stack_is_empty(&stack), 1);
    CU_ASSERT_EQUAL(stack_is_full(&stack), 0);
    stack_free(&stack);

}

int test_stack_suite(CU_pSuite stack_suite){
    
    if(NULL == CU_add_test(stack_suite, "test_stack_create", test_stack_create)){
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if(NULL == CU_add_test(stack_suite, "test_stack_push_pop", test_stack_push_pop)){
        CU_cleanup_registry();
        return CU_get_error();
    }

    return 0;
}
