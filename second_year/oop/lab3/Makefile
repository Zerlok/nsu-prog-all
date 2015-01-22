CC          := g++
NAME        := main
FLAGS       := -std=gnu++11
OBJECTS     := extra.cpp mode.cpp game.cpp
MAIN_OBJ    := main.cpp
LIBRARIES   := 


main:
	$(CC) $(FLAGS) -o $(NAME) $(MAIN_OBJ) $(OBJECTS) $(LIBRARIES)

clean:
	rm $(NAME)

all: main

.PHONY: all clean
