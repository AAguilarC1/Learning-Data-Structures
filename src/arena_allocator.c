#include "arena_allocator.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

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


void* arena_alloc_align(arena_t* arena, size_t size_bytes, size_t alignment){
 assert(arena != NULL && "Arena is NULL");
  assert(arena->pool != NULL && "Arena pool is NULL");
  assert(size_bytes > 0 && "Invalid allocation size requested. Size must be greater than 0");
  assert(alignment > 0 && "Invalid alignment requested. Alignment must be greater than 0");

  if(arena_isFull(arena)){
    return NULL;
  }

  if(!arena_hasSpace(arena, size_bytes)){
    return NULL;
  }
  
  if(alignment == 0 || (alignment & (alignment - 1)) != 0){
    return NULL;
  }

  region_t *current = arena->pool;

  while(current != NULL){
    uintptr_t offset = (uintptr_t) current->size + (uintptr_t) current->memory;
    uintptr_t padding = (~offset + 1) & (alignment - 1);
    offset += padding;

    if(offset + size_bytes <= (uintptr_t) current->memory + (uintptr_t) current->capacity){
      current->size += size_bytes + padding;
      arena->total_size += size_bytes + padding;
      memset((void*) offset, 0, size_bytes);
      return (void*) offset;
    }
    current = current->next;
  }

  if(arena->num_regions_available > 0){
    region_t *new_region = arena_region_alloc(arena->pool->capacity);
    
    uintptr_t offset = (uintptr_t) new_region->memory;
    uintptr_t padding = (~offset + 1) & (alignment - 1);
    offset += padding;

    if(offset + size_bytes > (uintptr_t) new_region->memory + (uintptr_t) new_region->capacity){
      arena_region_free(new_region);
      return NULL;
    }

    new_region->next = arena->pool;
    arena->pool = new_region;
    arena->num_regions_available--;
  
    new_region->size += size_bytes + padding;
    arena->total_size += size_bytes + padding;
    memset((void*) offset, 0, size_bytes);
    return (void*) offset;
  }

  return NULL;
}

void* arena_alloc(arena_t* arena, size_t size_bytes){
  return arena_alloc_align(arena, size_bytes, _Alignof(uint32_t));
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

