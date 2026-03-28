#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"
#include <iostream>
#include <string>
using namespace std;

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

