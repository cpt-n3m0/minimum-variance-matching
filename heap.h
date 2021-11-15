#ifndef graphimported
#include "graph.h"
#endif
#include <math.h>
#define GET_PARENT(i) (int)floor((i - 2)/2)
#define GET_LEFT_CHILD(i) 2 * i + 1
#define GET_RIGHT_CHILD(i) 2 * i + 2



typedef struct heap_element {
  node_t node;
  double priority;
} heap_element;

typedef struct heap {
  heap_element* content;
  int max_size;
  int size;
} heap;



heap* create_heap(int max_size);
void swap(heap* heap, int i, int j);
void bubble_up(heap* heap);
void bubble_down(heap* heap);
node_t pop(heap* heap);
void push(heap* heap, node_t node, int priority);
void dump_heap(heap* h);
