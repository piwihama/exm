CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude
TARGET = flight_management
OBJS = main.o flight.o

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c include/flight.h include/passenger.h
	$(CC) $(CFLAGS) -c main.c

flight.o: flight.c include/flight.h include/passenger.h
	$(CC) $(CFLAGS) -c flight.c

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
