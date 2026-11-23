//
// Created by rafae on 18/11/2026.
//
#include <stdio.h>
#include "modulo.h"

void exibirmenu(void) {
    int boole = 1;
    while (boole)
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
        printf("4: Sair\n");
        scanf("%d", &decisao);
        switch (decisao)
        {
            case (1):
            {
                cadastrarJogo();
                break;
            }
            case (2):
            {
                listaDeJogos();
                break;
            }
            case (3):
            {
                mediaDeHoras();
                break;
            }
            case (4):
            {
                boole = 0; 
            }
        }
    }
}

int cadastrarJogo()
{
    FILE *pF = fopen("dados.txt", "a");
    if (pF == NULL)
    {
        printf("Erro na leitura do arquivo");
        return -1;
    }
    struct Dados dado;
    printf("Digite o ID do jogo: ");
    scanf("%d", &dado.id);
    printf("Digite o Titulo do jogo: ");
    scanf(" %254[^\n]", dado.titulo);
    printf("Digite o desenvolvedora do jogo: ");
    scanf(" %254[^\n]", dado.desenvolvedora);
    printf("Digite o preco do jogo: ");
    scanf(" %f", &dado.preco);
    printf("Digite o horasJogadas do jogo: ");
    scanf(" %d", &dado.horasJogadas);

    fprintf(pF,"%d %s %s %.2f %d\n", dado.id, dado.titulo, dado.desenvolvedora, dado.preco, dado.horasJogadas);
    fclose(pF);
}

int listaDeJogos()
{
    printf("Não implementado");
}

int mediaDeHoras()
{
    printf("Não implementado");
}

// Implementação das funções