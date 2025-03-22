#include "trie.h"
#include <stdlib.h>



}

trie_t trie_create(void){
  trie_t trie = {0};
  trie.pool = arena_init(ARENA_SIZE, ARENA_PAGES);
  trie.root = arena_alloc(&trie.pool, sizeof(trie_node_t));
  return trie;
}

void trie_destroy(trie_t* trie){
  arena_destroy(&trie->pool);
  trie->root = NULL;
}


