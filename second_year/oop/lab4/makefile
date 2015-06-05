CC          := g++
NAME        := main
FLAGS       := -std=gnu++11
OBJECTS     := graph.cpp
MAIN_OBJ    := main.cpp
LIBRARIES   := 


all: clean main

main:
	$(CC) $(FLAGS) -o $(NAME) $(MAIN_OBJ) $(OBJECTS) $(LIBRARIES)

clean:
	rm $(NAME)

.PHONY: all clean