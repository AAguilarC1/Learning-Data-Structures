#include "binary_tree.h"

bnt_t bnt_create_bn_tree(int capacity){
  bnt_t root;
  root.size = 0;
  root.capacity = capacity;

  root.nodes = (ELEMENT) calloc(capacity, sizeof(int))
  assert(root.nodes != NULL & "<Null pointer excepetion> Unable to create elements of tree");
  return root;
}

int bnt_enqueue(bnt_t*, int data){
  return 0;
}

