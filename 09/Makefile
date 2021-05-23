CC=g++
FLAGS=-std=c++17 -pthread -Wall -pedantic -Wextra -Wno-unused-variable

main: test.o sort.o
	$(CC) test.o sort.o $(FLAGS) -o test
	./test

main.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

sort.o: sort.cpp sort.hpp
	$(CC) $(FLAGS) -c sort.cpp


clean:
	rm -rf *.o
