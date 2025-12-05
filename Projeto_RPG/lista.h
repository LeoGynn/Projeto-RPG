#ifndef LISTA_H
#define LISTA_H


#include "personagem.h"


#define CAPACIDADE 50


typedef struct {
Personagem dados[CAPACIDADE];
int tamanho;
} ListaPersonagens;


void lista_iniciar(ListaPersonagens *l);
int lista_adicionar(ListaPersonagens *l, Personagem p);
int lista_remover_por_nome(ListaPersonagens *l, const char *nome);
int lista_encontrar_indice(const ListaPersonagens *l, const char *nome);


#endif