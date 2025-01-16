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
  
  if(left_child > (root->size) || right_child > (root->size) || pivot > (root->size)){
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

void bnt_bubble_up(bnt_t* root, int index){
  int parent_index = bnt_get_prnt_index(index);
  if(parent_index <= 0) {
    return;
  }
 
  if(bnt_compare(root->data[parent_index], root->data[index])){
    return;
  }
  
  bnt_swap(root->data[parent_index], root->data[index]);
  bnt_bubble_up(root, parent_index);

}

void bnt_enqueue(bnt_t* root, ELEMENT value){
  if(bnt_isNull(root)){
    return;
  }

  if(bnt_isEmpty(root)){
    root->data[1] = value;
    root->size++;
  }

  if(bnt_isFull(root)){
    root->capacity *= 2;
    root->data = realloc(root->data, sizeof(ELEMENT) * root->capacity);
    if(root->data == NULL) return;
  }

  root->data[root->size+1] = value;
  root->size++; 
  bnt_bubble_up(root, root->size);

}

ELEMENT bnt_dequeue(bnt_t* root){
  if(bnt_isNull(root)){
    return NULL;
  }

  if(bnt_isEmpty(root)){
    return NULL;
  }
  
  bnt_swap(root->data[1], root->data[root->size]);
  ELEMENT ret = root->data[root->size];
  root->data[root->size] = 0;
  root->size--;

  bnt_heapify(root, 1);

  return ret;
}

int bnt_contains(bnt_t* root, ELEMENT value){
  if(bnt_isNull(root)) {
    return 0;
  }
  
  if(bnt_isEmpty(root)){
    return 0;
  }

  for(size_t i = 1; i < root->size + 1; i++){
    if(root->data[i] == value) {
      return 1;
    }
  }

  return 0;
}

