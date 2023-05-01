#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/flight.h"
#include "include/passenger.h"

void display_menu() {
    printf("\nFlight Management System\n");
    printf("1. Add a flight\n");
    printf("2. Add a passenger to a flight\n");
    printf("3. Print a flight\n");
    printf("4. Search for a flight by departure time\n");
    printf("5. Remove a flight\n");
    printf("6. Remove a passenger reservation\n");
    printf("7. Change a passenger's seat\n");
    printf("8. Find a passenger in flights\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    FLIGHT* head = NULL;
    int choice;
    char flight_id[10];
    char destination[50];
    char name[50];
    int num_seats, departure_time, seat_number, age, new_seat_number;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter flight ID: ");
                scanf("%s", flight_id);
                printf("Enter destination: ");
                scanf("%s", destination);
                printf("Enter the number of seats: ");
                scanf("%d", &num_seats);
                printf("Enter departure time: ");
                scanf("%d", &departure_time);
                head = insert_flight(&head, flight_id, destination, num_seats, departure_time);
                break;
            case 2:
                printf("Enter flight ID: ");
                scanf("%s", flight_id);
                FLIGHT* flight = find_flight_by_id(head, flight_id);
                if (flight) {
                    printf("Enter passenger name: ");
                    scanf("%s", name);
                    printf("Enter passenger age: ");
                    scanf("%d", &age);
                    printf("Enter seat number: ");
                    scanf("%d", &seat_number);
                    insert_traveler_to_flight(flight, name, age, seat_number);
                } else {
                    printf("Flight not found.\n");
                }
                break;
            case 3:
                printf("Enter flight ID: ");
                scanf("%s", flight_id);
                flight = find_flight_by_id(head, flight_id);
                if (flight) {
                    print_the_flight(flight);
                } else {
                    printf("Flight not found.\n");
                }
                break;
            case 4:
                printf("Enter departure time: ");
                scanf("%d", &departure_time);
                search_flight_by_takeoff_time(head, departure_time);
                break;
            case 5:
                printf("Enter flight ID: ");
                scanf("%s", flight_id);
                remove_flight(&head, flight_id);
                break;
            case 6:
                printf("Enter flight ID: ");
                scanf("%s", flight_id);
                flight = find_flight_by_id(head, flight_id);
                if (flight) {
                    printf("Enter seat number: ");
                    scanf("%d", &seat_number);
                    remove_traveler_reservation(flight, seat_number);
                } else {
                    printf("Flight not found.\n");
                }
                break;
		            case 7:
                printf("Enter flight ID: ");
                scanf("%s", flight_id);
                flight = find_flight_by_id(head, flight_id);
                if (flight) {
                    printf("Enter passenger name: ");
                    scanf("%s", name);
                    printf("Enter new seat number: ");
                    scanf("%d", &new_seat_number);
                    changeTravelersSeat(flight, name, new_seat_number);
                } else {
                    printf("Flight not found.\n");
                }
                break;
            case 8:
                printf("Enter passenger name: ");
                scanf("%s", name);
                findTravelerInFlights(head, name);
                break;
            case 9:
                printf("Exiting the program...\n");
                freeFlightList(head);
                exit(0);
            default:
        }
    }

    return 0;
}

            
