#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "timer.h"

int nthreads;
long long int limite;

typedef struct {
    long long int inicioSomatorio;
    long long int fimSomatorio;
    int id;
}ArgumentoSerieLeibnizConcorrente;

double serieLeibnizSequencial(long long int limite);

void definirLimitesSequenciaConcorrente(ArgumentoSerieLeibnizConcorrente *argumentosSerieLeibnizConcorrente);

void * serieLeibnizConcorrente(void * arg){
    double *somaConcorrenteLocal;
    double soma = 0;
    somaConcorrenteLocal = (double *) malloc(sizeof (double ));
    if (somaConcorrenteLocal == NULL){
        printf("erro-Malloc\n");
        exit(1);
    }
    *somaConcorrenteLocal = 0;
    ArgumentoSerieLeibnizConcorrente *argumentoSerieLeibnizConcorrente = (ArgumentoSerieLeibnizConcorrente *) arg;
    printf("o Id eh %d \n", argumentoSerieLeibnizConcorrente->id);
    printf("inicio: %lld \n", argumentoSerieLeibnizConcorrente->inicioSomatorio);
    printf("fim: %lld \n", argumentoSerieLeibnizConcorrente->fimSomatorio);
    for (long long int i = argumentoSerieLeibnizConcorrente->inicioSomatorio; i < argumentoSerieLeibnizConcorrente->fimSomatorio; i++) {
        soma += (4 * pow(-1,i) /(2*i + 1));
//        printf("%.15f \n", soma);
    }
    *somaConcorrenteLocal = soma;
    pthread_exit((void *) somaConcorrenteLocal);
}


int main(int argc, char *argv[]){
    double inicio, fim;
    double piAproximadoSequencial;
    double piAproximadoConcorrente;
    double *retornoThread;
    pthread_t *tid;
    if(argc<3){
        printf("Digite: %s <Limite do somatorio da serie de Leibniz> <numero de threads>\n", argv[0]);
        return 1;
    }
    limite = atoll(argv[1]);
    nthreads = atoi(argv[2]);
    tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
    if (tid == NULL){
        printf("ERRO --malloc\n");
        return 2;
    }
    ArgumentoSerieLeibnizConcorrente *argumentosSerieLeibnizConcorrente = (ArgumentoSerieLeibnizConcorrente *) malloc(sizeof(ArgumentoSerieLeibnizConcorrente) * nthreads);
    if (argumentosSerieLeibnizConcorrente == NULL){
        printf("ERRO--Malloc \n");
        return 2;
    }
    printf("O valor de Pi de acordo com a biblioteca math.h é %.15f \n", M_PI);
    GET_TIME(inicio);
    piAproximadoSequencial = serieLeibnizSequencial(limite);
    GET_TIME(fim);
    printf("A funcao sequencial demorou %f  e obteve o valor aproximado de Pi igual a %.15f \n", (fim - inicio), piAproximadoSequencial);
    definirLimitesSequenciaConcorrente(argumentosSerieLeibnizConcorrente);
    for (int i = 0; i < nthreads; i++) {
        printf("argumento %d \n", argumentosSerieLeibnizConcorrente[i].id);
        printf("%lld \n", argumentosSerieLeibnizConcorrente[i].inicioSomatorio);
        printf("%lld \n", argumentosSerieLeibnizConcorrente[i].fimSomatorio);
    }
    GET_TIME(inicio)
    for (int i = 0; i < nthreads; i++) {
        if (pthread_create(tid + i, NULL, serieLeibnizConcorrente, (void *) &argumentosSerieLeibnizConcorrente[i])){
            printf("ERRO --pthread_Create\n");
            return 3;
        }
    }
    for (int i = 0; i < nthreads; i++) {
        if (pthread_join(*(tid + i), (void**) &retornoThread)){
            fprintf(stderr, "ERRO --pthread_Join\n");
            return 4;
        }
        piAproximadoConcorrente += *retornoThread;
        free(retornoThread);
    }
    GET_TIME(fim)
    printf("A funcao concorrente demorou %f  e obteve o valor aproximado de Pi igual a %.15f \n", (fim - inicio), piAproximadoConcorrente);
    free(tid);
    free(argumentosSerieLeibnizConcorrente);
    return 0;
}

double serieLeibnizSequencial(long long int limite){
    double aproximacaoValorPi = 0;
    for (long long int i = 0; i < limite; i++) {
        aproximacaoValorPi += (4 * pow(-1,i) /(2*i + 1));
    }
    return aproximacaoValorPi;
}

void definirLimitesSequenciaConcorrente(ArgumentoSerieLeibnizConcorrente *argumentosSerieLeibnizConcorrente){
    long long int tamanhoSequencia = limite/nthreads;
    for (int i = 0; i < nthreads; i++) {
        argumentosSerieLeibnizConcorrente[i].id = i;
        argumentosSerieLeibnizConcorrente[i].inicioSomatorio = argumentosSerieLeibnizConcorrente[i].id * tamanhoSequencia;
        if (argumentosSerieLeibnizConcorrente[i].id == nthreads - 1){
            argumentosSerieLeibnizConcorrente[i].fimSomatorio = limite;
        } else{
            argumentosSerieLeibnizConcorrente[i].fimSomatorio = argumentosSerieLeibnizConcorrente[i].inicioSomatorio + tamanhoSequencia;
        }
    }

}