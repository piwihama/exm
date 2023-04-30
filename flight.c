#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/air_travel.h"

bool insertTravelerInFlight(FLIGHT *airTravel, const char *personName, int years, int seatNum) {

    // Find the flight in the list
    // (Assuming the flight pointer passed to this function is already the correct flight)

    // Allocate memory for the new traveler
    PASSENGER *new_traveler = (PASSENGER *)malloc(sizeof(PASSENGER));
    if (new_traveler == NULL) {
        return false;
    }

    // Set the traveler details
    strcpy(new_traveler->name, personName);
    new_traveler->age = years;
    new_traveler->seat_number = seatNum;
    new_traveler->next = NULL;

    // Add the traveler into the list, maintaining list order
    if (airTravel->passenger_list == NULL) {
        airTravel->passenger_list = new_traveler;
    } else {
        PASSENGER *curr = airTravel->passenger_list;
        PASSENGER *prev = NULL;

        while (curr != NULL && curr->seat_number < seatNum) {
            prev = curr;
            curr = curr->next;
        }

        if (prev == NULL) {
            new_traveler->next = airTravel->passenger_list;
            airTravel->passenger_list = new_traveler;
        } else {
            new_traveler->next = curr;
            prev->next = new_traveler;
        }
    }

    return true;
}

FLIGHT* addNewFlight(FLIGHT** headNode, const char* flightCode, const char* destinationName, int totalSeats, int timeDeparture) {
    // Allocate memory for the new flight
    FLIGHT* fresh_flight = (FLIGHT*)malloc(sizeof(FLIGHT));

    if (fresh_flight == NULL) {
        printf("Memory allocation for the new flight failed.\n");
        return NULL;
    }

    // Set the flight details
    strncpy(fresh_flight->flight_id, flightCode, sizeof(fresh_flight->flight_id) - 1);
    strncpy(fresh_flight->destination, destinationName, sizeof(fresh_flight->destination) - 1);
    fresh_flight->num_seats = totalSeats;
    fresh_flight->departure_time = timeDeparture;
    fresh_flight->passengers_head = NULL;

    // Insert the flight into the list, maintaining list order
    if (*headNode == NULL) { // If the list is empty
        fresh_flight->prev = NULL;
        fresh_flight->next = NULL;
        *headNode = fresh_flight;
    } else {
        Flight* curr = *headNode;
        Flight* prev = NULL;

        while (curr != NULL && strcmp(curr->flight_id, flightCode) < 0) {
            prev = curr;
            curr = curr->next;
        }

        if (prev == NULL) { // Insert at the beginning of the list
            fresh_flight->prev = NULL;
            fresh_flight->next = *headNode;
            (*headNode)->prev = fresh_flight;
            *headNode = fresh_flight;
        } else if (curr == NULL) { // Insert at the end of the list
            fresh_flight->prev = prev;
            fresh_flight->next = NULL;
            prev->next = fresh_flight;
        } else { // Insert in the middle of the list
            fresh_flight->prev = prev;
            fresh_flight->next = curr;
            prev


HER 


void displayFlightAtPos(FLIGHT *listHead, int position) {
    FLIGHT *currentFlight = listHead;
    int idx;

    // Go through the list to locate the flight at the given position
    for (idx = 1; idx < position && currentFlight != NULL; idx++) {
        currentFlight = currentFlight->next;
    }

    if (currentFlight == NULL) {
        printf("No flight found at position %d.\n", position);
        return;
    }

    // Show the flight information
    printf("Flight info at position %d:\n", position);
    printf("Flight ID: %s\n", currentFlight->flight_id);
    printf("Destination: %s\n", currentFlight->destination);
    printf("Seats available: %d\n", currentFlight->num_seats);
    printf("Time of departure: %d\n", currentFlight->departure_time);

    // Display the details for each passenger on the flight
    printf("List of passengers:\n");
    PASSENGER *traveler = currentFlight->passengers_head;
    while (traveler != NULL) {
        printf("Seat no.: %d\n", traveler->seat_number);
        printf("Name: %s\n", traveler->name);
        printf("Age: %d\n", traveler->age);
        printf("-----\n");
        traveler = traveler->next;
    }
}

int locateFlightByTime(FLIGHT *listHead, int timeOfDeparture) {
    FLIGHT *currentFlight = listHead;
    int currentPosition = 1;

    // Go through the list to find a flight with the specified departure time
    while (currentFlight != NULL) {
        if (currentFlight->departure_time == timeOfDeparture) {
            return currentPosition; // Return the flight's position in the list
        }
        currentFlight = currentFlight->next;
        currentPosition++;
    }

    return -1; // Return -1 if there is no flight with the specified departure time
}


HER


void removeFlight(FLIGHT **listHead, const char *flightID) {
    FLIGHT *currentFlight = *listHead;
    FLIGHT *previousFlight = NULL;

    // Find the flight in the list
    while (currentFlight != NULL && strcmp(currentFlight->flight_id, flightID) != 0) {
        previousFlight = currentFlight;
        currentFlight = currentFlight->next;
    }

    if (currentFlight == NULL) {
        printf("No flight found with ID %s.\n", flightID);
        return;
    }

    // Delete all reservations for passengers on the flight
    PASSENGER *traveler = currentFlight->passengers_head;
    while (traveler != NULL) {
        PASSENGER *nextTraveler = traveler->next;
        free(traveler);
        traveler = nextTraveler;
    }

    // Remove the flight from the list
    if (previousFlight == NULL) {
        *listHead = currentFlight->next;
    } else {
        previousFlight->next = currentFlight->next;
    }

    // Free the memory for the flight
    free(currentFlight);
}

void removePassengerBooking(FLIGHT *flight, int seatNum) {
    PASSENGER *currentTraveler = flight->passengers_head;
    PASSENGER *previousTraveler = NULL;

    // Find the passenger in the list
    while (currentTraveler != NULL && currentTraveler->seat_number != seatNum) {
        previousTraveler = currentTraveler;
        currentTraveler = currentTraveler->next;
    }

    if (currentTraveler == NULL) {
        printf("No passenger found with seat number %d.\n", seatNum);
        return;
    }

    // Remove the passenger from the list
    if (previousTraveler == NULL) {
        flight->passengers_head = currentTraveler->next;
    } else {
        previousTraveler->next = currentTraveler->next;
    }

    // Free the memory for the passenger
    free(currentTraveler);
}

HER

bool alterPassengerSeat(FLIGHT_DATA *flight_data, const char *person_name, int updated_seat_number) {
	TRAVELER *current_traveler = flight_data->travelers_head;
    TRAVELER *previous_traveler = NULL;
    TRAVELER *new_seat_previous_traveler = NULL;

    // Find the traveler in the list
    while (current_traveler != NULL && strcmp(current_traveler->name, person_name) != 0) {
	previous_traveler = current_traveler;
	current_traveler = current_traveler->next;
    }

    if (current_traveler == NULL) {
	printf("Traveler not found with name %s.\n", person_name);
	return false;
    }

    // Verify if the updated seat number is already occupied
    TRAVELER *updated_seat = flight_data->travelers_head;
    while (updated_seat != NULL && updated_seat->seat_number != updated_seat_number) {
	new_seat_previous_traveler = updated_seat;
	updated_seat = updated_seat->next;
    }

    if (updated_seat != NULL) {
	printf("The updated seat number %d is already occupied.\n", updated_seat_number);
	return false;
    }

    // Remove the traveler reservation from the list
    if (previous_traveler == NULL) {
	flight_data->travelers_head = current_traveler->next;
    } else {
	previous_traveler->next = current_traveler->next;
    }

    // Modify the seat number for the traveler
    current_traveler->seat_number = updated_seat_number;

    // Reinsert the traveler back into the list with the updated seat number
    if (flight_data->travelers_head == NULL || flight_data->travelers_head->seat_number > updated_seat_number) {
	current_traveler->next = flight_data->travelers_head;
	flight_data->travelers_head = current_traveler;
    } else {
	TRAVELER *following_traveler = new_seat_previous_traveler->next;
	new_seat_previous_traveler->next = current_traveler;
	current_traveler->next = following_traveler;
    }

    return true;
}
HER


void findTravelerInAllFlights(FLIGHT_DATA *head, const char *person_name) {
    FLIGHT_DATA *current_flight_data = head;
    bool traveler_found = false;

    printf("Looking for traveler %s in all flights:\n", person_name);

    while (current_flight_data != NULL) {
	TRAVELER *current_traveler = current_flight_data->travelers_head;

	while (current_traveler != NULL) {
	    if (strcmp(current_traveler->name, person_name) == 0) {
	        // Print the flight details
	        printf("Flight ID: %s\n", current_flight_data->flight_id);
	        printf("Destination: %s\n", current_flight_data->destination);
	        printf("Number of seats: %d\n", current_flight_data->num_seats);
	        printf("Departure time: %d\n", current_flight_data->departure_time);
	        printf("-----\n");
	        traveler_found = true;
	        break;
	    }
	    current_traveler = current_traveler->next;
	}

	current_flight_data = current_flight_data->next;
    }

    if (!traveler_found) {
	printf("No flights found for traveler %s.\n", person_name);
    }
}
