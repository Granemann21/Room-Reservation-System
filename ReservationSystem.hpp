#ifndef RESERVATIONSYSTEM_HPP
#define RESERVATIONSYSTEM_HPP

#include <iostream>
#include <string>
#include "ReservationRequest.hpp"

struct Reservation{
    std::string course_name;
    std::string weekday;
    int start_hour;
    int end_hour;
    int student_count;
};

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;
    Reservation* lista_reservas;


public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

#endif