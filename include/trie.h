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

struct TrieNode{
  bool is_end_of_word;
  struct TrieNode* children[26];
};

typedef struct TrieNode trie_node_t;

void trie_str_to_lower(char* str, size_t len);
bool trie_valid_key(const char* key);

trie_t trie_create(void);
void trie_destroy(trie_t* trie);

void trie_insert(trie_t* trie, const char* key);
bool trie_search(trie_t* trie, const char* key);

#endif // TRIE_H
