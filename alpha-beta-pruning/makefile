# Makefile
CC = g++
CFLAGS = -std=c++11 -Wall -pedantic

SRCS = main.cpp rc_game.cpp rc_manager.cpp
OBJS = $(SRCS:.cpp=.o)
TARGETS = main

all: $(TARGETS)

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses

clean:
	rm -f $(OBJS) $(TARGETS)
	

