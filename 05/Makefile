CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wno-unused-variable
test: test.o serializer.o
	$(CC) $(FLAGS) -o test test.o serializer.o
	./test
test.o:
	$(CC) $(FLAGS) -c test.cpp -o test.o
serializer.o:
	$(CC) $(FLAGS) -c serializer.cpp -o serializer.o
clean:
	rm -rf *.o

