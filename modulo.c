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

    fprintf(pF,"%d;%s;%s;%.2f;%d\n", dado.id, dado.titulo, dado.desenvolvedora, dado.preco, dado.horasJogadas);
    fclose(pF);
}


int listaDeJogos() {


        FILE *pF = fopen("dados.txt", "r");
        if (pF == NULL) {
            printf("Nenhum jogo cadastrado ainda ou erro ao abrir arquivo.\n");
            return -1;
        }

        struct Dados dado;
        printf("\n--- LISTA DE JOGOS ---\n");

        // CORREÇÃO 4: Removido o \n do final do formato para evitar falhas na última linha
        while (fscanf(pF, "%d;%[^;];%[^;];%f;%d", &dado.id, dado.titulo, dado.desenvolvedora, &dado.preco, &dado.horasJogadas) == 5) {
            printf("ID: %d | Titulo: %s | Dev: %s | Preco: R$%.2f | Horas: %d\n",
                   dado.id, dado.titulo, dado.desenvolvedora, dado.preco, dado.horasJogadas);
        }
        printf("----------------------\n");

        fclose(pF);
        return 0;
    }


int mediaDeHoras() {

    FILE *pF = fopen("dados.txt", "r");
    if (pF == NULL) {
        printf("Nenhum jogo cadastrado ainda.\n");
        return -1;
    }

    struct Dados dado;
    int totalHoras = 0;
    int qtdJogos = 0;

    // Lê ID e Horas, ignorando os campos do meio (;%*[^;];)
    while (fscanf(pF, "%d;%*[^;];%*[^;];%*f;%d", &dado.id, &dado.horasJogadas) == 2) {
        totalHoras += dado.horasJogadas;
        qtdJogos++;
    }

    fclose(pF); // CORREÇÃO 2: fclose agora está no lugar certo

    if (qtdJogos == 0) {
        printf("Não há jogos para calcular a média.\n");
    } else {
        float media = (float)totalHoras / qtdJogos;
        printf("\n--- MÉDIA DE HORAS ---\n");
        printf("Total de jogos: %d\n", qtdJogos);
        printf("Média de horas jogadas: %.2f horas\n", media);
        printf("----------------------\n");
    }

    return 0; // CORREÇÃO 2: Removido o código duplicado que estava aqui
}


// Implementação das funções