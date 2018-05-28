#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMREGISTROS 5

int  auxMergeSort(int vetor[], int temp[], int esq, int dir);
int merge(int vetor[], int temp[], int esq, int meio, int dir);

int mergeSort(int vetor[], int tamVetor){
    int *temp = (int *)malloc(sizeof(int)*tamVetor);
    return auxMergeSort(vetor, temp, 0, tamVetor - 1);
}

int auxMergeSort(int vetor[], int temp[], int esq, int dir){
  int meio, contadorInversoes = 0;
  if (dir > esq){
    // Pega o meio do array pra dividir em duas partes
    meio = (dir + esq)/2;

    /* Numero de inversoes sera a soma das inversoes
       da esquerda, da direta e do merge desses 2 */
    contadorInversoes  = auxMergeSort(vetor, temp, esq, meio);
    contadorInversoes += auxMergeSort(vetor, temp, meio+1, dir);
    contadorInversoes += merge(vetor, temp, esq, meio+1, dir);
  }
  return contadorInversoes;
}

int merge(int vetor[], int temp[], int esq, int meio, int dir){
  int i, j, k;
  int contadorInversoes = 0;

  i = esq; /* indice do subvetor da esquerda*/
  j = meio;  /* indice do subvetor da direita*/
  k = esq; /* indice do subvetor merjado*/

  while ((i <= meio - 1) && (j <= dir)){
    if (vetor[i] <= vetor[j]){
      temp[k++] = vetor[i++];
    }
    else{
      temp[k++] = vetor[j++];
      contadorInversoes = contadorInversoes + (meio - i);
    }
  }

  // Copia os elementos do subvetor da esquerda pro temporario
  while (i <= meio - 1)
    temp[k++] = vetor[i++];

  // Copia os elementos do subvetor da direita pro temporario
  while (j <= dir)
    temp[k++] = vetor[j++];

  // Copia os elementos merjados de volta para o array original
  for (i=esq; i <= dir; i++)
    vetor[i] = temp[i];

  return contadorInversoes;
}

int main(){
  int vetor[TAMREGISTROS];
  srand(time(NULL));

  for (int i = 0; i < TAMREGISTROS; ++i){
      vetor[i] = rand() % (TAMREGISTROS+5);
  }

  printf("------------ Array ------------\n");
  for (int i = 0; i < TAMREGISTROS; ++i){
      printf("%d ", vetor[i]);
  }
  printf("\n-------------------------------\n");

  printf("O numero de inversoes e %d \n", mergeSort(vetor, TAMREGISTROS));
  printf("Pressione ENTER\n");
  getchar();
  printf("Programa finalizado\n");
  return 0;
}
