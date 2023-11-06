CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11

all: main.cpp
	$(CC) $(CFLAGS) main.cpp instance.cpp tournament.cpp initial_solution.cpp headers.h -o RTTP

clean:
	rm -f RTTP
