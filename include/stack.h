#ifndef STACK_H
#define STACK_H

#ifndef MAX_STACK_SIZE
#define MAX_STACK_SIZE (1<<8) // 256
#endif // MAX_STACK_SIZE

#define stack_size(__stack__) (__stack__)->size
#define stack_is_empty(__stack__) (__stack__)->size == 0
#define stack_is_full(__stack__) (__stack__)->size == MAX_STACK_SIZE

struct Stack {
    unsigned int size;    
    int items[MAX_STACK_SIZE];
};
typedef struct Stack stack_t;

stack_t stack_create(void);
int stack_push(stack_t *stack, int item);
int stack_pop(stack_t *stack);

inline int stack_peek(stack_t *stack){
    if(stack_is_empty(stack)) {
        return -1;
    }
    return stack->items[stack->size - 1];
}

void stack_free(stack_t *stack);

#endif // STACK_H
