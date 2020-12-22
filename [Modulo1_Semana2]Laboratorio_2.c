/* multiplicao de matriz-vetor (considerando matrizes quadradas) */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

float *matEntrada1;
float *matEntrada2;
float *matSaida;
int nThreads; //numero de threads

typedef struct{
    int id; //identificador do elemento que a thread ira processar
    int dim; //dimensao das estruturas de entrada
}tArgs;

//funcao que as threads executarao
void * tarefa(void *arg){
    tArgs *args = (tArgs*) arg;
    printf("Thread %d\n", args->id);
    float soma = 0;
    for (int i = args->id; i < args->dim; i+=nThreads) { // cada thread vai executar uma linha
        for (int k = 0; k < args->dim ; k++) {
            soma = 0;
            for (int j = 0; j < args->dim; j++) {
                soma += matEntrada1[i * (args->dim) + j] * matEntrada2[j * (args->dim) + k];
            }
            matSaida[i * (args->dim) + k] = soma;
        }
    }
    pthread_exit(NULL);
}

//fluxo principal
int main(int argc, char* argv[]){
    int dim; //dimensao da matriz de entrada

    double inicio,fim,delta;

    GET_TIME(inicio);

    pthread_t *tid; //identificadores das threads no sistema

    tArgs *args; //identificadores locais das threads e dimensao

    //leitura e avaliacao dos parametros de entrada
    if(argc<3){
        printf("Digite: %s <dimensao da matriz> <numero de threads>\n", argv[0]);
        return 1;
    }
    dim = atoi(argv[1]);
    nThreads = atoi(argv[2]);
    if (nThreads > dim){
        nThreads = dim;
    }

    //alocacao de memoria para as estruturas de dados
    matEntrada1 = (float *) malloc(sizeof(float) * dim * dim);
    if (matEntrada1 == NULL){
        printf("ERRO--malloc\n");
        return 2;
    }
    matEntrada2 = (float *) malloc(sizeof(float) * dim * dim);
    if (matEntrada2 == NULL){
        printf("ERRO--malloc\n");
        return 2;
    }
    matSaida = (float *) malloc(sizeof(float) * dim * dim);
    if (matSaida == NULL){
        printf("ERRO--malloc\n");
        return 2;
    }


    //inicializar das estruturas de dados de entrada e saida
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matEntrada2[i*dim+j] = 1;
            matEntrada1[i*dim+j] = 1;
            matSaida[i*dim+j] = 0;
        }
    }
    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo inicializacao: %lf\n", delta);
    //multiplicacao da matriz pelo vetor
    GET_TIME(inicio);
    //alocacao das estruturas
    tid = (pthread_t *) malloc(sizeof(pthread_t)*nThreads);
    if (tid==NULL){
        puts("ERRO--Malloc");
        return 2;
    }
    args = (tArgs *) malloc(sizeof(tArgs)*nThreads);
    if (args==NULL){
        puts("ERRO--Malloc");
        return 2;
    }

    //criacao das threads
    for (int i = 0; i < nThreads; i++) {
        (args+i)->id = i;
        (args+i)->dim = dim;
        if (pthread_create(tid+i, NULL, tarefa, (void*) (args+i))){
            printf("ERRO--pthread_create");
            return 3;
        }
    }

    //espera pelo termino da threads
    for (int i = 0; i < nThreads; i++) {
        pthread_join(*(tid+i), NULL);
    }
    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo multiplicacao:  %lf\n", delta);

    //exibicao dos resultados
//    puts("matriz de entrada1");
//    for (int i = 0; i < dim; i++) {
//        for (int j = 0; j < dim; j++) {
//            printf("%.lf ", matEntrada1[i*dim+j]);
//        }
//        puts("");
//    }
//    puts("matriz de entrada2");
//    for (int i = 0; i < dim; i++) {
//        for (int j = 0; j < dim; j++) {
//            printf("%.lf ", matEntrada2[i*dim+j]);
//        }
//        puts("");
//    }
//    puts("matriz de saida");
//    for (int i = 0; i < dim; i++) {
//        for (int j = 0; j < dim; j++) {
//            printf("%.lf ", matSaida[i*dim+j]);
//        }
//        puts("");
//    }

    //liberacao da memoria
    GET_TIME(inicio);
    free(matEntrada1);
    free(matEntrada2);
    free(matSaida);
    free(tid);
    GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo finalizado:  %lf\n", delta);

    return 0;
}
