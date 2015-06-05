CC          := g++
NAME        := main
FLAGS       := -std=gnu++11
OBJECTS     := mode.cpp game.cpp
MAIN_OBJ    := main.cpp
TEST_OBJ    := unitest.cpp
LIBRARIES   := 


main:
	$(CC) $(FLAGS) -o $(NAME) $(MAIN_OBJ) $(OBJECTS) $(LIBRARIES)

gtest:
	$(CC) $(FLAGS) -o test_$(NAME) $(TEST_OBJ) $(OBJECTS) $(LIBRARIES) -lpthread -lgtest

clean:
	rm $(NAME) test_$(NAME)

all: gtest main

.PHONY: all clean
