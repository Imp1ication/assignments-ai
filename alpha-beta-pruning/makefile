# Makefile
CC = g++
CFLAGS = -std=c++11 -Wall -pedantic

SRCS = main.cpp rc_game.cpp
OBJS = $(SRCS:.cpp=.o)
TARGETS = main

all: $(TARGETS)

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
	

