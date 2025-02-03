#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>

#define DEFAULT_RING_BUFFER_SIZE 16
#define MAX_RING_BUFFER_SIZE 256
#define RB_ELEMENT int

#define RING_BUFFER_MASK(__rb__) ((__rb__)->capacity - 1)
#define rb_isEmpty(__rb__) ((__rb__)->size == 0)
#define rb_isFull(__rb__) ((__rb__)->size == (__rb__)->capacity)
#define rb_wrapIndex(__rb__, __index__) ((__index__) & RING_BUFFER_MASK(__rb__))
#define rb_isNull(__rb__) ((__rb__)->buffer == NULL)

struct ring_buffer {
  size_t size;
  size_t capacity;
  RB_ELEMENT *buffer;
  volatile _Atomic(uint16_t) read_index;
  volatile _Atomic(uint16_t) write_index;
};

typedef struct ring_buffer rb_t; 

rb_t rb_create_buffer(size_t capacity);
rb_t rb_create_buffer_array(RB_ELEMENT* arr, size_t array_size);
void rb_add_array(rb_t *rb, RB_ELEMENT* arr, size_t array_size);

void rb_push(rb_t *rb, RB_ELEMENT data);
RB_ELEMENT rb_pop(rb_t *rb);
void rb_flush(rb_t *rb);

void rb_free_buffer(rb_t *rb);
void rb_freeDeep_buffer(rb_t *rb);

void noop(void);

#endif // RING_BUFFER_H
