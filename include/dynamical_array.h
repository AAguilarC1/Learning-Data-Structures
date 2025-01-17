#ifndef DYNAMICAL_ARRAY_H
#define DYNAMICAL_ARRAY_H
#include<stdlib.h>
#include<stdio.h>

#define DN_MAX_ARRAY_CAPACITY 255
#define DN_DEFAULT_CAPACITY  8
#define DN_ELEMENT int

#define dn_arr_create_default() dn_arr_create(DN_DEFAULT_CAPACITY)
struct dynamic_array{
  size_t size;
  size_t capacity;
  DN_ELEMENT* arr;
};

typedef struct dynamic_array dn_arr_t; 

dn_arr_t dn_arr_create(int capacity);
#endif // DYNAMICAL_ARRAY_H

