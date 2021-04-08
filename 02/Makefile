CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wno-unused-variable
test: test.o parser.o
	$(CC) $(FLAGS) -o test test.o parser.o
	./test
test.o:
	$(CC) $(FLAGS) -c test.cpp -o test.o
parser.o:
	$(CC) $(FLAGS) -c parser.cpp -o parser.o
clean:
	rm -rf *.o

