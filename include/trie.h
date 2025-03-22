#ifndef TRIE_H
#define TRIE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "arena_allocator.h"

#define ARENA_SIZE KB(10)
#define ARENA_PAGES 10

struct Trie{
  struct TrieNode* root;
  arena_t pool;
};

typedef struct Trie trie_t;


void trie_str_to_lower(char* str, size_t len);
bool trie_valid_key(const char* key);

trie_t trie_create(void);
void trie_destroy(trie_t* trie);

#endif // TRIE_H
