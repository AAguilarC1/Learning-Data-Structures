#include "doubly_linked_list.h"

dll_t dll_create_list(int data){
    dnode_t* node = n_create_dnode(data);
    dll_t list = {node, node, 1};
    
    list.head->next = list.tail;
    list.head->prev = NULL;

    list.tail->next = NULL;
    list.tail->prev = list.head;

    return list;
}

int dll_add_node_head(dll_t* list, dnode_t* node){
    if(dll_is_null(list)){
        return -1;
    }

    if(node_is_null(node)){
        return -1;
    }

    if(dll_is_empty(list)){
        list->head = node;
        list->tail = node;
        list->length = 1;
        list->head->next = list->tail;
        list->head->prev = NULL;
        list->tail->next = NULL;
        list->tail->prev = list->head;

        return 0;
    }

    if(dll_length(list) == 1){
        list->head = node;
        list->head->next = list->tail;
        list->head->prev = NULL;
        list->tail->prev = list->head;
        list->tail->next = NULL;
        list->length++;
        return 0;
    }

    node->next = list->head;
    node->prev = NULL;

    list->head->prev = node;
    list->head = node;

    list->length++;

    return 0;
}

int dll_add_node_tail(dll_t* list, dnode_t* node){
    if(dll_is_null(list)){
        return -1;
    }

    if(node_is_null(node)){
        return -1;
    }

    if(dll_is_empty(list)){
        list->head = node;
        list->tail = node;

        list->head->next = list->tail;
        list->head->prev = NULL;
        list->tail->next = NULL;
        list->tail->prev = list->head;
        
        list->length = 1;
    }

    if(dll_length(list) == 1){
        list->tail = node;
        list->head->next = list->tail;
        list->tail->prev = list->head;
        list->tail->next = NULL;
        list->head->prev = NULL;
        list->length++;
        return 0;
    }

    node->prev = list->tail;
    node->next = NULL;

    list->tail->next = node;
    list->tail = node;
    list->length++;

    return 0;
}

int dll_insert_node_at(dll_t* list, dnode_t* node, unsigned int index){
    if(dll_is_null(list)){
        return -1;
    }

    if(node_is_null(node)){
        return -1;
    }

    if(index > dll_length(list)){
        return -1;
    }

    if(index == 0){
        return dll_add_node_head(list, node);
    }

    if(index == dll_length(list)){
        return dll_add_node_tail(list, node);
    }

    dnode_t* current = list->head;
    unsigned int i = 0;

    while(node_is_not_null(current)){
        if(i == index){
            node->next = current;
            node->prev = current->prev;

            current->prev->next = node;
            current->prev = node;

            list->length++;
            return 0;
        }

        current = current->next;
        i++;
    }

    return -1;
}

dnode_t dll_remove_node_head(dll_t* list){

    dnode_t ret = {0, NULL, NULL};

    if(dll_is_null(list)){
        return ret;
    }       

    if(dll_is_empty(list)){
        return ret;
    }

    dnode_t *temp = list->head;

    if(dll_length(list) == 1){
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        ret = *temp;
        n_free_dnode(temp);
        return ret;
    }

    list->head = list->head->next;
    list->head->prev = NULL;
    list->length--;

    ret = *temp;    
    n_free_dnode(temp); 

    return ret;
}

dnode_t dll_remove_node_tail(dll_t* list){
    dnode_t ret = {0, NULL, NULL};

    if(dll_is_null(list)){
        return ret;
    }

    if(dll_is_empty(list)){
        return ret;
    }

    dnode_t *temp = list->tail;

    if(dll_length(list) == 1){
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
        ret = *temp;
        n_free_dnode(temp);
        return ret;
    }

    list->tail = list->tail->prev;
    list->tail->next = NULL;
    list->length--;

    ret = *temp;
    n_free_dnode(temp);

    return ret;
}
dnode_t dll_remove_node_at(dll_t* list, unsigned int index){
    dnode_t ret = {0, NULL, NULL};

    if(dll_is_null(list)){
        return ret;
    }

    if(index >= dll_length(list)){
        return ret;
    }

    if(index == 0){
        return dll_remove_node_head(list);
    }

    if(index == dll_length(list) - 1){
        return dll_remove_node_tail(list);
    }

    dnode_t* current = list->head;
    unsigned int i = 0;

    while(node_is_not_null(current)){
        if(i == index){
            current->prev->next = current->next;
            current->next->prev = current->prev;

            ret = *current;
            n_free_dnode(current);
            list->length--;

            return ret;
        }

        current = current->next;
        i++;
    }

    return ret;
}

int dll_travel_list(dll_t* list, void (*callback)(void*)){
    if(dll_is_null(list)){
        return -1;
    }

    if(dll_is_empty(list)){
        return -1;
    }

    for(dnode_t* current = list->head; node_is_not_null(current); current = current->next){
        callback(current);
    }

    return 0;
}

dnode_t dll_search_list(dll_t* list, int data, void (*callback)(void*)){
    dnode_t ret = {0, NULL, NULL};
    if(dll_is_null(list)){
        return ret;
    }

    if(dll_is_empty(list)){
        return ret;
    }

    for(dnode_t* current = list->head; node_is_not_null(current); current = current->next){
        if(current->data == data){
            callback(current);
            return *current;
        }
    }

    return ret;
}

dnode_t dll_peek_head(dll_t* list) {
    if(dll_is_null(list)){
        dnode_t ret = {0, NULL, NULL};
        return ret;
    }

    if(dll_is_empty(list)){
        dnode_t ret = {0, NULL, NULL};
        return ret;
    }

    return *list->head;
}

dnode_t dll_peek_tail(dll_t* list){
    if(dll_is_null(list)){
        dnode_t ret = {0, NULL, NULL};
        return ret;
    }

    if(dll_is_empty(list)){
        dnode_t ret = {0, NULL, NULL};
        return ret;
    }

    return *list->tail;
}

dnode_t dll_peek_at(dll_t* list, unsigned int index){
    dnode_t ret = {0, NULL, NULL};

    if(dll_is_null(list)){
        return ret;
    }

    if(index >= dll_length(list)){
        return ret;
    }

    if(index == 0){
        return *list->head;
    }

    if(index == dll_length(list) - 1){
        return *list->tail;
    }

    dnode_t* current = list->head;
    unsigned int i = 0;

    while(node_is_not_null(current)){
        if(i == index){
            return *current;
        }

        current = current->next;
        i++;
    }

    return ret;
}


int dll_print_list(dll_t* list){
    if(dll_is_null(list)){
        printf("List is null\n");
        return -1;
    }

    if(dll_is_empty(list)){
        printf("List is empty\n");
        return -1;
    }

    dll_travel_list(list, n_print_dnode);

}

void dll_free_list(dll_t* list){
    if(dll_is_null(list)){
        return;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

void dll_freeDeep_list(dll_t* list){
    if(dll_is_null(list)){
        return;
    }

    dnode_t* current = list->head;
    dnode_t* temp = NULL;

    while(node_is_not_null(current)){
        temp = current->next;
        n_free_dnode(current);
        current = temp;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}
