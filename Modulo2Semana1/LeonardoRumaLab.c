/* Disciplina: Computacao Concorrente */
/* Nome: Leonardo Ruma */
/* DRE: 115198102 */
/* Laboratório*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  4

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

void *tudoBem () {
    pthread_mutex_lock(&x_mutex);
    x++;
    if ( x == 2) {
        pthread_cond_broadcast(&x_cond);
    }
    printf("thread 1: Tudo bem? \n");
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}

void *bomDia () {
    pthread_mutex_lock(&x_mutex);
    x++;
    if ( x == 2) {
        pthread_cond_broadcast(&x_cond);
    }
    printf("thread 2: Bom Dia! \n");
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}


void *ateMais () {
    pthread_mutex_lock(&x_mutex);
    if ( x < 2) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Thread 3: Ate Mais! \n");
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}

void *boaTarde () {
    pthread_mutex_lock(&x_mutex);
    if ( x < 2) {
        pthread_cond_wait(&x_cond, &x_mutex);
    }
    printf("Thread 4: Boa tarde! \n");
    pthread_mutex_unlock(&x_mutex);
    pthread_exit(NULL);
}


/* Funcao principal */
int main(int argc, char *argv[]) {
    pthread_t threads[NTHREADS];

    /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init (&x_cond, NULL);

    /* Cria as threads */
    pthread_create(&threads[0], NULL, tudoBem, NULL);
    pthread_create(&threads[1], NULL, bomDia, NULL);
    pthread_create(&threads[2], NULL, ateMais, NULL);
    pthread_create(&threads[3], NULL, boaTarde, NULL);

    /* Espera todas as threads completarem */
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    /* Desaloca variaveis e termina */
    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);
}
