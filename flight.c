#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/flight.h"

FLIGHT* insert_flight(FLIGHT** head, const char* flight_id, const char* destination, int num_seats, int departure_time) {
    // Allocate memory for the new flight
    FLIGHT* new_flight = (FLIGHT*)malloc(sizeof(Flight));

    if (new_flight == NULL) {
        printf("Memory allocation for the new flight failed.\n");
        return NULL;
    }

    // Initialize the flight details
    strncpy(new_flight->flight_id, flight_id, sizeof(new_flight->flight_id) - 1);
    strncpy(new_flight->destination, destination, sizeof(new_flight->destination) - 1);
    new_flight->num_seats = num_seats;
    new_flight->departure_time = departure_time;
    new_flight->passengers_head = NULL;

    // Insert the flight into the list, maintaining the list order
    if (*head == NULL) { // If the list is empty
        new_flight->prev = NULL;
        new_flight->next = NULL;
        *head = new_flight;
    } else {
        FLIGHT* current = *head;
        FLIGHT* previous = NULL;

        while (current != NULL && strcmp(current->flight_id, flight_id) < 0) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) { // Insert at the beginning of the list
            new_flight->prev = NULL;
            new_flight->next = *head;
            (*head)->prev = new_flight;
            *head = new_flight;
        } else if (current == NULL) { // Insert at the end of the list
            new_flight->prev = previous;
            new_flight->next = NULL;
            previous->next = new_flight;
        } else { // Insert in the middle of the list
            new_flight->prev = previous;
            new_flight->next = current;
            previous->next = new_flight;
            current->prev = new_flight;
        }
    }

    return new_flight;
}




bool insertTravelerToFlight(FLIGHT *flight, const char *name, int age, int seat_number) {
    // Locate the flight in the list
    // (Assuming that the flight pointer passed to this function is already the correct flight)

    // Allocate memory for the new passenger
    PASSENGER *new_passenger = (PASSENGER *)malloc(sizeof(PASSENGER));
    if (new_passenger == NULL) {
        return false;
    }

    // Initialize the passenger details
    strcpy(new_passenger->name, name);
    new_passenger->age = age;
    new_passenger->seat_number = seat_number;
    new_passenger->next = NULL;

    // Insert the passenger into the list, maintaining the list order
    if (flight->passenger_list == NULL) {
        flight->passenger_list = new_passenger;
    } else {
        PASSENGER *current = flight->passenger_list;
        PASSENGER *previous = NULL;

        while (current != NULL && current->seat_number < seat_number) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) {
            new_passenger->next = flight->passenger_list;
            flight->passenger_list = new_passenger;
        } else {
            new_passenger->next = current;
            previous->next = new_passenger;
        }
    }

    return true;
}


int searchFlightWithTakeoffTime(FLIGHT *head, int departure_time) {
    FLIGHT *current = head;
    int position = 1;

    // Traverse the list to find a flight with the matching departure time
    while (current != NULL) {
        if (current->departure_time == departure_time) {
            return position; // Return the position of the flight in the list
        }
        current = current->next;
        position++;
    }

    return -1; // Return -1 if no flight is found with the given departure time
}


void removeFlight(FLIGHT **head, const char *flight_id) {
    FLIGHT *current = *head;
    FLIGHT *previous = NULL;

    // Locate the flight in the list
    while (current != NULL && strcmp(current->flight_id, flight_id) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Flight not found with ID %s.\n", flight_id);
        return;
    }

    // Delete all passenger reservations for the flight
    PASSENGER *passenger = current->passengers_head;
    while (passenger != NULL) {
        PASSENGER *next_passenger = passenger->next;
        free(passenger);
        passenger = next_passenger;
    }

    // Remove the flight from the list
    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    // Release the memory for the flight
    free(current);
}

void removeTravelerReservaton(FLIGHT *flight, int seat_number) {
    PASSENGER *current = flight->passengers_head;
    PASSENGER *previous = NULL;

    // Locate the passenger in the list
    while (current != NULL && current->seat_number != seat_number) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Passenger not found with seat number %d.\n", seat_number);
        return;
    }

    // Remove the passenger from the list
    if (previous == NULL) {
        flight->passengers_head = current->next;
    } else {
        previous->next = current->next;
    }

    // Release the memory for the passenger
    free(current);
}

bool changeTravelersSeat(FLIGHT *flight, const char *name, int new_seat_number) {
    PASSENGER *current = flight->passengers_head;
    PASSENGER *previous = NULL;
    PASSENGER *new_seat_previous = NULL;

    // Locate the passenger in the list
    while (current != NULL && strcmp(current->name, name) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Passenger not found with name %s.\n", name);
        return false;
    }

    // Check if the new seat number is already taken
    PASSENGER *new_seat = flight->passengers_head;
    while (new_seat != NULL && new_seat->seat_number != new_seat_number) {
        new_seat_previous = new_seat;
        new_seat = new_seat->next;
    }

    if (new_seat != NULL) {
        printf("The new seat number %d is already taken.\n", new_seat_number);
        return false;
    }

    // Remove the passenger reservation from the list
    if (previous == NULL) {
        flight->passengers_head = current->next;
    } else {
        previous->next = current->next;
    }

    // Update the seat number for the passenger
    current->seat_number = new_seat_number;

    // Insert the passenger back into the list with the new seat number
    if (flight->passengers_head == NULL || flight->passengers_head->seat_number > new_seat_number) {
        current->next = flight->passengers_head;
        flight->passengers_head = current;
    } else {
        PASSENGER *next_passenger = new_seat_previous->next;
        new_seat_previous->next = current;
        current->next = next_passenger;
    }

    return true;
}


void findTravelerInFlights(FLIGHT *head, const char *name) {
    FLIGHT *current_flight = head;
    bool passenger_found = false;

    printf("Searching for passenger %s in all flights:\n", name);

    while (current_flight != NULL) {
        PASSENGER *current_passenger = current_flight->passengers_head;

        while (current_passenger != NULL) {
            if (strcmp(current_passenger->name, name) == 0) {
                // Print the flight details
                printf("Flight ID: %s\n", current_flight->flight_id);
                printf("Destination: %s\n", current_flight->destination);
                printf("Number of seats: %d\n", current_flight->num_seats);
                printf("Departure time: %d\n", current_flight->departure_time);
                printf("-----\n");
                passenger_found = true;
                break;
            }
            current_passenger = current_passenger->next;
        }

        current_flight = current_flight->next;
    }

    if (!passenger_found) {
        printf("No flights found for passenger %s.\n", name);
    }
}


FLIGHT* find_flight_by_id(FLIGHT* head, const char* flight_id) {
    FLIGHT* current = head;
    while (current != NULL) {
        if (strcmp(current->flight_id, flight_id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Flight not found
}
