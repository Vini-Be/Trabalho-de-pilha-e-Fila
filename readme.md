===================================================================
INSTITUTO FEDERAL BAIANO - CAMPUS GUANAMBI
Disciplina: Estrutura de Dados
Professor: Reinaldo Cotrim
Trabalho Avaliativo: Pilhas e Filas em C (ESPECIAL FOOD)
===================================================================

1. IDENTIFICACAO DO PROJETO E INTEGRANTES
- Nome do Projeto: Sistema Especial Food - Delivery
- Tema: Gerenciamento de Pedidos e Historico de Entregas (Especial Food)
- Integrantes da Equipe (ate 3 alunos):
  1. [Vinicius Benevides Reis]
  2. [Hiago Rocha Silva]

-------------------------------------------------------------------
2. DEFINICAO DO TEMA E JUSTIFICATIVAS TEORICAS
- Problema que o programa resolve:
  O sistema gerencia o fluxo de atendimento da lanchonete/restaurante
  Especial Food com servico de entrega (delivery). Ele organiza os pedidos que chegam
  e aguardam preparo, despacha os pedidos para entrega e mantem um
  historico auditavel das entregas realizadas, permitindo estornos.

- Informacoes armazenadas em cada No:
  * id (int): Identificador unico sequencial do pedido.
  * cliente (char[50]): Nome do cliente solicitante.
  * item (char[50]): Nome do lanche ou produto pedido.
  * valor (float): Valor total em reais (R$).
  * proximo (struct No*): Ponteiro para o proximo no da estrutura encadeada.

- Uso da FILA (Queue) e Justificativa FIFO (First In, First Out):
  * Justificativa: Os pedidos devem ser preparados e despachados na
    estrita ordem de chegada. O primeiro cliente a fazer o pedido deve
    ser o primeiro a ser atendido (FIFO).
  * Campos de controle: inicio (aponta para o proximo a ser atendido) e
    fim (aponta para o ultimo pedido cadastrado).

- Uso da PILHA (Stack) e Justificativa LIFO (Last In, First Out):
  * Justificativa: Conforme os pedidos sao despachados, eles entram
    no historico de entregas. Caso ocorra algum problema recente (ex:
    avaria, cancelamento ou estorno no momento da entrega), a operacao
    de estorno atua sobre o ultimo pedido despachado (LIFO).
  * Campo de controle: topo (aponta para o pedido despachado mais recentemente).

-------------------------------------------------------------------
3. ESTRUTURA DOS ARQUIVOS DO PROJETO
- delivery.h : Cabecalho com as definicoes das structs (No, Fila, Pilha)
               e prototipos das funcoes com encapsulamento adequado.
- fila.c     : Implementacao das operacoes dinamicas da Fila (FIFO).
- pilha.c    : Implementacao das operacoes dinamicas da Pilha (LIFO).
- main.c     : Menu interativo em terminal com banner visual (Especial Food),
               tratamento robusto de entradas e orquestracao do fluxo.

-------------------------------------------------------------------
4. COMANDO DE COMPILACAO
No terminal, dentro da pasta do projeto, execute:

gcc -Wall -Wextra main.c fila.c pilha.c -o delivery

-------------------------------------------------------------------
5. FORMA DE EXECUCAO
- No Windows (PowerShell / CMD):
  .\delivery.exe

- No Linux / macOS:
  ./delivery

-------------------------------------------------------------------
6. ROTEIRO DE TESTES OBRIGATORIOS (Secao 5 do Documento do Professor)
Para a apresentacao ao professor, execute os seguintes passos no menu:

[TESTE 1: Consulta e remocao na estrutura vazia com indicacao de falha]
- Inicie o programa (Fila e Pilha vazias).
- Digite 4 (Consultar Fila) -> Exibe mensagem de aviso de fila vazia.
- Digite 3 (Remover da Fila) -> Exibe mensagem de aviso de fila vazia.
- Digite 5 (Consultar Pilha) -> Exibe mensagem de aviso de historico vazio.
- Digite 6 (Remover da Pilha) -> Exibe mensagem de aviso de historico vazio.

[TESTE 2: Insercao de pelo menos 3 elementos e verificacao da ordem de saida]
- Digite 1 e cadastre o Pedido #1 (ex: Cliente: Ana, Item: Pizza, R$ 45.00).
- Digite 1 e cadastre o Pedido #2 (ex: Cliente: Bruno, Item: Burger, R$ 30.00).
- Digite 1 e cadastre o Pedido #3 (ex: Cliente: Carla, Item: Sushi, R$ 60.00).
- Digite 7 para ver a Fila: Pedido #1 esta no inicio e #3 no fim.
- Digite 2 (Atender/Entregar): Sai o Pedido #1 (comprovando FIFO da Fila) e entra na Pilha.
- Digite 2 (Atender/Entregar): Sai o Pedido #2.
- Digite 2 (Atender/Entregar): Sai o Pedido #3.
- Digite 7 para ver a Pilha: Pedido #3 esta no topo, depois #2, depois #1.
- Digite 6 (Estornar): Sai o Pedido #3 (comprovando LIFO da Pilha).

[TESTE 3: Consulta do proximo elemento sem alterar o conteudo ou a ordem]
- Insira pedidos e execute a Opcao 4 (Consultar Fila) ou Opcao 5 (Consultar Pilha).
- Em seguida, execute a Opcao 7 (Exibir).
- Comprove que nenhum no foi retirado nem a ordem foi alterada.

[TESTE 4: Remocao do unico elemento e conferencia dos campos de controle]
- Na Fila com apenas 1 pedido: execute a Opcao 3. O sistema informa que
  inicio = NULL e fim = NULL.
- Na Pilha com apenas 1 pedido: execute a Opcao 6. O sistema informa que
  topo = NULL.

[TESTE 5: Nova insercao apos esvaziar completamente a estrutura]
- Esvazie as estruturas com a Opcao 8 (Limpar Fila e Pilha).
- Digite 1 para cadastrar um novo pedido.
- Comprove que os ponteiros inicio e fim sao atualizados corretamente sem erros.

[TESTE 6: Encerramento do programa com elementos pendentes e limpeza correspondente]
- Com pedidos cadastrados na Fila ou na Pilha, digite 0 (Encerrar).
- O sistema percorre as duas estruturas, desaloca cada no individualmente
  com free(), exibe o total de nos liberados e finaliza sem vazamento de memoria.

-------------------------------------------------------------------
