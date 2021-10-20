#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


int thread_count = 4;
int n = 100000;


double sum = 0.0;
void *Thread_sum (void * rank);

int main(){
  long thread;
  pthread_t * thread_handles;
  thread_handles = malloc(thread_count * sizeof(pthread_t));

  for(thread = 0; thread < thread_count; thread++){
    pthread_create(&thread_handles[thread], NULL, Thread_sum ,
    (void*) thread);
  }
  for(thread = 0; thread < thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
  }

  free(thread_handles);

  //Saida
  printf("n = %d thread = %d pi-> %f\n",n,thread_count,sum*4.0);
  
  return 0;
}
void * Thread_sum (void * rank){
  long my_rank = (long) rank;
  double factor;
  long long i;
  long long my_n = n/thread_count;
  long long my_first_i = my_n*my_rank;
  long long my_last_i = my_first_i + my_n;

  if(my_first_i % 2 == 0) factor = 1.0;
  else factor = -1.0;

  for(i = my_first_i; i < my_last_i; i++, factor = -factor){
    sum += factor/(2*i+1);
  }

 return NULL;
}
