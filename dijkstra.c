#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "graph.h"
#include "heap.h"
#include "dijkstra.h"
#include "mvm.h"
#define INF 100000


#define nodecmp(a, b) (a.i == b.i) && (a.j == b.j)

node_t* invert_array(node_t* a, int size){
  node_t * ia = malloc(sizeof(node_t) * size);
  ALLOC_ERROR(ia, "failed to allocate");
  int j = 0;
  for(int i = size - 1; i >= 0; i--, j++)
  {
    ia[j] = a[i];
  }
  return ia;

}

path_t build_path(node_t ** prev_node_matrix, float** dist_matrix, node_t start, node_t goal){
  node_t cur = goal;
  path_t path;
  path.steps = malloc(sizeof(node_t*));
  ALLOC_ERROR(path.steps, "failed to allocate");
  path.num_steps = 0;
  path.distance = 0;

  while(1){
    path.steps = realloc(path.steps, sizeof(node_t) * (path.num_steps + 1));
    if(path.steps == NULL)
    {
      printf("ERROR: failed to increase step array size");
      exit(-1);
    }
    path.distance += cur.weight;
    path.steps[path.num_steps] = cur;
    path.num_steps += 1;
    if(nodecmp(cur, start))
      break;
    cur = prev_node_matrix[cur.i][cur.j];
  }
  path.steps = invert_array(path.steps, path.num_steps);
  return path;
}


path_t get_shortest_path(node_t start, node_t goal, float ** dist_matrix, int lenq, int lent){
  float** dists = create_matrix(lenq, lent, INF);
  float** visited = create_matrix(lenq, lent, 0);
  node_t** prev_node_matrix = create_node_matrix(lenq, lent);
  heap* to_visit = create_heap(lent* lenq);

  dists[start.i][start.j] = start.weight;
  push(to_visit, start, start.weight);

  while(to_visit->size){
    node_t cur = pop(to_visit);
    node_t* neighbours =get_neighbours(cur, dist_matrix, lenq, lent);
    int num_neighbours = get_num_neighbours(cur, lent);
    for(int i = 0; neighbours != NULL && i < num_neighbours; i++)
    {
      node_t  nbr = neighbours[i];
      if(visited[nbr.i][nbr.j] != 0)
        continue;

      float tmpdist = dists[cur.i][cur.j] + nbr.weight;
      if(tmpdist < dists[nbr.i][nbr.j])
      {
        dists[nbr.i][nbr.j] = tmpdist;
        prev_node_matrix[nbr.i][nbr.j] = cur;
        push(to_visit, nbr, dists[nbr.i][nbr.j]);
      }
      if(nodecmp(nbr, goal))
        break;
    }
    visited[cur.i][cur.j] = 1;
  }

  return build_path(prev_node_matrix, dists, start, goal);

}
