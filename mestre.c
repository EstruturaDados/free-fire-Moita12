#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

void lerLinha(char *s, int tam) {
    if (fgets(s, tam, stdin) == NULL) { s[0] = '\0'; return; }
    s[strcspn(s, "\n")] = 0;
}

void mostrarComponentes(Componente v[], int n) {
    printf("\nLista de componentes (%d):\n", n);
    printf("-----------------------------------------------\n");
    printf("%-3s %-25s %-12s %s\n", "No", "Nome", "Tipo", "Prioridade");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d %-25s %-12s %d\n", i+1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("-----------------------------------------------\n");
}

long long bubbleSortNome(Componente v[], int n) {
    long long comps = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            comps++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente t = v[j]; v[j] = v[j+1]; v[j+1] = t;
            }
        }
    }
    return comps;
}

long long insertionSortTipo(Componente v[], int n) {
    long long comps = 0;
    for (int i = 1; i < n; i++) {
        Componente key = v[i];
        int j = i - 1;
        while (j >= 0) {
            comps++;
            if (strcmp(v[j].tipo, key.tipo) > 0) {
                v[j+1] = v[j];
                j--;
            } else break;
        }
        v[j+1] = key;
    }
    return comps;
}

long long selectionSortPrioridade(Componente v[], int n) {
    long long comps = 0;
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            comps++;
            if (v[j].prioridade < v[min].prioridade) min = j;
        }
        if (min != i) {
            Componente t = v[i]; v[i] = v[min]; v[min] = t;
        }
    }
    return comps;
}

int buscaBinariaNome(Componente v[], int n, char chave[], long long *comparacoes) {
    *comparacoes = 0;
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        (*comparacoes)++;
        int cmp = strcmp(chave, v[m].nome);
        if (cmp == 0) return m;
        if (cmp < 0) r = m - 1;
        else l = m + 1;
    }
    return -1;
}

int main() {
    Componente comps[MAX_COMP];
    int n = 0;
    printf("Cadastro de componentes (max %d)\n", MAX_COMP);
    printf("Quantos componentes deseja cadastrar? ");
    if (scanf("%d", &n) != 1) return 0;
    if (n < 1) return 0;
    if (n > MAX_COMP) n = MAX_COMP;
    while (getchar() != '\n');

    for (int i = 0; i < n; i++) {
        printf("\nComponente %d\n", i+1);
        printf("Nome: "); lerLinha(comps[i].nome, sizeof(comps[i].nome));
        printf("Tipo: "); lerLinha(comps[i].tipo, sizeof(comps[i].tipo));
        printf("Prioridade (1-10): ");
        int p;
        while (scanf("%d", &p) != 1 || p < 1 || p > 10) {
            printf("Prioridade invalida. Digite 1 a 10: ");
            while (getchar() != '\n');
        }
        comps[i].prioridade = p;
        while (getchar() != '\n');
    }

    int opc = -1;
    int ordenadoPorNome = 0;
    long long compsCount = 0;
    double tempo = 0.0;

    while (1) {
        printf("\nMenu de ordenacao e busca\n");
        printf("1 - Bubble sort por nome\n");
        printf("2 - Insertion sort por tipo\n");
        printf("3 - Selection sort por prioridade\n");
        printf("4 - Busca binaria por nome (exige ordenacao por nome)\n");
        printf("5 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) break;
        while (getchar() != '\n');

        if (opc == 0) break;
        if (opc == 1) {
            Componente copia[MAX_COMP];
            for (int i=0;i<n;i++) copia[i]=comps[i];
            clock_t ini = clock();
            compsCount = bubbleSortNome(copia, n);
            clock_t fim = clock();
            tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
            printf("\nBubble sort por nome: comparacoes=%lld tempo=%.6f s\n", compsCount, tempo);
            for (int i=0;i<n;i++) comps[i]=copia[i];
            ordenadoPorNome = 1;
            mostrarComponentes(comps, n);
        } else if (opc == 2) {
            Componente copia[MAX_COMP];
            for (int i=0;i<n;i++) copia[i]=comps[i];
            clock_t ini = clock();
            compsCount = insertionSortTipo(copia, n);
            clock_t fim = clock();
            tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
            printf("\nInsertion sort por tipo: comparacoes=%lld tempo=%.6f s\n", compsCount, tempo);
            for (int i=0;i<n;i++) comps[i]=copia[i];
            ordenadoPorNome = 0;
            mostrarComponentes(comps, n);
        } else if (opc == 3) {
            Componente copia[MAX_COMP];
            for (int i=0;i<n;i++) copia[i]=comps[i];
            clock_t ini = clock();
            compsCount = selectionSortPrioridade(copia, n);
            clock_t fim = clock();
            tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
            printf("\nSelection sort por prioridade: comparacoes=%lld tempo=%.6f s\n", compsCount, tempo);
            for (int i=0;i<n;i++) comps[i]=copia[i];
            ordenadoPorNome = 0;
            mostrarComponentes(comps, n);
        } else if (opc == 4) {
            if (!ordenadoPorNome) {
                printf("Vetor nao esta ordenado por nome. Rode a opcao 1 primeiro.\n");
            } else {
                char chave[30];
                printf("Digite o nome do componente-chave: ");
                lerLinha(chave, sizeof(chave));
                long long cmpb = 0;
                clock_t ini = clock();
                int pos = buscaBinariaNome(comps, n, chave, &cmpb);
                clock_t fim = clock();
                double t = (double)(fim - ini) / CLOCKS_PER_SEC;
                if (pos >= 0) {
                    printf("Componente encontrado na posicao %d (comparacoes=%lld tempo=%.6f s)\n", pos+1, cmpb, t);
                    printf("Item: %s | %s | %d\n", comps[pos].nome, comps[pos].tipo, comps[pos].prioridade);
                } else {
                    printf("Componente nao encontrado (comparacoes=%lld tempo=%.6f s)\n", cmpb, t);
                }
            }
        } else if (opc == 5) {
            mostrarComponentes(comps, n);
        } else {
            printf("Opcao invalida\n");
        }
    }

    printf("Encerrando\n");
    return 0;
}
