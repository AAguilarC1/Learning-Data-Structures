#include "test_doubly_list.h"

void test_dll_create_list(void){
    dll_t list = dll_create_list(10);
    CU_ASSERT_EQUAL(dll_length(&list), 1);
    CU_ASSERT_EQUAL(dll_peek_head(&list).data, 10);
    CU_ASSERT_EQUAL(dll_peek_tail(&list).data, 10);
    dll_freeDeep_list(&list);
}

void test_dll_add_remove_node_head(void){
    unsigned int num = 100;
    dll_t list = dll_create_list(0);


    for(unsigned int i = 1; i < num; i++){
        dll_add_node_head(&list, n_create_dnode(i));
    }

    CU_ASSERT_EQUAL(dll_length(&list), num);
    CU_ASSERT_EQUAL(dll_peek_head(&list).data, num - 1);
    CU_ASSERT_EQUAL(dll_peek_tail(&list).data, 0);
    CU_ASSERT_EQUAL(dll_is_empty(&list), 0);

    for(unsigned int i = 0; i < num; i++){
        dnode_t temp = dll_remove_node_head(&list);
        CU_ASSERT_EQUAL(temp.data, num - i - 1);
    }

    CU_ASSERT_EQUAL(dll_length(&list), 0);
    CU_ASSERT_EQUAL(dll_is_empty(&list), 1);

    dll_freeDeep_list(&list);
}

void test_dll_add_remove_node_tail(void){
    unsigned int num = 100;
    dll_t list = dll_create_list(0);

    for(unsigned int i = 1; i < num; i++){
        dll_add_node_tail(&list, n_create_dnode(i));
    }

    CU_ASSERT_EQUAL(dll_length(&list), num);
    CU_ASSERT_EQUAL(dll_peek_head(&list).data, 0);
    CU_ASSERT_EQUAL(dll_peek_tail(&list).data, num - 1);
    CU_ASSERT_EQUAL(dll_is_empty(&list), 0);

    for(unsigned int i = 0; i < num; i++){
        dnode_t temp = dll_remove_node_tail(&list);
        CU_ASSERT_EQUAL(temp.data, num - i - 1);
    }

    CU_ASSERT_EQUAL(dll_length(&list), 0);
    CU_ASSERT_EQUAL(dll_is_empty(&list), 1);

    dll_freeDeep_list(&list);
}


void test_dll_insert_remove_node_at(void){
    unsigned int num = 50;
    dll_t list = dll_create_list(0);
    for(unsigned int i = 1; i < num; i++){
        dll_add_node_tail(&list, n_create_dnode(i));
    }

    for(unsigned int i = 0; i < num * 2; i++){
        if(i % 2 != 0){
            dll_insert_node_at(&list, n_create_dnode(i + num - 1), i);
        }
    }

    CU_ASSERT_EQUAL(dll_length(&list), 2 * num);
    CU_ASSERT_EQUAL(dll_peek_head(&list).data, 0);

    for(unsigned int i = 0; i < num * 2; i++){
        dnode_t temp = dll_remove_node_at(&list, i % dll_length(&list));
        CU_ASSERT_EQUAL(temp.data >= 0 && temp.data < num * 3, 1);
    }

    CU_ASSERT_EQUAL(dll_length(&list), 0);
    CU_ASSERT_EQUAL(dll_peek_tail(&list).data, 0);
    CU_ASSERT_EQUAL(dll_is_empty(&list), 1);

    dll_freeDeep_list(&list);

}

void test_dll_peek(void){
    unsigned int num = 50;
    dll_t list = dll_create_list(0);
    CU_ASSERT_EQUAL(dll_peek_head(&list).data, 0);
    CU_ASSERT_EQUAL(dll_peek_tail(&list).data, 0);
    CU_ASSERT_EQUAL(dll_peek_at(&list, 0).data, 0);

    for(unsigned int i = 1; i < 50; i++){
        int index = test_random_int(list.length, 0);
        dll_add_node_tail(&list, n_create_dnode(i));
        CU_ASSERT_EQUAL(dll_peek_head(&list).data, 0);
        CU_ASSERT_EQUAL(dll_peek_tail(&list).data, i);
        CU_ASSERT_EQUAL(dll_peek_at(&list, index).data,index);
    }

    dll_freeDeep_list(&list);
}

int test_doubly_linked_list_suite(CU_pSuite dll_suite){
    if(NULL == CU_add_test(dll_suite, "Test dll_create_list", test_dll_create_list)){
        return CU_get_error();
    }

    if(NULL == CU_add_test(dll_suite, "Test dll_add_remove_node_head", test_dll_add_remove_node_head)){
        return CU_get_error();
    }

    if(NULL == CU_add_test(dll_suite, "Test dll_add_remove_node_tail", test_dll_add_remove_node_tail)){
        return CU_get_error();
    }

    if(NULL == CU_add_test(dll_suite, "Test dll_insert_remove_node_at", test_dll_insert_remove_node_at)){
        return CU_get_error();
    }

    if(NULL == CU_add_test(dll_suite, "Test dll_peek", test_dll_peek)){
        return CU_get_error();
    }

    return CUE_SUCCESS;
}
