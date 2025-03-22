#include "trie.h"
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 55

void trie_str_to_lower(char* str, size_t len){
  for(size_t i = 0; i < len; i++){
    if(str[i] >= 'A' && str[i] <= 'Z'){
      str[i] ^= 0x20;
    }
  }
}

bool trie_valid_key(const char* key){
  size_t len = strlen(key);
  if(len > MAX_STR_LEN){
    return false;
  }

  for(size_t i = 0; i < len; i++){
    if((key[i] < 'a' || key[i] > 'z') && key[i] != 32){
      return false;
    }
  }

  return true;
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


