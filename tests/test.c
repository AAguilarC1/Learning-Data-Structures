#include <stdio.h>
#include <CUnit/Basic.h>

// Function to test
int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Test case
void testFibonacci() {
    CU_ASSERT_EQUAL(fibonacci(0), 0);
    CU_ASSERT_EQUAL(fibonacci(1), 1);
    CU_ASSERT_EQUAL(fibonacci(5), 5);
    CU_ASSERT_EQUAL(fibonacci(10), 55);
}

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
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add a suite to the registry
    CU_pSuite suite = CU_add_suite("Fibonacci Suite", initialize_suite, cleanup_suite);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test case to the suite
    if (NULL == CU_add_test(suite, "testFibonacci", testFibonacci)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}