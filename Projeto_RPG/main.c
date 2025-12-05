#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "personagem.h"
#include "lista.h"
#include "utils.h"
#include "ordenacao.h"

void recalcular_iniciativas(ListaPersonagens *l);
void mostrar_ordem(const ListaPersonagens *l);
int carregar_txt(ListaPersonagens *l, const char *arquivo);

int main() {
    ListaPersonagens lista;
    int metodo = 0;          // 0 = merge, 1 = insertion
    int opcao;
    int em_execucao = 1;

    srand((unsigned) time(NULL));
    
    lista_iniciar(&lista);

    carregar_txt(&lista, "personagem.txt");

    while (em_execucao) {
        printf("\nMENU\n");
        printf("1 - Criar personagem\n");
        printf("2 - Escolher metodo de ordenacao\n");
        printf("3 - Iniciar combate\n");
        printf("4 - Listar personagens\n");
        printf("0 - Sair\n");
        printf("> ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); // limpa resto da linha

        if (opcao == 1) {
            Personagem p;
            char dado_str[16];

            printf("Nome: ");
            fgets(p.nome, TAM_NOME, stdin);
            p.nome[strcspn(p.nome, "\n")] = '\0';

            printf("Nivel (1-20): ");
            scanf("%d", &p.nivel);
            while (getchar() != '\n');

            printf("Dado (d4, d6, d8, d10, d12, d20): ");
            fgets(dado_str, 16, stdin);
            dado_str[strcspn(dado_str, "\n")] = '\0';

            p.dado_max = ler_dado(dado_str);
            if (p.dado_max == 0) p.dado_max = 6;
            p.iniciativa = 0;

            if (!lista_adicionar(&lista, p)) {
                printf("Lista cheia.\n");
            }
        }
        else if (opcao == 2) {
            printf("0 - Merge Sort\n");
            printf("1 - Insertion Sort\n");
            printf("Escolha: ");
            scanf("%d", &metodo);
            while (getchar() != '\n');
            if (metodo != 0 && metodo != 1) metodo = 0;
        }
        else if (opcao == 3) {
            int opcao_combate = 1;
            while (opcao_combate) {
                printf("\nCOMBATE\n");
                printf("1 - Avancar turno (recalcular e ordenar)\n");
                printf("2 - Adicionar personagem\n");
                printf("3 - Remover personagem\n");
                printf("4 - Encerrar o COMBATE e Voltar para o menu\n");
                printf("> ");
                scanf("%d", &opcao_combate);
                while (getchar() != '\n');

                if (opcao_combate == 1) {
                    recalcular_iniciativas(&lista);
                    ordenar_personagens(&lista, metodo);
                    mostrar_ordem(&lista);
                }
                else if (opcao_combate == 2) {
                    Personagem p;
                    char dado_str[16];

                    printf("Nome: ");
                    fgets(p.nome, TAM_NOME, stdin);
                    p.nome[strcspn(p.nome, "\n")] = '\0';

                    printf("Nivel: ");
                    scanf("%d", &p.nivel);
                    while (getchar() != '\n');

                    printf("Dado (d4, d6, d8, d10, d12, d20): ");
                    fgets(dado_str, 16, stdin);
                    dado_str[strcspn(dado_str, "\n")] = '\0';

                    p.dado_max = ler_dado(dado_str);
                    if (p.dado_max == 0) p.dado_max = 6;
                    p.iniciativa = 0;

                    lista_adicionar(&lista, p);
                }
                else if (opcao_combate == 3) {
                    char nome[TAM_NOME];
                    printf("Nome a remover: ");
                    fgets(nome, TAM_NOME, stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    lista_remover_por_nome(&lista, nome);
                }
                else if (opcao_combate == 4) {
                    break;
                }
            }
        }
        else if (opcao == 4) {
            mostrar_ordem(&lista);
        }
        else if (opcao == 0) {
            em_execucao = 0;
        }
    }

    return 0;
}

void recalcular_iniciativas(ListaPersonagens *l) {
    int i;
    for (i = 0; i < l->tamanho; i++) {
        int r = rolar_dado(l->dados[i].dado_max);
        l->dados[i].iniciativa = l->dados[i].nivel + r;
    }
}

void mostrar_ordem(const ListaPersonagens *l) {
    int i;
    printf("\nOrdem de acao:\n");
    if (l->tamanho == 0) {
        printf("Nenhum personagem cadastrado.\n");
    }
    for (i = 0; i < l->tamanho; i++) {
        printf("%2d. %-20s | nivel %2d | d%d | ini %2d\n",
               i + 1,
               l->dados[i].nome,
               l->dados[i].nivel,
               l->dados[i].dado_max,
               l->dados[i].iniciativa);
    }
}

int carregar_txt(ListaPersonagens *l, const char *arquivo) {
    FILE *f;
    char linha[256];
    int qtd = 0;

    f = fopen(arquivo, "r");
    if (!f) {
        return 0;
    }

    while (fgets(linha, 256, f)) {
        char *nome;
        char *nivel_str;
        char *dado_str;
        Personagem p;

        if (l->tamanho >= CAPACIDADE) break;

        linha[strcspn(linha, "\n")] = '\0';

        nome = strtok(linha, ";");
        nivel_str = strtok(NULL, ";");
        dado_str = strtok(NULL, ";");

        if (!nome || !nivel_str || !dado_str) continue;

        strncpy(p.nome, nome, TAM_NOME - 1);
        p.nome[TAM_NOME - 1] = '\0';

        p.nivel = atoi(nivel_str);
        p.dado_max = ler_dado(dado_str);
        if (p.dado_max == 0) p.dado_max = 6;
        p.iniciativa = 0;

        if (lista_adicionar(l, p)) {
            qtd++;
        }
    }

    fclose(f);
    return qtd;
}
