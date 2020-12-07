#include <stdio.h>
#include <pthread.h>

//funcao que a thread ira executar
void *tarefa(void *arg){
    printf("ola, sou a thread nova!\n");
    pthread_exit(NULL);
}

//funcao principal
int main(void){
    pthread_t tid; //identificador da thread do sistema
    if ( pthread_create(&tid, NULL, tarefa, NULL) ){
        printf("ERRO -- pthread_create\n");
    }
    printf("Eu me chamo %lu", tid);
    printf("ola, sou a thread principal \n");
    //desvincula o termino da main no termino do programa.
    pthread_exit(NULL);
    return 0;
}