#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VETOR 100

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

Item mochilaVetor[MAX_VETOR];
int qtdVetor = 0;
int compSeqVetor = 0;
int compBinVetor = 0;
int vetorOrdenado = 0;

No* mochilaLista = NULL;
int compSeqLista = 0;

void lerString(char *dest, int tam) {
    fgets(dest, tam, stdin);
    dest[strcspn(dest, "\n")] = 0;
}

int lerInt() {
    int v;
    scanf("%d", &v);
    getchar();
    return v;
}

void inserirItemVetor(Item x) {
    if (qtdVetor < MAX_VETOR) mochilaVetor[qtdVetor++] = x;
    vetorOrdenado = 0;
    printf("Item inserido.\n");
}

void removerItemVetor(char nome[]) {
    int i;
    for (i = 0; i < qtdVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) break;
    }
    if (i == qtdVetor) {
        printf("Item nao encontrado.\n");
        return;
    }
    for (int j = i; j < qtdVetor - 1; j++)
        mochilaVetor[j] = mochilaVetor[j+1];
    qtdVetor--;
    printf("Item removido.\n");
}

void listarVetor() {
    if (qtdVetor == 0) {
        printf("Vazio.\n");
        return;
    }
    for (int i = 0; i < qtdVetor; i++)
        printf("%s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
}

int buscarSeqVetor(char nome[]) {
    compSeqVetor = 0;
    for (int i = 0; i < qtdVetor; i++) {
        compSeqVetor++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

void ordenarVetor() {
    for (int i = 0; i < qtdVetor - 1; i++)
        for (int j = 0; j < qtdVetor - 1 - i; j++)
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                Item tmp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = tmp;
            }
    vetorOrdenado = 1;
    printf("Ordenado.\n");
}

int buscarBinVetor(char nome[]) {
    compBinVetor = 0;
    if (!vetorOrdenado) {
        printf("Ordene antes.\n");
        return -1;
    }
    int ini = 0, fim = qtdVetor - 1;
    while (ini <= fim) {
        int m = (ini + fim) / 2;
        compBinVetor++;
        int r = strcmp(nome, mochilaVetor[m].nome);
        if (r == 0) return m;
        if (r < 0) fim = m - 1;
        else ini = m + 1;
    }
    return -1;
}

void inserirItemLista(Item x) {
    No* n = malloc(sizeof(No));
    n->dados = x;
    n->proximo = mochilaLista;
    mochilaLista = n;
    printf("Item inserido.\n");
}

void removerItemLista(char nome[]) {
    No *a = mochilaLista, *b = NULL;
    while (a) {
        if (strcmp(a->dados.nome, nome) == 0) {
            if (b) b->proximo = a->proximo;
            else mochilaLista = a->proximo;
            free(a);
            printf("Item removido.\n");
            return;
        }
        b = a;
        a = a->proximo;
    }
    printf("Item nao encontrado.\n");
}

void listarLista() {
    No* a = mochilaLista;
    if (!a) {
        printf("Vazio.\n");
        return;
    }
    while (a) {
        printf("%s | %s | %d\n", a->dados.nome, a->dados.tipo, a->dados.quantidade);
        a = a->proximo;
    }
}

No* buscarSeqLista(char nome[]) {
    compSeqLista = 0;
    No* a = mochilaLista;
    while (a) {
        compSeqLista++;
        if (strcmp(a->dados.nome, nome) == 0) return a;
        a = a->proximo;
    }
    return NULL;
}

void liberarLista() {
    No* a = mochilaLista;
    while (a) {
        No* p = a->proximo;
        free(a);
        a = p;
    }
}

void menuVetor() {
    while (1) {
        printf("\n1 Inserir\n2 Remover\n3 Listar\n4 Busca Sequencial\n5 Ordenar\n6 Busca Binaria\n0 Voltar\n");
        int op = lerInt();
        if (!op) break;

        Item x;
        char nome[30];

        if (op == 1) {
            printf("Nome: ");
            lerString(x.nome, 30);
            printf("Tipo: ");
            lerString(x.tipo, 20);
            printf("Quantidade: ");
            x.quantidade = lerInt();
            inserirItemVetor(x);

        } else if (op == 2) {
            printf("Nome a remover: ");
            lerString(nome, 30);
            removerItemVetor(nome);

        } else if (op == 3) {
            listarVetor();

        } else if (op == 4) {
            printf("Nome: ");
            lerString(nome, 30);
            int r = buscarSeqVetor(nome);
            if (r >= 0) printf("Encontrado (%d comparacoes)\n", compSeqVetor);
            else printf("Nao encontrado (%d comparacoes)\n", compSeqVetor);

        } else if (op == 5) {
            ordenarVetor();

        } else if (op == 6) {
            printf("Nome: ");
            lerString(nome, 30);
            int r = buscarBinVetor(nome);
            if (r >= 0) printf("Encontrado (%d comparacoes)\n", compBinVetor);
            else printf("Nao encontrado (%d comparacoes)\n", compBinVetor);
        }
    }
}

void menuLista() {
    while (1) {
        printf("\n1 Inserir\n2 Remover\n3 Listar\n4 Buscar\n0 Voltar\n");
        int op = lerInt();
        if (!op) break;

        Item x;
        char nome[30];

        if (op == 1) {
            printf("Nome: ");
            lerString(x.nome, 30);
            printf("Tipo: ");
            lerString(x.tipo, 20);
            printf("Quantidade: ");
            x.quantidade = lerInt();
            inserirItemLista(x);

        } else if (op == 2) {
            printf("Nome a remover: ");
            lerString(nome, 30);
            removerItemLista(nome);

        } else if (op == 3) {
            listarLista();

        } else if (op == 4) {
            printf("Nome: ");
            lerString(nome, 30);
            No* r = buscarSeqLista(nome);
            if (r) printf("Encontrado (%d comparacoes)\n", compSeqLista);
            else printf("Nao encontrado (%d comparacoes)\n", compSeqLista);
        }
    }
}

int main() {
    while (1) {
        printf("\n1 Vetor\n2 Lista\n3 Comparacoes\n0 Sair\n");
        int op = lerInt();
        if (!op) break;
        if (op == 1) menuVetor();
        else if (op == 2) menuLista();
        else if (op == 3) {
            printf("Seq Vetor = %d\nBin Vetor = %d\nSeq Lista = %d\n",
                compSeqVetor, compBinVetor, compSeqLista);
        }
    }
    liberarLista();
    return 0;
}
