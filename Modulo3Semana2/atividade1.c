#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define L 3 //numero de threads leitoras
#define E 3 //numero de threads escritoras


//variaveis do problema
int e=0, l=0; //globais

//variaveis para sincronizacao
sem_t em_e, em_l, escr, leit;

void *leitor (void *threadId){
    int *tid = (int*) threadId;
    while (1){
        sem_wait(&leit);
        sem_wait(&em_l);
        l++;
        if(l==1) {
            sem_wait(&escr);
        }
        sem_post(&em_l);
        sem_post(&leit);
        printf("Leitor %d está lendo\n", *tid);
        sem_wait(&em_l);
        l--;
        if(l==0){
            sem_post(&escr);
        }
        sem_post(&em_l);
        sleep(1);
    }
}

void *escritor (void *threadId){
    int *tid = (int*) threadId;
    while (1){
        sem_wait(&em_e);
        e++;
        if(e==1){
            sem_wait(&leit);
        }
        sem_post(&em_e);
        sem_wait(&escr);
        printf("escritor %d escrevendo \n", *tid);
        sem_post(&escr);
        sem_wait(&em_e);
        e--;
        if(e==0){
            sem_post(&leit);
        }
        sem_post(&em_e);
        sleep(1);
    }
}



int main(void){
    //identificadores das threads
    pthread_t tid[L+E];
    int id[L+E];

    //inicializa as variaveis de sincronizacao
    sem_init(&escr, 0, 1);
    sem_init(&leit, 0, 1);
    sem_init(&em_e, 0, 1);
    sem_init(&em_l, 0, 1);


    //cria as threads leitoras
    for(int i=0; i<L; i++) {
        id[i] = i+1;
        if(pthread_create(&tid[i], NULL, leitor, (void *) &id[i])) exit(-1);
    }

    //cria as threads escritoras
    for(int i=0; i<E; i++) {
        id[i+L] = i+1;
        if(pthread_create(&tid[i+L], NULL, escritor, (void *) &id[i+L])) exit(-1);
    }

    pthread_exit(NULL);
    return 0;

}