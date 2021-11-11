#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <time.h>

#define BILLION 1000000000.0 //timer config

#define size 1000000000
int *vector;
int fim;

void function();

int main(int argc, char* argv[])
{   

    printf("Criando o vetor...\n");
    int i = 0;//, fim = 0;
    int max = size;
    vector = malloc(max * sizeof(unsigned long));

    for(i = 0; i < max; i++){
        *(vector + i) = i+1;
    }

    
    printf("Iniciando o programa...\n");

    //               <timer>
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    //               <timer>

    int thread_count = strtol(argv[1],NULL,10);
    #pragma omp parallel num_threads(thread_count) 
    function();

    //               <fim-timer>
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
                      (end.tv_nsec - start.tv_nsec) / BILLION;

    printf("Tempo de execução %f \n", time_spent);
    //               <fim-timer>

    printf("Finalizado...\n");
    free(vector);
	return 0;
}

void function()
{
  int f = 0;  
  int idThread = omp_get_thread_num();
  int sizeThread = omp_get_num_threads();
   do{ 
        *( vector +  (f + idThread * (size/sizeThread))  ) = *( vector +  (f + idThread * (size/sizeThread))  ) * 4;
        f++;
    }while(f < size/sizeThread);
}
