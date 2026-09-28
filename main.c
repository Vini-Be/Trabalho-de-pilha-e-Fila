#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delivery.h"

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void lerTexto(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

void exibirCabecalho(void) {
    printf("\n");
    printf("  ===============================================================================\n");
    printf("   _____  ____  ____  _____  ____  ___     _     _      _____  ___   ___  ____ \n");
    printf("  | ____|/ ___||  _ \\| ____|/ ___||_ _|   / \\   | |    |  ___|/ _ \\ / _ \\|  _ \\\n");
    printf("  |  _|  \\___ \\| |_) |  _| | |     | |   / _ \\  | |    | |_  | | | | | | | | | |\n");
    printf("  | |___  ___) |  __/| |___| |___  | |  / ___ \\ | |___ |  _| | |_| | |_| | |_| |\n");
    printf("  |_____||____/|_|   |_____|\\____||___|/_/   \\_\\|_____||_|    \\___/ \\___/|____/ \n");
    printf("  ===============================================================================\n");
    printf("                     SISTEMA ESPECIAL FOOD - DELIVERY\n");
    printf("                 Estruturas: Fila (FIFO) & Pilha (LIFO)\n");
    printf("                      IF Baiano - Campus Guanambi\n");
    printf("  ===============================================================================\n");
}

void exibirMenu(void) {
    printf("  [1] Novo pedido (Inserir no FIM da Fila - FIFO)\n");
    printf("  [2] Preparar/Entregar pedido (Desenfileirar da Fila e Empilhar na Pilha)\n");
    printf("  [3] Cancelar pedido da Fila (Remover do INICIO da Fila sem empilhar)\n");
    printf("  [4] Consultar proximo pedido da Fila (INICIO - sem remover)\n");
    printf("  [5] Consultar ultimo pedido do Historico (TOPO da Pilha - sem remover)\n");
    printf("  [6] Estornar/Remover pedido do Historico (Desempilhar do TOPO - LIFO)\n");
    printf("  [7] Exibir Fila, Pilha e Ponteiros de Controle (inicio, fim, topo)\n");
    printf("  [8] Esvaziar / Limpar Fila e Pilha manualmente\n");
    printf("  [0] Encerrar programa (com liberacao automatica da memoria pendente)\n");
    printf("  -------------------------------------------------------------------------------\n");
    printf("  Escolha uma opcao: ");
}

int main(void) {
    Fila filaPedidos;
    Pilha pilhaHistorico;
    int opcao;
    int proximoId = 1;
    char cliente[50];
    char item[50];
    float valor;
    No pedidoTemp;

    inicializarFila(&filaPedidos);
    inicializarPilha(&pilhaHistorico);

    do {
        exibirCabecalho();
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            printf("\n  [ERRO] Entrada invalida! Digite um numero inteiro correspondente ao menu.\n");
            limparBuffer();
            opcao = -1;
            continue;
        }

        limparBuffer();

        switch (opcao) {
            case 1:
                printf("\n  +--- [NOVO PEDIDO] ---------------------------------+\n");
                printf("  | Nome do cliente: ");
                do {
                    lerTexto(cliente, sizeof(cliente));
                } while (strlen(cliente) == 0);

                printf("  | Item/Lanche pedido: ");
                do {
                    lerTexto(item, sizeof(item));
                } while (strlen(item) == 0);

                printf("  | Valor do pedido (R$): ");
                while (scanf("%f", &valor) != 1 || valor <= 0) {
                    printf("  | [ERRO] Valor invalido! Digite um valor positivo: ");
                    limparBuffer();
                }
                limparBuffer();
                printf("  +---------------------------------------------------+\n");

                if (enfileirar(&filaPedidos, proximoId, cliente, item, valor)) {
                    proximoId++;
                }
                break;

            case 2:
                printf("\n  +--- [PREPARACAO E ENTREGA: FILA -> PILHA] --------+\n");
                if (desenfileirar(&filaPedidos, &pedidoTemp)) {
                    empilhar(&pilhaHistorico, pedidoTemp.id, pedidoTemp.cliente, pedidoTemp.item, pedidoTemp.valor);
                    printf("  |  >> [ESPECIAL FOOD] Pedido preparado e arquivado no historico!\n");
                }
                printf("  +---------------------------------------------------+\n");
                break;

            case 3:
                printf("\n  +--- [CANCELAR PEDIDO DA FILA] ---------------------+\n");
                desenfileirar(&filaPedidos, NULL);
                printf("  +---------------------------------------------------+\n");
                break;

            case 4:
                consultarFila(&filaPedidos);
                break;

            case 5:
                consultarPilha(&pilhaHistorico);
                break;

            case 6:
                printf("\n  +--- [ESTORNO DE ENTREGA / DESEMPILHAR] -----------+\n");
                desempilhar(&pilhaHistorico, NULL);
                printf("  +---------------------------------------------------+\n");
                break;

            case 7:
                exibirFila(&filaPedidos);
                exibirPilha(&pilhaHistorico);
                break;

            case 8:
                printf("\n  +--- [LIMPEZA MANUAL DAS ESTRUTURAS] ---------------+\n");
                limparFila(&filaPedidos);
                limparPilha(&pilhaHistorico);
                printf("  +---------------------------------------------------+\n");
                break;

            case 0:
                printf("\n  ===============================================================================\n");
                printf("  Encerrando o sistema e liberando memoria pendente...\n");
                limparFila(&filaPedidos);
                limparPilha(&pilhaHistorico);
                printf("\n    >> [ESPECIAL FOOD] Sistema finalizado com sucesso!\n");
                printf("    Obrigado por utilizar o sistema. Ate a proxima!\n");
                printf("  ===============================================================================\n\n");
                break;

            default:
                printf("\n  [ERRO] Opcao invalida! Escolha entre 0 e 8.\n");
        }

    } while (opcao != 0);

    return 0;
}
