# Makefile
CC = g++
CFLAGS = -std=c++11 -Wall -pedantic
OBJECTS = main.o targeted_therapy.o ids.o

TargetedTherapy : $(OBJECTS)
	$(CC) $(CFLAGS) -o TargetedTherapy $(OBJECTS)

mian.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

targeted_therapy.o : targeted_therapy.cpp targeted_therapy.h
	$(CC) $(CFLAGS) -c targeted_therapy.cpp

ids.o : ids.cpp targeted_therapy.h
	$(CC) $(CFLAGS) -c ids.cpp

clean :
	rm TargetedTherapy $(OBJECTS)
