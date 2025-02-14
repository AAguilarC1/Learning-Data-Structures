#include "arena_allocator.h"

region_t* arena_region_alloc(size_t capacity){
  region_t *region = (region_t*) malloc(sizeof(region_t));
  region->size = 0;
  region->capacity = capacity;
  region->memory = (uint8_t*) calloc(capacity, sizeof(uint8_t));  
  region->next = NULL;

  return region;
}

void arena_region_free(region_t* region){
  assert(region != NULL);
  memset(region->memory, 0, region->capacity * sizeof(uint8_t));

  free(region->memory);
  region->capacity = 0;
  region->size = 0;
  region->memory = NULL;
  region->next = NULL;

}

arena_t arena_init(size_t region_capacity, uint8_t num_regions){
  assert(region_capacity > 0);
  assert(num_regions > 0 && num_regions <= ARENA_MAX_NUM_REGIONS);
  arena_t arena;
  arena.total_size = 0;
  arena.pool = arena_region_alloc(region_capacity);
  arena.num_regions_available = num_regions - 1;
  arena.total_capacity = region_capacity * num_regions * sizeof(uint8_t);
  return arena;
}

// TODO: Add alignment support for the allocation. Currently has undefined behavior according to 
// the undefined behavior sanitizer.
void* arena_alloc(arena_t* arena, size_t size_bytes){
  assert(arena != NULL && "Arena is NULL");
  assert(arena->pool != NULL && "Arena pool is NULL");
  assert(size_bytes > 0 && "Invalid allocation size requested. Size must be greater than 0");

  size_t size = size_bytes;

  if(size > arena->pool->capacity){
    return NULL;
  }

  if(arena_isFull(arena)){
    return NULL;
  }

  if(!arena_hasSpace(arena, size)){
    return NULL;
  }

  region_t *current = arena->pool;

  while(current != NULL){
    if(arena_region_hasSpace(current, size)){
      void* ptr = (uint8_t*) current->memory + current->size;
      current->size += size;
      arena->total_size += size;
      return ptr;
    }
    current = current->next;  
  }
    if(arena->num_regions_available > 0){
      region_t *new_region = arena_region_alloc(arena->pool->capacity);
      new_region->next = arena->pool;
      arena->pool = new_region;
      arena->num_regions_available--;

      void* ptr = new_region->memory;
      new_region->size += size;
      arena->total_size += size;
      return ptr;

    }
    
  return NULL;

}

void arena_reset(arena_t* arena){
  assert(arena != NULL);
  assert(arena->pool != NULL);
  
  region_t *current = arena->pool;
  while(current != NULL){
    memset(current->memory, 0, current->capacity * sizeof(uint8_t));
    current->size = 0;
    current = current->next;
  }

  arena->total_size = 0;

}

void arena_destroy(arena_t* arena){
  assert(arena != NULL);
  assert(arena->pool != NULL);

  while(arena->pool != NULL){
    region_t *temp = arena->pool;
    arena->pool = arena->pool->next;
    arena_region_free(temp);
    free(temp);
    temp = NULL;
  }

  arena->num_regions_available = 0;
  arena->total_size = 0;
  arena->total_capacity = 0;

}

