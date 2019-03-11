CFLAGS = -O -Wall -pedantic -std=c++17
CC = g++
SRC = logbuilder.cpp algorithm.cpp dijkstra.cpp
OBJ = $(SRC:.cpp = .o)
dijkstra: $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o dijkstra
clean:
	rm -f dijkstra *.o 
