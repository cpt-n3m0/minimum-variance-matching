#ifndef graphimported

#define ALLOC_ERROR(var, msg) if(var == NULL){\
                      printf("ERROR:%s:%s\n", #var, msg);\
                      exit(-1);\
                    }

#define  get_num_neighbours(n, c) (c - n.j - 1)

typedef struct node_t {
  float weight;
  int i;
  int j;
} node_t;
typedef struct path_t {
  node_t* steps;
  float distance;
  int num_steps;
} path_t;


node_t create_node(int i, int j, float weight);
node_t* get_neighbours(node_t node, float ** dist_matrix, int r, int c, int num);
char nodecmp(node_t a, node_t b);
node_t* invert_array(node_t* a, int size);
path_t build_path(node_t ** prev_node_matrix, float** dist_matrix, node_t start, node_t goal);
char is_visited(node_t n, float** dists);
path_t get_shortest_path(node_t start, node_t goal, float** dist_matrix, int lenq, int lent, int elasticity);
node_t ** create_node_matrix(int lenq, int lent);
#define graphimported
#endif
