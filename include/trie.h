#ifndef TRIE_H
#define TRIE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arena_allocator.h"

#define ARENA_SIZE KB(10)
#define ARENA_PAGES 10

void init_trie_arena(void);
void destroy_trie_arena(void);

#endif // TRIE_H
