#ifndef PERSONAGEM_H
#define PERSONAGEM_H


#define TAM_NOME 64


typedef struct {
char nome[TAM_NOME];
int nivel; // 1 a 20
int dado_max; // 4,6,8,10,12,20
int iniciativa; // calculada a cada turno
} Personagem;


#endif