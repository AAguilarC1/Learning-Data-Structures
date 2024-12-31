#ifndef STACK_H
#define STACK_H
#define MAX_STACK_SIZE (1<<8) // 256

#define stack_size(__stack__) (__stack__)->size
#define stack_is_empty(__stack__) (__stack__)->size == 0
#define stack_is_full(__stack__) (__stack__)->size == MAX_STACK_SIZE

struct Stack {
    unsigned int size;    
    int items[MAX_STACK_SIZE];
};
typedef struct Stack stack_t;

stack_t create_stack(void);
int push(stack_t *stack, int item);
int pop(stack_t *stack);

inline int peek(stack_t *stack){
    if(stack_is_empty(stack)) {
        return -1;
    }
    return stack->items[stack->size - 1];
}

void free_stack(stack_t *stack);

#endif // STACK_H