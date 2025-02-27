#include <stdio.h>
#include "binary_heap.h"
#include "ring_buffer.h"

int main(void) 
{  
  rb_t rb = rb_create_buffer(16);
  
  rb_push(&rb, 1);
  rb_push(&rb, 2);
  rb_push(&rb, 3);

  printf("Read index: %d\n", rb.read_index);
  printf("Write index: %d\n", rb.write_index);

  printf("Popped: %d\n", rb_pop(&rb));
  printf("Popped: %d\n", rb_pop(&rb));
  printf("Popped: %d\n", rb_pop(&rb));

  printf("Read index: %d\n", rb.read_index);
  printf("Write index: %d\n", rb.write_index);

  rb_freeDeep_buffer(&rb);

  return 0;
  int heap_arr[11] = { 1, 3, 2, 
                 5, 10, 3, 
                 7, 0, 2, 
                 4, -2};
  
  bnt_t heap = bnt_create_bn_tree_arr(&heap_arr, 11);

  bnt_t heap2 = bnt_create_bn_tree(8);
  bnt_enqueue(&heap2,(int*) -3);
  bnt_enqueue(&heap2,(int*) 1);
  bnt_enqueue(&heap2,(int*) 29);
  bnt_enqueue(&heap2,(int*) 33);
  bnt_enqueue(&heap2,(int*) -1);
  bnt_enqueue(&heap2,(int*) -7);
  
  bnt_merge_heaps(&heap, &heap2);

  bnt_print_heap(&heap);
  
  bnt_freeDeep(&heap);
  bnt_freeDeep(&heap2);

  return 0;

  printf("\n --- Print heap before dequeue ---\n");
  bnt_print_heap(&heap);
  
  size_t num_dq = 8;
  printf("\nDequeueing %d elements from queue:", num_dq);

  for(size_t i = 0; i < num_dq; i++){
    printf("%d, ", (int) bnt_dequeue(&heap));
  }
  printf("\n");

  printf("\n--- Print heap after dequeue ---\n");
  
  bnt_enqueue(&heap,(int*) 1);
  bnt_enqueue(&heap,(int*) -1);
  bnt_enqueue(&heap,(int*) -100);
  bnt_enqueue(&heap,(int*) 100);

  bnt_print_heap(&heap);

  dn_arr_t indexes = dn_arr_create_default();
  
  int look_for = 1;
  bnt_index_of(&heap, &indexes, 1, &look_for);
  
  printf("Found %i instances of %i With indexes: \[", indexes.size, look_for);

  for(size_t i = 0; i < indexes.size; i++){
    printf("%d, ", indexes.data[i]);
  }

  printf("\]\n");
  bnt_freeDeep(&heap);
  dn_arr_freeDeep(&indexes);

  return 0;
  }
