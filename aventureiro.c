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

void lerStringLinha(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = 0;
}

int lerInteiro() {
    int v;
    while (scanf("%d", &v) != 1) {
        printf("Entrada invalida. Tente novamente: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return v;
}

void inserirItemVetor(Item x) {
    if (qtdVetor >= MAX_VETOR) {
        printf("Mochila do vetor cheia (cap=%d).\n", MAX_VETOR);
        return;
    }
    mochilaVetor[qtdVetor++] = x;
    vetorOrdenado = 0;
    printf("Item inserido no vetor.\n");
}

void removerItemVetor(char nome[]) {
    int i, encontrado = 0;
    for (i = 0; i < qtdVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Item '%s' nao encontrado no vetor.\n", nome);
        return;
    }
    for (int j = i; j < qtdVetor - 1; j++) {
        mochilaVetor[j] = mochilaVetor[j+1];
    }
    qtdVetor--;
    printf("Item removido do vetor.\n");
}

void listarVetor() {
    if (qtdVetor == 0) {
        printf("(Vetor vazio)\n");
        return;
    }
    printf("Itens na mochila (vetor):\n");
    for (int i = 0; i < qtdVetor; i++) {
        printf(" %2d) %-28s | %-10s | x%d\n", i+1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

int buscarSequencialVetor(char nome[]) {
    compSeqVetor = 0;
    for (int i = 0; i < qtdVetor; i++) {
        compSeqVetor++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

void ordenarVetor() {
    if (qtdVetor <= 1) {
        vetorOrdenado = 1;
        printf("Vetor ordenado (trivial).\n");
        return;
    }
    for (int i = 0; i < qtdVetor - 1; i++) {
        for (int j = 0; j < qtdVetor - 1 - i; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                Item tmp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = tmp;
            }
        }
    }
    vetorOrdenado = 1;
    printf("Vetor ordenado por nome.\n");
}

int buscarBinariaVetor(char nome[]) {
    compBinVetor = 0;
    if (!vetorOrdenado) {
        printf("AVISO: vetor nao esta ordenado. Ordene antes de usar busca binaria.\n");
        return -1;
    }
    int ini = 0, fim = qtdVetor - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        compBinVetor++;
        int cmp = strcmp(nome, mochilaVetor[meio].nome);
        if (cmp == 0) return meio;
        if (cmp < 0) fim = meio - 1;
        else ini = meio + 1;
    }
    return -1;
}

void inserirItemLista(Item x) {
    No* novo = malloc(sizeof(No));
    if (!novo) {
        printf("Erro alocacao.\n");
        return;
    }
    novo->dados = x;
    novo->proximo = mochilaLista;
    mochilaLista = novo;
    printf("Item inserido na lista.\n");
}

void removerItemLista(char nome[]) {
    No *at = mochilaLista, *ant = NULL;
    while (at) {
        if (strcmp(at->dados.nome, nome) == 0) {
            if (ant) ant->proximo = at->proximo;
            else mochilaLista = at->proximo;
            free(at);
            printf("Item removido da lista.\n");
            return;
        }
        ant = at;
        at = at->proximo;
    }
    printf("Item '%s' nao encontrado na lista.\n", nome);
}

void listarLista() {
    if (!mochilaLista) {
        printf("(Lista vazia)\n");
        return;
    }
    printf("Itens na mochila (lista):\n");
    No* aux = mochilaLista;
    int i = 1;
    while (aux) {
        printf(" %2d) %-28s | %-10s | x%d\n", i++, aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
    }
}

No* buscarSequencialLista(char nome[]) {
    compSeqLista = 0;
    No* aux = mochilaLista;
    while (aux) {
        compSeqLista++;
        if (strcmp(aux->dados.nome, nome) == 0) return aux;
        aux = aux->proximo;
    }
    return NULL;
}

void liberarLista() {
    No* aux = mochilaLista;
    while (aux) {
        No* prox = aux->proximo;
        free(aux);
        aux = prox;
    }
    mochilaLista = NULL;
}

void submenuVetor() {
    while (1) {
        printf("\n--- Mochila (Vetor) ---\n");
        printf("1 Inserir item\n2 Remover item\n3 Listar itens\n4 Buscar sequencial\n5 Ordenar vetor\n6 Buscar binaria\n0 Voltar\nEscolha: ");
        int op = lerInteiro();
        if (op == 0) break;

        if (op == 1) {
            Item x;
            printf("Nome: "); lerStringLinha(x.nome, sizeof(x.nome));
            printf("Tipo: "); lerStringLinha(x.tipo, sizeof(x.tipo));
            printf("Quantidade: "); x.quantidade = lerInteiro();
            inserirItemVetor(x);
        } else if (op == 2) {
            char nome[30];
            printf("Nome do item a remover: "); lerStringLinha(nome, sizeof(nome));
            removerItemVetor(nome);
        } else if (op == 3) {
            listarVetor();
        } else if (op == 4) {
            char nome[30];
            printf("Nome a buscar (sequencial): "); lerStringLinha(nome, sizeof(nome));
            int pos = buscarSequencialVetor(nome);
            if (pos >= 0) printf("Encontrado na posicao %d (comparacoes=%d)\n", pos+1, compSeqVetor);
            else printf("Nao encontrado (comparacoes=%d)\n", compSeqVetor);
        } else if (op == 5) {
            ordenarVetor();
        } else if (op == 6) {
            char nome[30];
            printf("Nome a buscar (binaria): "); lerStringLinha(nome, sizeof(nome));
            int pos = buscarBinariaVetor(nome);
            if (pos >= 0) printf("Encontrado na posicao %d (comparacoes=%d)\n", pos+1, compBinVetor);
            else if (vetorOrdenado) printf("Nao encontrado (comparacoes=%d)\n", compBinVetor);
        } else {
            printf("Opcao invalida.\n");
        }
    }
}

void submenuLista() {
    while (1) {
        printf("\n--- Mochila (Lista) ---\n");
        printf("1 Inserir item\n2 Remover item\n3 Listar itens\n4 Buscar sequencial\n0 Voltar\nEscolha: ");
        int op = lerInteiro();
        if (op == 0) break;

        if (op == 1) {
            Item x;
            printf("Nome: "); lerStringLinha(x.nome, sizeof(x.nome));
            printf("Tipo: "); lerStringLinha(x.tipo, sizeof(x.tipo));
            printf("Quantidade: "); x.quantidade = lerInteiro();
            inserirItemLista(x);
        } else if (op == 2) {
            char nome[30];
            printf("Nome do item a remover: "); lerStringLinha(nome, sizeof(nome));
            removerItemLista(nome);
        } else if (op == 3) {
            listarLista();
        } else if (op == 4) {
            char nome[30];
            printf("Nome a buscar (sequencial): "); lerStringLinha(nome, sizeof(nome));
            No* r = buscarSequencialLista(nome);
            if (r) printf("Encontrado (comparacoes=%d): %s | %s | x%d\n", compSeqLista, r->dados.nome, r->dados.tipo, r->dados.quantidade);
            else printf("Nao encontrado (comparacoes=%d)\n", compSeqLista);
        } else {
            printf("Opcao invalida.\n");
        }
    }
}

int main() {
    while (1) {
        printf("\n==================== MOCHILA - Comparacao Vetor x Lista ====================\n");
        printf("1 Usar Mochila (Vetor)\n2 Usar Mochila (Lista Encadeada)\n3 Mostrar contadores de comparacao\n0 Sair\nEscolha: ");
        int op = lerInteiro();
        if (op == 0) break;
        if (op == 1) submenuVetor();
        else if (op == 2) submenuLista();
        else if (op == 3) {
            printf("\nContadores:\n - Busca sequencial (vetor): %d comparacoes (ultima)\n - Busca binaria (vetor): %d comparacoes (ultima)\n - Busca sequencial (lista): %d comparacoes (ultima)\n", compSeqVetor, compBinVetor, compSeqLista);
        } else {
            printf("Opcao invalida.\n");
        }
    }

    liberarLista();
    printf("Encerrando. Bye!\n");
    return 0;
}
