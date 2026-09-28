#ifndef DELIVERY_H
#define DELIVERY_H

typedef struct No {
    int id;
    char cliente[50];
    char item[50];
    float valor;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

typedef struct {
    No *topo;
} Pilha;

/* Operacoes da Fila (FIFO) */
void inicializarFila(Fila *f);
int filaVazia(Fila *f);
int enfileirar(Fila *f, int id, char cliente[], char item[], float valor);
int desenfileirar(Fila *f, No *removido);
void consultarFila(Fila *f);
void exibirFila(Fila *f);
void limparFila(Fila *f);

/* Operacoes da Pilha (LIFO) */
void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
int empilhar(Pilha *p, int id, char cliente[], char item[], float valor);
int desempilhar(Pilha *p, No *removido);
void consultarPilha(Pilha *p);
void exibirPilha(Pilha *p);
void limparPilha(Pilha *p);

#endif
