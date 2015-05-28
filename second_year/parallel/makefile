first:
	mpicc lab1/first_v1.c -o bin/first_v1
	mpicc lab1/first_v2.c -o bin/first_v2

second:
	gcc -fopenmp lab2/second_v1.cpp -o bin/second_v1
	gcc -fopenmp lab2/second_v2.cpp -o bin/second_v2

third:
	mpicc lab3/third_v1.c -o bin/third_v0

fourth:
	mpicc lab4/fourth.cpp -o bin/fourth_v0

fifth:
	mpicc lab5/fifth_v0.c -o bin/fifth_v0

all:
	first
	second
	third
	fourth
	fifth
