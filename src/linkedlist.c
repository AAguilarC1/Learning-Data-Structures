#include "linkedlist.h"

ll_t ll_create_list(int data){
    node_t* head = n_create_node(data);
    node_t* tail = NULL;
    head->next = tail;
    return (ll_t){
        .head = head,
        .tail = tail,
        .length = 1
    };
}

void ll_insert_node_head(ll_t* list, node_t* node){
    if(node_is_null(node)){
        return;
    }

    if(ll_is_empty(list)){
        list->head = node;
        list->head->next = list->tail;
        list->length++;
        return;
    }

    node->next = list->head;
    list->head = node;
    list->length++;
    return;
}

void ll_insert_node_tail(ll_t* list, node_t* node){
    if(node_is_null(node)){
        return;
    }

    if(ll_is_empty(list)){
        ll_insert_node_head(list, node);
    }

    for(node_t* current = list->head; node_is_not_null(current); current = current->next){
        if(ll_is_null(current->next)){
            current->next = node;
            node->next = list->tail;
            list->length++;
            return;
        }
    }

}

void ll_insert_node_at(ll_t* list, node_t* node, uint32_t index){
    if(node_is_null(node)){
        return;
    }

    if(ll_is_empty(list) || index == 0){
        ll_insert_node_head(list, node);
        return;
    }

    for(node_t* current = list->head; node_is_not_null(current->next); current = current->next){
        index--;
        if(index == 0){
            node->next = current->next;
            current->next = node;
            list->length++;
            return;
        }
    }

    if(index > 0){
        printf("Index out of bounds\n");
        n_free_node(node);
        return;
    }

    return;
}

node_t ll_delete_node_head(ll_t* list){
    if(ll_is_empty(list)){
        return (node_t){.data = -1, .next = NULL};
    }

    node_t temp = {
        .data = list->head->data,
        .next = NULL
    };

    node_t* temp_node = list->head;
    list->head = list->head->next;
    n_free_node(temp_node);
    list->length--;
    return temp;
}

node_t ll_delete_node_tail(ll_t* list){
    if(ll_is_empty(list)){
        return (node_t){.data = -1, .next = NULL};
    }

    node_t* temp_node = list->head;

    if(ll_is_tail(list, temp_node->next)){
        node_t temp = {
            .data = temp_node->data,
            .next = NULL
        };

        n_free_node(temp_node);
        list->head = list->tail;
        list->length--;
        return temp;
    }

    while(ll_is_not_tail(list, temp_node->next->next)){
        temp_node = temp_node->next;
    }

    node_t temp = {
        .data = temp_node->next->data,
        .next = NULL
    };

    n_free_node(temp_node->next);
    temp_node->next = list->tail;
    list->length--;
    return temp;

}

node_t ll_delete_node_at(ll_t* list, uint32_t index){
    if(ll_is_empty(list)){
        return (node_t){.data = -1, .next = NULL};
    }

    if(index == 0){
        return ll_delete_node_head(list);
    }

    node_t* current = list->head;

    // if(ll_is_tail(list, current->next) && index >= 1){
    //     printf("Index out of bounds\n");
    //     return (node_t){.data = -1, .next = NULL};
    // }

    for(; ll_is_not_tail(list, current->next); current = current->next){
        index--;
        if(index == 0){
            node_t temp = {
                .data = current->next->data,
                .next = NULL
            };

            node_t* temp_node = current->next;
            current->next = temp_node->next;
            n_free_node(temp_node);
            list->length--;
            return temp;
        }
    }

    if(index == 1 && current->next != list->tail){
        node_t temp = {
            .data = current->next->data,
            .next = NULL
        };

        node_t* temp_node = current->next;
        current->next = temp_node->next;
        n_free_node(temp_node);
        list->length--;
        return temp;
    }

    if(index > 0){
        printf("Index out of bounds\n");
        return (node_t){.data = -1, .next = NULL};
    }
}

void ll_travel_list(ll_t* list, void (*callback)(void*)){
    if(ll_is_empty(list)){
        return;
    }

    for(node_t* current = list->head; node_is_not_null(current); current = current->next){
        callback(current);
    }
}

void ll_search_list(ll_t* list, int data, void (*callback)(void*)){
    if(ll_is_empty(list)){
        return;
    }

    for(node_t* current = list->head; node_is_not_null(current); current = current->next){
        if(current->data == data){
            callback(current);
        }
    }
}

node_t ll_peek_head(ll_t* list){
    if(ll_is_empty(list)){
        printf("List is empty\n");
        return (node_t){.data = -1, .next = NULL};
    }
    #ifdef DEBUG
    n_print_node(list->head);
    #endif
    return *list->head;
}

node_t ll_peek_tail(ll_t* list){
    if(ll_is_empty(list)){
        printf("List is empty\n");
        return (node_t){.data = -1, .next = NULL};
    }

    for(node_t* current = list->head; node_is_not_null(current); current = current->next){
        if(ll_is_null(current->next)){
            #ifdef DEBUG
            n_print_node(current);
            #endif
            return *current;
        }
    }
}

node_t ll_peek_at(ll_t* list, uint32_t index){
    if(ll_is_empty(list)){
        printf("List is empty\n");
        return (node_t){.data = -1, .next = NULL};
    }

    for(node_t* current = list->head; node_is_not_null(current); current = current->next){
        if(index == 0){
            #ifdef DEBUG
            n_print_node(current);
            #endif
            return *current;
        }
        index--;
    }

    printf("Index out of bounds\n");
    return (node_t){.data = -1, .next = NULL};
}

void ll_print_list(ll_t* list){
    if(ll_is_empty(list)){
        printf("List is empty\n");
        return;
    }

    ll_travel_list(list, n_print_node);
    
}

void ll_free_list(ll_t* list){
    if(node_is_null(list->head)){
        return;
    }

    if(ll_is_empty(list)){
        return;
    }

    node_t* current = list->head;
    while(node_is_not_null(current)){
        node_t* temp = current;
        current = current->next;
        n_free_node(temp);
    }

}

void ll_freeDeep_list(ll_t* list){
    ll_free_list(list);
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
}

/*
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
        ll_freeDeep(node);
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

    if(ll_is_empty()){
        return;
    }
    
    n_free_node(node);
}

void ll_freeDeep(node_t* node){
    if(ll_is_empty()){
        return;
    }

    if(node_is_null(node)){
        return;
    }

    ll_freeDeep(node->next);
    n_free_node(node);
}
*/
