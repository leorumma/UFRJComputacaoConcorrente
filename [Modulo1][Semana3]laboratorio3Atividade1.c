#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "timer.h"

double serieLeibnizSequencial(long long int limite);

int main(int argc, char *argv[]){
    double inicio, fim;
    double piAproximadoSequencial = 0;
    long long int limite;
    if(argc<2){
        printf("Digite: %s <Limite do somatorio da serie de Leibniz>\n", argv[0]);
        return 1;
    }
    limite = atoll(argv[1]);
    printf("O valor de Pi de acordo com a biblioteca math.h é %.15f \n", M_PI);
    GET_TIME(inicio);
    piAproximadoSequencial = serieLeibnizSequencial(limite);
    GET_TIME(fim);
    printf("A funcao sequencial demorou %f e obteve o valor aproximado de Pi igual a %.15f \n", (fim - inicio), piAproximadoSequencial);
    return 0;
}

double serieLeibnizSequencial(long long int limite){
    double aproximacaoValorPi = 0;
    for (int i = 0; i < limite; i++) {
        aproximacaoValorPi += (4 * pow(-1,i) /(2*i + 1));
    }
    return aproximacaoValorPi;
}
