#ifndef DYNAMICAL_ARRAY_H
#define DYNAMICAL_ARRAY_H
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>

#define DN_MAX_ARRAY_CAPACITY 255
#define DN_DEFAULT_CAPACITY  8
#define DN_ELEMENT int

#define dn_arr_isNull(__arr__) (__arr__) == NULL
#define dn_arr_isEmpty(__arr__) (__arr__)->size == 0
#define dn_arr_isFull(__arr__) (__arr__)->size >= (__arr__)->capacity
#define dn_arr_create_default() dn_arr_create(DN_DEFAULT_CAPACITY)

struct dynamic_array{
  size_t size;
  size_t capacity;
  DN_ELEMENT* data;
};

typedef struct dynamic_array dn_arr_t; 

dn_arr_t dn_arr_create(int capacity);

void dn_arr_push(dn_arr_t* arr, DN_ELEMENT value);
DN_ELEMENT dn_arr_pop(dn_arr_t* arr);

inline DN_ELEMENT dn_arr_top(dn_arr_t* arr){
  if(dn_arr_isNull(arr)){
    return -1;
  }
  
  if(dn_arr_isEmpty(arr)){
    return -1;
  }

  return arr->data[arr->size - 1];
}

inline DN_ELEMENT dn_arr_bot(dn_arr_t* arr){
  if(dn_arr_isNull(arr)){
      return -1;
  } 
  
  if(dn_arr_isEmpty(arr)){
    return -1;
  }
  return arr->data[0];
}

void dn_arr_free(dn_arr_t* dn_arr);
void dn_arr_freeDeep(dn_arr_t* dn_arr);

#endif // DYNAMICAL_ARRAY_H

