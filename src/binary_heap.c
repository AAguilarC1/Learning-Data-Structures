#include "binary_heap.h"
#include "util.h"
#include <stddef.h>
#include <string.h>

/**
 * @brief Creates an empty heap with an specified capacity
 * @param capacity Is the capacity of the heap
 *
 * @note The heap dynamically increases its capacity when filled
 **/
bnt_t bnt_create_bn_tree(int capacity){
  if(capacity > MAX_CAPACITY){
    capacity = MAX_CAPACITY;
  }
    
  if(capacity <= 0){
    capacity = INITIAL_CAPACITY;
  }

  bnt_t root = {
  .capacity = capacity,
  .size = 0,
  .data = (ELEMENT) calloc(capacity, sizeof(ELEMENT))
  };

  return root;
}

/**
 * @brief This function generates a binary heap from an array.
 * @param arr - Pointer to the Array of Elements to be converted to a binary heap
 * @param length_arr - Length of the input array
**/
bnt_t bnt_create_bn_tree_arr(ELEMENT arr, size_t length_arr){
  size_t capacity = INITIAL_CAPACITY; 
  
  if(length_arr > MAX_CAPACITY){
    printf("Array larger than heap max capacity (%d)", MAX_CAPACITY);
    return (bnt_t) {.size = 0, .capacity = 0, .data = NULL};
  }

  while(capacity < length_arr){
    capacity <<= 1;
    if(capacity > MAX_CAPACITY){
      capacity = MAX_CAPACITY;
    }
  }
  
  bnt_t root = {
    .capacity = capacity,
    .size = length_arr,
    .data = (ELEMENT) calloc(capacity, sizeof(ELEMENT))
  };
  
  root.data[0] = 0;

  for(size_t i = 0; i < root.size; i++){
    root.data[i + 1] = arr[i];
  }
  
  size_t i = (length_arr - 1) / 2;

  while(i > 0){
    bnt_heapify(&root, i);
    i--;
  }

  return root;
}

/**
 * @brief The following function converts a given heap into:
 * - Min Heap
 * - Max heap
 *   Given which type was define in the header file
 *
 * @param root - Is the heap that is going to be heapify
 * @param index - Is the index from where the heapify function will start
 * @return A status flag if the function completed or fail along the way
 */
bnt_stat_t bnt_heapify(bnt_t* root, int index){
  if(bnt_isNull(root)){
    return STATUS_NOT_OK;
  }

  if(index < 0){
    return STATUS_NOT_OK;
  }

  size_t left_child = bnt_get_lchild_index(index);
  size_t right_child = bnt_get_rchild_index(index);
  size_t pivot = index;

  if(left_child <=0 || right_child <= 0 || pivot <= 0){
    return STATUS_NOT_OK;
  }
  
  // TODO: Re do this logic so it only terminates when pivot is out of bounds

  if(left_child == root->size){
    if(bnt_compare(root->data[left_child], root->data[index])){
      bnt_swap(root->data[left_child], root->data[index]);
      return STATUS_OK;
    }
  }

  if(right_child > (root->size) || pivot > (root->size)){
    return STATUS_OK;
  }

  size_t left_or_right = (bnt_compare(root->data[left_child],  root->data[right_child])) ? left_child : right_child;

  if(bnt_compare(root->data[left_or_right], root->data[index])){
    pivot = left_or_right;
  }
  
  if(pivot != (size_t) index){
    bnt_swap(root->data[pivot], root->data[index]);
    bnt_heapify(root, pivot);
  }

  return STATUS_OK;
}

/**
 * @brief This function merges two heaps without consuming the source heap
 * @param dst - Is the heap where the merge heaps will combine
 * @param src - Is the heap which will be merge to the final heap 
 * @return - A status flag if function completed or not 
 **/
bnt_stat_t bnt_merge_heaps(bnt_t* dst, bnt_t* src){
  if((bnt_isNull(dst)) || (bnt_isNull(src))){
    return STATUS_NOT_OK;
  }
  
  if((bnt_isEmpty(dst)) && bnt_isEmpty(src)){
    return STATUS_NOT_OK;
  }
  
  if(bnt_isEmpty(src)){
    return STATUS_OK;
  }

  size_t Total_Cap = dst->capacity + src->capacity;

  if(Total_Cap > MAX_CAPACITY){
    printf("Not Enought Memory. Max allocation size is %d", MAX_CAPACITY);
    return STATUS_NOT_OK;
  }
  
  if(dst->capacity < Total_Cap){
    while(Total_Cap > dst->capacity){
      dst->capacity <<= 1;
    }

    dst->data = (ELEMENT) realloc(dst->data, dst->capacity * sizeof(ELEMENT));

    if(bnt_isNull(dst->data)){
      return STATUS_NOT_OK;
    }
  }

  for(size_t i = 1; i <= src->size; i++){
    bnt_enqueue(dst, src->data[i]);
  }

  return STATUS_OK;
}

/**
 * @brief Merges two heaps where the source heap is consumed and freed
 * @param dst - The heap where the combine heaps will be stored
 * @param src - The source heap which will be freed and combined to the destination heap
 * @return - A status flag if the function completed or not
 */
bnt_stat_t bnt_merge_heaps_consumer(bnt_t* dst, bnt_t* src){
  if(bnt_isNull(dst) || bnt_isNull(src)){
    return STATUS_NOT_OK;
  }
  
  if(bnt_isEmpty(dst) && bnt_isEmpty(src)){
    return STATUS_NOT_OK;
  }

  if(bnt_isEmpty(src)){
    bnt_free(src);
    return STATUS_OK;
  }

  size_t total_size = dst->size + src->size;

  if(total_size > MAX_CAPACITY){
    return STATUS_NOT_OK;
  }

  if(dst->capacity < total_size){
    while(dst->capacity < total_size){
      dst->capacity <<= 1;
    }
  
    dst->data = (ELEMENT) realloc(dst->data, dst->capacity * sizeof(ELEMENT));

    if(bnt_isNull(dst->data)){
      return STATUS_NOT_OK;
    }
  }
  
  while(!(bnt_isEmpty(src))){
    ELEMENT temp = bnt_dequeue(src);
    bnt_enqueue(dst, temp);
  }

  bnt_free(src);

  return STATUS_OK;
}

/**
 * @brief This functions moves the current children upwards until the heap is balanced
 * @param root - Is the heap where the index is located
 * @param index - Is the index of the children that is going to be moved upwards
**/
void bnt_bubble_up(bnt_t* root, int index){
  if(index <= 0 || index > root->size){
    return;
  }

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

/**
 * @brief This function enqueues a value key onto the heap
 * @param root - The heap to where the value is going to be enqueued 
 * @param value - The value to be enqueued onto the heap
 * @return - A status flag if the function completed successfully or not
**/
bnt_stat_t bnt_enqueue(bnt_t* root, ELEMENT value){
  if(bnt_isNull(root)){
    return STATUS_NOT_OK; 
  }
  if(bnt_isEmpty(root)){
    root->data[1] = value;
    root->size++;
    return STATUS_OK;
  }

  if(bnt_isFull(root)){
    root->capacity <<= 1;
    root->data = realloc(root->data, sizeof(ELEMENT) * root->capacity);
    if(bnt_isNull(root->data)) {
      return STATUS_NOT_OK;
    }
  }

  root->size++; 
  root->data[root->size] = value;
  bnt_bubble_up(root, root->size);
  return STATUS_OK;
}

/**
 * @brief The function removes the top value of the heap
 * @param root - The heap where the top most value will be removed from
 * @return The element stored at the top most important vaue of the root
**/
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

/**
 * @brief The function returns true or false if the value is contained in the heap
 * @param root - Is the heap where the value is going to be searched
 * @param value - Is the value that is going to be search for
 * @return True or False if the value is contained or not in the heap
**/
bool bnt_contains(bnt_t* root, ELEMENT value){
  if(bnt_isNull(root)) {
    return false;
  }
  
  if(bnt_isEmpty(root)){
    return false; 
  }
  
  for(size_t i = 1; i < root->size + 1; i++){
    if(root->data[i] == value) {
      return true;
    }
  }

  return false;
}

/**
 * @brief This function will return all the indexes where Value is found
 * @param root - Is the heap where the value is going to be searched
 * @param indexes - Is a dynamic array where the indexes will be stored
 * @param curr_index - Is the current index that is going to be check for the value
 * @param value - Is the element that is being search within the heap
 * @return - A status flag whether function completed successfully or not
**/
bnt_stat_t bnt_index_of(bnt_t* root, dn_arr_t* indexes, size_t curr_index, ELEMENT value){
  if(bnt_isNull(root) || dn_arr_isNull(indexes)){
    return STATUS_NOT_OK;
  }
  
  if(curr_index > root->size){
    return STATUS_OK;
  }

  bnt_stat_t lstat = bnt_index_of(root,
                                  indexes,
                                  bnt_get_lchild_index(curr_index),
                                  value);
  bnt_stat_t rstat = bnt_index_of(root,
                                  indexes,
                                  bnt_get_rchild_index(curr_index),
                                  value);

  if(root->data[curr_index] == value){
    dn_arr_push(indexes, curr_index);
  }

  return(lstat && rstat);
}

/**
 * @brief This function will print the values contained in the heap
 * @param heap - Is the heap that is going to be printed
 * @param name - The name that will be assigned to the heap
 * @return - A status flag whether the function had failed or successfully completed
 **/
bnt_stat_t bnt_print_heap_with_name(bnt_t* heap, const char* name){
  if(bnt_isNull(heap)){
    return  STATUS_NOT_OK;
  }

  printf("%s: \{\n", name);

  for(size_t i = 1; i <= heap->size; i++){
    printf("\t %li: %d,\n", i, heap->data[i]);
  }
  printf("\}\n");

  return STATUS_OK;
}

/**
 * @brief This function will free the heap
 * @param root - Is the heap that will be freed
 **/
void bnt_free(bnt_t* root){
  root->size = 0;
  root->capacity = 0;
  free(root->data);
  root->data = NULL;
}

/**
 * @brief This function will free the heap and set its values to 0
 * @param root - The heap to be freed and its values set to 0
 **/
void bnt_freeDeep(bnt_t* root){
  for(size_t i = 1; i <= root->size; i++){
    root->data[i] = 0;
  }

  bnt_free(root);

 }

