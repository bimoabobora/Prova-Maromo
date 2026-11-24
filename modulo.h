//
// Created by rafae on 18/11/2026.
//

#ifndef PROVA_MAROMO_MODULO_H
#define PROVA_MAROMO_MODULO_H
// Struct
// Constantes
// Protótipos das funções

struct Dados
{
    int id;
    char titulo[255];
    char desenvolvedora[255];
    float preco;
    int horasJogadas;
};


void exibirmenu(void);
int cadastrarJogo();
int listaDeJogos();
int mediaDeHoras();
#endif 

//PROVA_MAROMO_MODULO_H
