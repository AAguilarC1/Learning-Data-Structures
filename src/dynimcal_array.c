#include "dynamical_array.h"

dn_arr_t dn_arr_create(int capacity){
  if(capacity > DN_MAX_ARRAY_CAPACITY){
    capacity = DN_MAX_ARRAY_CAPACITY;
  }

  dn_arr_t dn_arr = {
    .size = 0,
    .capacity = capacity,
    .arr = (DN_ELEMENT*) calloc(capacity, sizeof(DN_ELEMENT))
  };
 
  return dn_arr;

}
