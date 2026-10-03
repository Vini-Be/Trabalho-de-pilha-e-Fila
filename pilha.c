#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delivery.h"

void inicializarPilha(Pilha *p) {
    p->topo = NULL;
} 

int pilhaVazia(Pilha *p) { 
    return (p->topo == NULL);
}

int empilhar(Pilha *p, int id, char cliente[], char item[], float valor) {
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL) {
        printf("\n  [ERRO] Falha de alocacao de memoria na Pilha!\n");
        return 0;
    }

    novo->id = id;
    strncpy(novo->cliente, cliente, sizeof(novo->cliente) - 1);
    novo->cliente[sizeof(novo->cliente) - 1] = '\0';
    strncpy(novo->item, item, sizeof(novo->item) - 1);
    novo->item[sizeof(novo->item) - 1] = '\0';
    novo->valor = valor;
    novo->proximo = p->topo;
    p->topo = novo;

    printf("\n  [OK] Pedido #%d registrado no TOPO do historico (Pilha).\n", id);
    printf("  [CONTROLE PILHA] topo -> Pedido #%d\n", p->topo->id);
    return 1;
}

int desempilhar(Pilha *p, No *removido) {
    if (pilhaVazia(p)) {
        printf("\n  [AVISO] O historico (Pilha) esta vazio! Nao ha pedido para remover.\n");
        return 0;
    }

    No *aux = p->topo;

    if (removido != NULL) {
        removido->id = aux->id;
        strncpy(removido->cliente, aux->cliente, sizeof(removido->cliente) - 1);
        removido->cliente[sizeof(removido->cliente) - 1] = '\0';
        strncpy(removido->item, aux->item, sizeof(removido->item) - 1);
        removido->item[sizeof(removido->item) - 1] = '\0';
        removido->valor = aux->valor;
        removido->proximo = NULL;
    }

    p->topo = aux->proximo;

    printf("\n  [OK] Pedido #%d (%s - %s) removido do TOPO do historico.\n",
           aux->id, aux->cliente, aux->item);

    free(aux);

    if (p->topo == NULL) {
        printf("  [CONTROLE PILHA] A pilha ficou vazia: topo = NULL.\n");
    } else {
        printf("  [CONTROLE PILHA] Novo topo -> Pedido #%d\n", p->topo->id);
    }

    return 1;
}

void consultarPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("\n  [AVISO] Consulta falhou: o historico (Pilha) esta vazio!\n");
        return;
    }

    printf("\n  +--- ULTIMO PEDIDO PROCESSADO (TOPO DA PILHA) ------+\n");
    printf("  | ID: #%d\n", p->topo->id);
    printf("  | Cliente: %s\n", p->topo->cliente);
    printf("  | Item: %s\n", p->topo->item);
    printf("  | Valor: R$ %.2f\n", p->topo->valor);
    printf("  | [CONTROLE] topo aponta para este no (#%d)\n", p->topo->id);
    printf("  +---------------------------------------------------+\n");
}

void exibirPilha(Pilha *p) {
    printf("\n  ================ ESTADO DA PILHA (HISTORICO) ================\n");

    if (pilhaVazia(p)) {
        printf("  Pilha vazia -> [topo = NULL]\n");
    } else {
        printf("  [topo -> Pedido #%d]\n", p->topo->id);
        printf("  Encadeamento LIFO (do topo para a base):\n  ");

        No *atual = p->topo;
        while (atual != NULL) {
            printf(" [ #%d | %s | %s | R$ %.2f ] -> ",
                   atual->id, atual->cliente, atual->item, atual->valor);
            atual = atual->proximo;
        }

        printf("NULL\n");
    }

    printf("  =============================================================\n");
}

void limparPilha(Pilha *p) {
    int contador = 0;

    while (!pilhaVazia(p)) {
        No *remover = p->topo;
        p->topo = remover->proximo;
        free(remover);
        contador++;
    }

    printf("\n  [LIMPEZA PILHA] %d no(s) liberado(s) da memoria.\n", contador);
    printf("  [CONTROLE PILHA] topo = NULL.\n");
}
