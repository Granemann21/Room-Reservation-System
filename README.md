# Room Reservation System


## Descrição do Trabalho
O **Room Reservation System** foi projetado para gerenciar a logística de salas de aula durante um semana letiva (segunda a sexta).
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





