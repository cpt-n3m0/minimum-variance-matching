#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "mvm.h"
#include "graph.h"

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
void print_ts(float* ts, int len)
{
  FILE* f = fopen("mvm_output.txt", "a");
  char* s = malloc(sizeof(char) * len * 9);
  s[0] = '\0';
  char tmp[8] = "";
  for(int i = 0; i < len; i++)
  {
    printf("%2.2f, ", ts[i]);
    sprintf(tmp, "%2.2f, ", ts[i]);
    strcat(s, tmp);
  }
  printf("\n");
  fputs(s, f);
  fputs("\n", f);
  fflush(f);
  fclose(f);
}

match_t mvm(float* query, int lenq, float* target, int lent, int elasticity){
  node_t start;
  /*clock_t start_clk, end_clk;*/

  float ** dist_matrix = get_dist_matrix(query, lenq, target, lent);
  start = create_node(0, 0, dist_matrix[0][0] * dist_matrix[0][0]);
  /*start_clk = clock();*/
  path_t path = get_shortest_path(start, dist_matrix, lenq, lent, elasticity);
  /*end_clk = clock();*/
  /*PRINT_PERF(get_shortest_path, start_clk, end_clk)*/

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
  float query[] = {0.21270409953466315, 0.24105910680854856, 0.2994682903905675, 0.32102659396860034};
  float target[] = {0.1225145950318306, 0.34860867638809184, 0.5613872899312321, 0.7049469610859275, 0.7049469610859275, 0.8869577678441778, 0.8135544777477108, 0.761382781687954, 0.5662923478900557, 0.4879827013308508, 0.320466160470615, 0.1476702678981975, 0.6063617845753195, 0.6559265717137032, 1.0, 0.8157871740722203, 0.6029983753890008, 0.49705546991629157, 0.5891750708105631, 0.48644904647306947, 0.24898865312498858, 0.23306714882281185, 0.21585024484204296, 0.2638464798299429, 0.22407446140847365, 0.1742555327070716, 0.1721110737813777, 0.11796952699418185, 0.10375583938732019, 0.13587368446082987, 0.045906566840661474, 0.08332643672204776, 0.0, 0.04329198863054318, 0.18929214716975543, 0.18934816544019245, 0.20848166119878142, 0.034410343590019585, 0.2008075233531364, 0.2222709206277106, 0.19151354245238403, 0.1717227805326912, 0.18789962345618266, 0.15186689052603622, 0.10819491704294697, 0.08053002738565047, 0.07242533404672595, 0.10118944784590454, 0.12870819494544752, 0.09745217097782473, 0.10021055849647532, 0.04362107821637742, 0.05254925636202487, 0.08531673888614037, 0.3290364891976342, 0.30651377648742534, 0.20986909234231452, 0.1781780086959589, 0.14281047497426874, 0.0518895960843288, 0.09020174104622206, 0.08834726442049953, 0.07374023157315909, 0.09545566034189075, 0.1145901908457868, 0.12811431200667117 };
  int qlen = 4;
  int tlen = 66;
  /*float* query = gen_timeseries(qlen, 1, 5);*/
  /*float* target = gen_timeseries(tlen, 1, 5);*/
  match_t matches = mvm(query, qlen, target, tlen, 10);
  for (int i = 0 ; i < qlen; i++){
    printf("%d -> %d\n", matches.matches[i][0], matches.matches[i][1]);
  }
  printf("Distance %f\n", matches.distance);
}
