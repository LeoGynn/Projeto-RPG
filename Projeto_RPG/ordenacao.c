#include <stdlib.h>
#include "ordenacao.h" 

// neste arquivo eu implemento 2 metodos de ordenacao:
// insertion sort e merge sort
// a ordenacao e feita pela iniciativa, do maior para o menor

// insertion sort: algoritmo simples, O(n^2)
static void insertion_sort(ListaPersonagens *l) {
    // comeca do segundo elemento (indice 1) ate o fim da lista
    for (int i = 1; i < l->tamanho; i++) {
        // guarda o personagem atual na variavel chave
        Personagem chave = l->dados[i];
        int j = i - 1;

        // enquanto o indice j for valido e a iniciativa na posicao j
        // for MENOR que a iniciativa da chave, desloca para a direita
        while (j >= 0 && l->dados[j].iniciativa < chave.iniciativa) {
            l->dados[j+1] = l->dados[j]; // move o personagem da posicao j para j+1
            j--;
        }

        // quando termina o while, a posicao correta da chave e j+1
        l->dados[j+1] = chave;
    }
}

// funcao auxiliar do merge sort: mescla duas metades ordenadas
// arr[esq..meio] e arr[meio+1..dir] ja estao ordenados
// tmp e um vetor temporario usado para guardar o resultado
static void mesclar(Personagem *arr, Personagem *tmp, int esq, int meio, int dir) {
    int i = esq;       // indice da metade esquerda
    int j = meio + 1;  // indice da metade direita
    int k = esq;       // indice do vetor temporario

    // enquanto ainda houver elementos nas duas metades
    while (i <= meio && j <= dir) {
        // compara pela iniciativa, pegando sempre o maior primeiro
        if (arr[i].iniciativa >= arr[j].iniciativa) {
            tmp[k++] = arr[i++]; // copia da esquerda
        } else {
            tmp[k++] = arr[j++]; // copia da direita
        }
    }

    // se ainda sobraram elementos na metade esquerda, copia todos
    while (i <= meio) {
        tmp[k++] = arr[i++];
    }

    // se ainda sobraram elementos na metade direita, copia todos
    while (j <= dir) {
        tmp[k++] = arr[j++];
    }

    // copia o trecho mesclado de volta do vetor temporario para o original
    for (i = esq; i <= dir; i++) {
        arr[i] = tmp[i];
    }
}

// funcao recursiva do merge sort
static void merge_sort_rec(Personagem *arr, Personagem *tmp, int esq, int dir) {
    // condicao de parada: se o intervalo tiver 0 ou 1 elemento, ja esta ordenado
    if (esq >= dir) return;

    int meio = (esq + dir) / 2;

    // ordena a metade esquerda
    merge_sort_rec(arr, tmp, esq, meio);
    // ordena a metade direita
    merge_sort_rec(arr, tmp, meio+1, dir);

    // mescla as duas metades ordenadas
    mesclar(arr, tmp, esq, meio, dir);
}

// funcao principal do merge sort para a lista
static void merge_sort(ListaPersonagens *l) {
    // se tiver 0 ou 1 personagem, nao precisa ordenar
    if (l->tamanho <= 1) return;

    // aloca um vetor temporario do mesmo tamanho da lista
    Personagem *tmp = malloc(sizeof(Personagem) * l->tamanho);
    if (!tmp) return; // se nao conseguiu alocar, simplesmente retorna

    // chama a funcao recursiva, passando o vetor interno da lista
    merge_sort_rec(l->dados, tmp, 0, l->tamanho - 1);

    // libera a memoria temporaria
    free(tmp);
}

// funcao que escolhe qual algoritmo usar de acordo com o parametro metodo
void ordenar_personagens(ListaPersonagens *l, int metodo) {
    if (metodo == 0) {
        // metodo 0: usa merge sort (mais eficiente)
        merge_sort(l);
    } else {
        // metodo 1 (ou qualquer outro valor): usa insertion sort (mais simples)
        insertion_sort(l);
    }
}