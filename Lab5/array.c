// Crie um programa em C que multiplica todos os elementos de um array por 4 ou por um valor fornecido pelo usuário;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int g = 0;
int n;
int  arr[5] =  {33,22,11,30,10};

void *myThreadFun(void *vargp)
{
  printf("Digite um numero para multiplicar o vetor: ");
  scanf("%d",&n);
  
  int *myid = (int *)vargp;
  

  for (g = 0; g<5; g++){
      arr[g] *= n;
    }
	
  for (g = 0; g<5; g++){
    printf("ID: %d, Value: %d\n", *myid, arr[g]);
  }
  	return NULL;
}

int main()
{
	int i;
	pthread_t tid;
  
  pthread_create(&tid, NULL, myThreadFun, (void *)&tid);

  pthread_exit(NULL);
	return 0;
}
