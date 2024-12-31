#include "stack.h"

stack_t create_stack(void) {
    stack_t stack;
    stack.size = 0;
    for(int i = 0; i < MAX_STACK_SIZE; i++) {
        stack.items[i] = 0;
    }
    return stack;
}

int push(stack_t *stack, int item) {
    if(stack_is_full(stack)) {
        return -1;
    }
    stack->items[stack->size] = item;
    stack->size++;
    return 0;
}

int pop(stack_t *stack) {
    if(stack_is_empty(stack)) {
        return -1;
    }
    stack->size--;
    return stack->items[stack->size];
}

void free_stack(stack_t *stack) {
    stack->size = 0;
    for(int i = 0; i < MAX_STACK_SIZE; i++) {
        stack->items[i] = 0;
    }
}