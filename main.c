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
	int n;
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
                    insertTravelerToFlight(flight, name, age, seat_number);
                } else {
                    printf("Flight not found.\n");
                }
                break;
            case 3:


                printf("Enter the position of the flight: ");
                scanf("%d", &n);

                printTheFlight(head, n);
                break;
            
            case 4:
                printf("Enter departure time: ");
                scanf("%d", &departure_time);
                searchFlightByTakeoffTime(head, departure_time);
                break;
            case 5:
                printf("Enter flight ID: ");
                scanf("%s", flight_id);
                removeFlight(&head, flight_id);
                break;
            case 6:
				printf("Enter the takeoff time to search for a flight (HH:MM): ");
				fgets(buffer, BUFFER_SIZE, stdin);
				sscanf(buffer, "%2d:%2d", &search_time.tm_hour, &search_time.tm_min);

				flight = searchFlightByTakeoffTime(head, search_time);
				if (flight == NULL) {
					printf("No flight found with the specified takeoff time.\n");
				} else {
					printf("Flight found:\n");
					printf("ID: %d\n", flight->id);
					printf("Destination: %s\n", flight->destination);
					printf("Number of seats: %d\n", flight->num_seats);
					printf("Departure time: %02d:%02d\n", flight->departure_time.tm_hour, flight->departure_time.tm_min);
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
				break;
        }
    }

    return 0;
}

            
