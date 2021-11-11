#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define BILLION 1000000000.0 //timer config

#define lenght 1000000000 //Tamanho do vetor a ser executado
int *vector;
long sizeThread;

/*
  Minha thread onde eu multiplico 4 pelo valor
  do array
*/

void *myThreadFun(void *vargp);

/*
  Main onde é criado as 4 threads 
*/
int main(int argc, char* argv[])
{
    //Vetor --------------------------
    printf("Criando o vetor...\n");
    int i = 0;
    int max = lenght;
    vector = malloc(max * sizeof(int));
    
    for(i; i < max; i++){
        *(vector + i) = i+1;
    }
    //Vetor --------------------------

    printf("Iniciando o programa...\n");
  

    //               <timer>
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    //               <timer>

    //Inicialização....
    sizeThread = atoi(argv[1]);
    int * arg = malloc(sizeof(int) * sizeThread);
    pthread_t * threads = malloc (sizeof(pthread_t) * sizeThread);
    for(int j = 0 ;j < sizeThread ;j++){
        *(arg + j) = j;
        pthread_create(&threads[j], NULL, myThreadFun, &arg[j]);
    }

    for(int k = 0 ;k < sizeThread ;k++){
        pthread_join(threads[k], NULL);
    }

    //               <fim-timer>
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
                      (end.tv_nsec - start.tv_nsec) / BILLION;

    printf("Tempo de execução %f \n", time_spent);
    //               <fim-timer>

    free(threads);
    printf("Finalizado...\n");

    free(vector);
    return 0;
}

void *myThreadFun(void *vargp)
{
    int flag = 0;
    int *getArg = (int *)vargp;
    int myid = getArg[0];

    do{
      *( vector +(flag + myid * (lenght/sizeThread))  ) = *( vector +  (flag + myid * (lenght/sizeThread))  ) * 4;
      flag++;
    }while(flag < lenght/sizeThread);
