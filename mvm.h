#ifndef mvmimported



typedef struct match_t {
  int** matches;
  float distance;
} match_t;
//int compute_dist(int* query, int lenq, int* targ, int lentarg);
float ** create_matrix (int r, int c, float default_val);
float ** get_dist_matrix(float* query, int lenq, float* target, int lent);
void print_matrix(float** dist_matrix, int r, int c);
match_t mvm(float* query, int lenq, float* target, int lent, int elasticity);
float* gen_timeseries(int len, float min, float max);

#define mvmimported
#endif
