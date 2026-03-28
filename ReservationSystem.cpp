#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"
#include <iostream>
#include <string>
using namespace std;

// Construtor de Room
Room::Room() {
    this->room_capacity = 0;
    this->num_reservations = 0;
    this->array_size = 2;
    this->reserved = new ReservationRequest*[this->array_size];
};

// Destrutor de Room
Room::~Room() {
    for (int i = 0; i < this->num_reservations; i++) {
        delete reserved[i];
    }

    delete[] reserved;
};

// Metodos de Room
void Room::setCapacity(int cap) {
    this->room_capacity = cap;
};

int Room::dayToInt(string day) {
    if (day == "segunda") return 1;
    if (day == "terca") return 2;
    if (day == "quarta") return 3;
    if (day == "quinta") return 4;
    if (day == "sexta") return 5;
    return 0;
};

bool Room::addReservation(ReservationRequest request) {
    // Varificacao de erro nos horarios inseridos
    if (request.getStartHour() < 7 || request.getEndHour() > 21 
    || request.getEndHour() <= request.getStartHour()) {
        return false; 
    }

    // Verifica conflitos de horario
    for (int i = 0; i < this->num_reservations; i++) {
        // Verifica se o dia da semana eh o mesmo
        if (this->reserved[i]->getWeekday() == request.getWeekday()) {
            // Verifica se existe sobreposicao
            if (this->reserved[i]->getStartHour() < request.getEndHour() 
            && request.getStartHour() < this->reserved[i]->getEndHour()){
                return false;
            }
        }
    }

    // Verifica se cabe mais reservas no array
    if (this->num_reservations == this->array_size) {
        int new_size = this->array_size * 2;
        ReservationRequest** new_arr = new ReservationRequest*[new_size];

        for (int i = 0; i < this->num_reservations; i++) {
            new_arr[i] = this->reserved[i];
        }

        delete[] this->reserved;

        this->reserved = new_arr;
        this->array_size = new_size;
    }

    // Insere o novo horario de forma ordenada
    int pos = 0;
    int request_day = dayToInt(request.getWeekday());
    while (pos < this->num_reservations) {
        // Se o dia da reserva for antes da reserva atual
        if (request_day < dayToInt(this->reserved[pos]->getWeekday())) {
            break;
        }
        // Se for no mesmo dia, mas a hora da reserva for menor que a do atual
        if (request_day == dayToInt(this->reserved[pos]->getWeekday()) &&
            request.getStartHour() < this->reserved[pos]->getStartHour()) {
            break;
        }
        pos++;
    }

    // Desloca as reservas
    for (int j = this->num_reservations; j > pos; j--) {
    this->reserved[j] = this->reserved[j - 1];
    }  

    // Insere a nova reserva
    this->reserved[pos] = new ReservationRequest(request);
    this->num_reservations++;
    return true;
};

bool Room::removeReservation(string course_name) {

    // Verificar se existe essa reversa pra esse curso nessa sala
    int pos = 0;
    while (pos < this->num_reservations) {
    // Se encontra ja deleta 
    if (this->reserved[pos]->getCourseName() == course_name) {
        break;
    }
    pos++;
    }
    // Vai retonar falso se não encontrar o nome do curso
    if (pos==this->num_reservations) {
        return false;
    }

    // Remove a reserva
    delete this->reserved[pos];
    
    // Desloca as reservas restantes para a esquerda
    for(int i = pos; i < this->num_reservations - 1; i++) {
        this->reserved[i] = this->reserved[i + 1];
    }

    this->num_reservations--;

    return true;
};

void Room::printRoomSchedule() {

    std::string arr_days[5] = {"segunda:", "terca:", "quarta:", "quinta:", "sexta:"};

    // Itera em cada dia da semana
    for (int i = 0; i < 5; i++) {
        bool dia_impresso = false;

        // Itera em todas as reservas
        for (int j = 0; j < this->num_reservations; j++) {

            // Se o dia em forma de inteiro for maior que o i + 1  
            // (dia inteiro atual) já vai para o próximo dia da semana.
            if (this->dayToInt(this->reserved[j]->getWeekday()) > i + 1){
                break;
            }

            // Printa todos as aulas daquele dia
            if (this->dayToInt(this->reserved[j]->getWeekday()) == i + 1){
                if (!dia_impresso) {
                    cout << arr_days[i] << endl;
                    dia_impresso = true;
                }
                cout << this->reserved[j]->getStartHour() 
                << "h~" << this->reserved[j]->getEndHour() << "h: " 
                << this->reserved[j]->getCourseName() << endl; 
            }   
        }
    }
};


// Construtor de ReservationSystem
ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;

    // Fazendo uma copia das capacidades das salas
    this->room_capacities = new int[room_count];
    for (int i = 0; i < room_count; i++) {
        this->room_capacities[i] = room_capacities[i];
    };

    // Adicionando as capacidades de cada Room
    this->rooms = new Room[this->room_count];
    for (int i = 0; i < this->room_count; i++) {
        rooms[i].setCapacity(this->room_capacities[i]);
    }
}

// Destrutor de ReservationSystem
ReservationSystem::~ReservationSystem() {
    delete[] this->room_capacities;
    delete[] this->rooms;
};

// Metodos do ReservationSystem
bool ReservationSystem::reserve(ReservationRequest request) {
    for (int i = 0; i < this->room_count; i++) {
        if (this->room_capacities[i] >= request.getStudentCount()) {
            if (this->rooms[i].addReservation(request)) {
                return true;
            }
        }
    }
    return false;
};

bool ReservationSystem::cancel(string course_name) {
    for (int i = 0; i < this->room_count; i++) {
        if (this->rooms[i].removeReservation(course_name)) {
            return true;
        }
    }
    return false;
};

void ReservationSystem::printSchedule() {
    for (int i = 0; i < this->room_count; i++) {
        if (i > 0) {
            cout << endl;
        }

        cout << "Room " << i + 1 << endl;
        this->rooms[i].printRoomSchedule();
    }
};
