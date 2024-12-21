#include "../include/linkedlist.h"

node_t* head = NULL;
node_t* tail = NULL;

node_t* ll_create_node(int data){

    node_t* node = (node_t*)malloc(sizeof(node_t));
    assert(ll_is_not_null(node) && "Memory allocation failed");

    node->data = data;
    node->next = NULL;
    return node;
}

void ll_insert_node_head(node_t* node){
    if(ll_is_empty()){
        head = node;
        head->next = tail;
        return;
    }

    node->next = head;
    head = node;
    return;
}

void ll_insert_node_tail(node_t* node){
    if(ll_is_empty()){
        head = node;
        head->next = tail;
        return;
    } 

    for(node_t* current = head; ll_is_not_null(current); current = current->next){
        if(ll_is_null(current->next)){
            current->next = node;
            node->next = tail;
        }
    }
    
    return;
}

void ll_insert_node_at(node_t* node, uint32_t index){
    if(ll_is_empty()){
        head = node;
        head->next = tail;
        return;
    }

    if(index == 0){
        ll_insert_node_head(node);
        return;
    }

    for(node_t* current = head; ll_is_not_null(current->next); current = current->next){
        index--;
        if(index == 0){
            node->next = current->next;
            current->next = node;
            break;
        }
    }

    if(index > 0){
        printf("Index out of bounds\n");
        ll_freeDeep_node(node);
        return;

    }

    return;
}

node_t ll_delete_node_head(){
    assert(!ll_is_empty() && "List is empty");
    node_t temp = {
        .data = head->data,
        .next = NULL
    };

    node_t* temp_node = head;
    head = head->next;
    ll_free_node(temp_node);
    return temp;

}
node_t ll_delete_node_tail(){
    assert(!ll_is_empty() && "List is empty");
    node_t* temp_ptr = head;

    while(temp_ptr->next->next != tail){
        temp_ptr = temp_ptr->next;
    }

    node_t temp = {
        .data = temp_ptr->next->data,
        .next = NULL
    };

    ll_free_node(temp_ptr->next);
    temp_ptr->next = tail;
}

node_t ll_delete_node_at(uint32_t index){
    assert(!ll_is_empty() && "List is empty");
    if(index == 0){
        return ll_delete_node_head();
    }

    node_t* current = head;
    if(current->next == tail && index >= 1){
        printf("Index out of bounds\n");
        return (node_t){.data = -1, .next = NULL};
    }

    for(; ll_is_not_null(current->next->next); current = current->next){
        index--;
        if(index == 0){
            node_t temp = {
                .data = current->next->data,
                .next = NULL
            }; 

            node_t* temp_node = current->next;
            current->next = temp_node->next;
            ll_free_node(temp_node);
            return temp;
        }
    }

    if(index == 1 && current->next != tail){
        node_t temp = {
            .data = current->next->data,
            .next = NULL
        }; 

        node_t* temp_node = current->next;
        current->next = temp_node->next;
        ll_free_node(temp_node);
        return temp;
    }

    if(index > 0){
        printf("Index out of bounds\n");
        return (node_t){.data = -1, .next = NULL};
    }

}

void ll_travel_list(void (*callback)(void*), node_t* node){
    if(ll_is_empty()){
        return;
    }

    if(ll_is_null(node)){
        return;
    }

    for(node_t* current = node; ll_is_not_null(current); current = current->next){
        callback(current);
    }
}

void ll_search_list_from(int data, void (*callback)(void*), node_t* node){
    if(ll_is_null(node)){
        return;
    }
    
    if(ll_is_empty()){
        return;
    }

    for(node_t* current = node; ll_is_not_null(current); current = current->next){
        if(current->data == data){
            callback(current);
        }
    }
}

size_t ll_length(){
    size_t length = 0;
    for(node_t* current = head; ll_is_not_null(current); current = current->next){
        length++;
    }
    return length;
}

int ll_peek_head(){
    assert(ll_is_not_null(head) && "List is empty");
    ll_print_node(head);
    return head->data;
}

int ll_peek_tail(){
    assert(ll_is_not_null(head) && "List is empty");
    for(node_t* current = head; ll_is_not_null(current); current = current->next){
        if(ll_is_null(current->next)){
            ll_print_node(current);
            return current->data;
        }
    }
}

int ll_peek_at(uint32_t index){
    assert(ll_is_not_null(head) && "List is empty");
    for(node_t* current = head; ll_is_not_null(current); current = current->next){
        if(index == 0){
            ll_print_node(current);
            return current->data;
        }
        index--;
    }

    printf("Index out of bounds\n");
    return -1;
}

void ll_print_node(node_t* node){
    if(ll_is_null(node)){
        printf("Node is null\n");
        return;
    }
    printf("Node : {ref = %p; data = %d, next = %p}\n", node, node->data, node->next);
}

void ll_print_list(){
    if(ll_is_empty()){
        printf("List is empty\n");
        return;
    }

    ll_travel_full_list(ll_print_node);

}

void ll_print_list_from(node_t* node){
    if(ll_is_null(node)){
        printf("Node is null\n");
        return;
    }

    if(ll_is_empty()){
        printf("List is empty\n");
        return;
    }

    ll_travel_list(ll_print_node, node);
}

void ll_free_node(node_t* node){
    if(ll_is_null(node)){
        return;
    }

    if(ll_is_empty()){
        return;
    }
    
    node->data = 0;
    free(node);
}

void ll_freeDeep_node(node_t* node){
    if(ll_is_null(node)){
        return;
    }

    if(ll_is_empty()){
        return;
    }

    ll_freeDeep_node(node->next);
    ll_free_node(node);
}