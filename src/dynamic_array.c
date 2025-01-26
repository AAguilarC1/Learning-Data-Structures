#include "dynamic_array.h"

dn_arr_t dn_arr_create(int capacity){
  if(capacity > DN_MAX_ARRAY_CAPACITY){
    capacity = DN_MAX_ARRAY_CAPACITY;
  }
  if(capacity <= 0){
    capacity = DN_DEFAULT_CAPACITY;
  }
  
  dn_arr_t dn_arr = {
    .size = 0,
    .capacity = capacity,
    .data = (DN_ELEMENT*) calloc(capacity, sizeof(DN_ELEMENT))
  };
 
  return dn_arr;

}

void dn_arr_push(dn_arr_t* arr, DN_ELEMENT value){
  if(dn_arr_isNull(arr)){
    return;
  }

  if(arr->size == DN_MAX_ARRAY_CAPACITY){
    return;
  }
  
  if(dn_arr_isFull(arr)){
    arr->capacity <<= 1;
    if(arr->capacity >= DN_MAX_ARRAY_CAPACITY){
      arr->capacity = DN_MAX_ARRAY_CAPACITY;
    }

    arr->data = (DN_ELEMENT*) realloc(arr->data, sizeof(DN_ELEMENT) * arr->capacity);
    
    if(dn_arr_isNull(arr->data)){
      return;
    }
  }

  arr->data[arr->size] = value;
  arr->size++;
}

DN_ELEMENT dn_arr_pop(dn_arr_t* arr){
  if(dn_arr_isNull(arr)){
    return -1;
  }
  
  if(dn_arr_isEmpty(arr)){
    return -1;
  }

  DN_ELEMENT ret = arr->data[arr->size - 1];
  arr->data[arr->size - 1] = 0;
  arr->size--;

  return ret;
}

void dn_arr_free(dn_arr_t* arr){
  if(dn_arr_isNull(arr)){
    return;
  }

  arr->size = 0;
  arr->capacity = 0;
  free(arr->data);
  arr->data = NULL;
}

void dn_arr_freeDeep(dn_arr_t* arr){
  if(dn_arr_isNull(arr)){
    return;
  }

  for(size_t i = 0; i < arr->size; i++){
    arr->data[i] = 0;
  }
  
  dn_arr_free(arr);

}

