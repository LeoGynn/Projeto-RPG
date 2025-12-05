#include <string.h>
#include "lista.h"


void lista_iniciar(ListaPersonagens *l) {
l->tamanho = 0;
}


int lista_encontrar_indice(const ListaPersonagens *l, const char *nome) {
for (int i = 0; i < l->tamanho; i++) {
if (strcmp(l->dados[i].nome, nome) == 0) return i;
}
return -1;
}


int lista_adicionar(ListaPersonagens *l, Personagem p) {
if (l->tamanho >= CAPACIDADE) return 0;
l->dados[l->tamanho++] = p;
return 1;
}
