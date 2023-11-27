CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11

all: main.cpp
	$(CC) $(CFLAGS) main.cpp instance.cpp tournament.cpp initial_solution.cpp headers.h moves.cpp hc.cpp -o RTTP

clean:
	rm -f RTTP
