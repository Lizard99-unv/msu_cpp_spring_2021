CFLAGS = -c -Wall -Werror -std=c++1z

all: my_prog

my_prog: test.o
	g++ -o tests test.o -lpthread
	./tests

test.o: test.cpp pool.hpp
	g++ $(CFLAGS) test.cpp

clean:
	rm -rf *.o my_prog
	rm -rf *.stackdump my_prog
	rm -rf *.exe my_prog
