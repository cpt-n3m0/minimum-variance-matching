#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

node_t  create_node(int i, int j, float weight){
  node_t node;
  node.i = i;
  node.j = j;
  node.weight = weight;
  return node;
}

node_t ** create_node_matrix(int lenq, int lent){
  node_t ** node_matrix;
  node_matrix = malloc(sizeof(node_t*) * lenq);
  ALLOC_ERROR(node_matrix, "failed to allocate first dim")
  for(int i = 0; i < lenq; i++)
  {
    node_matrix[i] = malloc(sizeof(node_t) * lent);
    ALLOC_ERROR(node_matrix, "failed to allocate second dim")
  }
  return node_matrix;
}


 node_t*  get_neighbours(node_t node, float ** dist_matrix, int r, int c){
  node_t * neighbours = NULL;
  int i = node.i;
  int j = node.j;
  int num_neighbours = get_num_neighbours(node, c);
  if (i == r - 1)
    return neighbours;

  neighbours = malloc(sizeof(node_t) * num_neighbours);
  for( int k = 1 ; k <= num_neighbours; k++){
    node_t new_node = create_node(i + 1, j + k, dist_matrix[i + 1][j + k] * dist_matrix[i + 1][j + k]);
    neighbours[k - 1] = new_node;
  }
  return neighbours;
}
