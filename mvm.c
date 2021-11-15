#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "graph.h"
#include "mvm.h"
#include "dijkstra.h"

#define PRINT_PERF(func, s, e) printf("%s: %Lfs\n", #func, (e-s)/(long double)CLOCKS_PER_SEC);


float ** create_matrix (int r, int c, float default_val){
  float** matrix = NULL;
  matrix = (float**)malloc(sizeof(float*) * r);
  ALLOC_ERROR(matrix, "failed to allocate d1");
  for(int i = 0; i < r; i++){
    matrix[i] = (float*)malloc(sizeof(float) * c);
    ALLOC_ERROR(matrix, "failed to allocate d2");
    for(int j = 0; j < c ; j ++)
      matrix[i][j] = default_val;
  }
  return matrix;
}

float ** get_dist_matrix(float* query, int lenq, float* target, int lent){
  float ** dist_matrix = create_matrix(lenq, lent, 0);
  for (int j = 0; j < lenq; j++)
    for (int i = 0; i < lent; i++)
      dist_matrix[j][i] = query[j] - target[i];

  return dist_matrix;
}

void print_matrix(float** dist_matrix, int r, int c){
  for(int i = 0 ; i < r; i ++ )
  {
    for(int j = 0 ; j < c; j ++ )
      printf("%3.2f\t" , dist_matrix[i][j]);
    printf("\n");
  }
}

match_t mvm(float* query, int lenq, float* target, int lent){
  node_t start, goal;

  clock_t start_clk, end_clk;

  float ** dist_matrix = get_dist_matrix(query, lenq, target, lent);
  /*print_matrix(dist_matrix, lenq, lent);*/
  start = create_node(0, 0, dist_matrix[0][0] * dist_matrix[0][0]);
  goal = create_node(lenq - 1, lent - 1, dist_matrix[0][0] * dist_matrix[0][0]);
  start_clk = clock();
  path_t path = get_shortest_path(start,  goal, dist_matrix, lenq, lent);
  end_clk = clock();
  PRINT_PERF(get_shortest_path, start_clk, end_clk)

  int ** coord_match = malloc(sizeof(int*) * path.num_steps);

  ALLOC_ERROR(coord_match, "failed to allocate first dim")
  for(int i = 0; i< path.num_steps; i++){
    coord_match[i] = malloc(sizeof(int) * 2);
    ALLOC_ERROR(coord_match, "failed to allocate second dim")
    coord_match[i][0] = path.steps[i].i;
    coord_match[i][1] = path.steps[i].j;
  }
  match_t res;
  res.matches = coord_match;
  res.distance = path.distance;
  return res;
}
float* gen_timeseries(int len, float min, float max){
  float* ts;
  time_t t;
  srand((unsigned)time(&t));
  ts = malloc(sizeof(float*) * len);
  ALLOC_ERROR(ts, "failed to allocate")
  for(int i = 0; i < len; i++)
    ts[i] = fmod(rand(), (max - min + 1)) + min;
  return ts;
}
int main(void){
  /*float query[] = {1, 2, 8, 6, 8};*/
  /*float target[] = {1, 2, 9, 3, 3, 5, 9 };*/
  int qlen = 100;
  int tlen = 1000;
  float* query = gen_timeseries(qlen, 1, 5);
  float* target = gen_timeseries(tlen, 1, 5);
  match_t matches = mvm(query, qlen, target, tlen);
  for (int i = 0 ; i < qlen; i++){
    printf("%d -> %d\n", matches.matches[i][0], matches.matches[i][1]);
  }
  printf("Distance %f\n", matches.distance);
}
