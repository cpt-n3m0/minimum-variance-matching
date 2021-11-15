#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

heap* create_heap(int max_size){
  heap* h;
  h = malloc(sizeof(heap));
  ALLOC_ERROR(h, "failed to allocate heap");
  h->max_size = max_size;
  h->size = 0;
  h->content = (heap_element*)malloc(sizeof(heap_element) * max_size);
  ALLOC_ERROR(h->content, "failed to allocate");
  return h;
}

void dump_heap(heap* h){

  for (int i =0; i < h->size ; i++)
    printf("%f ", h->content[i].priority);
  printf("\n");
}

void swap(heap* heap, int i, int j){
    heap_element tmp = heap->content[i];
    heap->content[i] = heap->content[j];
    heap->content[j] = tmp;
}

void bubble_up(heap* heap){
  int c = heap->size - 1;

  while(heap->content[c].priority < heap->content[GET_PARENT(c)].priority){
    swap(heap, c, GET_PARENT(c));
    c = GET_PARENT(c);
    if(c <= 0)
      break;
  }
}

void bubble_down(heap* heap){

  int c = 0;
  while( c < heap->size)
  {
    int lowest = -1;
    int leftc = GET_LEFT_CHILD(c);
    int rightc = GET_RIGHT_CHILD(c);

    if (rightc < heap->size && leftc < heap->size)
    {
      int rightp = heap->content[rightc].priority;
      int leftp = heap->content[leftc].priority;
      lowest = rightp < leftp ? rightc : leftc;
    }
    else if (rightc < heap->size)
    {
      lowest = rightc;
    }
    else if (leftc < heap->size)
    {
      lowest = leftc;
    }
    else
      break;

    if(heap->content[c].priority > heap->content[lowest].priority)
    {
      swap(heap, lowest, c);
      c = lowest;
    }
    else
      break;

  }

}

node_t pop(heap* heap){
  if(heap->size == 0){
    printf("ERROR: heap is empty");
    exit(-1);
  }
  heap_element min_e = heap->content[0];
  heap->size -= 1;
  heap->content[0] = heap->content[heap->size] ;
  if (heap->size > 0)
    bubble_down(heap);
  return min_e.node;

}
void push(heap* heap, node_t node, int priority){

  if (heap->size == heap->max_size){
    printf("ERROR: adding to a full heap");
    return;
  }


  heap_element new_elem;
  new_elem.node = node;
  new_elem.priority = priority;

  heap->content[heap->size] = new_elem;
  heap->size += 1;
  if (heap->size > 1)
    bubble_up(heap);

}
