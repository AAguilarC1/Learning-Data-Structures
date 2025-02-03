#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>

#define DEFAULT_RING_BUFFER_SIZE 16
#define MAX_RING_BUFFER_SIZE 255
#define RB_ELEMENT int

#define RING_BUFFER_MASK(__rb__) ((__rb__)->capacity - 1)
#define rb_isEmpty(__rb__) ((__rb__)->read_index == (__rb__)->write_index)
#define rb_isFull(__rb__) (rb_wrapIndex(__rb__, (__rb__)->write_index + 1) == (__rb__)->read_index)
#define rb_wrapIndex(__rb__, __index__) ((__index__) & RING_BUFFER_MASK(__rb__))
#define rb_isNull(__rb__) ((__rb__)->buffer == NULL)

struct ring_buffer {
  volatile _Atomic(uint16_t) read_index;
  volatile _Atomic(uint16_t) write_index;
  RB_ELEMENT *buffer;
  size_t capacity;
};

typedef struct ring_buffer rb_t; 

rb_t rb_create_buffer(size_t capacity);
rb_t rb_create_buffer_array(RB_ELEMENT* arr, size_t capacity);
void rb_add_array(rb_t *rb, RB_ELEMENT* arr, size_t size);

void rb_push(rb_t *rb, RB_ELEMENT data);
RB_ELEMENT rb_pop(rb_t *rb);

void rb_free_buffer(rb_t *rb);
void rb_freeDeep_buffer(rb_t *rb);

void noop(void);

#endif // RING_BUFFER_H
