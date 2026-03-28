#ifndef RESERVATION_SYSTEM_HPP
#define RESERVATION_SYSTEM_HPP

#include <string>
#include "ReservationRequest.hpp"

// Classe auxiliar Room
class Room {
private:
    int room_capacity;
    ReservationRequest** reserved;
    int num_reservations;
    int array_size;

public:
    Room();
    ~Room();

    void setCapacity(int cap);
    int dayToInt(std::string day);
    bool addReservation(ReservationRequest request);
    bool removeReservation(std::string course_name);
    void printRoomSchedule();
};

class ReservationSystem {
private:
    int room_count;
    int* room_capacities;
    Room* rooms;

public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);
    void printSchedule();
};

#endif