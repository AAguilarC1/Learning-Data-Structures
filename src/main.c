#include "trie.h"

int main(void) {  
  trie_t trie = trie_create();
  trie_insert(&trie, "Hello");
  trie_insert(&trie, "world");

  trie_insert(&trie, "cat");
  trie_insert(&trie, "dog");
  trie_insert(&trie, "apple");
  trie_insert(&trie, "car");

  printf("hello: %d\n", trie_search(&trie, "heLlo"));
  printf("world: %d\n", trie_search(&trie, "world"));
  printf("cat: %d\n", trie_search(&trie, "cat"));
  printf("dog: %d\n", trie_search(&trie, "dog"));
  printf("apple: %d\n", trie_search(&trie, "apple"));
  printf("car: %d\n", trie_search(&trie, "car"));

  printf("hello world: %d\n", trie_search(&trie, "hello WorlD"));

  trie_destroy(&trie);

  return 0;
}
