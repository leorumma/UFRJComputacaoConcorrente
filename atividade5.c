#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS  2 //total de threads a serem criadas

int vetor[100];

typedef struct {
    int posicaoInicial, posicaoFinal;
} t_Args;
t_Args vetorArgs[2];

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
    t_Args *args = (t_Args *) arg;
    for (int i = args->posicaoInicial; i < args->posicaoFinal; i++){
        vetor[i] += 1;
    }
    free(arg); //liberar a alocacao feita na main
    pthread_exit(NULL);
}

void dividirVetor(){
    vetorArgs[0].posicaoInicial = 0;
    if (calcularTamanhoDoVetor()%NTHREADS == 0){
        vetorArgs[0].posicaoFinal = calcularTamanhoDoVetor()/NTHREADS; // Para tratar de casos onde o tamanho do vetor é impar ou par
    } else{
        vetorArgs[0].posicaoFinal = calcularTamanhoDoVetor()-1/NTHREADS;
    }
    vetorArgs[1].posicaoInicial = vetorArgs[0].posicaoFinal;
    vetorArgs[1].posicaoFinal = calcularTamanhoDoVetor();
}

int main(){
    iniciarVetorComZeros();
    printf("----------------------------------------VALOR INICIAL DO VETOR:----------------------------------------\n");
    imprimirValorDeCadaPosicaoDoVetor();
    pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
    dividirVetor();
    int thread; //variavel auxiliar
    t_Args *arg; //receberá os argumentos para a thread
    for(thread=0; thread < NTHREADS; thread++) {
        printf("--Cria a thread %d\n", thread);
        arg = malloc(sizeof(t_Args));
        if (arg == NULL) {
            printf("--ERRO: malloc()\n"); exit(-1);
        }
        arg->posicaoInicial = vetorArgs[thread].posicaoInicial;
        arg->posicaoFinal = vetorArgs[thread].posicaoFinal;
        if (pthread_create(&tid_sistema[thread], NULL, somarVetorEmUmaUnidade,(void*) arg)) {
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
    }
    //espera todas as threads terminarem
    for (thread=0; thread<NTHREADS; thread++) {
        if (pthread_join(tid_sistema[thread], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1);
        }
    }
    printf("----------------------------------------VALOR FINAL DO VETOR:----------------------------------------\n");
    imprimirValorDeCadaPosicaoDoVetor();
    printf("--Thread principal terminou\n");
    pthread_exit(NULL);
}
