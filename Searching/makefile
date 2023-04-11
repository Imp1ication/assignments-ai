# Makefile
CC = g++
CFLAGS = -std=c++11 -Wall -pedantic

SRCS = targeted_therapy.cpp IDS.cpp IDASTAR.cpp board_creator.cpp
OBJS = $(SRCS:.cpp=.o)
TARGETS = IDS IDASTAR board_creator

all: $(TARGETS)

IDS: IDS.o targeted_therapy.o
	$(CC) $(CFLAGS) $^ -o $@

IDASTAR: IDASTAR.o targeted_therapy.o 
	$(CC) $(CFLAGS) $^ -o $@

board_creator: board_creator.o 
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
	
