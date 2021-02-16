cmake_minimum_required(VERSION 3.17)
project(Modulo2Semana2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Modulo2Semana2
        atividade1PrioridadeEscritor.c
        atividade1PrioridadeIgual.c
        atividade1PrioridadeLeitor.c
        atividade1SemPrioridade.c
        barreira.c
        leitesc.c)
