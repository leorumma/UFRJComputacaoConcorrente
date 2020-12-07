#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  2 //total de threads a serem criadas

int vetor[50];

int calcularTamanhoDoVetor(){
    return sizeof(vetor)/sizeof(vetor[0]);
}

void iniciarVetorComZeros(){
    for (int i = 0; i < calcularTamanhoDoVetor() ; i++) {
        vetor[i] = 0;
    }
}

void imprimirValorDeCadaPosicaoDoVetor(){
    for (int i = 0; i < calcularTamanhoDoVetor(); i++) {
        printf("Posicao %d tem o valor %d \n", i, vetor[i]);
    }
}

void *somarVetorEmUmaUnidade(void *arg) {
    for (int i = 0; i < calcularTamanhoDoVetor(); i++){
        vetor[i] += 1;
    }
}

int main(){
    iniciarVetorComZeros();
    imprimirValorDeCadaPosicaoDoVetor();
    pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
    int thread; //variavel auxiliar
    for(thread=0; thread < NTHREADS; thread++) {
        printf("--Cria a thread %d\n", thread);
        if (pthread_create(&tid_sistema[thread], NULL, somarVetorEmUmaUnidade,NULL)) {
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
    }
    imprimirValorDeCadaPosicaoDoVetor();
    printf("--Thread principal terminou\n");
    pthread_exit(NULL);
}
