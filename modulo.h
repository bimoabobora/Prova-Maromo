//
// Created by rafae on 18/11/2026.
//

#ifndef PROVA_MAROMO_MODULO_H
#define PROVA_MAROMO_MODULO_H
// Struct
// Constantes
// Protótipos das funções

#define MAX 255

struct Dados
{
    int id;
    char titulo[MAX];
    char desenvolvedora[MAX];
    float preco;
    int horasJogadas;
};


void exibirmenu(void);
int cadastrarJogo();
int listaDeJogos();
int mediaDeHoras();
#endif 

//PROVA_MAROMO_MODULO_H
