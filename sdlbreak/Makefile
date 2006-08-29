CC = g++
OBJ = main.o cdisplay.o cball.o csurface.o
CFLAGS = -c -Wall `sdl-config --cflags`

main: $(OBJ)
	g++ $(OBJ) SDLMain.o -o main -Wall `sdl-config --libs` 
main.o: main.cpp
	g++ main.cpp $(CFLAGS)
cdisplay.o: cdisplay.cpp
	g++ cdisplay.cpp $(CFLAGS)
cball.o: cball.cpp
	g++ cball.cpp $(CFLAGS)
csurface.o: csurface.cpp
	g++ csurface.cpp $(CFLAGS)
	
