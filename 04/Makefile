CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wno-unused-variable
test: test.o BigInt.o
	$(CC) $(FLAGS) -o test test.o BigInt.o
	./test
test.o:
	$(CC) $(FLAGS) -c test.cpp -o test.o
matrix.o:
	$(CC) $(FLAGS) -c BigInt.cpp -o BigInt.o
clean:
	rm -rf *.o

