# Room Reservation System


## Descrição do Trabalho
O **Room Reservation System** foi projetado para gerenciar a logística de salas de aula durante uma semana letiva (segunda a sexta).
O sistema atua como um decisor inteligente: ao receber uma solicitação, ele identifica a **primeira sala disponível** que satisfaça 
simultaneamente os requisitos de capacidade de alunos e ausência de sobreposição de horários.

---
## Instruções de Compilação e Execução
O sistema utiliza compilação modular para garantir a separação de responsabilidades e facilitar a manutenção.

Para compilar o projeto completo, execute o seguinte comando no terminal:
```bash
g++ main.cpp ReservationSystem.cpp ReservationRequest.cpp -o reservation_system
```

Após a compilação, o binário gerado pode ser executado nos seguintes ambientes:

Windows (PowerShell ou CMD):
```PowerShell
.\reservation_system.exe
```

Linux/MacOS (Terminal):
```Bash
chmod +x reservation_system
./reservation_system
```
---

## Organização Interna e Arquitetura

A arquitetura do sistema foi projetada sob a premissa de uso zero do STL, exigindo uma implementação de baixo nível para todas as estruturas de dados. Isso garante total controle sobre a alocação de memória e o comportamento do sistema.

### 1. Hierarquia de Componentes
O sistema é estruturado em três camadas de responsabilidade:

* **`ReservationSystem` (Gerenciador principal)**: Atua como a interface de entrada. Ele gerencia o conjunto de salas e implementa o algoritmo de busca, que identifica a primeira sala capaz de suportar a carga de alunos e a janela de horário solicitada.
* **`Room` (Gerenciador de reservas da sala)**: Unidade fundamental de armazenamento. Cada sala gerencia seu próprio **Array Dinâmico de Ponteiros para objetos ReservationRequest** (`ReservationRequest**`). A escolha por ponteiros em vez de objetos diretos permite manipulações de memória mais rápidas durante o reordenamento (*shifting*).
* **`ReservationRequest` (Entity)**: Objeto que encapsula os dados da reserva, fornecendo acesso através de métodos (getters).

---

### 2. Estratégia de Gerenciamento de Memória
Como o sistema não utiliza containers automáticos, implementamos um mecanismo redimensionamento dinâmico do array:

* **Estratégia de duplicação de tamanho**: Cada sala inicia com uma capacidade base. Ao atingir o limite, o sistema aloca um novo bloco de memória com o dobro do tamanho atual, transfere os endereços dos ponteiros e libera o bloco antigo.
* **Liberação completa de memória**: O sistema implementa destruição em cascata. Ao encerrar o `ReservationSystem`, ele dispara o destrutor de cada `Room`, que por sua vez percorre e deleta cada `ReservationRequest` individual antes de liberar o próprio array.

---

### 3. Otimização de Performance (Ordenação no momento da inserção)
Diferente de sistemas que ordenam os dados apenas no momento da exibição, este projeto utiliza o conceito de Inserção Ordenada:

* No momento em que o `reserve()` é chamado, o sistema já identifica a posição cronológica exata (considerando Dia da Semana e Hora de Início).
* Isso transforma a complexidade de exibição (`printSchedule`) em **O(N)**, permitindo que relatórios sejam gerados instantaneamente sem sobrecarga de processamento.

---
### 4. Funcionamento das Operações

- **Reserva (`reserve`)**:
  O sistema percorre sequencialmente todas as salas. Para cada sala, verifica se a capacidade é suficiente e se não há conflito de horário. A reserva é inserida na primeira sala que satisfaz ambas as condições.

- **Cancelamento (`cancel`)**:
  O sistema percorre todas as salas em busca de uma reserva com o nome da disciplina informado. Ao encontrar, remove a reserva e reorganiza o array interno.

- **Verificação de Conflito de Horário**:
  Para cada reserva existente na sala, o sistema verifica se há sobreposição utilizando a condição:
  
  `(inicio_existente < fim_novo && inicio_novo < fim_existente)`
  
  Caso essa condição seja verdadeira, há conflito e a reserva não é realizada.
---

## Limitações

- O sistema assume que o nome das disciplinas é único, conforme especificado no enunciado.
- Não há validação de entradas inválidas para dias da semana, pois o enunciado garante que serão sempre corretos.
  
---
## Autores
* **Murilo Granemann de Souza**
* **Luis Eduardo Weigert Weiss**

---
*Projeto desenvolvido para o Trabalho 1 da disciplina de Estrutura de Dados - Março de 2026.*






