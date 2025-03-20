#include "trie.h"
#include "arena_allocator.h"
static const arena_t* trie_arena;

void init_trie_arena(void){
  trie_arena  = malloc(sizeof(arena_t)); 
  arena_t temp = arena_init(ARENA_SIZE, ARENA_PAGES);
  memcpy(trie_arena, &temp, sizeof(arena_t));
}

void destroy_trie_arena(void){
  arena_destroy(trie_arena);
}

