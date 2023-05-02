#ifndef FLIGHT_H
#define FLIGHT_H

#include <stdbool.h>
#include "passenger.h"


typedef struct FLIGHT {
    struct FLIGHT* prev;          // Pointer to the previous flight
    struct FLIGHT* next;          // Pointer to the next flight
    char flight_id[10];           // Flight ID
    char destination[50];         // Destination
    int num_seats;                // Number of seats
    int departure_time;           // Departure time
    PASSENGER* passengers_head;   // Head of the single-linked list of passengers
} FLIGHT;


// Function declarations
bool insertTravelerToFlight(FLIGHT *flight, const char *name, int age, int seat_number);
FLIGHT* insert_flight(FLIGHT** head, const char* flight_id, const char* destination, int num_seats, int departure_time);
void printTheFlight(FLIGHT *head, int n);
int searchFlightByTakeoffTime(FLIGHT *head, int departure_time);
void removeTravelerReservaton(FLIGHT *flight, int seat_number);
void removeFlight(FLIGHT **head, const char *flight_id);
bool changeTravelersSeat(FLIGHT *flight, const char *name, int new_seat_number);
void findTravelerInFlights(FLIGHT *head, const char *name);
FLIGHT* find_flight_by_id(FLIGHT* head, const char* flight_id);
FLIGHT* searchFlightByID(FLIGHT *head, const char *flight_id);
void freeFlightList(FLIGHT *head);
void freePassengerList(PASSENGER *head);

#endif // FLIGHT_H
