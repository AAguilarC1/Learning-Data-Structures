#include "linkedlist.h"
#include "test_linkedlist.h"
// TODO: Implement tests for linkedlist

void testCreateList(void){
    ll_t list = ll_create_list(5);
    CU_ASSERT_PTR_NOT_NULL(list.head);
    CU_ASSERT_PTR_NULL(list.head->next);
    CU_ASSERT_EQUAL(list.length, 1);

    CU_ASSERT_EQUAL(list.head->data, 5);

    ll_freeDeep_list(&list);
}

void test_ll_insert_node_head(void){
    unsigned int num = 1000;
    ll_t list = ll_create_list(0);

    for (unsigned int i = 1; i < num; i++){
        ll_insert_node_head(&list, n_create_node(i));
    }

    CU_ASSERT_EQUAL(list.length, num);
    CU_ASSERT_PTR_NOT_NULL(list.head);
    for(unsigned int i = 0; i < num; i++){
        CU_ASSERT_EQUAL(ll_peek_at(&list, i).data, num - i - 1);
    }

    ll_freeDeep_list(&list);
    CU_ASSERT_PTR_NULL(list.head);
    CU_ASSERT_EQUAL(list.length, 0);
}

void test_ll_insert_node_tail(void){
    unsigned int num = 1000;
    ll_t list = ll_create_list(0);

    for (unsigned int i = 1; i < num; i++){
        ll_insert_node_tail(&list, n_create_node(i));
    }

    CU_ASSERT_EQUAL(list.length, num);
    CU_ASSERT_PTR_NOT_NULL(list.head);
    CU_ASSERT_EQUAL(list.head->data, 0);

    for(unsigned int i = 0; i < num; i++){
        CU_ASSERT_EQUAL(ll_peek_at(&list, i).data, i);
    }

    ll_freeDeep_list(&list);
    CU_ASSERT_PTR_NULL(list.head);
    CU_ASSERT_EQUAL(list.length, 0);
}

void test_ll_insert_node_at(void){
    unsigned int num = 100;
    ll_t list = ll_create_list(0);

    for (unsigned int i = 1; i < num; i++){
        ll_insert_node_head(&list, n_create_node(i));
    }
    

    for(unsigned int i = 0; i < num; i++){
        ll_insert_node_at(&list, n_create_node(i + num), 50);
    }

    CU_ASSERT_EQUAL(list.length, 2 * num);
    CU_ASSERT_PTR_NOT_NULL(list.head);
    CU_ASSERT_EQUAL(list.head->data, 99);
    CU_ASSERT_EQUAL(ll_peek_tail(&list).data, 0);

    for(unsigned int i = 0; i < num; i++){
        CU_ASSERT_EQUAL(ll_peek_at(&list, 50 + i).data, 199 - i);
    }

    ll_freeDeep_list(&list);
    CU_ASSERT_PTR_NULL(list.head);
    CU_ASSERT_EQUAL(list.length, 0);
}

void test_ll_delete_node_head(void){
    unsigned int num = 1000;
    ll_t list = ll_create_list(0);

    for (unsigned int i = 1; i < num; i++){
        ll_insert_node_head(&list, n_create_node(i));
    }

    CU_ASSERT_EQUAL(list.length, num);

    node_t temp = {
        .data = 0, 
        .next = NULL
    };

    for (unsigned int i = 0; i < num; i++){
        temp = ll_delete_node_head(&list);
        CU_ASSERT_EQUAL(temp.data, num - i - 1);
    }

    CU_ASSERT_EQUAL(list.length, 0);
}

void test_ll_delete_node_tail(void){
    unsigned int num = 1000;
    ll_t list = ll_create_list(0);

    for (unsigned int i = 1; i < num; i++){
        ll_insert_node_head(&list, n_create_node(i));
    }

    CU_ASSERT_EQUAL(list.length, num);

    node_t temp = {
        .data = 0, 
        .next = NULL
    };

    for (unsigned int i = 0; i < num; i++){
        temp = ll_delete_node_tail(&list);
        CU_ASSERT_EQUAL(temp.data, i);
    }

    CU_ASSERT_EQUAL(list.length, 0);

}

void test_ll_delete_node_at(void){
    unsigned int num = 100;
    ll_t list = ll_create_list(0);

    for (unsigned int i = 1; i < num; i++){
        ll_insert_node_tail(&list, n_create_node(i));
    }

    CU_ASSERT_EQUAL(list.length, num);

    node_t temp = {
        .data = 0, 
        .next = NULL
    };


    for (unsigned int i = 0; i < num; i++){
        int index = rand() % list.length;
        temp = ll_delete_node_at(&list, index);
        CU_ASSERT_EQUAL(1, temp.data >= 0 && temp.data <= 99);
    }

    CU_ASSERT_EQUAL(list.length, 0);
     
}

void test_peek(void){
    unsigned int num = 100;
    ll_t list = ll_create_list(0);

    for (unsigned int i = 1; i < num; i++){
        ll_insert_node_tail(&list, n_create_node(i));
    }

    CU_ASSERT_EQUAL(list.length, num);

    CU_ASSERT_EQUAL(ll_peek_head(&list).data, 0);
    CU_ASSERT_EQUAL(ll_peek_tail(&list).data, 99);

    for (unsigned int i = 0; i < num; i++){
        CU_ASSERT_EQUAL(ll_peek_at(&list, i).data, i);
    }

    ll_freeDeep_list(&list);
    CU_ASSERT_PTR_NULL(list.head);
    CU_ASSERT_EQUAL(list.length, 0);
}

int test_linkedlist_suite(CU_pSuite linkedlist_suite){
    if (NULL == CU_add_test(linkedlist_suite, "testCreateList", testCreateList)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(linkedlist_suite, "test_ll_insert_node_head", test_ll_insert_node_head)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(linkedlist_suite, "test_ll_insert_node_tail", test_ll_insert_node_tail)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(linkedlist_suite, "test_ll_insert_node_at", test_ll_insert_node_at)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(linkedlist_suite, "test_ll_delete_node_head", test_ll_delete_node_head)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(linkedlist_suite, "test_ll_delete_node_tail", test_ll_delete_node_tail)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(linkedlist_suite, "test_ll_delete_node_at", test_ll_delete_node_at)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(linkedlist_suite, "test_peek", test_peek)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    return 0;
}
