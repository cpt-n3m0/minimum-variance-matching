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

node_t create_node(int i, int j, float weight);
node_t* get_neighbours(node_t node, float ** dist_matrix, int r, int c);

#define graphimported
#endif
