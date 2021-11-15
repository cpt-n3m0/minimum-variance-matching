#include "graph.h"

typedef struct path_t {
  node_t* steps;
  float distance;
  int num_steps;
} path_t;

char nodecmp(node_t a, node_t b);
node_t* invert_array(node_t* a, int size);
path_t build_path(node_t ** prev_node_matrix, float** dist_matrix, node_t start, node_t goal);
char is_visited(node_t n, float** dists);
path_t get_shortest_path(node_t start, node_t goal, float** dist_matrix, int lenq, int lent);
node_t ** create_node_matrix(int lenq, int lent);
