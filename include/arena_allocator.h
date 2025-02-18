#ifndef ARENA_ALLOCATOR_H
#define ARENA_ALLOCATOR_H 

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define KB(__SIZE__) ((__SIZE__) * 1024)
#define MB(__SIZE__) ((__SIZE__) * 1024 * 1024)
#define ARENA_DEFAULT_REGION_CAPACITY KB(1)

#ifndef ARENA_MAX_NUM_REGIONS
#define ARENA_MAX_NUM_REGIONS 10
#endif // ARENA_MAX_NUM_REGIONS

#define arena_isFull(__ARENA__) ((__ARENA__)->total_size == (__ARENA__)->total_capacity)
#define arena_isEmpty(__ARENA__) ((__ARENA__)->total_size == 0)
#define arena_hasSpace(__ARENA__,__SIZE__) ((__ARENA__)->total_size + (__SIZE__) <= (__ARENA__)->total_capacity)
#define arena_region_hasSpace(__REGION__,__SIZE__) ((__REGION__)->size + (__SIZE__) <= (__REGION__)->capacity)

struct Region{
  size_t size;
  size_t capacity;
  void* memory; 
  struct Region* next;
};

typedef struct Region region_t; 

struct Arena{
  size_t total_capacity;
  size_t total_size;
  region_t* pool;
  uint8_t num_regions_available;
};

typedef struct Arena arena_t;

region_t* arena_region_alloc(size_t capacity);
void arena_region_free(region_t* region);

arena_t arena_init(size_t region_capacity, uint8_t num_regions);
void* arena_alloc_align(arena_t* arena, size_t size_bytes, size_t alignment);
void* arena_alloc(arena_t* arena, size_t size_bytes);
void arena_reset(arena_t* arena);

void arena_destroy(arena_t* arena);

#endif // ARENA_ALLOCATOR_H
