/* multiplicao de matriz-vetor (considerando matrizes quadradas) */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

float *mat; //matriz de entrada
float *vet; // vetor de entrada
float *saida; // vetor de saida
int nThreads; //numero de threads

typedef struct{
    int id; //identificador do elemento que a thread ira processar
    int dim; //dimensao das estruturas de entrada
}tArgs;

//funcao que as threads executarao
void * tarefa(void *arg){
    tArgs *args = (tArgs*) arg;
    printf("Thread %d\n", args->id);
    for (int i = args->id; i < args->dim; i+=nThreads) {
        for (int j = 0; j < args->dim; j++) {
            saida[i] += mat[i * (args->dim) + j] * vet[j];
        }
    }
    pthread_exit(NULL);
}

//fluxo principal
int main(int argc, char* argv[]){
    int dim; //dimensao da matriz de entrada

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
    mat = (float *) malloc(sizeof(float) * dim * dim);
    if (mat == NULL){
        printf("ERRO--malloc\n");
        return 2;
    }
    vet = (float *) malloc(sizeof(float) * dim);
    if (vet == NULL){
        printf("ERRO--malloc\n");
        return 2;
    }
    saida = (float *) malloc(sizeof(float) * dim);
    if (saida == NULL){
        printf("ERRO--malloc\n");
        return 2;
    }

    //inicializar das estruturas de dados de entrada e saida
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            mat[i*dim+j] = 1; //ma[i][j]
        }
        vet[i] = 1;
        saida[i] = 0;
    }
    //multiplicacao da matriz pelo vetor

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

    //exibicao dos resultados
    puts("matriz de entrada");
    for (int i = 0; i < nThreads; i++) {
        for (int j = 0; j < dim; j++) {
            printf("%.lf ", mat[i*dim+j]);
        }
        puts("");
    }
    puts("Vetor de entrada:");
    for (int j = 0; j < dim; j++) {
        printf("%.lf ", vet[j]);
    }
    puts("");
    puts("Vetor de saida");
    for (int j = 0; j < dim; j++) {
        printf("%.lf ", saida[j]);
    }
    puts("");

    //liberacao da memoria
    free(mat);
    free(vet);
    free(saida);
    free(tid);

    return 0;
}
