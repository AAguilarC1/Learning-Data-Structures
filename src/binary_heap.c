#include "binary_heap.h"

bnt_t bnt_create_bn_tree(int capacity){
  bnt_t root = {
  .capacity = capacity,
  .size = 0,
  .data = NULL
  };

  root.data = (ELEMENT) calloc(capacity, sizeof(ELEMENT));
  /*assert((root.nodes != NULL) && "<Null pointer excepetion> Unable to create elements of tree");*/
  return root;
}

bnt_t bnt_create_bn_tree_arr(ELEMENT arr, size_t length_arr){
  size_t capacity = INITIAL_CAPACITY; 
  
  if(length_arr > MAX_CAPACITY){
    printf("Array larger than heap max capacity (%d)", MAX_CAPACITY);
    return (bnt_t) {.size = 0, .capacity = 0, .data = NULL};
  }

  if(capacity < length_arr){
    capacity *= 2;
    if(capacity > MAX_CAPACITY){
      capacity = MAX_CAPACITY;
    }
  }
  
  bnt_t root = {
    .capacity = capacity,
    .size = length_arr,
    .data = (ELEMENT) calloc(length_arr + 1, sizeof(ELEMENT))
  };
  
  root.data[0] = 0;

  for(size_t i = 0; i < root.size + 1; i++){
    root.data[i + 1] = arr[i];
  }
  
  size_t i = (length_arr - 1) / 2;

  while(i > 0){
    bnt_heapify(&root, i);
    i--;
  }

  return root;
}

void bnt_heapify(bnt_t* root, int index){
  if(bnt_isNull(root)){
    return;
  }

  if(index < 0){
    return;
  }
  
  int left_child = bnt_get_lchild_index(index);
  int right_child = bnt_get_rchild_index(index);
  int pivot = index;

  if(left_child <= 0 || right_child <= 0 || pivot <= 0) {
    return;
  }
  
  if(left_child > (root->size + 1) || right_child > (root->size + 1) || pivot > (root->size + 1)){
    return;
  }

  int left_or_right = (bnt_compare(root->data[left_child],  root->data[right_child])) ? left_child : right_child;

  if(bnt_compare(root->data[left_or_right], root->data[index])){
    pivot = left_or_right;
  }
  
  if(pivot != index){
    bnt_swap(root->data[pivot], root->data[index]);
    bnt_heapify(root, pivot);
  }

}
