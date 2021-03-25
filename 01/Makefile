CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wno-unused-variable
test: test.o allocator.o
	$(CC) $(FLAGS) -o test test.o allocator.o
	./test
test.o:
	$(CC) $(FLAGS) -c test.cpp -o test.o
allocator.o:
	$(CC) $(FLAGS) -c allocator.cpp -o allocator.o

