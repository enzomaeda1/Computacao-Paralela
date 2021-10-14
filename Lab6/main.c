#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int thread_count = 3;
void *Pth_mat_vec (void * rank);

int m = 3;
int n = 3;
int y[3] = {0,0,0};
int A[3][3] = {{10,11,12},{13,14,15},{16,17,18}};
int x[3] = {10,5,20};

int main(){
  long thread;
  pthread_t * thread_handles;
  thread_handles = malloc(thread_count * sizeof(pthread_t));

  for(thread = 0; thread < thread_count; thread++){
    pthread_create(&thread_handles[thread], NULL, Pth_mat_vec ,
    (void*) thread);
  }

  for(thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
  }

  free(thread_handles);

  printf("1 = %i \n2 = %i \n3 = %i\n",y[0],y[1],y[2]);

  return 0;
}
void *Pth_mat_vec (void * rank){
  long my_rank = (long) rank;
  int i, j ;
  int local_m = m/thread_count;
  int my_first_row = my_rank * local_m;
  int my_last_row = (my_rank + 1) * local_m  -1;

  for(i  = my_first_row; i <= my_last_row; i++){
    y[i] = 0.0;
    for(j = 0; j < n; j++){
      y[i] += A[i][j] * x[j];
    }
  }
 return NULL;
}
