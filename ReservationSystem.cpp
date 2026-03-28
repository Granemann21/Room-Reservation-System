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
};

bool Room::addReservation(ReservationRequest request) {

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

};

void Room::printRoomSchedule() {

};



ReservationSystem::ReservationSystem(int room_count, int* room_capacities){
    this->room_count = room_count;

    // Fazendo uma copia das capacidades das salas
    this->room_capacities = new int[room_count];
    for (int i = 0; i < room_count; i++) {
        this->room_capacities[i] = room_capacities[i];
    };

    //TODO: criar o array com salas.

}

ReservationSystem::~ReservationSystem() {
    delete[] this->room_capacities;
};

