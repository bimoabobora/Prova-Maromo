//
// Created by rafae on 18/11/2026.
//
#include <stdio.h>
#include "modulo.h"

void exibirmenu(void) {
    while (1)
    {
        int decisao;

        printf("============================== \n");
        printf("       CADASTRO DE JOGOS\n");
        printf("============================== \n");
        printf("--Escolha a sua opção--\n");
        printf("============================== \n");
        printf("1: Cadastro de jogos\n");
        printf("2: Lista de Jogos jogados\n");
        printf("3: Média de horas jogadas\n");
        scanf("%d", &decisao);
        switch (decisao)
        {
            case (1):
            {
                cadastrarJogo();
            }
            case (2):
            {
                listaDeJogos();
            }
            case (3):
            {
                mediaDeHoras();
            }
        }
    }
}

void cadastrarJogo()
{
    FILE *pF = fopen("dados.txt", "a");
}

// Implementação das funções