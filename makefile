CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11

all: main.cpp instances.cpp greedy.cpp
	$(CC) $(CFLAGS) main.cpp instances.cpp tournament.cpp -o RTTP

clean:
	rm -f RTTP
