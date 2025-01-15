#include "test.h"

// Test suite initialization
int initialize_suite() {
    return 0;
}

// Test suite cleanup
int cleanup_suite() {
    return 0;
}

// Main function
int main() {
    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    CU_pSuite min_heap_suite = CU_add_suite("min_heap_suite", initialize_suite, cleanup_suite);

    CU_pSuite linkedlist_suite = CU_add_suite("linkedlist_suite", initialize_suite, cleanup_suite);

    CU_pSuite stack_suite = CU_add_suite("stack_suite", initialize_suite, cleanup_suite);

    CU_pSuite doubly_linked_list_suite = CU_add_suite("doubly_linked_list_suite", initialize_suite, cleanup_suite);

    if (NULL == min_heap_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == linkedlist_suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add a suite to the registry
    if (test_min_heap_suite(min_heap_suite) != 0) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (test_linkedlist_suite(linkedlist_suite) != 0) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if(test_stack_suite(stack_suite) != 0){
        CU_cleanup_registry();
        return CU_get_error();
    }

    if(test_doubly_linked_list_suite(doubly_linked_list_suite) != 0){
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}