CC = g++
OBJ = main.o
CFLAGS = -c -Wall `sdl-config --cflags`

main: $(OBJ)
	g++ $(OBJ) -o main -Wall `sdl-config --libs` 
main.o: main.cpp
	g++ main.cpp $(CFLAGS)
