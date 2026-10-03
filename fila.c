#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delivery.h"

void inicializarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int filaVazia(Fila *f) {
    return (f->inicio == NULL);
}

int enfileirar(Fila *f, int id, char cliente[], char item[], float valor) {
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL) {
        printf("\n  [ERRO] Falha de alocacao de memoria na Fila!\n");
        return 0;
    }

    novo->id = id;
    strcpy(novo->cliente, cliente);
    strcpy(novo->item, item);
    novo->valor = valor;
    novo->proximo = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->proximo = novo;
        f->fim = novo;
    }

    printf("\n  [OK] Pedido #%d inserido no FIM da fila de espera.\n", id);
    printf("  [CONTROLE FILA] inicio -> Pedido #%d | fim -> Pedido #%d\n",
           f->inicio->id, f->fim->id);
    return 1;
}

int desenfileirar(Fila *f, No *removido) {
    if (filaVazia(f)) {
        printf("\n  [AVISO] A fila de pedidos esta vazia! Nao ha pedido para remover.\n");
        return 0;
    }

    No *aux = f->inicio;

    if (removido != NULL) {
        removido->id = aux->id;
        strcpy(removido->cliente, aux->cliente);
        strcpy(removido->item, aux->item);
        removido->valor = aux->valor;
        removido->proximo = NULL;
    }

    f->inicio = aux->proximo;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    printf("\n  [OK] Pedido #%d (%s - %s) saiu do INICIO da fila.\n",
           aux->id, aux->cliente, aux->item);

    free(aux);

    if (f->inicio == NULL && f->fim == NULL) {
        printf("  [CONTROLE FILA] A fila ficou vazia: inicio = NULL e fim = NULL.\n");
    } else {
        printf("  [CONTROLE FILA] Novo inicio -> Pedido #%d | fim -> Pedido #%d\n",
               f->inicio->id, f->fim->id);
    }

    return 1;
}

void consultarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\n  [AVISO] Consulta falhou: a fila de pedidos esta vazia!\n");
        return;
    }

    printf("\n  +--- PROXIMO PEDIDO DA FILA (INICIO) ----------------+\n");
    printf("  | ID: #%d\n", f->inicio->id);
    printf("  | Cliente: %s\n", f->inicio->cliente);
    printf("  | Item: %s\n", f->inicio->item);
    printf("  | Valor: R$ %.2f\n", f->inicio->valor);
    printf("  | [CONTROLE] inicio aponta para #%d | fim aponta para #%d\n",
           f->inicio->id, f->fim->id);
    printf("  +---------------------------------------------------+\n");
}

void exibirFila(Fila *f) {
    printf("\n  ================ ESTADO DA FILA (AGUARDANDO) ================\n");

    if (filaVazia(f)) {
        printf("  Fila vazia -> [inicio = NULL | fim = NULL]\n");
    } else {
        printf("  [inicio -> Pedido #%d | fim -> Pedido #%d]\n",
               f->inicio->id, f->fim->id);
        printf("  Encadeamento FIFO (do inicio ao fim):\n  ");

        No *atual = f->inicio;
        while (atual != NULL) {
            printf(" [ #%d | %s | %s | R$ %.2f ] -> ",
                   atual->id, atual->cliente, atual->item, atual->valor);
            atual = atual->proximo;
        }

        printf("NULL\n");
    }
}

void limparFila(Fila *f) {
    int contador = 0;

    while (!filaVazia(f)) {
        No *remover = f->inicio;
        f->inicio = remover->proximo;
        free(remover);
        contador++;
    }

    f->fim = NULL;
    printf("\n  [LIMPEZA FILA] %d no(s) liberado(s) da memoria.\n", contador);
    printf("  [CONTROLE FILA] inicio = NULL | fim = NULL.\n");
}
