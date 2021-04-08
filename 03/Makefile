CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wno-unused-variable
test: test.o matrix.o
	$(CC) $(FLAGS) -o test test.o matrix.o
	./test
test.o:
	$(CC) $(FLAGS) -c test.cpp -o test.o
matrix.o:
	$(CC) $(FLAGS) -c matrix.cpp -o matrix.o
clean:
	rm -rf *.o

