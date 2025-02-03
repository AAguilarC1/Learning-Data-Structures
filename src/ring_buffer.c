#include "ring_buffer.h" 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>

rb_t rb_create_buffer(size_t capacity){
  rb_t rb;
  
  if(capacity > MAX_RING_BUFFER_SIZE){
    capacity = MAX_RING_BUFFER_SIZE;
  }

  if(capacity < DEFAULT_RING_BUFFER_SIZE){
    rb.capacity = DEFAULT_RING_BUFFER_SIZE;
  }

  rb.capacity = capacity;
  rb.read_index = 0;
  rb.write_index = 0;
  rb.buffer = (RB_ELEMENT*) calloc(capacity, sizeof(RB_ELEMENT));
  return rb;
}

rb_t rb_create_buffer_array(RB_ELEMENT* arr, size_t capacity){
  rb_t rb;
  if(capacity > MAX_RING_BUFFER_SIZE){
    return (rb_t) {
      .read_index = 0,
      .write_index = 0,
      .capacity = 0,
      .buffer = NULL
    };
  }
  
  if (capacity < DEFAULT_RING_BUFFER_SIZE){
    rb.capacity = DEFAULT_RING_BUFFER_SIZE;
  }

  rb.capacity = capacity;
  rb.read_index = 0;
  rb.write_index = 0;
  rb.buffer = arr;
  return rb;
}

void rb_add_array(rb_t *rb, RB_ELEMENT* arr, size_t size){
  if(arr == NULL){
    return;
  }

  if(size > MAX_RING_BUFFER_SIZE){
    return;
  }
  
  if(!rb_isEmpty(rb)){
    return;
  } 
  
  if(rb->capacity < size){
    while(rb->capacity < size){
      rb->capacity <<= 1;
    }
    rb->buffer = (RB_ELEMENT*) realloc(rb->buffer, rb->capacity * sizeof(RB_ELEMENT));

    if(rb->buffer == NULL){
      return;
    }
  }

  memcpy(rb->buffer, arr, size * sizeof(RB_ELEMENT));
  rb->write_index = 0;
  rb->read_index = 0;
  
}

void rb_push(rb_t* rb, RB_ELEMENT data){
  if(rb_isNull(rb)){
    return;
  }

  if(rb_isFull(rb)){
    return;
  }
  
  uint16_t index; 
  index = atomic_load(&rb->write_index);

  rb->buffer[index] = data;
  atomic_store(&rb->write_index, rb_wrapIndex(rb, index + 1));
}

RB_ELEMENT rb_pop(rb_t* rb){
  if(rb_isNull(rb)){
    return 0;
  }

  if(rb_isEmpty(rb)){
    return 0;
  }
  
  uint16_t index;
  index = atomic_load(&rb->read_index);

  RB_ELEMENT data = rb->buffer[index];
  atomic_store(&rb->read_index, rb_wrapIndex(rb, index + 1));

  return data;
}

void rb_free_buffer(rb_t *rb){
  if(rb->buffer == NULL){
    return;
  }

  rb->read_index = 0;
  rb->write_index = 0;
  rb->capacity = 0;
  free(rb->buffer);
  rb->buffer = NULL;
}

void rb_freeDeep_buffer(rb_t *rb){
  if(rb->buffer == NULL){
    return;
  }

  for(size_t i = 0; i < rb->capacity; i++){
    rb->buffer[i] = 0;
  }

  rb_free_buffer(rb);
}

void noop(void);

