CC = g++
OBJ = main.o cdisplay.o
CFLAGS = -c -Wall `sdl-config --cflags`

main: $(OBJ)
	g++ $(OBJ) SDLMain.o -o main -Wall `sdl-config --libs` 
main.o: main.cpp
	g++ main.cpp $(CFLAGS)
cdisplay.o: cdisplay.cpp
	g++ cdisplay.cpp $(CFLAGS)
