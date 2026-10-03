# Sistema Especial Food - Delivery 🍔🍕
**Trabalho Avaliativo: Pilhas e Filas em C**

**Instituto Federal Baiano - Campus Guanambi**
**Disciplina:** Estrutura de Dados
**Professor:** Reinaldo Cotrim

---

## 1. Identificação do Projeto e Integrantes
- **Nome do Projeto:** Sistema Especial Food - Delivery
- **Tema:** Gerenciamento de Pedidos e Histórico de Entregas (Especial Food)
- **Integrantes da Equipe:**
  1. Vinícius Benevides Reis
  2. Hiago Rocha Silva

---

## 2. Definição do Tema e Justificativas Teóricas
### Problema que o programa resolve:
O sistema gerencia o fluxo de atendimento da lanchonete/restaurante Especial Food com serviço de entrega (delivery). Ele organiza os pedidos que chegam e aguardam preparo, despacha os pedidos para entrega e mantém um histórico auditável das entregas realizadas, permitindo estornos.

### Informações armazenadas em cada Nó:
* `id` (int): Identificador único sequencial do pedido.
* `cliente` (char[50]): Nome do cliente solicitante.
* `item` (char[50]): Nome do lanche ou produto pedido.
* `valor` (float): Valor total em reais (R$).
* `proximo` (struct No*): Ponteiro para o próximo nó da estrutura encadeada.

### Uso da FILA (Queue) e Justificativa FIFO (First In, First Out):
* **Justificativa:** Os pedidos devem ser preparados e despachados na estrita ordem de chegada. O primeiro cliente a fazer o pedido deve ser o primeiro a ser atendido (FIFO).
* **Campos de controle:** `inicio` (aponta para o próximo a ser atendido) e `fim` (aponta para o último pedido cadastrado).

### Uso da PILHA (Stack) e Justificativa LIFO (Last In, First Out):
* **Justificativa:** Conforme os pedidos são despachados, eles entram no histórico de entregas. Caso ocorra algum problema recente (ex: avaria, cancelamento ou estorno no momento da entrega), a operação de estorno atua sobre o último pedido despachado (LIFO).
* **Campo de controle:** `topo` (aponta para o pedido despachado mais recentemente).

---

## 3. Estrutura dos Arquivos do Projeto
* `delivery.h`: Cabeçalho com as definições das structs (No, Fila, Pilha) e protótipos das funções.
* `fila.c`: Implementação das operações dinâmicas da Fila (FIFO).
* `pilha.c`: Implementação das operações dinâmicas da Pilha (LIFO).
* `main.c`: Menu interativo em terminal, com sistema de controle e interações com o usuário.

---

## 4. Instruções de Execução

### Comando de Compilação
No terminal, dentro da pasta do projeto, execute o comando abaixo (necessário ter o compilador GCC instalado):

```bash
gcc -Wall -Wextra main.c fila.c pilha.c -o delivery
```

### Forma de Execução
No **Windows** (PowerShell / CMD):
```powershell
.\delivery.exe
```

No **Linux / macOS**:
```bash
./delivery
```

---

## 5. Exemplo de Uso e Roteiro de Testes
Para a apresentação ao professor e validação dos requisitos do trabalho, siga este roteiro no menu do sistema:

### TESTE 1: Consulta e remoção na estrutura vazia
- Inicie o programa (Fila e Pilha vazias).
- Digite `4` (Consultar Fila) -> Exibe mensagem de aviso de fila vazia.
- Digite `3` (Remover da Fila) -> Exibe mensagem de aviso de fila vazia.
- Digite `5` (Consultar Pilha) -> Exibe mensagem de aviso de histórico vazio.
- Digite `6` (Remover da Pilha) -> Exibe mensagem de aviso de histórico vazio.

### TESTE 2: Inserção e verificação da ordem de saída
- Digite `1` e cadastre o Pedido #1 (ex: Cliente: Ana, Item: Pizza, R$ 45.00).
- Digite `1` e cadastre o Pedido #2 (ex: Cliente: Bruno, Item: Burger, R$ 30.00).
- Digite `1` e cadastre o Pedido #3 (ex: Cliente: Carla, Item: Sushi, R$ 60.00).
- Digite `7` para ver a Fila: Pedido #1 está no início e #3 no fim.
- Digite `2` (Atender/Entregar): Sai o Pedido #1 (comprovando FIFO da Fila) e entra na Pilha.
- Digite `2` (Atender/Entregar): Sai o Pedido #2.
- Digite `2` (Atender/Entregar): Sai o Pedido #3.
- Digite `7` para ver a Pilha: Pedido #3 está no topo, depois #2, depois #1.
- Digite `6` (Estornar): Sai o Pedido #3 (comprovando LIFO da Pilha).

### TESTE 3: Consulta do próximo elemento sem alterar
- Com pedidos na fila/pilha, execute a Opção `4` ou `5`.
- Em seguida, execute a Opção `7` (Exibir).
- Comprove que nenhum nó foi retirado nem a ordem foi alterada.

### TESTE 4: Remoção do único elemento e conferência de controle
- Na Fila com apenas 1 pedido: execute a Opção `3`. O sistema informa que `inicio = NULL` e `fim = NULL`.
- Na Pilha com apenas 1 pedido: execute a Opção `6`. O sistema informa que `topo = NULL`.

### TESTE 5: Nova inserção após esvaziar a estrutura
- Esvazie as estruturas com a Opção `8` (Limpar Fila e Pilha).
- Digite `1` para cadastrar um novo pedido.
- Comprove que os ponteiros `inicio` e `fim` são atualizados corretamente (Opção `7`).

### TESTE 6: Encerramento com limpeza pendente
- Com pedidos cadastrados na Fila ou na Pilha, digite `0` (Encerrar).
- O sistema percorre as duas estruturas, desaloca cada nó individualmente com `free()` (evitando vazamento de memória) e exibe o encerramento.
