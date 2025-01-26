#include "stack.h"

stack_t stack_create(void) {
    stack_t stack;
    stack.size = 0;
    for(unsigned int i = 0; i < MAX_STACK_SIZE; i++) {
        stack.items[i] = 0;
    }
    return stack;
}

int stack_push(stack_t *stack, int item) {
    if(stack_is_full(stack)) {
        return -1;
    }
    stack->items[stack->size] = item;
    stack->size++;
    return 0;
}

int stack_pop(stack_t *stack) {
    if(stack_is_empty(stack)) {
        return -1;
    }
    stack->size--;
    return stack->items[stack->size];
}

void stack_free(stack_t *stack) {
    stack->size = 0;
    for(unsigned int i = 0; i < MAX_STACK_SIZE; i++) {
        stack->items[i] = 0;
    }
}
