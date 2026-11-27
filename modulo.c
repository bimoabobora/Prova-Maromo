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
        printf("4: Deletar jogos \n");
        printf("5: Altera jogos \n");
        printf("6: menu de busca de jogos \n");
        printf("7: Sair\n");
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
            case (4): {
                deletarJogoPorId();
                break;
            }
            case (5): {
                alterarJogoPorId();
                break;
            }
            case(6): {
                menuBuscarJogo();
                break;
            }
            case (7):
            {
                boole = 0;
                break;
            }
            default:
            {
                printf("Opção não identificada\n");
                break;
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
        while (fscanf(pF, "%d;%254[^;];%245[^;];%f;%d", &dado.id, dado.titulo, dado.desenvolvedora, &dado.preco, &dado.horasJogadas) == 5) {
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
int buscarJogoPorId(int idProcurado, struct Dados *encontrado) {
    FILE *pF = fopen("dados.txt", "r");
    if (pF == NULL) {
        return -1;
    }

    struct Dados atual;
    while (fscanf(pF, "%d;%254[^;];%254[^;];%f;%d",
                  &atual.id, atual.titulo, atual.desenvolvedora,
                  &atual.preco, &atual.horasJogadas) == 5) {
        if (atual.id == idProcurado) {
            if (encontrado != NULL) {
                *encontrado = atual;
            }
            fclose(pF);
            return 1;
        }
    }

    fclose(pF);
    return 0;
}

void menuBuscarJogo(void) {
    int idBuscado;
    struct Dados jogo;

    printf("Digite o ID do jogo para buscar: ");
    if (scanf("%d", &idBuscado) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("ID invalido.\n");
        return;
    }

    int status = buscarJogoPorId(idBuscado, &jogo);
    if (status == -1) {
        printf("Nenhum jogo cadastrado ainda ou erro ao abrir dados.txt.\n");
    } else if (status == 0) {
        printf("Jogo com ID %d nao encontrado.\n", idBuscado);
    } else {
        printf("\n--- JOGO ENCONTRADO ---\n");
        printf("ID: %d | Titulo: %s | Dev: %s | Preco: R$%.2f | Horas: %d\n",
               jogo.id, jogo.titulo, jogo.desenvolvedora, jogo.preco, jogo.horasJogadas);
        printf("-----------------------\n");
    }
}

int alterarJogoPorId(void) {
    int idAlvo;
    printf("Digite o ID do jogo que deseja alterar: ");
    if (scanf("%d", &idAlvo) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("ID invalido.\n");
        return -1;
    }

    FILE *origem = fopen("dados.txt", "r");
    if (origem == NULL) {
        printf("Nenhum jogo cadastrado ainda ou erro ao abrir dados.txt.\n");
        return -1;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(origem);
        return -1;
    }

    struct Dados dado;
    int encontrado = 0;

    while (fscanf(origem, "%d;%254[^;];%254[^;];%f;%d",
                  &dado.id, dado.titulo, dado.desenvolvedora,
                  &dado.preco, &dado.horasJogadas) == 5) {
        if (dado.id == idAlvo) {
            encontrado = 1;
            printf("\nEditando jogo ID %d (atual: %s)\n", dado.id, dado.titulo);

            printf("Novo titulo: ");
            scanf(" %254[^\n]", dado.titulo);

            printf("Nova desenvolvedora: ");
            scanf(" %254[^\n]", dado.desenvolvedora);

            printf("Novo preco: ");
            scanf(" %f", &dado.preco);

            printf("Novas horas jogadas: ");
            scanf(" %d", &dado.horasJogadas);
        }

        fprintf(temp, "%d;%s;%s;%.2f;%d\n",
                dado.id, dado.titulo, dado.desenvolvedora,
                dado.preco, dado.horasJogadas);
    }

    fclose(origem);
    fclose(temp);

    if (!encontrado) {
        remove("temp.txt");
        printf("Jogo com ID %d nao encontrado.\n", idAlvo);
        return 0;
    }

    if (remove("dados.txt") != 0 || rename("temp.txt", "dados.txt") != 0) {
        printf("Erro ao atualizar dados.txt.\n");
        return -1;
    }

    printf("Jogo com ID %d alterado com sucesso!\n", idAlvo);
    return 1;
}

int deletarJogoPorId(void) {
    int idAlvo;
    printf("Digite o ID do jogo que deseja deletar: ");
    if (scanf("%d", &idAlvo) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        printf("ID invalido.\n");
        return -1;
    }

    FILE *origem = fopen("dados.txt", "r");
    if (origem == NULL) {
        printf("Nenhum jogo cadastrado ainda ou erro ao abrir dados.txt.\n");
        return -1;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(origem);
        return -1;
    }

    struct Dados dado;
    int removido = 0;

    while (fscanf(origem, "%d;%254[^;];%254[^;];%f;%d",
                  &dado.id, dado.titulo, dado.desenvolvedora,
                  &dado.preco, &dado.horasJogadas) == 5) {
        if (dado.id == idAlvo) {
            removido = 1;
            continue; // Ignora o registro para remover
        }

        fprintf(temp, "%d;%s;%s;%.2f;%d\n",
                dado.id, dado.titulo, dado.desenvolvedora,
                dado.preco, dado.horasJogadas);
    }

    fclose(origem);
    fclose(temp);

    if (!removido) {
        remove("temp.txt");
        printf("Jogo com ID %d nao encontrado.\n", idAlvo);
        return 0;
    }

    if (remove("dados.txt") != 0 || rename("temp.txt", "dados.txt") != 0) {
        printf("Erro ao atualizar dados.txt.\n");
        return -1;
    }

    printf("Jogo com ID %d removido com sucesso!\n", idAlvo);
    return 1;
}

// Implementação das funções