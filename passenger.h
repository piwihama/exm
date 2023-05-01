// passenger.h
#ifndef PASSENGER_H
#define PASSENGER_H

typedef struct Passenger {
    int seat_number;
    char name[50];
    int age;
    struct Passenger *next;
} PASSENGER;

#endif // PASSENGER_H
