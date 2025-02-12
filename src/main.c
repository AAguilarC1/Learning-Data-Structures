#include "arena_allocator.h"

struct TestStruct{
  int a;
  int b;
  int c;
};
typedef struct TestStruct test_struct;

int main(void) 
{  
  arena_t arena = arena_init(1024, 3);
  printf("Before allocation\n");
  printf("Arena region capacity: %lu\n", arena.pool->capacity);
  printf("Arena total size: %lu\n", arena.total_size);
  printf("Arena num regions: %u\n", arena.num_regions_available);
  printf("Max total size: %lu\n", arena.total_capacity);

  size_t ptr3_len = 100;
  size_t ptr4_len = 100;
  int32_t* ptr3 = (int32_t*) arena_alloc(&arena, ptr3_len * sizeof(int32_t));
  double* ptr4 = (double*) arena_alloc(&arena, ptr4_len * sizeof(double));
  char* ptr5 = (char*) arena_alloc(&arena, 55 * sizeof(char));

  printf("After allocation\n");
  printf("Arena total size: %lu\n", arena.total_size);
  printf("Arena num regions available: %u\n", arena.num_regions_available);

  if(ptr5 != NULL){
    memcpy(ptr5, "Hello, World!", 13);
    printf("ptr5: %s\n", ptr5);
  }
  
  test_struct* ptr6 = (test_struct*) arena_alloc(&arena,  sizeof(test_struct));
  if(ptr6 != NULL){
    ptr6->a = 10;
    ptr6->b = 20;
    ptr6->c = 30;

    printf("ptr6->a: %i\n", ptr6->a);
    printf("ptr6->b: %i\n", ptr6->b);
    printf("ptr6->c: %i\n", ptr6->c);
  }

  if(ptr4 != NULL){
    for(size_t i = 0; i < ptr4_len; i++){
      ptr4[i] = rand() / (float) RAND_MAX; 
    }

    for(size_t i = 0; i < ptr4_len; i++){
      printf("ptr4[%lu]: %f\n", i, ptr4[i]);
    }
  }

  if(ptr3 != NULL){
    for(size_t i = 0; i < ptr3_len; i++){
      ptr3[i] = (uint16_t) i;
    }

    for(size_t i = 0; i < ptr3_len; i++){
      printf("ptr3[%lu]: %i\n", i, ptr3[i]);
    }
  }
  arena_destroy(&arena);

  return 0;

}
