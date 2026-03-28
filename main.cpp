#include <iostream>
#include <string>
#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"

using namespace std;

int main() {
    // Limpando o terminal e iniciando os testes
    cout << "\n\n\n";
    cout << "---------- Inicio dos Testes ----------" << endl;


    // Inicializando o sistema com 3 salas
    int capacidades[2] = {30, 50};
    ReservationSystem system(2, capacidades);

    // Reserva que cabe na sala 1
    ReservationRequest req1("Linear Algebra", "segunda", 11, 13, 25);
    if (system.reserve(req1)) {
        cout << "[OK] Linear Algebra reservada com sucesso (deve estar em Room 1)" << endl;
    }

    // Reserva com muitos alunos (deve pular a sala 1 e alocar na 2)
    ReservationRequest req2("Data Structures", "segunda", 7, 9, 45);
    if (system.reserve(req2)) {
        cout << "[OK] Data Structures reservado com sucesso (deve estar em Room 2)" << endl;
    }

    // Conflito de horarios
    ReservationRequest req3("Calculus", "segunda", 8, 10, 45);
    if (!system.reserve(req3)) {
        cout << "[OK] Sistema barrou Calculus corretamente por conflito de horario." << endl;
    }

    // Ordenacao no mesmo dia (adicionando mais aulas em Room 1)
    ReservationRequest req4("Probability", "segunda", 9, 11, 25);
    system.reserve(req4);

    ReservationRequest req5("Programming Language", "segunda", 15, 17, 25);
    system.reserve(req5);

    // Aula em outro dia
    ReservationRequest req6("Data Structures", "quarta", 7, 9, 45);
    system.reserve(req6);

    cout << "\n---------- Agenda Atual ----------" << endl;
    system.printSchedule();

    cout << "\n---------- Cancelando Probability ----------" << endl;
    if (system.cancel("Probability")) {
        cout << "[OK] Probability cancelada" << endl;
    }

    cout << "\n---------- Agenda Apos Cancelamento ----------" << endl;
    system.printSchedule();

    // Fim dos testes
    cout << "\n---------- Fim dos Testes ----------" << endl;
    return 0;
}